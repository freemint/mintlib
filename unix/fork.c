/* public domain fork() for MiNT */

#include <errno.h>
#include <unistd.h>
#include <mint/mintbind.h>

#include "lib.h"

int
__fork (void)
{
	long r;

	r = Pfork ();
	if (r < 0) {
		__set_errno (-r);
		return -1;
	}
	return r;
}
weak_alias (__fork, fork)
