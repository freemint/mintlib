/*  dirname.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <libgen.h>
#include <string.h>

#include "lib.h"

#define my_tolower(c) ((c >= 'A' && c <= 'Z') ? c += ('a' - 'A') : c)

char*
dirname (char *path)
{
  static const char here[] = ".";
  char* backslash;
  char* slash;
  char* last_slash;
  
  if (path == NULL)
    {
      return (char*) here;  /* Yes, this is stupid.  See below!  */
    }
  else if ((path[0] == 'U' || path[0] == 'u')
           && path[1] == ':' && path[2] == '\0' && __mint)
    {
      path[0] = '/';
      path[1] = '\0';
      return path;
    }
  else if (path[1] == ':' && path[2] == '\0'
           && ((path[0] >= 'A' && path[0] <= 'Z' && path[0] != 'U')
                || (path[0] >= 'a' && path[0] <= 'z')
                || (path[0] >= '0' && path[0] <= '9')))
    {
      /* A drive letter followed by a colon.  */
      if (__mint)
        {
          path[1] = my_tolower (path[1]);
          path[0] = '/';
        }
      return path;  /* It IS null-terminated.  */
    }
  
  slash = strrchr (path, '/');
  backslash = strrchr (path, '\\');
  
  if (slash > backslash)
    last_slash = slash;
  else if (backslash != NULL)
    last_slash = backslash;
  else
    last_slash = NULL;

  /* End of Atari-specifific kludges.  The rest is more or less taken
     unchanged from the GNU libc.  */
  if (last_slash == path)
    {
      /* The last slash is the first character in the string.  We have to
         return "/".  */
      ++last_slash;
    }
  else if (last_slash != NULL && last_slash[1] == '\0')
    {
      /* The '/' or '\\' is the last character, we have to look further.  */
      char* maybe_last_slash = memchr (path, last_slash - path, '/');
      if (maybe_last_slash == NULL)
        maybe_last_slash = memchr (path, last_slash - path, '\\');
      last_slash = maybe_last_slash;
    }

  if (last_slash != NULL)
    /* Terminate the path.  */
    last_slash[0] = '\0';
  else
    /* This assignment is ill-designed but the XPG specs require to
       return a string containing "." in any case no directory part is
       found and so a static and constant string is required.  */
    path = (char*) here;

  return path;
}
