/*  fchown.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <stddef.h>
#include <unistd.h>

#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <limits.h>
#include <mintbind.h>

int __fchown (int fd, uid_t owner, gid_t group)
{
  int retval;
  
#ifndef __MSHORT__
  if (fd > SHRT_MAX)
    {
      errno = EBADF;
      return -1;
    }
#endif
  retval = Ffchown (fd, owner, group);
  if (retval != 0)
    {
      errno = -retval;
      return -1;
    }
  return 0;
}
weak_alias (__fchown, fchown)
