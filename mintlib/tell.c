/*  src/tell.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <unistd.h>
#include <errno.h>
#include <mintbind.h>

long tell (int desc)
{
  long retval;
    
  retval = Fseek (0L, desc, SEEK_CUR);
  if (retval < 0) {
    __set_errno (-retval);
    return -1L;
  }
  return retval;
}
