/*  getspnam_r.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <shadow.h>
#include <errno.h>
#include <string.h>
#include <paths.h>
#include <stdio.h>

int __getspnam_r (const char* name, struct spwd* result_buf,
                  char* buffer, size_t buflen, 
                  struct spwd** result)
{
  FILE* spfile = fopen (_PATH_SHADOW, "r");
  int retval = -1;
  int save_errno;
  
  if (spfile == NULL)
    return -1;
  
  while (1)
    {
      if (fgetspent_r (spfile, result_buf, buffer, buflen, result) != 0)
        break;
      
      if (strcmp (result_buf->sp_namp, name) == 0)
        {
          retval = 0;
          break;
        }
    }
  save_errno = errno;
  (void) fclose (spfile);
  __set_errno (save_errno);
  return retval;
}

weak_alias (__getspnam_r, getspnam_r)
