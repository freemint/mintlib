/*  fchmod.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <stddef.h>

#ifdef __TURBOC__
# include <sys\stat.h>
# include <sys\types.h>
#else
# include <sys/stat.h>
# include <sys/types.h>
#endif

#include <limits.h>
#include <mintbind.h>

int __fchmod (int fd, mode_t mode)
{
  int retval;
  
#ifndef __MSHORT__
  if (fd > SHRT_MAX)
    {
      __set_errno (EBADF);
      return -1;
    }
#endif
  retval = Ffchmod (fd, mode);
  if (retval != 0)
    {
      __set_errno (-retval);
      return -1;
    }
  return 0;
}
weak_alias (__fchmod, fchmod)
