/*  src/getpgrp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <mintbind.h>

#include "lib.h"

pid_t
__getpgrp (void)
{
  static short have_pgrp = 1;
	
  if (have_pgrp) 
    {
      int retval;

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
weak_alias (__getpgrp, getpgrp)
