/* killpg() for MiNT */

#include <stdlib.h>
#include <errno.h>
#include <osbind.h>
#include <signal.h>
#include <unistd.h>
#include <mintbind.h>

#include "lib.h"

int
__killpg(pgrp, sig)
	int pgrp, sig;
{
	if (pgrp < 0) {
		__set_errno (ESRCH);
		return -1;
	}
	return kill (-pgrp, sig);
}

weak_alias (__killpg, killpg)
