/*  mktime.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

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

#include "tzstruct.h"

static int __increment_overflow __PROTO ((int*, long));
static int __normalize_overflow __PROTO ((int*, int*, long));
static time_t __time1 __PROTO ((struct tm*, 
                                void (*) __PROTO ((const time_t*, 
                                                   long, struct tm*)),
                                long));
static time_t __time2 __PROTO ((struct tm*,
                                void (*) __PROTO ((const time_t*,
                                long, struct tm*)),
                                long offset, long *okayp));
static time_t   __time2sub __PROTO ((struct tm*,
                                     void (*) __PROTO ((const time_t*,
                                     long, 
                                     struct tm*)),
                                     long, long*, long));
static long __tmcomp __PROTO ((const struct tm*, const struct tm*));

void __timesub(const time_t* timep, long offset, register const struct state* sp,
               register struct tm* tmp)
{
  const struct lsinfo* lp;
  long days;
  long  rem;
  long y;
  int yleap;
  const long* ip;
  long  corr;
  int hit;
  int i;

  corr = 0;
  hit = 0;
  i = (sp == NULL) ? 0 : sp->leapcnt;

  while (--i >= 0) 
    {
      lp = &sp->lsis[i];
      if (*timep >= lp->ls_trans) 
        {
          if (*timep == lp->ls_trans) 
            {
              hit = ((i == 0 && lp->ls_corr > 0) ||
                     lp->ls_corr > sp->lsis[i - 1].ls_corr);
              if (hit)
              while (i > 0 &&
                     sp->lsis[i].ls_trans == sp->lsis[i - 1].ls_trans + 1 &&
                     sp->lsis[i].ls_corr == sp->lsis[i - 1].ls_corr + 1) 
                {
                  ++hit;
                  --i;
                }
            }
        
          corr = lp->ls_corr;
          break;
        }
    }
    
  days = *timep / SECSPERDAY;
  rem = *timep % SECSPERDAY;

  if (*timep == 0x80000000L) 
    {
      /* A 3B1 muffs the division on the most negative number.  */
      days = -24855;
      rem = -11648;
    }

  rem += (offset - corr);
  while (rem < 0) 
    {
      rem += SECSPERDAY;
      --days;
    }
    
  while (rem >= SECSPERDAY) 
    {
      rem -= SECSPERDAY;
      ++days;
    }
    
  tmp->tm_hour = (int) (rem / SECSPERHOUR);
  rem = rem % SECSPERHOUR;
  tmp->tm_min = (int) (rem / SECSPERMIN);
  /* A positive leap second requires a special
     representation.  This uses "... ??:59:60" et seq.  */

  tmp->tm_sec = (int) (rem % SECSPERMIN) + hit;
  tmp->tm_wday = (int) ((EPOCH_WDAY + days) % DAYSPERWEEK);
  if (tmp->tm_wday < 0)
    tmp->tm_wday += DAYSPERWEEK;
  y = EPOCH_YEAR;
#define LEAPS_THRU_END_OF(y)  ((y) / 4 - (y) / 100 + (y) / 400)
  while (days < 0 || days >= (long) __year_lengths[yleap = isleap(y)]) 
    {
      register long  newy;

      newy = y + days / DAYSPERNYEAR;
      if (days < 0)
        --newy;
      days -= (newy - y) * DAYSPERNYEAR +
              LEAPS_THRU_END_OF(newy - 1) -
              LEAPS_THRU_END_OF(y - 1);
      y = newy;
    }
  tmp->tm_year = y - TM_YEAR_BASE;
  tmp->tm_yday = (int) days;
  ip = __mon_lengths[yleap];
  for (tmp->tm_mon = 0; days >= (long) ip[tmp->tm_mon]; ++(tmp->tm_mon))
    days = days - (long) ip[tmp->tm_mon];
  tmp->tm_mday = (int) (days + 1);
  tmp->tm_isdst = 0;
  tmp->TM_GMTOFF = offset;
}

/* Adapted from code provided by Robert Elz, who writes:
   The "best" way to do mktime I think is based on an idea of Bob
   Kridle's (so its said...) from a long time ago.
   [kridle@xinet.com as of 1996-01-16.]
   It does a binary search of the time_t space.  Since time_t's are
   just 32 bits, its a max of 32 iterations (even at 64 bits it
   would still be very reasonable).  */

#ifndef WRONG
# define WRONG  (-1)
#endif /* !defined WRONG */

/* Simplified normalize logic courtesy Paul Eggert (eggert@twinsun.com).  */
static int
__increment_overflow (number, delta)
     int* number;
     long  delta;
{
  long number0;

  number0 = *number;
  *number += delta;
  return (*number < number0) != (delta < 0);
}

