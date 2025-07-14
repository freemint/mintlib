/*  wait3.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>

__typeof__(wait3) __wait3;

pid_t
__wait3 (__WP stat_loc, int options, struct rusage *usage)
{
	return wait4 (-1, stat_loc, options, usage);
}
weak_alias (__wait3, wait3)
