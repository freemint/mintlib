/*  getpwnam.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <errno.h>
#include <string.h>

extern int __getpwnam_r (const char* name,
                         struct passwd* result_buf, char* buffer,
                         size_t buflen, struct passwd** result);

static struct passwd passwd;
static char buf[1024];

struct passwd* getpwnam (const char* name)
{
  struct passwd* result;
  
  if (__getpwnam_r (name, &passwd, buf, 1024, &result) != 0)
    return NULL;
  return result;
}
