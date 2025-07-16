/* `fd_set' type and related macros, and `select'/`pselect' declarations.
   Copyright (C) 1996, 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Guido Flohr <guido@freemint.de>.  */

/*	POSIX 1003.1g: 6.2 Select from File Descriptor Sets <sys/select.h>  */

#ifndef _SYS_SELECT_H
# define _SYS_SELECT_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

/* Get definition of needed basic types.  */
#include <bits/types.h>

/* Get definition of timer specification structures.  */
#define __need_timespec
#include <time.h>

__BEGIN_DECLS

/* Get definition of needed basic types.  */
#include <bits/types.h>

/* Get __FD_* definitions.  */
#include <bits/select.h>

/* Get __sigset_t.  */
#include <bits/sigset.h>

/* Get definition of struct timeval.  */
#define __need_timeval
#include <bits/time.h>

typedef __fd_mask fd_mask;

/* Representation of a set of file descriptors.  */
typedef __fd_set fd_set;

/* Maximum number of file descriptors in `fd_set'.  */
#define	FD_SETSIZE		__FD_SETSIZE

#ifdef __USE_MISC
/* Number of bits per word of `fd_set' (some code assumes this is 32).  */
# define NFDBITS		__NFDBITS
#endif


/* Access macros for `fd_set'.  */
#define	FD_SET(fd, fdsetp)	__FD_SET ((fd), (fdsetp))
#define	FD_CLR(fd, fdsetp)	__FD_CLR ((fd), (fdsetp))
#define	FD_ISSET(fd, fdsetp)	__FD_ISSET ((fd), (fdsetp))
#define	FD_ZERO(fdsetp)		__FD_ZERO (fdsetp)


/* Check the first NFDS descriptors each in READFDS (if not NULL) for read
   readiness, in WRITEFDS (if not NULL) for write readiness, and in EXCEPTFDS
   (if not NULL) for exceptional conditions.  If TIMEOUT is not NULL, time out
   after waiting the interval specified therein.  Returns the number of ready
   descriptors, or -1 for errors.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
#ifndef __USE_TIME_BITS64
extern int select (int __nfds, fd_set *__readfds,
		   fd_set *__writefds, fd_set *__exceptfds,
		   struct timeval *__timeout) __THROW;
#else
extern int __REDIRECT (select,
                       (int __nfds, fd_set *__restrict __readfds,
                        fd_set *__restrict __writefds,
                        fd_set *__restrict __exceptfds,
                        struct timeval *__restrict __timeout),
                       __select64);
#endif

#ifdef __USE_GNU
/* XXX Once/if POSIX.1g gets official this prototype will be available
   when defining __USE_POSIX.  */
/* Same as above only that the TIMEOUT value is given with higher
   resolution and a sigmask which is been set temporarily.  This version
   should be used.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
# ifndef __USE_TIME_BITS64
extern int pselect (int __nfds, fd_set *__readfds,
		    fd_set *__writefds, fd_set *__exceptfds,
		    const struct timespec *__timeout,
		    const __sigset_t *__sigmask) __THROW;
#else
extern int __REDIRECT (pselect,
                       (int __nfds, fd_set *__restrict __readfds,
                        fd_set *__restrict __writefds,
                        fd_set *__restrict __exceptfds,
                        const struct timespec *__restrict __timeout,
                        const __sigset_t *__restrict __sigmask),
                       __pselect64);
#endif
#endif

__END_DECLS

#endif /* sys/select.h */
