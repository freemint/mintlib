/*  src/execlp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdarg.h>
#include <unistd.h>

/* execlp: Try to execute a program on the default system
   execution path. WARNING: the current directory is always searched
   first.
*/

int
execlp (const char *name, ...)
{
	va_list args;
	int r;

	va_start (args, name);
	r = __execve (name, (char **) args, NULL);
	va_end (args);

	return r;
}
