#include <stdlib.h>
#include <mint/mintbind.h>
#include <errno.h>
#include <time.h>
#include "semaphoreP.h"

/* Adapted to MiNTLib by Thorsten Otto */

int sem_clockwait(sem_t *sem, clockid_t clockid, const struct timespec *abstime)
{
	long ret;

	/* Check that supplied clockid is one we support, even if we don't end up
	   waiting.  */
	if (clockid != CLOCK_REALTIME)
	{
		__set_errno(EINVAL);
		return -1;
	}

	if (!valid_nanoseconds(abstime->tv_nsec))
	{
		__set_errno(EINVAL);
		return -1;
	}

	if (__sem_wait_fast(sem, 0) == 0)
	{
		ret = Psemaphore(2, sem->sem_id, 0);
		if (ret != 0)
		{
			if (ret == -EACCES)
				ret = -ETIMEDOUT;
			/* no attempt to emulate this on Single-TOS */
			__set_errno(-(int)ret);
			return -1;
		}
		return 0;
	}

	return __sem_wait_slow(sem, clockid, abstime);
}


