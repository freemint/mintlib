/*  src/getsid.c -- MiNTLib.
    Copyright (C) 2002 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <mint/mintbind.h>

pid_t
__getsid (pid_t pid)
{
  static short have_pgrp = 1;
  int rc = -1;

  if (have_pgrp) 
    {
      long prc_pgrp = Psetpgrp (pid, -1);
      if (prc_pgrp == -ENOSYS) 
        {
  	  have_pgrp = 0;
 	  __set_errno (ENOSYS);
        }
      else if (prc_pgrp < 0)
        {
          __set_errno(-prc_pgrp);
        }
      else
          rc = (int) prc_pgrp;
    }
  else
    {
      __set_errno (ENOSYS);
    }
    	
  return (pid_t) rc;
}

weak_alias (__getsid, getsid)
