/*  waitpid.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdlib.h>
#include <sys/wait.h>


pid_t
__waitpid (pid_t pid, int *stat_loc, int options)
{
	return wait4 (pid, (__WP) stat_loc, options, NULL);
}
weak_alias (__waitpid, waitpid)
