/*  localtime.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/*  This file is derived from localtime.c from the tz database.
    localtime.c is in the public domain, so clarified as of
    1996-06-05 by Arthur David Olson (arthur_david_olson@nih.gov).
*/


/*
** The easy way to behave "as if no library function calls" localtime
** is to not call it--so we drop its guts into "localsub", which can be
** freely called.  (And no, the PANS doesn't require the above behavior--
** but it *is* desirable.)
**
** The unused offset argument is for the benefit of mktime variants.
*/

#include "tzstruct.h"

struct tm __tmbuf;

/*ARGSUSED*/
#ifdef __TURBOC__
void __localsub (const time_t* timep, long offset, struct tm* tmp)
#else
void
__localsub (timep, offset, tmp)
     const time_t* const timep;
     const long offset;
     struct tm* const tmp;
#endif
{
  register struct state* sp;
  register const struct ttinfo* ttisp;
  register int i;
  const time_t t = *timep;

  sp = __lclptr;

  if (sp == NULL) 
    {
      __gmtsub(timep, offset, tmp);
      return;
    }

  if (sp->timecnt == 0 || t < sp->ats[0]) 
    {
      i = 0;
      while (sp->ttis[i].tt_isdst)
        {
          if (++i >= sp->typecnt) 
            {
              i = 0;
              break;
            }
        }
    } 
  else 
    {
      for (i = 1; i < sp->timecnt; ++i)
        if (t < sp->ats[i])
          break;
      i = sp->types[i - 1];
    }
    
  ttisp = &sp->ttis[i];
  /* To get (wrong) behavior that's compatible with System V Release 2.0
     you'd replace the statement below with
     t += ttisp->tt_gmtoff;
     __timesub(&t, 0L, sp, tmp);  */
     
  __timesub (&t, ttisp->tt_gmtoff, sp, tmp);
  tmp->tm_isdst = ttisp->tt_isdst;
  tzname[tmp->tm_isdst] = &sp->chars[ttisp->tt_abbrind];

  tmp->TM_ZONE = &sp->chars[ttisp->tt_abbrind];
}

#ifdef __TURBOC__
struct tm* localtime(const time_t* timep)
#else
struct tm*
localtime (timep)
const time_t* const timep;
#endif
{
  tzset ();
  __localsub (timep, 0L, &__tmbuf);
  return &__tmbuf;
}

#ifdef __TURBOC__
struct tm* localtime_r (const time_t *timep, struct tm* tm)
#else
struct tm*
localtime_r (timep, tm)
const time_t* const timep;
struct tm* tm;
#endif
{
  tzset ();
  __localsub (timep, 0L, tm);
  return tm;
}
