/* killpg() for MiNT */

#include <errno.h>
#include <signal.h>

#include "lib.h"

__typeof__(killpg) __killpg;

int
__killpg (int pgrp, int sig)
{
	if (pgrp < 0) {
		__set_errno (ESRCH);
		return -1;
	}
	return kill (-pgrp, sig);
}
weak_alias (__killpg, killpg)
