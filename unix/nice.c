/*  nice.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef __TURBOC__
# include <sys\resource.h>
#else
# include <sys/resource.h>
#endif

#include <errno.h>
#include <mintbind.h>

#include "lib.h"

int __nice (increment)
     int increment;
{
  /* Actually the return value of this function is not meaningful.
   * Yet many programs expect that it returns the current priority,
   * which is what MiNT intends to do.  But the code looks like:
   *
   *   return ((long) current_priority & 0x0ffff);
   *
   * Thus we can never find out if the return value was positive
   * or negative.  But we use our insider knowledge of the
   * kernel sources and fix the bug here.
   *
   * Another potiential problem is the sign of the return value:
   * If our process has a priority of 0 and we call Pnice with
   * an argument of 5 the function will return -5.  Maybe this
   * is a bug in MiNT, maybe it isn't.  But we will return here
   * what most programs (notably GNU nice) expect and revert
   * the sign of the return value.
   */
  
  int saved_priority = getpriority (PRIO_PROCESS, 0);
  return setpriority (PRIO_PROCESS, 0, saved_priority + increment);
}

weak_alias (__nice, nice)
