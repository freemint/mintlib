/*  syscall.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdarg.h>
#include <syscall.h>
#include <errno.h>

struct _dispatch
{
  void* call;
  long (*wrap) (int opcode, va_list args);
};

#pragma GCC diagnostic ignored "-Wstrict-prototypes"

#if __GNUC_PREREQ(13, 0)
typedef long (*func) (...);
#else
typedef long (*func) ();
#endif

/* Grab the array.  */
#include "syscalls.h"

#ifdef __MSHORT__
long syscall (int opcode, ...);
long syscall (int opcode, ...)
#else
int syscall (int opcode, ...);
int syscall (int opcode, ...)
#endif
{
  va_list args;
  long retval;
  
  if (opcode < 0 || opcode > MAX_SYS_OPCODE)
    {
      __set_errno (EINVAL);
      return -1;
    }

  va_start (args, opcode);
  retval = (long) funcs[opcode].wrap (opcode, args);
  va_end (args);
  return retval;
}

