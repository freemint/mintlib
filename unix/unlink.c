/*  unlink.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <mint/osbind.h>
#include <sys/stat.h>

#include "lib.h"

int
__unlink (const char *filename)
{
  char dosnamebuf[PATH_MAX];
  int retval;
  char* dosname = (char*) filename;

  if (filename == NULL)
    {
      __set_errno (EFAULT);
      return -1;
    }
  if (!__libc_unix_names)
    {
      dosname = dosnamebuf;
      _unx2dos (filename, dosname, sizeof (dosnamebuf));
    }

  retval = (int) Fdelete (dosname);

  if (retval < 0) 
    {
      struct stat sb;
      
      if ((retval == -ENOTDIR) && (_enoent (dosname)))
        retval = -ENOENT;
      else if (retval == -EACCES && __quickstat (filename, &sb, 0) == 0)
        {
          if (S_ISDIR (sb.st_mode))
            retval = -EISDIR;
        }
      __set_errno (-retval);
      return -1;
    }
  return 0;
}
weak_alias (__unlink, unlink)
