/* get resource limits */
/* written by Eric R. Smith and placed in the public domain */

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <mint/mintbind.h>

long __sysconf (int var);

int
__getrlimit (enum __rlimit_resource kind, struct rlimit *rl)
{
	long limit;
	int mode;

	switch(kind) {
		case RLIMIT_CPU:
			mode = 1;
			break;
		case RLIMIT_RSS:
			mode = 2;
			break;
		case RLIMIT_DATA:
			mode = 3;
			break;
		case RLIMIT_STACK:
		case RLIMIT_FSIZE:
		case RLIMIT_CORE:
			__set_errno (EINVAL);
			return -1;
		/* fake it until the kernel catch up */
		case RLIMIT_OPEN_FILES:
			rl->rlim_cur = 
			rl->rlim_max = __sysconf (_SC_OPEN_MAX);
			return 0;
		default:
			__set_errno (EINVAL);
			return -1;
	}

	limit = Psetlimit(mode, -1L);
	if (limit < 0) {
		__set_errno (-limit);
		return -1;
	}

	if (limit == 0)
		limit = RLIM_INFINITY;

	rl->rlim_cur = limit;
	rl->rlim_max = RLIM_INFINITY;
	return 0;
}
weak_alias (__getrlimit, getrlimit)
