/*  time.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef	_TIME_H

#if !defined(__need_time_t) && !defined(__need_clock_t) && \
  !defined(__need_timespec)
# define _TIME_H 1

# ifndef _FEATURES_H
#  include <features.h>
# endif

__BEGIN_DECLS

#endif

#ifdef _TIME_H

# define __need_size_t
# define __need_NULL
#include <stddef.h>

#define CLOCKS_PER_SEC (200UL) /* Clock ticks per second.  */

#ifdef __USE_POSIX
# ifndef CLK_TCK
#  define CLK_TCK CLOCKS_PER_SEC /* Old name for this.  */
# endif
#endif

#endif /* not _TIME_H */

#if !defined __clock_t_defined && (defined _TIME_H || defined __need_clock_t)
# define __clock_t_defined	1

# include <bits/types.h>

/* Returned by `clock'.  */
typedef __clock_t clock_t;

#endif /* clock_t not defined and <time.h> or need clock_t.  */
#undef	__need_clock_t

#if !defined __time_t_defined && (defined _TIME_H || defined __need_time_t)
# define __time_t_defined	1

# include <bits/types.h>

/* Returned by `time'.  */
typedef __time_t time_t;

#endif /* time_t not defined and <time.h> or need time_t.  */
#undef	__need_time_t

#if !defined __timespec_defined && \
    ((defined _TIME_H && defined __USE_POSIX199309) || defined __need_timespec)
# define __timespec_defined	1

/* POSIX.4 structure for a time value.  This is like a `struct timeval' but
   has nanoseconds instead of microseconds.  */
struct timespec
  {
    long int tv_sec;		/* Seconds.  */
    long int tv_nsec;		/* Nanoseconds.  */
  };

#endif /* timespec not defined and <time.h> or need timespec.  */
#undef	__need_timespec

#ifdef _TIME_H

# ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
#  if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 5) || __STRICT_ANSI__
#   define __attribute__(Spec) /* empty */
#  endif
/* The __-protected variants of `format' and `printf' attributes
   are accepted by gcc versions 2.6.4 (effectively 2.7) and later.  */
#  if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7)
#   define __format__ format
#   define __printf__ printf
#  endif
# endif

struct tm
  {
    int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
    int tm_min;			/* Minutes.	[0-59] */
    int tm_hour;		/* Hours.	[0-23] */
    int tm_mday;		/* Day.		[1-31] */
    int tm_mon;			/* Month.	[0-11] */
    int tm_year;		/* Year	- 1900.  */
    int tm_wday;		/* Day of week.	[0-6] */
    int tm_yday;		/* Days in year.[0-365]	*/
    int tm_isdst;		/* DST.		[-1/0/1]*/

#ifdef  __USE_BSD
    long int tm_gmtoff;		/* Seconds east of UTC (for current local time).  */
    const char *tm_zone;        /* Timezone abbreviation.  */
#else
    long int __tm_gmtoff;	/* Seconds east of UTC (for current local time).  */
    const char *__tm_zone;      /* Timezone abbreviation.  */
#endif
};

/* Time used by the program so far (user time + system time).
   The result / CLOCKS_PER_SECOND is program time in seconds.  
   Note that this function is not very accurate due to limits of
   the MiNT kernel.  */
__EXTERN clock_t clock __PROTO ((void));

__EXTERN clock_t _clock __PROTO ((void));

/* Return the current time and put it in *TIMER if TIMER is not NULL.  */
__EXTERN time_t time __PROTO ((time_t *__timer));

/* Return the difference between TIME1 and TIME0.  */
__EXTERN double difftime __PROTO ((time_t __time1, time_t __time0))
     __attribute__ ((const));

/* Return the `time_t' representation of TP and normalize TP.  */
__EXTERN time_t mktime __PROTO ((struct tm *__tp));

/* Format TP into S according to FORMAT.
   Write no more than MAXSIZE characters and return the number
   of characters written, or 0 if it would exceed MAXSIZE.  */
__EXTERN size_t strftime __PROTO ((char *__s, size_t __maxsize,
			     const char *__format, const struct tm *__tp));

/* Return the `struct tm' representation of *TIMER
   in Universal Coordinated Time (aka Greenwich Mean Time).  */
__EXTERN struct tm *gmtime __PROTO ((const time_t *__timer));

/* Return the `struct tm' representation
   of *TIMER in the local timezone.  */
__EXTERN struct tm *localtime __PROTO ((const time_t *__timer));

#if defined __USE_POSIX || defined __USE_MISC
/* Return the `struct tm' representation of *TIMER in UTC,
   using *TP to store the result.  */
__EXTERN struct tm *gmtime_r __PROTO ((const time_t *__timer,
				 struct tm *__tp));

/* Return the `struct tm' representation of *TIMER in local time,
   using *TP to store the result.  */
__EXTERN struct tm *localtime_r __PROTO ((const time_t *__timer,
				    struct tm *__tp));
#endif	/* POSIX or misc */

/* Return a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
__EXTERN char *asctime __PROTO ((const struct tm *__tp));

/* Equivalent to `asctime (localtime (timer))'.  */
__EXTERN char *ctime __PROTO ((const time_t *__timer));

#if defined __USE_POSIX || defined __USE_MISC
/* Reentrant versions of the above functions.  */

/* Return in BUF a string of the form "Day Mon dd hh:mm:ss yyyy\n"
   that is the representation of TP in this format.  */
__EXTERN char *asctime_r __PROTO ((const struct tm *__tp, char *__buf));

/* Equivalent to `asctime_r (localtime_r (timer, *TMP*), buf)'.  */
__EXTERN char *ctime_r __PROTO ((const time_t *__timer, char *__buf));
#endif	/* POSIX or misc */


/* Defined in tz.c.  */
#if defined __USE_POSIX
extern char *tzname[2];		/* Current timezone names.  */

/* Set time conversion information from the TZ environment variable.
   If TZ is not defined, a system-dependent default is used.  */
__EXTERN void tzset __PROTO ((void));
#endif

#if defined __USE_BSD
__EXTERN void tzsetwall __PROTO ((void));
#endif

#if defined __USE_SVID || defined __USE_XOPEN
extern int daylight;			/* If daylight-saving time is ever in use.  */
extern long int timezone;	/* Seconds west of UTC (for local standard
                                   time only!)  */
#endif /* SVID or XOPEN */

#ifdef __USE_SVID
/* Set the system time to *WHEN.
   This call is restricted to the superuser.  */
__EXTERN int stime __PROTO ((const time_t *__when));
#endif

__END_DECLS

#endif /* _TIME_H */

#endif /* _TIME_H  */
