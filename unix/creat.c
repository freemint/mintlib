/*  src/creat.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <fcntl.h>
#include "lib.h"

int
__creat(name, mode)
     const char *name;
     unsigned short mode;
{
  return open (name, O_WRONLY | O_CREAT | O_TRUNC, mode);
}
weak_alias (__creat, creat)
