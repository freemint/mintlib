/*  src/creat.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <fcntl.h>
#include "lib.h"

int
__creat (const char *file, mode_t mode)
{
	return open (file, O_WRONLY|O_CREAT|O_TRUNC, mode);
}
weak_alias (__creat, creat)
