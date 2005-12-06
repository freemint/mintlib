/* sigaction() and sigset functions for MiNT; placed in the public domain */

#include <errno.h>
#include <mintbind.h>
#include <signal.h>
#include <stddef.h>

#include "lib.h"


#ifdef __MSHORT__
typedef void __CDECL (*__KerSigfunc) (long, long);
extern void __CDECL _trampoline (long sig, long code);
#else
typedef void __CDECL (*__KerSigfunc) (int);
#endif

int
__sigaction(sig, act, oact)
	int sig;
	const struct sigaction *act;
	struct sigaction *oact;
{
	long r;
	sighandler_t oldfunc;
	static short have_psigaction = 1;

	if (have_psigaction) {
		struct ksigact {
			__KerSigfunc	sa_handler;	/* pointer to signal handler */
			long		sa_mask;	/* additional signals masked during delivery */
			short		sa_flags;	/* signal specific flags, kernel */
		} kact, koact;

		if (sig < 0 || sig >= __NSIG) {
			__set_errno (ERANGE);
			return -1;
		}

#ifdef __MSHORT__
/* NOTE: MiNT passes 32 bit numbers for signals, so we want our
 * own signal dispatcher to switch these to 16 bit ints
 */
		oldfunc = _sig_handler[sig];
#endif
		if (act) {
			kact.sa_handler = (__KerSigfunc) act->sa_handler;
			kact.sa_mask = act->sa_mask;
			kact.sa_flags = (short) act->sa_flags;
#ifdef __MSHORT__
			_sig_handler[sig] = (sighandler_t)kact.sa_handler;
			if (_sig_handler[sig] != SIG_DFL && _sig_handler[sig] != SIG_IGN) {
				kact.sa_handler = _trampoline;
			}
#endif
		}
		r = Psigaction(sig, (act ? &kact : 0L), (oact ? &koact : 0L));
		if (r < 0) {
			if (r == -ENOSYS) {
				have_psigaction = 0; /* don't try again */
				goto no_psigaction;
			}
			__set_errno (-r);
			return -1;
		}
		if (oact) {
			oact->sa_mask = koact.sa_mask;
			oact->sa_flags = (int) koact.sa_flags;
#ifdef __MSHORT__
			oact->sa_handler =
			  ((koact.sa_handler == (__KerSigfunc) _trampoline)
			   ? oldfunc
			   : (sighandler_t) koact.sa_handler);
#else
			oact->sa_handler = (sighandler_t) koact.sa_handler;
#endif
		}
	}
	else {
no_psigaction:
		if (act)
			oldfunc = signal(sig, act->sa_handler);
		else {
			long omask;

			omask = sigblock(sig);
			oldfunc = signal(sig, SIG_DFL);
			signal(sig, oldfunc);	/* need to put it back */
			sigsetmask(omask);	/* may remask sig (this is what we want) */
		}
		if (oldfunc == SIG_ERR)
			return -1;
		if (oact) {
			oact->sa_handler = oldfunc;
			/* we could do something useful with sa_mask when __mint */
			oact->sa_flags = 0;
			oact->sa_mask = 0;
		}
	}
	return 0;
}

weak_alias (__sigaction, sigaction)
