/*  reboot.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <sys/reboot.h>
#include <mint/ssystem.h>
#include <mintbind.h>
#include <errno.h>
#include <unistd.h>

/* Reboot the system or change the behavior of the CTRL-ALT-DEL key
   combination.  */
int 
#ifndef __MSHORT__
reboot (int howto)
#else
reboot (long int howto)
#endif
{
  int retval, arg = 0;
  
  if (geteuid () != 0) {
    __set_errno (EPERM);
    return -1;
  }
  
  switch (howto) {
    case RB_AUTOBOOT:
      /* Reset the system.  */
      arg = 1;
    case RB_HALT:
      /* Halt.  */
      break;
    case RB_ENABLE_CAD:
      retval = Ssystem (S_CTRLALTDEL, 0, 0);
      if (retval != 0) {
        __set_errno (retval);
        return -1;
      }
      return 0;
    case RB_DISABLE_CAD:
      retval = Ssystem (S_CTRLALTDEL, 1, 0);
      if (retval != 0) {
        __set_errno (retval);
        return -1;
      }
      return 0;
    default:
      __set_errno (EINVAL);
      return -1;
    }
  
  retval = Shutdown (arg);

  /* If we get here something went wrong.  */
  __set_errno (-retval);
  return -1;
}
