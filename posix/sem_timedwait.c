/*
 *   M.Medour 2023/05/24
 *   rev.1 
 *   semaphore.h for freemint
 */

/* Adapted to MiNTLib by Thorsten Otto */

#include <stdlib.h>
#include <mint/mintbind.h>
#include <errno.h>
#include <time.h>
#include "semaphoreP.h"

/* This is in a separate file because because sem_timedwait is only provided
   if __USE_XOPEN2K is defined.  */
int sem_timedwait(sem_t *sem, const struct timespec *abstime)
{
	long ret;

	if (!valid_nanoseconds(abstime->tv_nsec))
	{
		__set_errno(EINVAL);
		return -1;
	}

#ifdef HAVE_PTHREAD_H
	/* Check sem_wait.c for a more detailed explanation why it is required.  */
	__pthread_testcancel();
#endif

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

	return __sem_wait_slow(sem, CLOCK_REALTIME, abstime);
}
