/*  getitimer.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef __TURBOC__
# include <sys\time.h>
#else
# include <sys/time.h>
#endif

#include <stdlib.h>

#include "lib.h"

int 
__getitimer (enum __itimer_which which, struct itimerval* old)
{
  return setitimer (which, NULL, old);
}

weak_alias (__getitimer, getitimer)
