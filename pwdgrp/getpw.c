/*  getpw.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <errno.h>
#include <stdio.h>

extern int __getpwuid_r (uid_t uid, struct passwd* resultbuf,
                         char* buffer, size_t buflen,
                         struct passwd** result);

int __getpw (uid_t uid, char* buf);

int
__getpw (uid_t uid, char* buf)
{
  char buffer[256];
  struct passwd result_buf;
  struct passwd* result;

  if (buf == NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  if (__getpwuid_r (uid, &result_buf, buffer, 256, &result) < 0)
    return -1;

  (void) sprintf (buf, "%s:%s%s%s:%lu:%lu:%s:%s:%s",
                  result_buf.pw_name,
                  result_buf.pw_passwd,
                  result_buf.pw_age != NULL && result_buf.pw_age[0] != ' ' ?
                       "," : "",
                  result_buf.pw_age != NULL && result_buf.pw_age[0] != ' ' ?
                       result_buf.pw_age : "",
                  (unsigned long) result_buf.pw_uid,
                  (unsigned long) result_buf.pw_gid,
                  result_buf.pw_gecos,
                  result_buf.pw_dir,
                  result_buf.pw_shell);
  return 0;
}

weak_alias (__getpw, getpw)
