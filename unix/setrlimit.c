/* set resource limits */
/* written by Eric R. Smith and placed in the public domain */

#include <errno.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <mint/mintbind.h>

int
__setrlimit (enum __rlimit_resource kind, struct rlimit *rl)
{
	unsigned long limit;
	int mode;
	long r;

	limit = rl->rlim_cur;

	if (limit >= RLIM_INFINITY)
		limit = 0;
	else if (limit == 0)
		limit = 1;

	switch (kind) {
		case RLIMIT_CPU:
			mode = 1; break;
		case RLIMIT_RSS:
			mode = 2; break;
		case RLIMIT_DATA:
			mode = 3; break;
		default:
			__set_errno (EINVAL);
			return -1;
	}

	r = Psetlimit (mode, limit);

	if (r < 0) {
		if (r == -EACCES)
			r = -EPERM;
		__set_errno (-r);
		return -1;
	}

	return 0;
}
weak_alias (__setrlimit, setrlimit)
