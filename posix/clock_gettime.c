#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <mint/sysctl.h>
#include <mint/mintbind.h>

static inline int
realtime_gettime(struct timespec *tp)
{
	struct timeval tv;
	int retval = gettimeofday(&tv, NULL);
	if (retval == 0)
    /* Convert into `timespec'.  */
		TIMEVAL_TO_TIMESPEC(&tv, tp);
	return retval;
}

/* Get current value of CLOCK and store it in TP.  */

__typeof__(clock_gettime) __clock_gettime;

int
__clock_gettime(clockid_t clock_id, struct timespec *tp)
{
	int retval = -1;

	switch (clock_id)
	{
	case CLOCK_MONOTONIC:
	case CLOCK_REALTIME:
		retval = realtime_gettime(tp);
		break;
	case CLOCK_BOOTTIME:
		{
			long name[2];
			unsigned long len;
			long r;
			struct timeval tv;

			name[0] = CTL_KERN;
			name[1] = KERN_BOOTTIME;
			len = sizeof(tv);
			r = Psysctl(name, 2, &tv, &len, NULL, 0);
			if (r == 0)
			{
				TIMEVAL_TO_TIMESPEC(&tv, tp);
				retval = 0;
			} else
			{
				__set_errno(-(int)r);
			}
		}
		break;
	default:
		__set_errno(EINVAL);
		break;
    }
	return retval;
}

weak_alias (__clock_gettime, clock_gettime)
