/*  stime.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <time.h>

#ifdef __TURBOC__
# include <sys\time.h>
#else
# include <sys/time.h>
#endif

#include <errno.h>

int stime (now)
  const time_t* now;
{
  struct timeval tv;
  
  if (now == (const time_t*) 0)
    {
      errno = EINVAL;
      return -1;
    }
    
  tv.tv_sec = *now;
  tv.tv_usec = 0;
  return settimeofday (&tv, (struct timezone*) 0);
}
