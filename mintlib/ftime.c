/*  ftime.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <sys/timeb.h>
#include <sys/time.h>
#include "time/tzstruct.h"

int
ftime (struct timeb *timebuf)
{
  struct timeval tv;
  struct timezone tz;
  struct tm tm;
  int retval = gettimeofday (&tv, &tz);

  if (retval < 0)
    return retval;
  timebuf->time = (time_t) tv.tv_sec;
  timebuf->millitm = ((short int) tv.tv_usec) / 1000;
  timebuf->timezone = (short int) tz.tz_minuteswest;
  
  /* I'm not quite sure but I think that the interpretation of member
   * dstflag differs from the tz_dsttime member of struct timezone.
   * I think that this time we have to return whether was used when
   * computing the other values.
   */
  
  __localsub (&timebuf->time, 0, &tm);
  timebuf->dstflag = (short int) tm.tm_isdst;

  return 0;
}
