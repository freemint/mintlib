/*  tz.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

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

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mintbind.h>
#include <limits.h>

#include "tzstruct.h"
#include "new_york.h"

char *tzname[2];        /* Current timezone names.  */
int daylight;           /* If daylight-saving time is ever in use.  */
long int timezone;      /* Seconds west of UTC.  */

char __lcl_TZname[TZ_STRLEN_MAX + 1];
int __lcl_is_set = 0;
int __gmt_is_set = 0;

struct state* __lclptr;
struct state* __gmtptr;

const long __mon_lengths[2][MONSPERYEAR] = 
{
  { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
  { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

const int __year_lengths[2] = 
{
  DAYSPERNYEAR, DAYSPERLYEAR
};

static char wildabbr[] = "WILDABBR";

static long   __detzcode __PROTO ((const char*));
static const char*  __getzname __PROTO ((const char*));
static const char*  __getnum __PROTO ((const char*, long*, long, long));
static const char*  __getsecs __PROTO ((const char*, long*));
static const char*  __getoffset __PROTO ((const char*, long*));
static const char*  __getrule __PROTO ((const char*, struct rule*));
static void   __settzname __PROTO ((void));
static time_t __transtime __PROTO ((time_t, long, const struct rule*, 
                                    long));

#ifdef __TURBOC__
static long __detzcode(const char* codep)
#else
static long
__detzcode(codep)
     const char* const codep;
#endif
{
  register long result;
  register int  i;
  
  result = (codep[0] & 0x80) ? ~0L : 0L;
  for (i = 0; i < 4; ++i)
    result = (result << 8) | (codep[i] & 0xff);
  return result;
}

static void
__settzname (void)
{
  register struct state* const sp = __lclptr;
  register int i;
  
  tzname[0] = wildabbr;
  tzname[1] = wildabbr;
  
  daylight = 0;
  timezone = 0;
  
  if (sp == NULL) 
    {
      tzname[0] = tzname[1] = "GMT";
      return;
    }
  
  for (i = 0; i < sp->typecnt; ++i) 
    {
      register const struct ttinfo* const ttisp = &sp->ttis[i];
      
      tzname[ttisp->tt_isdst] = &sp->chars[ttisp->tt_abbrind];

      if (ttisp->tt_isdst)
        daylight = 1;
      if (i == 0 || !ttisp->tt_isdst)
        timezone = -(ttisp->tt_gmtoff);
    }

  /* And to get the latest zone names into tzname.  */
  for (i = 0; i < sp->timecnt; ++i) 
    {
      register const struct ttinfo* const ttisp = &sp->ttis[sp->types[i]];

      tzname[ttisp->tt_isdst] = &sp->chars[ttisp->tt_abbrind];
    }
}

int __tzload (register const char* name, register struct state* sp)
{
  register const char*  p;
  register int          i;
  register long         fid;

  if (name == NULL && (name = TZDEFAULT) == NULL)
    return -1;
  
  {
    register int        doaccess;
    
    /* Section 4.9.1 of the C standard says that
       "FILENAME_MAX expands to an integral constant expression
       that is the size needed for an array of char large enough
       to hold the longest file name string that the implementation
       guarantees can be opened."  */

    char fullname[FILENAME_MAX + 1];

    if (name[0] == ':')
      ++name;

    /* We can't call _unx2dos here because NAME is read-only.  So
       we do a little check here if we may have found a valid 
       pathname and then set DOACCESS accordingly.  We can safely
       use the slash as path separator because only library functions
       (which will call _unx2dos anyway) get called on the filename.  */
    doaccess = (name[0] == '/' || name[0] == '\\' ||
                name[1] == ':');
                
    if (!doaccess) 
      {
        if ((p = TZDIR) == NULL)
          return -1;
        if ((strlen(p) + strlen(name) + 1) >= sizeof fullname)
          return -1;
        
        (void) strcpy (fullname, p);
        (void) strcat (fullname, "/");
        (void) strcat (fullname, name);
        
        /* Set doaccess if '.' (as in "../") shows up in name.  */
           if (strchr (name, '.') != NULL)
             doaccess = 1;
           name = fullname;
      }

    if (doaccess && access (name, R_OK) != 0)
      return -1;
      
    {
      extern int __libc_unix_names;
      char* filename = (char*) name;
      char buf[PATH_MAX];
      extern int _unx2dos __P ((char*, char*, unsigned long));
      
      if (!__libc_unix_names) 
        {
          filename = buf;
          (void) _unx2dos ((char*) name, filename, PATH_MAX);
        }
            
      if ((fid = Fopen (filename, O_RDONLY)) < 0)
        {
          __set_errno (-fid);
          return -1;
        }
    }
  }

  {
    struct tzhead* tzhp;
                
    union 
    {
      struct tzhead tzhead;
      char           buf[sizeof *sp + sizeof *tzhp];
    } u;
    long ttisstdcnt;
    long ttisgmtcnt;

    i = Fread (fid, sizeof u.buf, u.buf);
    if ((fid = Fclose(fid)) != 0)
      {
        __set_errno (-fid);
        return -1;
      }
    
    ttisstdcnt = (long) __detzcode (u.tzhead.tzh_ttisgmtcnt);
    ttisgmtcnt = (long) __detzcode (u.tzhead.tzh_ttisstdcnt);
                
    sp->leapcnt = (long) __detzcode (u.tzhead.tzh_leapcnt);
    sp->timecnt = (long) __detzcode (u.tzhead.tzh_timecnt);
    sp->typecnt = (long) __detzcode (u.tzhead.tzh_typecnt);
    sp->charcnt = (long) __detzcode (u.tzhead.tzh_charcnt);
    p = u.tzhead.tzh_charcnt + sizeof u.tzhead.tzh_charcnt;
    
    if (sp->leapcnt < 0 || sp->leapcnt > TZ_MAX_LEAPS ||
        sp->typecnt <= 0 || sp->typecnt > TZ_MAX_TYPES ||
        sp->timecnt < 0 || sp->timecnt > TZ_MAX_TIMES ||
        sp->charcnt < 0 || sp->charcnt > TZ_MAX_CHARS ||
        (ttisstdcnt != sp->typecnt && ttisstdcnt != 0) ||
        (ttisgmtcnt != sp->typecnt && ttisgmtcnt != 0))
      return -1;

    if (i - (p - u.buf) < sp->timecnt * 4 +     /* ats */
        sp->timecnt +                           /* types */
        sp->typecnt * (4 + 2) +         /* ttinfos */
        sp->charcnt +                   /* chars */
        sp->leapcnt * (4 + 4) +         /* lsinfos */
        ttisstdcnt +                    /* ttisstds */
        ttisgmtcnt)                     /* ttisgmts */
      return -1;

    for (i = 0; i < sp->timecnt; ++i) 
      {
        sp->ats[i] = __detzcode(p);
        p += 4;
      }

    for (i = 0; i < sp->timecnt; ++i) 
      {
        sp->types[i] = (unsigned char) *p++;
        if (sp->types[i] >= sp->typecnt)
          return -1;
      }

    for (i = 0; i < sp->typecnt; ++i) 
      {
        register struct ttinfo* ttisp;

        ttisp = &sp->ttis[i];
        ttisp->tt_gmtoff = __detzcode(p);
        p += 4;
        ttisp->tt_isdst = (unsigned char) *p++;
        if (ttisp->tt_isdst != 0 && ttisp->tt_isdst != 1)
          return -1;
        ttisp->tt_abbrind = (unsigned char) *p++;
        if (ttisp->tt_abbrind < 0 ||
            ttisp->tt_abbrind > sp->charcnt)
          return -1;
      }

    for (i = 0; i < sp->charcnt; ++i)
      sp->chars[i] = *p++;
    sp->chars[i] = '\0';        /* ensure '\0' at end */

    for (i = 0; i < sp->leapcnt; ++i) 
      {
        register struct lsinfo* lsisp;

        lsisp = &sp->lsis[i];
        lsisp->ls_trans = __detzcode (p);
        p += 4;
        lsisp->ls_corr = __detzcode (p);
        p += 4;
      }

    for (i = 0; i < sp->typecnt; ++i) 
      {
        register struct ttinfo* ttisp;

        ttisp = &sp->ttis[i];
        if (ttisstdcnt == 0)
          {
            ttisp->tt_ttisstd = 0;
          }
        else 
          {
            ttisp->tt_ttisstd = *p++;
            if (ttisp->tt_ttisstd != 1 &&
                ttisp->tt_ttisstd != 0)
              return -1;
          }
      }

    for (i = 0; i < sp->typecnt; ++i) 
      {
        register struct ttinfo *        ttisp;

        ttisp = &sp->ttis[i];
        if (ttisgmtcnt == 0)
          {
            ttisp->tt_ttisgmt = 0;
          }
        else 
          {
            ttisp->tt_ttisgmt = *p++;
            if (ttisp->tt_ttisgmt != 1 &&
                ttisp->tt_ttisgmt != 0)
              return -1;
          }
     }
  }

  return 0;
}

/* Given a pointer into a time zone string, scan until a character that is not
   a valid character in a zone name is found.  Return a pointer to that
   character.  */

static const char *
__getzname (strp)
     register const char* strp;
{
  register char c;

  while ((c = *strp) != '\0' && !is_digit(c) && c != ',' && c != '-' &&
      c != '+')
    ++strp;
  return strp;
}

/* Given a pointer into a time zone string, extract a number from that string.
   Check that the number is within a specified range; if it is not, return
   NULL.
   Otherwise, return a pointer to the first character not part of the number.
*/

static const char * __getnum (register const char* strp, long* nump, 
                              long min, long max)
{
  register char c;
  register int num;

  if (strp == NULL || !is_digit(c = *strp))
      return NULL;
    num = 0;
  
  do 
    {
      num = num * 10 + (c - '0');
      if (num > max)
        return NULL;    /* illegal value */
      c = *++strp;
    } while (is_digit(c));
  
  if (num < min)
    return NULL;                /* illegal value */
  *nump = num;

  return strp;
}

/* Given a pointer into a time zone string, extract a number of seconds,
   in hh[:mm[:ss]] form, from the string.
   If any error occurs, return NULL.
   Otherwise, return a pointer to the first character not part of the number
   of seconds.
*/

static const char *__getsecs(register const char* strp, long* secsp)
{
  long num;

  /* `HOURSPERDAY * DAYSPERWEEK - 1' allows quasi-Posix rules like
     "M10.4.6/26", which does not conform to Posix,
     but which specifies the equivalent of
     ``02:00 on the first Sunday on or after 23 Oct''.  */

  strp = __getnum (strp, &num, 0, HOURSPERDAY * DAYSPERWEEK - 1);
  if (strp == NULL)
    return NULL;
  *secsp = num * (long) SECSPERHOUR;
  if (*strp == ':') 
    {
      ++strp;
      strp = __getnum (strp, &num, 0, MINSPERHOUR - 1);
      if (strp == NULL)
        return NULL;

      *secsp += num * SECSPERMIN;
      if (*strp == ':') 
        {
          ++strp;
          /* `SECSPERMIN' allows for leap seconds.  */
          strp = __getnum (strp, &num, 0, SECSPERMIN);
          if (strp == NULL)
            return NULL;
          *secsp += num;
        }
    }

  return strp;
}

/* Given a pointer into a time zone string, extract an offset, in
   [+-]hh[:mm[:ss]] form, from the string.
   If any error occurs, return NULL.
   Otherwise, return a pointer to the first character not part of the time.  */

#ifdef __TURBOC__
static const char *__getoffset(register const char* strp, long* offsetp)
#else
static const char *
__getoffset (strp, offsetp)
     register const char* strp;
     long* const offsetp;
#endif
{
  register long neg = 0;

  if (*strp == '-') 
    {
      neg = 1;
      ++strp;
    } 
  else if (*strp == '+')
    {
      ++strp;
    }

  strp = __getsecs (strp, offsetp);
  if (strp == NULL)
    return NULL;                /* illegal time */
  if (neg)
    *offsetp = -*offsetp;

  return strp;
}

/* Given a pointer into a time zone string, extract a rule in the form
   date[/time].  See POSIX section 8 for the format of "date" and "time".
   If a valid rule is not found, return NULL.
   Otherwise, return a pointer to the first character not part of the rule.  */

#ifdef __TURBOC__
static const char* __getrule(const char* strp, register struct rule* rulep)
#else
static const char*
__getrule (strp, rulep)
     const char* strp;
     register struct rule* const rulep;
#endif
{
  if (*strp == 'J') 
    {
      /* Julian day.  */
      rulep->r_type = JULIAN_DAY;
      ++strp;
      strp = __getnum (strp, &rulep->r_day, 1, DAYSPERNYEAR);
     } 
  else if (*strp == 'M') 
    {
      /* Month, week, day.  */
      rulep->r_type = MONTH_NTH_DAY_OF_WEEK;
      ++strp;
      strp = __getnum (strp, &rulep->r_mon, 1, MONSPERYEAR);
      if (strp == NULL)
        return NULL;
      if (*strp++ != '.')
        return NULL;
      
      strp = __getnum (strp, &rulep->r_week, 1, 5);
      if (strp == NULL)
        return NULL;
      if (*strp++ != '.')
        return NULL;
      strp = __getnum(strp, &rulep->r_day, 0, DAYSPERWEEK - 1);
    } 
  else if (is_digit(*strp)) 
    {
      /* Day of year.  */
      rulep->r_type = DAY_OF_YEAR;
      strp = __getnum (strp, &rulep->r_day, 0, DAYSPERLYEAR - 1);
    } 
  else 
    {
      return NULL;              /* invalid format */
    }
    
  if (strp == NULL)
    return NULL;
  if (*strp == '/') 
    {
      /* Time specified.  */
      ++strp;
      strp = __getsecs (strp, &rulep->r_time);
    } 
  else 
    {   
      rulep->r_time = 2 * SECSPERHOUR;  /* default = 2:00:00 */
    }
  
  return strp;
}

/* Given the Epoch-relative time of January 1, 00:00:00 UTC, in a year, the
   year, a rule, and the offset from UTC at the time that rule takes effect,
   calculate the Epoch-relative time that rule takes effect.  */

static time_t __transtime(time_t janfirst, long year, 
                          register const struct rule* rulep, long offset)
{
  register int  leapyear;
  register time_t value;
  register int i;
  long d, m1, yy0, yy1, yy2, dow;

  value = 0;  /* Shut up compiler.  */
  leapyear = isleap(year);
  switch (rulep->r_type) 
    {
      case JULIAN_DAY:
        /* Jn - Julian day, 1 == January 1, 60 == March 1 even in leap
           years.
           In non-leap years, or if the day number is 59 or less, just
           add SECSPERDAY times the day number-1 to the time of
           January 1, midnight, to get the day.  */
        value = janfirst + (rulep->r_day - 1) * SECSPERDAY;
        if (leapyear && rulep->r_day >= 60)
          value += SECSPERDAY;
        break;

      case DAY_OF_YEAR:
        /* n - day of year.
          Just add SECSPERDAY times the day number to the time of
          January 1, midnight, to get the day.  */
        value = janfirst + rulep->r_day * SECSPERDAY;
        break;

      case MONTH_NTH_DAY_OF_WEEK:
        /* Mm.n.d - nth "dth day" of month m.  */
           value = janfirst;
           for (i = 0; i < rulep->r_mon - 1; ++i)
             value += __mon_lengths[leapyear][i] * SECSPERDAY;

        /* Use Zeller's Congruence to get day-of-week of first day of
           month.  */
        m1 = (rulep->r_mon + 9) % 12 + 1;
        yy0 = (rulep->r_mon <= 2) ? (year - 1) : year;
        yy1 = yy0 / 100;
        yy2 = yy0 % 100;
        dow = ((26 * m1 - 2) / 10 +
                1 + yy2 + yy2 / 4 + yy1 / 4 - 2 * yy1) % 7;
        if (dow < 0)
          dow += DAYSPERWEEK;

        /* "dow" is the day-of-week of the first day of the month.  Get
           the day-of-month (zero-origin) of the first "dow" day of the
           month.  */
        d = rulep->r_day - dow;
        if (d < 0)
          d += DAYSPERWEEK;
        for (i = 1; i < rulep->r_week; ++i) 
          {
            if (d + DAYSPERWEEK >= __mon_lengths[leapyear][rulep->r_mon - 1])
              break;
            d += DAYSPERWEEK;
          }

        /* "d" is the day-of-month (zero-origin) of the day we want.  */
        value += d * SECSPERDAY;
        break;
    }

  /* "value" is the Epoch-relative time of 00:00:00 UTC on the day in
     question.  To get the Epoch-relative time of the specified local
     time on that day, add the transition time and the current offset
     from UTC.  */
  
  return value + rulep->r_time + offset;
}

/* Given a POSIX section 8-style TZ string, fill in the rule tables as
   appropriate.  */

int __tzparse (const char* name, register struct state* sp, long lastditch)
{
  const char* stdname;
  const char* dstname = NULL;  /* Shut up compiler.  */
  size_t stdlen;
  size_t dstlen;
  long stdoffset;
  long dstoffset;
  register time_t* atp;
  register unsigned char* typep;
  register char* cp;
  
  stdname = name;
  if (lastditch) 
    {
      stdlen = strlen (name);   /* Length of standard zone name.  */
      name += stdlen;
      if (stdlen >= sizeof sp->chars)
        stdlen = (sizeof sp->chars) - 1;
      stdoffset = 0;
    } 
  else 
    {
      name = __getzname (name);
      stdlen = name - stdname;
      if (stdlen < 3)
        return -1;
      if (*name == '\0')
        return -1;
      name = __getoffset (name, &stdoffset);
      if (name == NULL)
        return -1;
    }
  
  if (__tzload (TZDEFRULES, sp) != 0)
     {
       /* The original implementation of the tz database gives up below
          iff there was no file containing default rules and iff an
          alternative time zone was specified in the environment.  IMHO 
          (Guido) this is not acceptable for the MiNTLib because it is 
          not even probable that the user has installed a file with default 
          rules.

          We fall back to POSIX and fill in the values from "America/New_York"
          instead.  The state structure will get overwritten by what we
          know.  */
        memcpy (sp, &new_york, sizeof new_york);
     }
     
  if (*name != '\0') 
    {
      dstname = name;
      name = __getzname (name);
      dstlen = name - dstname;  /* Length of DST zone name.  */
      if (dstlen < 3)
        return -1;
      if (*name != '\0' && *name != ',' && *name != ';') 
        {
          name = __getoffset (name, &dstoffset);
          if (name == NULL)
            return -1;
        } 
      else 
        {   
          dstoffset = stdoffset - SECSPERHOUR;
        }
  
      if (*name == ',' || *name == ';') 
        {
          struct rule start;
          struct rule end;
          register long year;
          register time_t janfirst;
          time_t starttime;
          time_t endtime;
          
          ++name;
          if ((name = __getrule (name, &start)) == NULL)
            return -1;
          if (*name++ != ',')
            return -1;
          if ((name = __getrule (name, &end)) == NULL)
            return -1;
          if (*name != '\0')
            return -1;
          sp->typecnt = 2;  /* Standard time and DST.  */
          
          /* Two transitions per year, from EPOCH_YEAR to 2037.  */
          sp->timecnt = 2 * (2037 - EPOCH_YEAR + 1);
          if (sp->timecnt > TZ_MAX_TIMES)
            return -1;
          sp->ttis[0].tt_gmtoff = -dstoffset;
          sp->ttis[0].tt_isdst = 1;
          sp->ttis[0].tt_abbrind = stdlen + 1;
          sp->ttis[1].tt_gmtoff = -stdoffset;
          sp->ttis[1].tt_isdst = 0;
          sp->ttis[1].tt_abbrind = 0;
          atp = sp->ats;
          typep = sp->types;
          janfirst = 0;
          for (year = EPOCH_YEAR; year <= 2037; ++year) 
            {
              starttime = __transtime(janfirst, year, &start, stdoffset);
              endtime = __transtime (janfirst, year, &end, dstoffset);
              if (starttime > endtime) 
                {
                  *atp++ = endtime;
                  *typep++ = 1;     /* DST ends.  */
                  *atp++ = starttime;
                  *typep++ = 0;     /* DST begins.  */
                }
              else 
                {
                  *atp++ = starttime;
                  *typep++ = 0;     /* DST begins.  */
                  *atp++ = endtime;
                  *typep++ = 1;     /* DST ends.  */
                }
              
              janfirst += __year_lengths[isleap(year)] * SECSPERDAY;
            }
        } 
      else 
        {
          register long theirstdoffset;
          register long theirdstoffset;
          register long theiroffset;
          register long isdst;
          register long i;
          register long j;
          
          if (*name != '\0')
            return -1;
          
          /* Initial values of theirstdoffset and theirdstoffset.  */
          theirstdoffset = 0;
          for (i = 0; i < sp->timecnt; ++i) 
            {
              j = sp->types[i];
              if (!sp->ttis[j].tt_isdst) 
                {
                  theirstdoffset = -sp->ttis[j].tt_gmtoff;
                  break;
                }
            }
          
          theirdstoffset = 0;
          for (i = 0; i < sp->timecnt; ++i) 
            {
              j = sp->types[i];
              if (sp->ttis[j].tt_isdst) 
                {
                  theirdstoffset = -sp->ttis[j].tt_gmtoff;
                  break;
                }
            }
          
          /* Initially we're assumed to be in standard time.  */
          isdst = 0;
          theiroffset = theirstdoffset;
          
          /* Now juggle transition times and types
             tracking offsets as you do.  */
          for (i = 0; i < sp->timecnt; ++i) 
            {
              j = sp->types[i];
              sp->types[i] = sp->ttis[j].tt_isdst;
              if (sp->ttis[j].tt_ttisgmt) 
                {
                  /* No adjustment to transition time.  */
                }
              else 
                {
                  /* If summer time is in effect, and the transition time was 
                     not specified as standard time, add the summer time 
                     offset to the transition time; otherwise, add the 
                     standard time offset to the transition time.
                  
                     Transitions from DST to DDST will effectively 
                     disappear since POSIX provides for only one DST 
                     offset.  */
                
                  if (isdst && !sp->ttis[j].tt_ttisstd) 
                    {
                      sp->ats[i] += dstoffset - theirdstoffset;
                    } 
                  else 
                    {
                      sp->ats[i] += stdoffset - theirstdoffset;
                    }
                }
              
              theiroffset = -sp->ttis[j].tt_gmtoff;
              if (sp->ttis[j].tt_isdst)
                theirdstoffset = theiroffset;
              else  
                theirstdoffset = theiroffset;
            }
  
          /* Finally, fill in ttis.  ttisstd and ttisgmt need not 
             be handled.  */
          sp->ttis[0].tt_gmtoff = -stdoffset;
          sp->ttis[0].tt_isdst = 0;
          sp->ttis[0].tt_abbrind = 0;
          sp->ttis[1].tt_gmtoff = -dstoffset;
          sp->ttis[1].tt_isdst = 1;
          sp->ttis[1].tt_abbrind = stdlen + 1;
          sp->typecnt = 2;
        }
    } 
  else 
    {
      dstlen = 0;
      sp->typecnt = 1;          /* Only standard time.  */
      sp->timecnt = 0;
      sp->ttis[0].tt_gmtoff = -stdoffset;
      sp->ttis[0].tt_isdst = 0;
      sp->ttis[0].tt_abbrind = 0;
    }
  sp->charcnt = stdlen + 1;
  if (dstlen != 0)
    sp->charcnt += dstlen + 1;
  if ((size_t) sp->charcnt > sizeof sp->chars)
    return -1;
  cp = sp->chars;
  (void) strncpy (cp, stdname, stdlen);
  cp += stdlen;
  *cp++ = '\0';
  
  if (dstlen != 0)
    {
      (void) strncpy (cp, dstname, dstlen);
      *(cp + dstlen) = '\0';
    }
  
  return 0;
}

void
tzsetwall (void)
{
  if (__lcl_is_set < 0)
    return;
  __lcl_is_set = -1;

  if (__lclptr == NULL) 
    {
      __lclptr = (struct state*) malloc (sizeof *__lclptr);
      if (__lclptr == NULL) 
        {
          __settzname();        /* All we can do.  */
          return;
        }
    }

  if (__tzload ((char *) NULL, __lclptr) != 0 
      && __tzload ("GMT", __lclptr) != 0)
    (void) __tzparse ("GMT", __lclptr, 1);
  __settzname ();
}

void
tzset (void)
{
  register const char* name = getenv ("TZ");
  
  if (name == NULL) 
    {
      tzsetwall ();
      return;
     }

  if (__lcl_is_set > 0 && strcmp (__lcl_TZname, name) == 0)
    return;
  __lcl_is_set = (strlen (name) < sizeof (__lcl_TZname));
  if (__lcl_is_set)
    (void) strcpy (__lcl_TZname, name);

  if (__lclptr == NULL) 
    {
      __lclptr = (struct state*) malloc (sizeof *__lclptr);
      if (__lclptr == NULL) 
        {
          __settzname();        /* All we can do.  */
          return;
        }
    }

  if (*name == '\0') 
    {
      /* User wants it fast rather than right.  */
      __lclptr->leapcnt = 0;            /* So, we're off a little.  */
      __lclptr->timecnt = 0;
      __lclptr->ttis[0].tt_gmtoff = 0;
      __lclptr->ttis[0].tt_abbrind = 0;
      (void) strcpy (__lclptr->chars, "GMT");
    } 
  else if (__tzload (name, __lclptr) != 0)
    if (name[0] == ':' || __tzparse (name, __lclptr, 0) != 0)
      if (__tzload ("GMT", __lclptr) != 0)
        (void) __tzparse ("GMT", __lclptr, 1);
      
  __settzname();
}
