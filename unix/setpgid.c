/*  src/setpgid.c -- MiNTLib.
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

__EXTERN int __bsd_setpgrp __PROTO ((int, int));

int
setpgid(pid, pgid)
     pid_t pid, pgid;
{
  return (__bsd_setpgrp ((int) pid, (int) pgid));
}
