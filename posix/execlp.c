/*  src/execlp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

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

#ifdef __STDC__
int execlp (const char *name, ...)
#else
int execlp (name)
     char* name;
#endif
{
  va_list args;

  va_start (args, name);
  return execvp (name, (char **)args);
}
