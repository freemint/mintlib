/*  src/bsd_setpgrp.c -- MiNTLib.
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

int
__bsd_setpgrp (pid, grp)
     int pid, grp;
{
  int retval = 0;
  static short have_pgrp = 1;
	
  if (have_pgrp) 
    {
      retval = Psetpgrp (pid, grp);
      if (retval == -ENOSYS) 
        {
	  if (grp != -1) 
	    have_pgrp = 0;
	  retval = 0;
	} 
      else if (retval < 0) 
        {
          if (retval == -EACCES)
          	retval = -EPERM;
          else if (retval == -ENOENT)
          	retval = ESRCH;
	  __set_errno (-retval);
      	  retval = -1;
	}	
    }
  return retval;
}
