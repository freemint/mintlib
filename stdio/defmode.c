/*  defmode.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* 
 * If you put your own global definition of __default_mode__ into your
 * sources, this definition will be used.
 */
#include <stdio.h>

__io_mode __default_mode__ = { 0, 0, 0, 0, 0, 0, 0 };
