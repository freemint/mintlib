/* get resource limits */
/* written by Eric R. Smith and placed in the public domain */

#ifdef __TURBOC__
# include <sys\types.h>
# include <sys\resource.h>
# include <sys\time.h>
#else
# include <sys/types.h>
# include <sys/resource.h>
# include <sys/time.h>
#endif

#include <mintbind.h>
#include <errno.h>

int
__getrlimit(kind, rl)
	enum __rlimit_resource kind;
	struct rlimit *rl;
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
	default:
		errno = EINVAL;
		return -1;
	}
	limit = Psetlimit(mode, -1L);
		
	if (limit < 0) {
		errno = (int ) -limit;
		return -1;
	}

	if (limit == 0)
		limit = RLIM_INFINITY;

	rl->rlim_cur = limit;
	rl->rlim_max = RLIM_INFINITY;
	return 0;
}

weak_alias (__getrlimit, getrlimit)
