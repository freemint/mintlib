/*  settimeofday.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <mintbind.h>

int 
__settimeofday (const struct timeval *tp, const struct timezone *tzp)
{
  int retval = 0;
  static int have_Tsettimeofday = 1;

  if (have_Tsettimeofday != 0) {
    retval = Tsettimeofday (tp, tzp);
    if (retval == -ENOSYS) {
      have_Tsettimeofday = 0;
    } else if (retval < 0) {
      if (retval == -EACCES)
      	retval = -EPERM;
      __set_errno (-retval);
      return -1;
    }
  }
  
  /* Fall through to emulation.  Don't emulate setting of timezone
   * stuff.
   */
  if (tzp != NULL) {
    __set_errno (ENOSYS);
    return -1;
  }
  
  if (tp != NULL) {
    struct tm then;
    short int tos_time, tos_date;

    /* The T[gs]et(date|time) system calls always expect local
     * times.
     */    
    localtime_r((time_t*) &tp->tv_sec, &then);
    
    if (then.tm_year < 80) {
      __set_errno (EINVAL);
      return -1;
    }
    
    tos_time = then.tm_sec / 2;
    /* I'm not sure if TOS can handle leapseconds.  Better take care.  */
    if (tos_time > 29)
      tos_time = 29;
    tos_time |= ((then.tm_min << 5) | (then.tm_hour << 11));
    tos_date = (then.tm_mday | ((then.tm_mon + 1) << 5)
        | ((then.tm_year - 80) << 9));
    
    retval = Tsettime (tos_time);
    if (retval < 0) {
      if (retval == -EACCES)
        retval = -EPERM;
      __set_errno (-retval);
      return -1;
    }
    retval = Tsetdate (tos_date);
    if (retval < 0) {
      if (retval == -EACCES)
        retval = -EPERM;
      __set_errno (-retval);
      return -1;
    }
    
  }
    
  return 0;
}
weak_alias (__settimeofday, settimeofday)
