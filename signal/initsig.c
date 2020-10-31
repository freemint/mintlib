/* signal() for MiNT; written by ERS, placed in the public domain */

#include <errno.h>
#include <signal.h>
#include "lib.h"

/* vector of signal handlers (for TOS, or for MiNT with -mshort) */
sighandler_t _sig_handler[NSIG];

/*
 * static check that ensures that SIG_DFL is really 0, and gives compile error otherwise
 */
static __inline__ void sig_dfl_check(void)
{
	typedef char verify_sig_dfl_0[(SIG_DFL == 0) ? NSIG : -1];
}

/* vector giving which signals are currently blocked from delivery (for TOS) */
long _sigmask;

/* vector giving an indication of which signals are currently pending (for TOS) */
long _sigpending;
