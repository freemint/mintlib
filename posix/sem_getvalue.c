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

/* Get the semaphore value. */
int sem_getvalue(sem_t *sem, int *sval)
{
	/* XXX Check for valid SEM parameter.  */
	/* FIXME This uses relaxed MO, even though POSIX specifies that this function
	   should be linearizable.  However, its debatable whether linearizability
	   is the right requirement.  We need to follow up with POSIX and, if
	   necessary, use a stronger MO here and elsewhere (e.g., potentially
	   release MO in all places where we consume a token).  */

	*sval = atomic_load_relaxed(&sem->value) >> SEM_VALUE_SHIFT;

	return 0;
}
