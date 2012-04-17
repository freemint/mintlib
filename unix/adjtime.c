/*  adjtime.c -- MiNTLib.
    Copyright (C) 2004 Standa Opichal <opichals@seznam.cz>

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

int __adjtime (__const struct timeval *__delta,
		    struct timeval *__olddelta)
{
  int retval = 0;
  static int have_Tadjtime = 1;

  if (have_Tadjtime != 0) {
    retval = Tadjtime (__delta, __olddelta);
    if (retval == -ENOSYS) {
      have_Tadjtime = 0;
    } else if (retval < 0) {
      if (retval == -EACCES)
      	retval = -EPERM;
      __set_errno (-retval);
      return -1;
    }
  }
  
  /* Fall through to emulation? */
  
  if (__delta != NULL) {
    struct timeval tv;
    int retval = __gettimeofday (&tv, NULL);
    if (retval < 0)
	return retval;

    tv.tv_usec += __delta->tv_usec;
    if (tv.tv_usec >= 1000000L)
    {
      tv.tv_usec -= 1000000L;
      tv.tv_sec++;
    }
    tv.tv_sec += __delta->tv_sec;

    __settimeofday(&tv, NULL);
  }
    
  return 0;
}
weak_alias (__adjtime, adjtime)
