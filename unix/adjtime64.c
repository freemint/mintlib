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
#include "lib.h"

__typeof__(adjtime) __adjtime;

int __adjtime64 (__const struct timeval64 *__delta, struct timeval64 *__olddelta)
{
  int retval = 0;
  struct timeval tv;
  struct timeval oldtv;
  struct timeval *delta32 = 0;

  /*
   * kernel does not have Tadjtime64().
   * Simply disallow ridiculous large values.
   */
  if (__delta != NULL)
  {
  	__int32_t high = (__delta->tv_sec >> 32);
  	if (high != 0 && high != -1)
  	{
  	  __set_errno(-EBADARG);
  	  return -1;
  	}
  	tv.tv_sec = __delta->tv_sec;
  	tv.tv_usec = __delta->tv_usec;
  	delta32 = &tv;
  }
  retval = __adjtime(delta32, &oldtv);
  if (retval == 0 && __olddelta)
  {
    __olddelta->tv_sec = oldtv.tv_sec;
    __olddelta->tv_usec = oldtv.tv_usec;
  }
  return retval;
}
weak_alias (__adjtime64, adjtime64)
