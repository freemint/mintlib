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
#include "lib.h"

#if __GNUC_PREREQ(7, 0)
#pragma GCC diagnostic ignored "-Wnonnull-compare"
#endif

int __settimeofday64(const struct timeval64 *tp, const struct timezone *tzp)
{
  int retval = 0;
  static int have_Tsettimeofday = 1;

  if (have_Tsettimeofday != 0) {
    /*
     * MiNTs timezone structure is different than ours
     */
    struct __mint_timezone minttz;
    struct __mint_timezone *minttzp = NULL;

    if (tzp != NULL)
    {
      minttz.tz_minuteswest = tzp->tz_minuteswest;
      minttz.tz_dsttime = tzp->tz_dsttime;
      minttzp = &minttz;
    }
    retval = Tsettimeofday64(tp, minttzp);
    if (retval == -ENOSYS && tp) {
      struct timeval tv;
      if ((__uint32_t)tp->tv_sec >= TIME32_MAX)
      {
      	retval = -EOVERFLOW;
      } else
      {
        tv.tv_sec = tp->tv_sec;
        tv.tv_usec = tp->tv_usec;
        retval = Tsettimeofday(&tv, minttzp);
      }
    }
    if (retval == -ENOSYS) {
      have_Tsettimeofday = 0;
    } else if (retval < 0) {
      if (retval == -EACCES)
      	retval = -EPERM;
      __set_errno (-retval);
      return -1;
    } else {
      return 0;
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
    __localtime64_r(&tp->tv_sec, &then);
    
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
      if (retval == -1)
        retval = -EINVAL;
      __set_errno (-retval);
      return -1;
    }
    retval = Tsetdate (tos_date);
    if (retval < 0) {
      if (retval == -1)
        retval = -EINVAL;
      __set_errno (-retval);
      return -1;
    }
    
  }
    
  return 0;
}
weak_alias (__settimeofday64, settimeofday64)
