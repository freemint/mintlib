/* signal() for MiNT; written by ERS, placed in the public domain */

#include <errno.h>
#include <signal.h>
#include "lib.h"

/* vector of signal handlers (for TOS, or for MiNT with -mshort) */
sighandler_t _sig_handler[NSIG];

/* vector giving which signals are currently blocked from delivery (for TOS) */
long _sigmask;

/* vector giving an indication of which signals are currently pending (for TOS) */
long _sigpending;

void
_init_signal (void)
{
	int i;

	for (i = 0; i < __NSIG; i++)
		_sig_handler[i] = SIG_DFL;

	_sigpending = _sigmask = 0;
}
