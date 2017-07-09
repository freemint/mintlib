/*  sys/time.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _SYS_TIME_H
# define _SYS_TIME_H 1

#ifndef _FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

#include <bits/types.h>
#define __need_time_t
#include <time.h>
#define __need_timeval
#include <bits/time.h>

#ifndef _SYS_SELECT_H
# include <sys/select.h>
#endif

#ifndef __suseconds_t_defined
typedef __suseconds_t suseconds_t;
# define __suseconds_t_defined
#endif


#ifdef __USE_GNU
/* Macros for converting between `struct timeval' and `struct timespec'.  */
# define TIMEVAL_TO_TIMESPEC(tv, ts) {                                   \
        (ts)->tv_sec = (tv)->tv_sec;                                    \
        (ts)->tv_nsec = (tv)->tv_usec * 1000;                           \
}
# define TIMESPEC_TO_TIMEVAL(tv, ts) {                                   \
        (tv)->tv_sec = (ts)->tv_sec;                                    \
        (tv)->tv_usec = (ts)->tv_nsec / 1000;                           \
}
#endif


#ifdef __USE_BSD
/* Structure crudely representing a timezone.
   This is obsolete and should never be used.  */
struct timezone
  {
    int tz_minuteswest;		/* Minutes west of GMT.  */
    int tz_dsttime;		/* Nonzero if DST is ever in effect.  */
  };
struct __mint_timezone
  {
    long tz_minuteswest;		/* Minutes west of GMT.  */
    long tz_dsttime;		/* Nonzero if DST is ever in effect.  */
  };

typedef struct timezone *__restrict __timezone_ptr_t;
#else
typedef void *__restrict __timezone_ptr_t;
#endif

/* Get the current time of day and timezone information,
   putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
   Returns 0 on success, -1 on errors.
   NOTE: This form of timezone information is obsolete.
   Use the functions and variables declared in <time.h> instead.  */
extern int gettimeofday (struct timeval *__tv,
			 struct timezone *__tz) __THROW;
extern int __gettimeofday (struct timeval *__tv,
			   struct timezone *__tz) __THROW;

#ifdef __USE_BSD
/* Set the current time of day and timezone information.
   This call is restricted to the super-user.  */
extern int settimeofday (const struct timeval *__tv,
			      const struct timezone *__tz) __THROW;
extern int __settimeofday (const struct timeval *__tv,
			      const struct timezone *__tz) __THROW;

/* Adjust the current time of day by the amount in DELTA.
   If OLDDELTA is not NULL, it is filled in with the amount
   of time adjustment remaining to be done from the last `adjtime' call.
   This call is restricted to the super-user.  */
extern int adjtime (__const struct timeval *__delta,
		    struct timeval *__olddelta) __THROW;
extern int __adjtime (__const struct timeval *__delta,
		    struct timeval *__olddelta) __THROW;
#endif


/* Values for the first argument to `getitimer' and `setitimer'.  */
enum __itimer_which
  {
    /* Timers run in real time.  */
    ITIMER_REAL = 0,
#define ITIMER_REAL ITIMER_REAL
    /* Timers run only when the process is executing.  */
    ITIMER_VIRTUAL = 1,
#define ITIMER_VIRTUAL ITIMER_VIRTUAL
    /* Timers run when the process is executing and when
       the system is executing on behalf of the process.  */
    ITIMER_PROF = 2
#define ITIMER_PROF ITIMER_PROF
  };

/* Type of the second argument to `getitimer' and
   the second and third arguments `setitimer'.  */
struct itimerval
  {
    /* Value to put into `it_value' when the timer expires.  */
    struct timeval it_interval;
    /* Time to the next timer expiration.  */
    struct timeval it_value;
  };

#if defined __USE_GNU && !defined __cplusplus
/* Use the nicer parameter type only in GNU mode and not for C++ since the
   strict C++ rules prevent the automatic promotion.  */
typedef enum __itimer_which __itimer_which_t;
#else
typedef int __itimer_which_t;
#endif

/* Set *VALUE to the current setting of timer WHICH.
   Return 0 on success, -1 on errors.  */
extern int getitimer (__itimer_which_t __which,
		      struct itimerval *__value) __THROW;

/* Set the timer WHICH to *NEW.  If OLD is not NULL,
   set *OLD to the old value of timer WHICH.
   Returns 0 on success, -1 on errors.  */
extern int setitimer (__itimer_which_t __which,
		      __const struct itimerval *__restrict __new,
		      struct itimerval *__restrict __old) __THROW;

/* Change the access time of FILE to TVP[0] and
   the modification time of FILE to TVP[1].  */
extern int utimes (__const char *__file, __const struct timeval __tvp[2])
     __THROW;


#ifdef __USE_BSD
/* Convenience macros for operations on timevals.
   NOTE: `timercmp' does not work for >= or <=.  */
# define timerisset(tvp)	((tvp)->tv_sec || (tvp)->tv_usec)
# define timerclear(tvp)	((tvp)->tv_sec = (tvp)->tv_usec = 0)
# define timercmp(a, b, CMP) 						      \
  (((a)->tv_sec == (b)->tv_sec) ? 					      \
   ((a)->tv_usec CMP (b)->tv_usec) : 					      \
   ((a)->tv_sec CMP (b)->tv_sec))
# define timeradd(a, b, result)						      \
  do {									      \
    (result)->tv_sec = (a)->tv_sec + (b)->tv_sec;			      \
    (result)->tv_usec = (a)->tv_usec + (b)->tv_usec;			      \
    if ((result)->tv_usec >= 1000000)					      \
      {									      \
	++(result)->tv_sec;						      \
	(result)->tv_usec -= 1000000;					      \
      }									      \
  } while (0)
# define timersub(a, b, result)						      \
  do {									      \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;			      \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec;			      \
    if ((result)->tv_usec < 0) {					      \
      --(result)->tv_sec;						      \
      (result)->tv_usec += 1000000;					      \
    }									      \
  } while (0)
#endif	/* BSD */

__END_DECLS

#endif /* sys/time.h */
