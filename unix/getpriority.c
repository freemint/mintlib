/*  getpriority.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the FreeType project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>
#include <mint/mintbind.h>

static int initialized = 0;
static int have_Pgetpriority = 1;
static int have_Prenice = 1;
static int have_Pnice = 1;

int
__getpriority (enum __priority_which class, int id)
{
  if (class != PRIO_PROCESS && class != PRIO_PGRP && class != PRIO_USER)
    {
      __set_errno (EINVAL);
      return -1;
    }
  if (have_Pgetpriority) {
    /* Fine.  */
    int retval = Pgetpriority (class, id);
    if (retval == -ENOSYS) {
      have_Pgetpriority = 0;
    } else {
      /* Really fine.  */
      if (retval < 0) {
        if (retval == -ENOENT)
          retval = -ESRCH;
          
        __set_errno (-retval);
        return -1;
      } else {
        return retval + PRIO_MIN;
      }
    }
  }
  
  if (!initialized) {
    int retval = Pnice (0);
    if (retval == -ENOSYS)
      have_Pnice = 0;
    initialized = 1;
  }
  
  if (class != PRIO_PROCESS) {
    __set_errno (ENOSYS);
    return -1;
  }

  if (have_Prenice) {
    int renice_id = id == 0 ? (int) getpid () : id;
    short int retval = (short int) Prenice (renice_id, 0);
    if (retval == -ENOSYS) {
      have_Prenice = 0;
    } else if (retval < PRIO_MIN || retval > PRIO_MAX) {
      if (retval == -ENOENT)
        retval = -ESRCH;

      __set_errno (-retval);
      return -1;
    } else {
      return -retval;
    }
  }
  
  /* Next try.  */
  if (have_Pnice) {
    if (id != 0 && id != (int) getpid ()) {
      __set_errno (ENOSYS);
      return -1;
    } else {
      short int retval = (short int) Pnice ((long) 0);
       
      if (retval == -ENOSYS) {
        have_Pnice = 0;
      } else if (retval < PRIO_MIN || retval > PRIO_MAX) {
        /* An error has occured.  */
        if (retval == -ENOENT)
          retval = -ESRCH;

        __set_errno (-retval);
        return -1;
      } else {
        return -retval;
      }
    }
  }
  
  /* For TOS all processes have the same priority.  */
  return 0;
}
weak_alias (__getpriority, getpriority)
