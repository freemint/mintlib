/*  strerror_r.c -- MiNTLib.
    Copyright (C) 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <string.h>

/* The MiNTLib is actually reentrant.  The thread-safe version is
   provided here for compatibility with the GNU libc.  */
char* __strerror_r (errnum, buf, bufsize)
     int errnum;
     char* buf;
     size_t bufsize;
{
  char* retval = strerror (errnum);
  size_t len = strlen (retval);
  /* Ignore possible underflow in bufsize.  We'll check later if it's
     zero.  */
  size_t copylen = len < (bufsize - 1) ? len : (bufsize - 1);
  
  if (buf == NULL || bufsize == 0)
    return buf;

  memcpy (buf, retval, copylen);
  buf[copylen] = '\0';
  return buf;    
}

weak_alias (__strerror_r, strerror_r);
