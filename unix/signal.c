/* signal() for MiNT; written by ERS, placed in the public domain */

#include <compiler.h>
#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include <signal.h>

#include "lib.h"

/* vector of signal handlers (for TOS, or for MiNT with -mshort) */
extern __sighandler_t _sig_handler[NSIG];

/* vector giving which signals are currently blocked from delivery (for TOS) */
extern long _sigmask;

/* vector giving an indication of which signals are currently pending (for TOS) */
extern long _sigpending;

#ifdef __MSHORT__
/* trampoline code: for any caught signal, converts the 32 bit signal
 * number MiNT passed us into a 16 bit one, and jumps to the handler
 * we previously established
 */

void __CDECL _trampoline __PROTO((long, long));

/* the argument is on the stack */
void __CDECL _trampoline(sig, code)
	long sig, code;
{
	void (*func) __PROTO ((int, int));

	func = (void (*) __PROTO ((int, int))) _sig_handler[sig];

/* note: func should never be SIG_IGN or SIG_DFL; if it is, something
 * really bad happened and we want to crash anyway!
 */
	(*func)((int)sig, (int) code);
}
#endif

__sighandler_t
__bsd_signal(sig, func)
	int sig;
	__sighandler_t func;
{
	long old;
	__sighandler_t oldfunc;
	static short have_psignal = 1;
	
#ifdef __MSHORT__
/* NOTE: MiNT passes 32 bit numbers for signals, so we want our
 * own signal dispatcher to switch these to 16 bit ints
 */
	if (sig < 0 || sig >= NSIG) {
		errno = EINVAL;
		return SIG_ERR;
	}
	oldfunc = _sig_handler[sig];
	_sig_handler[sig] = func;
	if (func != SIG_DFL && func != SIG_IGN)
		func = (__sighandler_t) _trampoline;
#endif
	if (have_psignal) {
		old = Psignal((short)sig, (long)func);
		if (old == -ENOSYS)
			have_psignal = 0;
		else if (old < 0) {
			errno = (int) -old;
			return SIG_ERR;
		}
		else {
			func = (__sighandler_t) old;
#ifdef __MSHORT__
			if (func == (__sighandler_t) _trampoline) func = oldfunc;
#endif
			return func;
		}
	}
	
#ifndef __MSHORT__ 
	if (sig < 0 || sig >= NSIG) {
		errno = ERANGE;
		return SIG_ERR;
	}
	oldfunc = _sig_handler[sig];
	_sig_handler[sig] = func;
#endif
	return oldfunc;
}
weak_alias (__bsd_signal, bsd_signal)
weak_alias (__bsd_signal, signal)
weak_alias (__bsd_signal, ssignal)
weak_alias (__bsd_signal, __signal)
