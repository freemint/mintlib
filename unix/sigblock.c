/* signal blocking stuff for MiNT */

#include <errno.h>
#include <mint/mintbind.h>
#include "lib.h"


int
__sigblock(long mask)
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
