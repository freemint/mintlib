/* __sig_atomic_t, __sigset_t, and related definitions.  Generic/BSD version.
   Copyright (C) 1991, 1992, 1994, 1996, 1997, 2007
   Free Software Foundation, Inc.
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

/* We only want to define these functions if <signal.h> was actually
   included; otherwise we were included just to define the types.  Since we
   are namespace-clean, it wouldn't hurt to define extra macros.  But
   trouble can be caused by functions being defined (e.g., any global
   register vars declared later will cause compilation errors).  */

#if !defined _SIGSET_H_fns
#define _SIGSET_H_fns 1

#include <bits/types/sigset_t.h>

/* Return a mask that includes SIG only.  The cast to `sigset_t' avoids
   overflow if `sigset_t' is wider than `int'.  */
#define	__sigmask(sig)	(((__sigset_t) 1) << (sig))

#define	__sigemptyset(set)	((*(set) = (__sigset_t) 0), 0)
#define	__sigfillset(set)	((*(set) = ~(__sigset_t) 0), 0)

#ifdef _GNU_SOURCE
# define __sigisemptyset(set)	(*(set) == (__sigset_t) 0)
# define __sigandset(dest, left, right) \
				((*(dest) = (*(left) & *(right))), 0)
# define __sigorset(dest, left, right) \
				((*(dest) = (*(left) | *(right))), 0)
#endif

/* These functions needn't check for a bogus signal number -- error
   checking is done in the non __ versions.  */

# define __SIGSETFN(NAME, BODY, CONST)					      \
  static __inline__ int							      \
  NAME (CONST __sigset_t *__set, int __sig)				      \
  {									      \
    __sigset_t __mask = __sigmask (__sig);				      \
    return BODY;							      \
  }

__SIGSETFN (__sigismember, (*__set & __mask) ? 1 : 0, __const)
__SIGSETFN (__sigaddset, ((*__set |= __mask), 0), )
__SIGSETFN (__sigdelset, ((*__set &= ~__mask), 0), )

# undef __SIGSETFN


#endif /* ! _SIGSET_H_fns.  */
