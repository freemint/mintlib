/*  gettimeofday.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <mint/mintbind.h>

int 
__gettimeofday (struct timeval *tp, struct timezone *tzp)
{
  unsigned short tos_time;
  unsigned short tos_date;
  struct tm now;
  static int have_Tgettimeofday = 1;
  
  if (have_Tgettimeofday != 0) {
    long retval = Tgettimeofday (tp, tzp);
    if (retval == -ENOSYS) {
      have_Tgettimeofday = 0;
    } else if (retval < 0) {
      __set_errno (-retval);
      return -1;
    } else {
      return 0;
    }
  } /* have_Tgettimeofday != 0 */
    
  /* Don't use `else' here.  The have_Tgettimeofday flag may have
   * changed and we want to fall back to the emulation.
   */
  tos_time = Tgettime ();
  tos_date = Tgetdate ();
    
  now.tm_sec = (tos_time & 0x1f) * 2;
  now.tm_min = (tos_time >> 5) & 0x3f;
  now.tm_hour = tos_time >> 11;
  now.tm_mday = tos_date & 0x1f;
  now.tm_mon = ((tos_date >> 5) & 0xf) - 1;
  now.tm_year = (tos_date >> 9) + 80;
  now.tm_isdst = -1;  /* Dunno.  */
     
  if (tp != NULL) {
    tp->tv_sec = mktime (&now);
    tp->tv_usec = 0;
  }
    
  if (tzp != NULL) {
    /* We should actually punish the user by returning -1 and setting
     * errno to ENOSYS.  In fact many library bindings always refuse
     * to get or set timezone information via [gs]ettimeofday.  The
     * absence of the Tgettimeofday system call is even a better argument
     * for this behavior.
     * 
     * But we want to keep MiNT and non-MiNT behavior as similar as 
     * possible.  So we soft-emulate Tgettimeofday completely and
     * retrieve the requested information from the TZ environment
     * variable.  This is probably what the user (resp. the client
     * programmer) wants.
     *
     * First make sure the database is initialized.  
     */
    tzset ();
    tzp->tz_minuteswest = -(timezone) / 60;
    
    /* Common misunderstanding:  The tz_dsttime member of struct 
     * timezone does _not_ specify whether DST is currently in
     * use but whether DST may be in use at all during some
     * part of the year.  Unfortunately there is no standard
     * call that detects this information.  So maybe my solution
     * is a hack.
     */
    tzp->tz_dsttime = strcmp (tzname[0], tzname[1]);
  } 

  return 0;
}

weak_alias (__gettimeofday, gettimeofday)
