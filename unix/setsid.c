/*  src/setsid.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

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
__setsid (void)
{
  long prc_pgrp;
  int tty_fd;
  int rc = -1;
  static short have_pgrp = 1;

  if (have_pgrp) 
    {
      prc_pgrp = Pgetpgrp ();
      if (prc_pgrp == -ENOSYS) 
        {
  	  have_pgrp = 0;
 	  __set_errno (ENOSYS);
        }
      else 
        {	
          if (prc_pgrp != Pgetpid ()) 
            {
    	      if (isatty (-1)) 
    	        {
      	          tty_fd = open ("/dev/tty", O_RDWR | O_NOCTTY);
      	          if (tty_fd < __SMALLEST_VALID_HANDLE)
                    return (pid_t) -1;
      	          if (ioctl (tty_fd, TIOCNOTTY, 0) < 0) return -1;
      	          (void) close (tty_fd);
    	        }
            }
          rc = (int) Psetpgrp (0, 0);
          if (rc < 0) 
            {
              if (rc == -EACCES)
              	rc = -EPERM;
              else if (rc == -ENOENT)
              	rc = -ESRCH;
   	      __set_errno (-rc);
	      rc = -1;
            }
        }
    }
  else
    {
      __set_errno (ENOSYS);
    }
    	
  return (pid_t) rc;
}

weak_alias (__setsid, setsid)
