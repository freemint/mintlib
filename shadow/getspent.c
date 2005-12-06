/*  getspent.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <shadow.h>
#include <errno.h>
#include <stddef.h>

extern int __getspent_r (struct spwd* resultbuf, char* buffer,
                         size_t buflen, struct spwd** result);

static struct spwd spwd;
static char buffer[1024];

struct spwd* getspent (void)
{
  struct spwd* result;
  int retval = __getspent_r(&spwd, buffer, 1024, &result);
  
  if (retval != 0)
    return NULL;
  return &spwd;
}
