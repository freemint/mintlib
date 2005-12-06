/*  getpwuid.c -- MiNTLib.
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

extern int __getpwuid_r (uid_t uid, struct passwd* result_buf,
                         char* buffer, size_t buflen,
                         struct passwd** result);

static struct passwd passwd;
static char buf[1024];

struct passwd* getpwuid (uid_t uid)
{
  struct passwd* result;
  
  if (__getpwuid_r (uid, &passwd, buf, 1024, &result) != 0)
    return NULL;
  return result;
}
