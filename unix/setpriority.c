/*  setpriority.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>
#include <mint/mintbind.h>

static int initialized = 0;
static int have_Psetpriority = 1;
static int have_Prenice = 1;
static int have_Pnice = 1;

int
__setpriority (enum __priority_which class, int id, int priority)
{
  int saved_priority;
  int increment;
  int saved_errno;

  /* Check some errors first.  */
  if (class != PRIO_PROCESS && class != PRIO_PGRP && class != PRIO_USER)
    {
      __set_errno (EINVAL);
      return -1;
    }
    
  if (have_Psetpriority) {
    /* Fine.  */
    int retval = Psetpriority (class, id, priority);

    if (retval == -ENOSYS) {
      have_Psetpriority = 0;
    } else {
      /* Really fine.  */
      if (retval < 0) {
        if (retval == -ENOENT)
          retval = -ESRCH;
        __set_errno (-retval);
        return -1;
      } else {
        return 0;
      }
    }
  }
  
  if (!initialized) {
    int retval = Pnice (0);
    if (retval == -ENOSYS)
      have_Pnice = 0;
    initialized = 1;
  }
  
  saved_errno = errno;
  __set_errno (0);
  saved_priority = getpriority (class, id);
  if (errno != 0)
    return -1;
  __set_errno (saved_errno);

  if (class != PRIO_PROCESS) {
    __set_errno (ENOSYS);
    return -1;
  }

  increment = priority - saved_priority;
  
  if (have_Prenice) {
    int renice_id = id == 0 ? (int) getpid () : id;
    short int retval = (short int) -(Prenice (renice_id, increment));
    if (retval == -ENOSYS) {
      have_Prenice = 0;
    } else if (retval < PRIO_MIN || retval > PRIO_MAX) {
      if (retval == -ENOENT)
        __set_errno (ESRCH);
      else
        __set_errno (-retval);
      return -1;
    } else {
      return 0;
    }
  }
  
  /* Next try.  */
  if (have_Pnice) {
    if (id != 0 && id != (int) getpid ()) {
      __set_errno (ENOSYS);
      return -1;
    } else {
      short int retval = (short int) -(Pnice ((long) increment));
       
      if (retval == -ENOSYS) {
        have_Pnice = 0;
      } else if (retval < PRIO_MIN || retval > PRIO_MAX) {
        if (retval == -ENOENT)
          __set_errno (ESRCH);
        else
          __set_errno (-retval);
        return -1;
      } else {
        return 0;
      }
    }
  }
  
  __set_errno (ENOSYS);  
  return -1;
}
weak_alias (__setpriority, setpriority)
