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

static long gen_sem_id(void)
{
	int n;
	static char const charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	long sem_id = 0;

	for (n = 0; n < 4; n++)
	{
		int key = (short)rand() % (short) (sizeof(charset) - 1);

		sem_id <<= 8;
		sem_id |= charset[key];
	}
	return sem_id;
}

int sem_init(sem_t *sem, int pshared, unsigned int value)
{
	long ret;

	if (value > SEM_VALUE_MAX)
	{
		__set_errno(EINVAL);
		return -1;
	}
	/* pshared is currently unused */
	sem->__private = pshared ? 1 : 0;
	/* Use the values the caller provided.  */
	sem->value = value << SEM_VALUE_SHIFT;
	sem->nwaiters = 0;

	do
	{
		sem->sem_id = gen_sem_id();
		ret = Psemaphore(0, sem->sem_id, 0);
	} while (ret == -EACCES);
	if (ret != 0)
	{
		/* no attempt to emulate this on Single-TOS */
		__set_errno(-(int)ret);
		return -1;
	}

	return 0;
}
