/*  src/umask.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* umask -- change default file creation mask.  */

#include <errno.h>
#include <mint/mintbind.h>
#include "lib.h"

/*
 * This function never fails
 */

mode_t
__umask (mode_t complmode)
{
	if (__current_umask == -1) {
		__current_umask = Pumask (0);

		if (__current_umask < 0)
			 __current_umask = 0;

		/* put back the old umask */
		Pumask(__current_umask);
	}

	if (complmode == (mode_t) __current_umask)
		return __current_umask;

	__current_umask = Pumask (complmode);

	return __current_umask;
}
weak_alias (__umask, umask)
