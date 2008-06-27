/*  tempnam.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <mint/osbind.h>
#include <sys/types.h>

#include "lib.h"

/* In diraccess.c.  */
extern const char* __get_tmpdir (const char*, int try_tmpdir);
extern int __exists (const char* pathname);

extern const char __tmp_letters[62];

char*
tempnam (const char* dir, const char* prefix)
{
  static char buf[L_tmpnam];
  pid_t pid = getpid ();
  unsigned int i0, i1, i2, j0, j1, j2;
  int saved_errno;
  size_t len;
  char* tmpdir = (char*) (dir == NULL || (strlen (dir) > L_tmpnam - 13) ? 
  				__get_tmpdir (NULL, 1)
  				: __get_tmpdir (dir, 1));

  if (tmpdir == NULL)
    return NULL;
  strcpy (buf, tmpdir);
  	
  len = strlen (buf);
  if (buf[len - 1] != '/' && buf[len - 1] != '\\')
    {
      if (__mint)
        buf[len] = '/';
      else
        buf[len] = '\\';
      len++;
    }

  if (prefix != NULL)
    {
      int i;
      for (i = 0; i < 5 && prefix[i]; i++)
        buf[len++] = prefix[i];
    }
  buf[len] = '\0';

  /* By using the dot we can make sure that the function doesn't
     even fail on 8 + 3 file systems.  */
  len += 7;
  buf[len - 4] = '.';

  /* Create the filename.  */
  buf[len - 3] = pid / 100 + '0';
  pid %= 100;
  buf[len - 2] = pid / 10 + '0';
  buf[len - 1] = pid % 10 + '0';

  /* Choose a random start point to minimize the possibility of
     conflicts.  */
  i0 = Random () % sizeof __tmp_letters;
  i1 = Random () % sizeof __tmp_letters;
  i2 = Random () % sizeof __tmp_letters;

  saved_errno = errno;

  for (j0 = 0; j0 < sizeof __tmp_letters; j0++, i0++)
    {
      buf[len - 7] = __tmp_letters[i0 % sizeof __tmp_letters];
      for (j1 = 0; j1 < sizeof __tmp_letters; j1++, i1++)
        {
          buf[len - 6] = __tmp_letters[i1 % sizeof __tmp_letters];
          for (j2 = 0; j2 < sizeof __tmp_letters; j2++, i2++)
            {
              buf[len - 5] = __tmp_letters[i2 % sizeof __tmp_letters];
              if (!__exists (buf))
                return __strdup (buf);
            }
        }
    }

  __set_errno (EEXIST);
  return NULL;
}
