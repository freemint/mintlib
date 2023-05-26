/*
 *   M.Medour 2023/05/24
 *   rev.1 
 *   semaphore.h for freemint
 */

/* Adapted to MiNTLib by Thorsten Otto */

#include <stdlib.h>
#include <mint/mintbind.h>
#include <errno.h>
#include "semaphoreP.h"

/* We're done with the semaphore, destroy it. */
int sem_destroy(sem_t *sem)
{
	/* XXX Check for valid parameter.  */
	long ret;

	ret = Psemaphore(1, sem->sem_id, 0);
	if (ret < 0)
	{
		__set_errno(-(int)ret);
		return -1;
	}
	return 0;
}
