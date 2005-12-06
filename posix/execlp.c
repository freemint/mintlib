/*  src/execlp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <unistd.h>

/* execlp: Try to execute a program on the default system
   execution path. WARNING: the current directory is always searched
   first.
*/

int
execlp (const char *file, const char *arg, ...)
{
	return execvp(file, (char **) &arg);
}
