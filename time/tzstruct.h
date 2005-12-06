/*  tzstruct.h -- MiNTLib.
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

/*  For internal library use only.  Not to be installed in your system 
    include path!  */

#include <time.h>
#include <limits.h>
#undef TZNAME_MAX  /* Is only 3 in limits.h.  */

#ifdef __USE_BSD
# define TM_GMTOFF tm_gmtoff
# define TM_ZONE   tm_zone
#else
# define TM_GMTOFF __tm_gmtoff
# define TM_ZONE   __tm_zone
#endif

#define BIGGEST(a, b) (((a) > (b)) ? (a) : (b))

#ifdef TZNAME_MAX
# define MY_TZNAME_MAX  TZNAME_MAX
#endif /* defined TZNAME_MAX */
#ifndef TZNAME_MAX
# define MY_TZNAME_MAX  255
#endif /* !defined TZNAME_MAX */

#define JULIAN_DAY    0 /* Jn - Julian day */
#define DAY_OF_YEAR   1 /* n - day of year */
#define MONTH_NTH_DAY_OF_WEEK 2 /* Mm.n.d - month, week, day of week */

#define HAVE_LONG_DOUBLE 1

/* Unlike <ctype.h>'s isdigit, this also works if c < 0 | c > UCHAR_MAX.  */
#define is_digit(c) ((unsigned)(c) - '0' <= 9)

#ifndef TYPE_BIT
#define TYPE_BIT(type)  (sizeof (type) * CHAR_BIT)
#endif /* !defined TYPE_BIT */

#ifndef TYPE_SIGNED
#define TYPE_SIGNED(type) (((type) -1) < 0)
#endif /* !defined TYPE_SIGNED */

#ifndef INT_STRLEN_MAXIMUM
/* 302 / 1000 is log10(2.0) rounded up.
   Subtract one for the sign bit if the type is signed;
   add one for integer division truncation;
   add one more for a minus sign if the type is signed.  */
#define INT_STRLEN_MAXIMUM(type) \
    ((TYPE_BIT(type) - TYPE_SIGNED(type)) * 302 / 100 + 1 + TYPE_SIGNED(type))
#endif /* !defined INT_STRLEN_MAXIMUM */

#include "tzfile.h"

struct ttinfo         /* time type information.  */
{
  long  tt_gmtoff;    /* UTC offset in seconds.  */
  int   tt_isdst;     /* Used to set tm_isdst.  */
  int   tt_abbrind;   /* abbreviation list index.  */
  int   tt_ttisstd;   /* Non-zero if transition is 
                         std time.  */
  int   tt_ttisgmt;   /* Non-zero if transition is UTC.  */
};

struct lsinfo         /* Leap second information.  */
{
  time_t    ls_trans; /* Transition time.  */
  long    ls_corr;    /* Correction to apply.  */
};

struct state {
  long   leapcnt;
  long   timecnt;
  long   typecnt;
  long   charcnt;
  time_t    ats[TZ_MAX_TIMES];
  unsigned char types[TZ_MAX_TIMES];
  struct ttinfo ttis[TZ_MAX_TYPES];
  char    chars[BIGGEST (BIGGEST (TZ_MAX_CHARS + 1, sizeof "GMT"),
        (2 * (MY_TZNAME_MAX + 1)))];
  struct lsinfo lsis[TZ_MAX_LEAPS];
};

struct rule {
  long   r_type;   /* type of rule--see below */
  long   r_day;    /* day number of rule */
  long   r_week;   /* week number of rule */
  long   r_mon;    /* month number of rule */
  long    r_time;   /* transition time of rule */
};

/* This structure is used both by localtime and gmtime.  They have
   to return the same pointer according to the C standard.  */
extern struct tm __tmbuf;  /* In localtime.c.  */

extern const long __mon_lengths[2][MONSPERYEAR];
extern const int __year_lengths[2];

/* Prototypes for internal functions.  */

extern void   __gmtsub (const time_t*, long, struct tm*);
extern void   __localsub (const time_t*, long, 
                                             struct tm*);
extern void   __timesub (const time_t*, long,
                    const struct state*, struct tm*);
extern int    __tzload (const char*, struct state*);
extern int    __tzparse (const char*, struct state*,
                    long lastditch);

extern struct state* __lclptr;
extern struct state* __gmtptr;

#ifndef TZ_STRLEN_MAX
#define TZ_STRLEN_MAX 255
#endif /* !defined TZ_STRLEN_MAX */

extern char __lcl_TZname[TZ_STRLEN_MAX + 1];
extern int  __lcl_is_set;
extern int  __gmt_is_set;
