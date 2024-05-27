/* signal() for MiNT; written by ERS, placed in the public domain */

#include <compiler.h>
#include <errno.h>
#include <osbind.h>
#include <mintbind.h>
#include <signal.h>

#include "lib.h"

__sighandler_t __bsd_signal(int sig, __sighandler_t func);


#if NEED_SIGNAL_TRAMPOLINE
/* trampoline code: for any caught signal, converts the 32 bit signal
 * number MiNT passed us into a 16 bit one, and jumps to the handler
 * we previously established
 */
/* the argument is on the stack */
void __CDECL __signal_trampoline(long sig, long code)
{
	/* FIXME: should be typeof(sa_sigaction) */
	void (*func) (int, int);

	func = (void (*) (int, int)) _sig_handler[sig];

/* note: func should never be SIG_IGN or SIG_DFL; if it is, something
 * really bad happened and we want to crash anyway!
 */
	(*func)((int)sig, (int) code);
}
#endif

__sighandler_t
__bsd_signal(int sig, __sighandler_t func)
{
	long old;
	__sighandler_t oldfunc;
	static short have_psignal = 1;
	
#if NEED_SIGNAL_TRAMPOLINE
/* NOTE: MiNT passes 32 bit numbers for signals, so we want our
 * own signal dispatcher to switch these to 16 bit ints
 */
	if (sig < 0 || sig >= NSIG) {
		__set_errno (EINVAL);
		return SIG_ERR;
	}
	oldfunc = _sig_handler[sig];
	_sig_handler[sig] = func;
	if (func != SIG_DFL && func != SIG_IGN)
		func = (__sighandler_t) __signal_trampoline;
#endif
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
#if NEED_SIGNAL_TRAMPOLINE
			if (func == (__sighandler_t) __signal_trampoline) func = oldfunc;
#endif
			return func;
		}
	}

	/* plain TOS emulation */
#if !NEED_SIGNAL_TRAMPOLINE
	if (sig < 0 || sig >= NSIG) {
		__set_errno (ERANGE);
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
