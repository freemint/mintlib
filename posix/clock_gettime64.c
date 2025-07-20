#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include "lib.h"

static inline int realtime_gettime(struct timespec64 *tp)
{
	struct timeval64 tv;
	int retval = __gettimeofday64(&tv, NULL);
	if (retval == 0)
    /* Convert into `timespec'.  */
		TIMEVAL_TO_TIMESPEC(&tv, tp);
	return retval;
}

/* Get current value of CLOCK and store it in TP.  */

int __clock_gettime64(clockid_t clock_id, struct timespec64 *tp)
{
	int retval = -1;

	switch (clock_id)
	{
	case CLOCK_MONOTONIC:
	case CLOCK_REALTIME:
		retval = realtime_gettime(tp);
		break;
	default:
		__set_errno(EINVAL);
		break;
    }
	return retval;
}
