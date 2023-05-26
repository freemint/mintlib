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

/* Try a wait for semaphore (non-blocking). */
int sem_trywait(sem_t *sem)
{
	long ret;

	/* We must not fail spuriously, so require a definitive result even if this
	   may lead to a long execution time.  */
	if (__sem_wait_fast(sem, 1) == 0)
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
	__set_errno(EAGAIN);
	return -1;
}
