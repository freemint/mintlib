/*  strtok.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <string.h>

#undef strtok

static char* save_ptr;

char*
strtok (s, delim)
     char *s;
     register const char *delim;
{
  return __strtok_r (s, delim, &save_ptr);
}
