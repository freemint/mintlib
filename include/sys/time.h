/*  sys/time.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef	_SYS_TIME_H
#if !defined(__need_timeval)
# define	_SYS_TIME_H 1

#ifndef _FEATURES_H
# include <features.h>
#endif

#ifndef _TIME_H
# include <time.h>
#endif
#ifndef _SYS_SELECT_H
# include <sys/select.h>
#endif

__BEGIN_DECLS

/* Macros for converting between `struct timeval' and `struct timespec'.  */
#define TIMEVAL_TO_TIMESPEC(tv, ts) {                                   \
        (ts)->tv_sec = (tv)->tv_sec;                                    \
        (ts)->tv_nsec = (tv)->tv_usec * 1000;                           \
}
#define TIMESPEC_TO_TIMEVAL(tv, ts) {                                   \
        (tv)->tv_sec = (ts)->tv_sec;                                    \
        (tv)->tv_usec = (ts)->tv_nsec / 1000;                           \
}

#endif /* not __need_timeval */

#ifndef _STRUCT_TIMEVAL
# define _STRUCT_TIMEVAL 1
/* Struct representing a calendar time.  */
struct timeval {
  long int tv_sec;  /* Seconds since epoch (equiv. to time_t).  */
  long int tv_usec; /* Fractional second value in microseconds.  */
};
#endif

#if !defined(__need_timeval) || defined(_SYS_TIME_H)

/* Structure crudely representing a timezone.
   This is obsolete and should never be used.  */
struct timezone
  {
    int tz_minuteswest;		/* Minutes west of GMT.  */
    int tz_dsttime;		/* Nonzero if DST is ever in effect.  */
  };

/* Get the current time of day and timezone information,
   putting it into *TV and *TZ.  If TZ is NULL, *TZ is not filled.
   Returns 0 on success, -1 on errors.
   NOTE: This form of timezone information is obsolete.
   Use the functions and variables declared in <time.h> instead.  */
__EXTERN int gettimeofday __PROTO ((struct timeval *__tv,
			      struct timezone *__tz));
__EXTERN int __gettimeofday __PROTO ((struct timeval *__tv,
			      struct timezone *__tz));

/* Set the current time of day and timezone information.
   This call is restricted to the super-user.  */
__EXTERN int settimeofday __PROTO ((const struct timeval *__tv,
			      const struct timezone *__tz));
__EXTERN int __settimeofday __PROTO ((const struct timeval *__tv,
			      const struct timezone *__tz));

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

/* Set *VALUE to the current setting of timer WHICH.
   Return 0 on success, -1 on errors.  */
__EXTERN int getitimer __PROTO ((enum __itimer_which __which,
			   struct itimerval *__value));

/* Set the timer WHICH to *NEW.  If OLD is not NULL,
   set *OLD to the old value of timer WHICH.
   Returns 0 on success, -1 on errors.  */
__EXTERN int setitimer __PROTO ((enum __itimer_which __which,
			   const struct itimerval *__new,
			   struct itimerval *__old));

/* Change the access time of FILE to TVP[0] and
   the modification time of FILE to TVP[1].  */
__EXTERN int utimes __PROTO ((const char *__file, struct timeval __tvp[2]));


/* Convenience macros for operations on timevals.
   NOTE: `timercmp' does not work for >= or <=.  */
#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timerclear(tvp)		((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define	timercmp(a, b, CMP) 						      \
  (((a)->tv_sec == (b)->tv_sec) ? 					      \
   ((a)->tv_usec CMP (b)->tv_usec) : 					      \
   ((a)->tv_sec CMP (b)->tv_sec))
#define	timeradd(a, b, result)						      \
  do {									      \
    (result)->tv_sec = (a)->tv_sec + (b)->tv_sec;			      \
    (result)->tv_usec = (a)->tv_usec + (b)->tv_usec;			      \
    if ((result)->tv_usec >= 1000000)					      \
      {									      \
	++(result)->tv_sec;						      \
	(result)->tv_usec -= 1000000;					      \
      }									      \
  } while (0)
#define	timersub(a, b, result)						      \
  do {									      \
    (result)->tv_sec = (a)->tv_sec - (b)->tv_sec;			      \
    (result)->tv_usec = (a)->tv_usec - (b)->tv_usec;			      \
    if ((result)->tv_usec < 0) {					      \
      --(result)->tv_sec;						      \
      (result)->tv_usec += 1000000;					      \
    }									      \
  } while (0)

__END_DECLS

#endif /* not __need_timeval */

#undef __need_timeval

#endif /* SYS_TIME_H */
