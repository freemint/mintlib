/*  src/setpgrp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mint/mintbind.h>
#include "lib.h"

int
__setpgrp (void)
{
	static short have_pgrp = 1;

	if (have_pgrp) {
		int r = 0;

		r = Psetpgrp (0, 0);
		if (r == -ENOSYS) {
			have_pgrp = 0;
		}
		else if (r < 0) {
			if (r == -ENOENT)
				r = -ESRCH;
			else if (r == -EACCES)
				r = -EPERM;
			__set_errno (-r);
			return -1;
		}
	}

	return 0;
}
weak_alias (__setpgrp, setpgrp)
