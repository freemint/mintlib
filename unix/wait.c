/*  wait.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifdef __TURBOC__
# include <sys\wait.h>
#else
# include <sys/wait.h>
#endif

#include <stdlib.h>

pid_t __wait (stat_loc)
  __WP stat_loc;
{
  return wait4 (-1, stat_loc, 0, NULL);
}

weak_alias (__wait, wait)
