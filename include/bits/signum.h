/* Signal number definitions.  FreeMiNT version.
   Copyright (C) 1995, 1996, 1997, 1998, 1999 Free Software Foundation, Inc.
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
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#ifdef	_SIGNAL_H


#define	__NSIG		32		/* number of signals recognized */

#define	SIGNULL		0		/* not really a signal */
#define SIGHUP		1		/* hangup signal */
#define SIGINT		2		/* sent by ^C */
#define SIGQUIT		3		/* quit signal */
#define SIGILL		4		/* illegal instruction */
#define SIGTRAP		5		/* trace trap */
#define SIGABRT		6		/* abort signal */
# define SIGIOT SIGABRT
#define SIGPRIV		7		/* privilege violation */
# define SIGEMT SIGPRIV
#define SIGFPE		8		/* divide by zero */
#define SIGKILL		9		/* cannot be ignored */
#define SIGBUS		10		/* bus error */
#define SIGSEGV		11		/* illegal memory reference */
#define SIGSYS		12		/* bad system call */
#define SIGPIPE		13		/* broken pipe */
#define SIGALRM		14		/* alarm clock */
#define SIGTERM		15		/* software termination signal */

#define SIGURG		16		/* urgent condition on I/O channel */
#define SIGSTOP		17		/* stop signal not from terminal */
#define SIGTSTP		18		/* stop signal from terminal */
#define SIGCONT		19		/* continue stopped process */
#define SIGCHLD		20		/* child stopped or exited */
#define SIGTTIN		21		/* read by background process */
#define SIGTTOU		22		/* write by background process */
#define SIGIO		23		/* I/O possible on a descriptor */
# define SIGPOLL SIGIO
#define SIGXCPU		24		/* CPU time exhausted */
#define SIGXFSZ		25		/* file size limited exceeded */
#define SIGVTALRM	26		/* virtual timer alarm */
#define SIGPROF		27		/* profiling timer expired */
#define SIGWINCH	28		/* window size changed */
#define SIGUSR1		29		/* user signal 1 */
#define SIGUSR2		30		/* user signal 2 */
#define SIGPWR		31		/* power failure restart (System V) */

#ifndef BADSIG
#define BADSIG		SIG_ERR
#endif


#define       SIG_ERR	((__sighandler_t)-1L)
#define       SIG_DFL	((__sighandler_t) 0L)
#define       SIG_IGN	((__sighandler_t) 1L)
#ifdef __USE_UNIX98
# define      SIG_HOLD	((__sighandler_t) 2L)	/* Add signal to hold mask.  */
#endif


#ifdef __USE_MISC
# define SignalBad	SIG_ERR
# define SignalDefault	SIG_DFL
# define SignalIgnore	SIG_IGN
#endif


#endif	/* <signal.h> included.  */
