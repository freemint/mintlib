/* signal blocking stuff for MiNT */

#include <errno.h>
#include <mint/mintbind.h>

#include "lib.h"


__typeof__(sigsetmask) __sigsetmask;


/* checksigs: for TOS: this checks to see if we just unmasked any
 * pending signals
 */

static void
checksigs(void)
{
	register int sig;
	register long send;

	if ((send = (_sigpending & ~_sigmask)) != 0) {
		for (sig = 0; sig < NSIG; sig++) {
			if (send & (1L << sig))
				kill(0, sig);
		}
	}
}

int
__sigsetmask(long mask)
{
	register long omask;
	long r;

	if ((r = Psigsetmask(mask)) != -ENOSYS)
		return r;

	omask = _sigmask;
	_sigmask = mask;
	checksigs();
	return omask;
}

weak_alias (__sigsetmask, sigsetmask)
