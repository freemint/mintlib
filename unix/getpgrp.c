/*  src/getpgrp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

#include <unistd.h>
#include <mintbind.h>
#include <errno.h>
#include "lib.h"

pid_t
getpgrp()
{
  int retval;
  static short have_pgrp = 1;
	
  if (have_pgrp) 
    {
      retval = Pgetpgrp ();
      if (retval == -ENOSYS)
        have_pgrp = 0;
      else if (retval < 0)
        {
          __set_errno (-retval);
          return -1;
        }
      else
        return (pid_t) retval;
    }
  return 0;
}
