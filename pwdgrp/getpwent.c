/*  getpwent.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <errno.h>
#include <stddef.h>

extern int __getpwent_r (struct passwd* resultbuf, char* buffer,
                         size_t buflen, struct passwd** result);

static struct passwd passwd;
static char buffer[1024];

struct passwd* getpwent (void)
{
  struct passwd* result;
  int retval = __getpwent_r(&passwd, buffer, 1024, &result);
  
  if (retval != 0)
    return NULL;
  return &passwd;
}