static int __normalize_overflow (int* tensptr, int* unitsptr, long base)
{
  register long tensdelta;

  tensdelta = (*unitsptr >= 0) ?
                  (*unitsptr / base) :
                      (-1 - (-1 - *unitsptr) / base);
  *unitsptr -= tensdelta * base;
  return __increment_overflow (tensptr, tensdelta);
}

static long __tmcomp(register const struct tm* atmp, 
                     register const struct tm* btmp)
{
  register long  result;

  if ((result = (atmp->tm_year - btmp->tm_year)) == 0 &&
      (result = (atmp->tm_mon - btmp->tm_mon)) == 0 &&
      (result = (atmp->tm_mday - btmp->tm_mday)) == 0 &&
      (result = (atmp->tm_hour - btmp->tm_hour)) == 0 &&
      (result = (atmp->tm_min - btmp->tm_min)) == 0)
    result = atmp->tm_sec - btmp->tm_sec;
  
  return result;
}

static time_t __time2sub(struct tm* tmp, 
                         void (*funcp) __PROTO ((const time_t*, long, struct tm*)),
                         long offset, long* okayp, long do_norm_secs)
{
  register const struct state*  sp;
  register long dir;
  register long bits;
  register int i, j ;
  register long saved_seconds;
  time_t newt;
  time_t t;
  struct tm yourtm, mytm;

  *okayp = 1;
  yourtm = *tmp;
  if (do_norm_secs) 
    {
      if (__normalize_overflow (&yourtm.tm_min, &yourtm.tm_sec,
          SECSPERMIN))
        return WRONG;
    }
    
  if (__normalize_overflow (&yourtm.tm_hour, &yourtm.tm_min, MINSPERHOUR))
    return WRONG;
  if (__normalize_overflow (&yourtm.tm_mday, &yourtm.tm_hour, HOURSPERDAY))
    return WRONG;
  if (__normalize_overflow (&yourtm.tm_year, &yourtm.tm_mon, MONSPERYEAR))
    return WRONG;
  /* Turn yourtm.tm_year into an actual year number for now.
     It is converted back to an offset from TM_YEAR_BASE later.  */
  if (__increment_overflow (&yourtm.tm_year, TM_YEAR_BASE))
    return WRONG;
    
  while (yourtm.tm_mday <= 0) 
    {
      if (__increment_overflow (&yourtm.tm_year, -1))
        return WRONG;
      i = yourtm.tm_year + (1 < yourtm.tm_mon);
      yourtm.tm_mday += __year_lengths[isleap(i)];
    }
  
  while (yourtm.tm_mday > DAYSPERLYEAR) 
    {
      i = yourtm.tm_year + (1 < yourtm.tm_mon);
      yourtm.tm_mday -= __year_lengths[isleap(i)];
      if (__increment_overflow(&yourtm.tm_year, 1))
        return WRONG;
    }
  
  for ( ; ; ) 
    {
      i = __mon_lengths[isleap (yourtm.tm_year)][yourtm.tm_mon];
      if (yourtm.tm_mday <= i)
        break;
      yourtm.tm_mday -= i;
      if (++yourtm.tm_mon >= MONSPERYEAR) 
        {
          yourtm.tm_mon = 0;
          if (__increment_overflow(&yourtm.tm_year, 1))
            return WRONG;
        }
    }
    
  if (__increment_overflow (&yourtm.tm_year, -TM_YEAR_BASE))
    return WRONG;
  if (yourtm.tm_year + TM_YEAR_BASE < EPOCH_YEAR) 
    {
      /* We can't set tm_sec to 0, because that might push the
         time below the minimum representable time.
         Set tm_sec to 59 instead.
         This assumes that the minimum representable time is
         not in the same minute that a leap second was deleted from,
         which is a safer assumption than using 58 would be.  */
      if (__increment_overflow (&yourtm.tm_sec, 1 - SECSPERMIN))
        return WRONG;
      saved_seconds = yourtm.tm_sec;
      yourtm.tm_sec = SECSPERMIN - 1;
    } 
  else 
    {
      saved_seconds = yourtm.tm_sec;
      yourtm.tm_sec = 0;
    }
    
  /* Divide the search space in half
     (this works whether time_t is signed or unsigned).  */
  bits = TYPE_BIT (time_t) - 1;
  
  /* If time_t is signed, then 0 is just above the median,
     assuming two's complement arithmetic.
     If time_t is unsigned, then (1 << bits) is just above the median.  */
  t = TYPE_SIGNED (time_t) ? 0 : (((time_t) 1) << bits);
  for ( ; ; ) 
    {
      (*funcp) (&t, offset, &mytm);
      dir = __tmcomp (&mytm, &yourtm);
      if (dir != 0) 
        {
          if (bits-- < 0)
            return WRONG;
          if (bits < 0)
            --t; /* May be needed if new t is minimal.  */
          else if (dir > 0)
            t -= ((time_t) 1) << bits;
          else  
            t += ((time_t) 1) << bits;
          continue;
        }
        
      if (yourtm.tm_isdst < 0 || mytm.tm_isdst == yourtm.tm_isdst)
        break;
      
      /* Right time, wrong type.
         Hunt for right time, right type.
         It's okay to guess wrong since the guess
         gets checked.  */
      sp = (const struct state *)
        ((funcp == __localsub) ?
            __lclptr : __gmtptr);

      if (sp == NULL)
        return WRONG;

      for (i = sp->typecnt - 1; i >= 0; --i) 
        {
          if (sp->ttis[i].tt_isdst != yourtm.tm_isdst)
            continue;
      
          for (j = sp->typecnt - 1; j >= 0; --j) 
            {
              if (sp->ttis[j].tt_isdst == yourtm.tm_isdst)
                continue;
              newt = t + sp->ttis[j].tt_gmtoff -
              sp->ttis[i].tt_gmtoff;
              (*funcp) (&newt, offset, &mytm);
              if (__tmcomp(&mytm, &yourtm) != 0)
                continue;
              if (mytm.tm_isdst != yourtm.tm_isdst)
                continue;
              /* We have a match.   */
              t = newt;
              goto label;
            }
        }
        
      return WRONG;
    
    }
    
label:
  newt = t + saved_seconds;
  if ((newt < t) != (saved_seconds < 0))
    return WRONG;
  t = newt;
  (*funcp) (&t, offset, tmp);
  *okayp = 1;
  return t;
}

