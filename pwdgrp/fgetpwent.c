/*  fgetpwent.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <stdio.h>
#include <errno.h>


static char buffer[1024];
static struct passwd passwd;

extern int __fgetpwent_r (FILE* stream, struct passwd* resultbuf,
                          char* buffer, size_t buflen, 
                          struct passwd** result);

struct passwd* fgetpwent (FILE* stream)
{
  struct passwd* result;
  int retval = __fgetpwent_r (stream, &passwd, buffer, 1024, &result);
  
  if (retval != 0)
    return NULL;
  return &passwd;
}
