/* by ERS, modified by entropy */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <mintbind.h>
#include <errno.h>
#include "lib.h"

#ifndef SIGABRT
#define SIGABRT SIGIOT
#endif

__EXITING
abort()
{
#ifdef __MINT__
	if (Pkill(Pgetpid(), SIGABRT) != -ENOSYS) {
		/* process still alive, maybe SIGABRT was blocked */
		(void) Psigsetmask(Psigblock(0) & ~(sigmask(SIGABRT)));
		/* process still alive, maybe SIGABRT was ignored */
		/* is this correct if user SIGABRT handler returns? */
		(void) Psignal(SIGABRT, (long) SIG_DFL);
		(void) Pkill(Pgetpid(), SIGABRT);
        }
	else
		raise(SIGABRT);
	_fclose_all_files();
	_exit(127);
#else
	raise(SIGABRT);
	exit(127);
#endif
}
