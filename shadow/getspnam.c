/*  getspnam.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <shadow.h>
#include <errno.h>
#include <string.h>

extern int __getspnam_r (const char* name,
                         struct spwd* result_buf, char* buffer,
                         size_t buflen, struct spwd** result);

static struct spwd spwd;
static char buf[1024];

struct spwd* getspnam (const char* name)
{
  struct spwd* result;
  
  if (__getspnam_r (name, &spwd, buf, 1024, &result) != 0)
    return NULL;
  return result;
}
