/*  strndup.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#undef strndup
#undef __strndup

char*
__strndup (const char* src, size_t n)
{
  char* result;
  size_t length = strlen (src);
  if (length > n)
    length = n;
  
  result = malloc (length + 1);
  if (result == NULL)
    return NULL;
  
  result[length] = '\0';
  return memcpy (result, src, length);
}
weak_alias (__strndup, strndup)
