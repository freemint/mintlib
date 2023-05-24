#include <stdlib.h>
#include <mint/mintbind.h>
#include <errno.h>
#include "semaphoreP.h"

/*
 *   M.Medour 2023/05/24
 *   rev.1 
 *   semaphore.h for freemint
 */

/* See sem_wait for an explanation of the algorithm.  */
int sem_post(sem_t *sem)
{
	long ret;
	/* Add a token to the semaphore */
	unsigned long v = atomic_load_relaxed(&sem->value);

	do
	{
		if ((v >> SEM_VALUE_SHIFT) == SEM_VALUE_MAX)
		{
			__set_errno(EOVERFLOW);
			return -1;
		}
	} while (!atomic_compare_exchange_weak_release(&sem->value, &v, v + (1 << SEM_VALUE_SHIFT)));

	/* If there is any potentially blocked waiter, wake one of them.  */
#if 0
	if ((v & SEM_NWAITERS_MASK) != 0)
		futex_wake(&sem->value, 1, sem->__private);
#endif
	ret = Psemaphore(3, sem->sem_id, 0);
	if (ret < 0)
	{
		__set_errno(-(int)ret);
		return -1;
	}

	return 0;
}
