/*  mkstemp.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

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
#include <fcntl.h>
#include <osbind.h> /* For Random ().  */

#ifdef __TURBOC__
# include <sys\types.h>
#else
# include <sys/types.h>
#endif

__EXTERN int __diraccess __PROTO ((const char* dir));
extern const char __tmp_letters[62];

/* The `mkstemp' function generates a unique file name just as `mktemp' 
   does, but it also opens the file for you with `open'.  If successful, 
   it modifies TEMPLATE in place and returns a file descriptor open on 
   that file for reading and writing.  If `mkstemp' cannot create a
   uniquely-named file, it makes TEMPLATE an empty string and returns
   `-1'.  If TEMPLATE does not end with `XXXXXX', `mkstemp' returns
   `-1' and does not modify TEMPLATE.

   Unlike `mktemp', `mkstemp' is actually guaranteed to create a unique
   file that cannot possibly clash with any other program trying to create
   a temporary file.  This is because it works by calling `open' with the
   `O_EXCL' flag bit, which says you want to always create a new file, and
   get an error if the file already exists.  */

int
mkstemp (char* template)
{
  size_t len;
  pid_t pid = getpid ();
  int i0, i1, i2, j0, j1, j2;
  int saved_errno;
  
  if (template == NULL)
    {
      errno = EINVAL;
      return -1;
    }
  
  len = strlen (template);
  
  if (len < 6 
      || template[len - 6] != 'X' || template[len - 5] != 'X' 
      || template[len - 4] != 'X' || template[len - 3] != 'X' 
      || template[len - 2] != 'X' || template[len - 1] != 'X')
    {
      errno = EINVAL;
      template[0] = -1;
      return -1;
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
              int fd;
              template[len - 4] = __tmp_letters[i2 % sizeof __tmp_letters];
              
              fd = open (template, O_RDWR | O_CREAT | O_EXCL, 0666);
              
              if (fd >= 0)
                {
                  errno = saved_errno;
                  return fd;
                }
              else if (errno != EEXIST)
                {
                  template[0] = '\0';
                  return -1;
                }
            }
        }
    }
        
  /* So, what error number to set?  */
  errno = ENMFILES;
  template[0] = '\0';
  return -1;
}