static time_t __time2(struct tm* tmp, 
                      void (*funcp) __PROTO ((const time_t*, long, struct tm*)),
     		      long offset, long* okayp)
{
  time_t  t;

  /* First try without normalization of seconds
    (in case tm_sec contains a value associated with a leap second).
     If that fails, try with normalization of seconds.  */
  t = __time2sub (tmp, funcp, offset, okayp, 0);
  return *okayp ? t : __time2sub (tmp, funcp, offset, okayp, 1);
}

static time_t __time1 (struct tm* tmp, 
                       void (*funcp) __PROTO ((const time_t*, long, struct tm*)),
     		       long offset)
{
  register time_t t;
  register const struct state*  sp;
  register long samei, otheri;
  long okay;

  if (tmp->tm_isdst > 1)
    tmp->tm_isdst = 1;
  t = __time2 (tmp, funcp, offset, &okay);

  /* PCTS code courtesy Grant Sullivan (grant@osf.org).  */
  if (okay)
    return t;
  if (tmp->tm_isdst < 0)
    tmp->tm_isdst = 0;  /* Reset to std and try again.  */

  /* We're supposed to assume that somebody took a time of one type
     and did some math on it that yielded a "struct tm" that's bad.
     We try to divine the type they started from and adjust to the
     type they need.  */

  sp = (const struct state *) ((funcp == __localsub) ?
                                    __lclptr : __gmtptr);
  if (sp == NULL)
    return WRONG;

  for (samei = sp->typecnt - 1; samei >= 0; --samei) 
    {
      if (sp->ttis[samei].tt_isdst != tmp->tm_isdst)
        continue;
      for (otheri = sp->typecnt - 1; otheri >= 0; --otheri) 
        {
          if (sp->ttis[otheri].tt_isdst == tmp->tm_isdst)
            continue;
          tmp->tm_sec += sp->ttis[otheri].tt_gmtoff -
          sp->ttis[samei].tt_gmtoff;
          tmp->tm_isdst = !tmp->tm_isdst;
          t = __time2 (tmp, funcp, offset, &okay);
          if (okay)
            return t;
          tmp->tm_sec -= sp->ttis[otheri].tt_gmtoff -
          sp->ttis[samei].tt_gmtoff;
          tmp->tm_isdst = !tmp->tm_isdst;
        }
    }
    
  return WRONG;
}

time_t
mktime (struct tm * const tmp)
{
  tzset();
  
  /* Set DST flag to undecided.  Otherwise, if it is zero and __time1
     finds out that DST applies, we get an error.  */
  tmp->tm_isdst = -1;
  return __time1 (tmp, __localsub, 0L);
}
