/*
 * BSD signal handleing emulation.
 *
 * (w) 1994, Kay Roemer.
 */

#include <signal.h>
#include <errno.h>

extern int errno;

int
sigvec (sig, sv, osv)
	int sig;
	struct sigvec *sv, *osv;
{
	struct sigaction sa, osa;
	int i, r;
	
	if (sv) {
		if (sv->sv_flags & (SV_ONSTACK|SV_INTERRUPT|SV_RESETHAND)) {
			errno = EINVAL;
			return -1;
		}
		sa.sa_handler = sv->sv_handler;
		sa.sa_flags = sv->sv_flags;
		sigemptyset (&sa.sa_mask);
		for (i = 0; i < __NSIG; ++i) {
			if (sv->sv_mask & (1L << i)) {
				sigaddset (&sa.sa_mask, i);
			}
		}
	}
	r = sigaction (sig, sv ? &sa : 0, osv ? &osa : 0);
	if (r < 0) return r;

	if (osv) {
		osv->sv_handler = osa.sa_handler;
		osv->sv_flags = osa.sa_flags;
		osv->sv_mask = 0;
		for (i = 0; i < __NSIG; ++i) {
			if (sigismember (&osa.sa_mask, i)) {
				osv->sv_mask |= (1L << i);
			}
		}
	}
	return r;
}

int
siginterrupt (sig, fail)
	int sig, fail;
{
	if (fail)
	  {
 	    errno = EINVAL;
	    return -1;
	  }
	return 0;
}
