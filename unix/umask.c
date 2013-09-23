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
	mode_t r = __current_umask;
	complmode &= (~S_IFMT);
	if( r != complmode )
	{
		r = Pumask(complmode);
		__current_umask = complmode;
	}
	return r;
}
weak_alias (__umask, umask)
