/* signal blocking stuff for MiNT */

#include <errno.h>
#include <mint/mintbind.h>
#include "lib.h"


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
