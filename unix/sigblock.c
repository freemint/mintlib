/* signal blocking stuff for MiNT */

#include <signal.h>
#include <errno.h>
#include <mintbind.h>

extern long _sigmask;

#ifdef __MSHORT__
long
#else
int
#endif
__sigblock(mask)
	long mask;
{
	register long omask;
	long r;

	if ((r = Psigblock(mask)) != -ENOSYS)
		return r;

	omask = _sigmask;
	_sigmask |= mask;
	return omask;
}

weak_alias (__sigblock, sigblock)
