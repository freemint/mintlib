/* signal() for MiNT; written by ERS, placed in the public domain */

#include <compiler.h>
#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include <signal.h>

#include "lib.h"

__sighandler_t __bsd_signal(int sig, __sighandler_t func);



__sighandler_t
__bsd_signal(int sig, __sighandler_t func)
{
	long old;
	__sighandler_t oldfunc;
	static short have_psignal = 1;
	
	if (have_psignal) {
		old = Psignal((short)sig, (long)func);
		if (old == -ENOSYS)
			have_psignal = 0;
		else if (old < 0) {
			__set_errno (-old);
			return SIG_ERR;
		}
		else {
			func = (__sighandler_t) old;
			return func;
		}
	}
	
	if (sig < 0 || sig >= NSIG) {
		__set_errno (ERANGE);
		return SIG_ERR;
	}
	oldfunc = _sig_handler[sig];
	_sig_handler[sig] = func;
	return oldfunc;
}
weak_alias (__bsd_signal, bsd_signal)
weak_alias (__bsd_signal, signal)
weak_alias (__bsd_signal, ssignal)
weak_alias (__bsd_signal, __signal)
