/*  sys/timeb.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the FreeType project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _SYS_TIMEB_H
#define _SYS_TIMEB_H	1

#ifndef _TIME_H
# ifndef __need_time_t
#  define __need_time_t
# endif
# include <time.h>
# undef __need_time_t
#endif

#ifndef _COMPILER_H
# include <compiler.h>
#endif

/* Structure returned by the `ftime' function.  */

struct timeb {
  time_t time;		        /* Seconds since epoch, as from `time'.  */
  unsigned short int millitm;	/* Additional milliseconds.  */
  short int timezone;		/* Minutes west of GMT.  */
  short int dstflag;		/* Nonzero if Daylight Savings Time used.  */
};

/* For compatibility reasons.  Actually obsoleted by gettimeofday().  */
__EXTERN int ftime __PROTO((struct timeb *__timebuf));

#endif	/* _SYS_TIMEB_h */
