/* public domain fork() for MiNT */

#include <unistd.h>
#include <errno.h>
#include <mintbind.h>

#include "lib.h"

int
__fork()
{
	int r;

	r = (int)Pfork();
	if (r < 0) {
		errno = -r;
		return -1;
	}
	return r;
}

weak_alias (__fork, fork)

