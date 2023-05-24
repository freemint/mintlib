#include <stdlib.h>
#include <mint/mintbind.h>
#include <errno.h>
#include <time.h>
#include "semaphoreP.h"

/*
 *   M.Medour 2023/05/24
 *   rev.1 
 *   semaphore.h for freemint
 */

int sem_wait(sem_t *sem)
{
	long ret;

	/* We need to check whether we need to act upon a cancellation request here
	   because POSIX specifies that cancellation points "shall occur" in
	   sem_wait and sem_timedwait, which also means that they need to check
	   this regardless whether they block or not (unlike "may occur"
	   functions).  See the POSIX Rationale for this requirement: Section
	   "Thread Cancellation Overview" [1] and austin group issue #1076 [2]
	   for thoughs on why this may be a suboptimal design.

	   [1] http://pubs.opengroup.org/onlinepubs/9699919799/xrat/V4_xsh_chap02.html
	   [2] http://austingroupbugs.net/view.php?id=1076 for thoughts on why this
	 */
#ifdef HAVE_PTHREAD_H
	__pthread_testcancel();
#endif

	if (__sem_wait_fast(sem, 0) == 0)
	{
		ret = Psemaphore(2, sem->sem_id, -1);
		if (ret != 0)
		{
			/* no attempt to emulate this on Single-TOS */
			__set_errno(-(int)ret);
			return -1;
		}
		return 0;
	}
	return __sem_wait_slow(sem, CLOCK_REALTIME, NULL);
}

