/*  pty.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _PTY_H
#define _PTY_H	1  /* Allow multiple inclusion.  */

#ifndef _FEATURES_H
# include <features.h>
#endif

#include <termios.h>

__BEGIN_DECLS

/* Create pseudo tty master slave pair with NAME and set terminal
   attributes according to TERMP and WINP and return handles for both
   ends in AMASTER and ASLAVE.  */
__EXTERN int openpty __P ((int *__amaster, int *__aslave, char *__name,
			   struct termios *__termp, struct winsize *__winp));

/* Create child process and establish the slave pseudo terminal as the
   child's controlling terminal.  */
__EXTERN int forkpty __P ((int *__amaster, char *__name,
			 struct termios *__termp, struct winsize *__winp));

__END_DECLS

#endif	/* pty.h */
