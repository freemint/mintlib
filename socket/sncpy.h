/*  sncpy.h -- MiNTLib.
    Copyright (C) 2000 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _SNCPY_H
#define _SNCPY_H	1

#include <stdio.h>	/* for size_t */


int _sncpy (char *dst, const char *src, size_t len);


#endif /* _SNCPY_H */
