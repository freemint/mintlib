/*  src/bsd_getpgrp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include "lib.h"

__EXTERN int __bsd_setpgrp __PROTO ((int, int));

int
__bsd_getpgrp(pid)
     int pid;
{
  return __bsd_setpgrp (pid, -1);
}
