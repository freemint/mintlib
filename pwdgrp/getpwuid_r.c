/*  getpwuid_r.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <pwd.h>
#include <errno.h>
#include <stdio.h>

int __getpwuid_r (uid_t uid, struct passwd* result_buf,
                  char* buffer, size_t buflen, 
                  struct passwd** result)
{
  FILE* pwfile = fopen ("/etc/passwd", "r");
  int retval = -1;
  int save_errno;
  
  if (pwfile == NULL)
    return -1;
  
  while (1)
    {
      if (fgetpwent_r (pwfile, result_buf, buffer, buflen, result) != 0)
        break;
      
      if (result_buf->pw_uid == uid)
        {
          retval = 0;
          break;
        }
    }
  save_errno = errno;
  (void) fclose (pwfile);
  __set_errno (save_errno);
  return retval;
}

weak_alias (__getpwuid_r, getpwuid_r)
