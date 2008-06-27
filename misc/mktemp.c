/*  mktemp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <mint/osbind.h>  /* For Random().  */
#include <sys/types.h>

extern int __diraccess (const char* dir);
extern int __exists (const char* pathname);
extern const char __tmp_letters[62];

char*
mktemp (char* template)
{
  size_t len;
  pid_t pid = getpid ();
  unsigned int i0, i1, i2, j0, j1, j2;
  int saved_errno;
  
  if (template == NULL)
    {
      __set_errno (EINVAL);
      return NULL;
    }
  
  len = strlen (template);
  
  if (len < 6 
      || template[len - 6] != 'X' || template[len - 5] != 'X' 
      || template[len - 4] != 'X' || template[len - 3] != 'X' 
      || template[len - 2] != 'X' || template[len - 1] != 'X')
    {
      __set_errno (EINVAL);
      template[0] = -1;
      return NULL;
    }

  /* Create the filename.  */
  template[len - 3] = pid / 100 + '0';
  pid %= 100;
  template[len - 2] = pid / 10 + '0';
  template[len - 1] = pid % 10 + '0';

  /* Choose a random start point to minimize the possibility of
     conflicts.  */
  i0 = Random () % sizeof __tmp_letters;
  i1 = Random () % sizeof __tmp_letters;
  i2 = Random () % sizeof __tmp_letters;
  
  saved_errno = errno;
  
  for (j0 = 0; j0 < sizeof __tmp_letters; j0++, i0++)
    {
      template[len - 6] = __tmp_letters[i0 % sizeof __tmp_letters];
      for (j1 = 0; j1 < sizeof __tmp_letters; j1++, i1++)
        {
          template[len - 5] = __tmp_letters[i1 % sizeof __tmp_letters];
          for (j2 = 0; j2 < sizeof __tmp_letters; j2++, i2++)
            {
              template[len - 4] = __tmp_letters[i2 % sizeof __tmp_letters];
              
              if (!__exists (template))
                return template;
            }
        }
    }
        
  /* So, what error number to set?  */
  __set_errno (ENMFILES);
  template[0] = '\0';
  return template;
}
