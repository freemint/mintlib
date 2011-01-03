/* O_*, F_*, FD_* bit values for stub configuration.
   Copyright (C) 1991, 1992, 1997, 2000 Free Software Foundation, Inc.
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

/* These values should be changed as appropriate for your system.  */

#ifndef	_FCNTL_H
# error "Never use <bits/fcntl.h> directly; include <fcntl.h> instead."
#endif


/* File access modes for `open' and `fcntl'.  */
#define	O_RDONLY	0	/* Open read-only.  */
#define	O_WRONLY	1	/* Open write-only.  */
#define	O_RDWR		2	/* Open read/write.  */


/* Bits OR'd into the second argument to open.  */
#define	O_CREAT		0x200		/* create new file if needed */
#define	O_TRUNC		0x400		/* make file 0 length */
#define	O_EXCL		0x800		/* error if file exists */
#define O_NOCTTY	0x4000		/* do not open new controlling tty */

#ifdef __USE_GNU
# define O_NOATIME	0x04		/* Do not set atime.  */
# define O_DIRECTORY	0x10000		/* Must be a directory.	 */
# define O_NOFOLLOW	0x20000		/* Do not follow links.	 */
#endif

/* File status flags for `open' and `fcntl'.  */
#define	O_APPEND	0x1000		/* position at EOF */
#define _REALO_APPEND	0x08		/* this is what MiNT uses */
#define	O_NONBLOCK	0x100		/* Non-blocking I/O */

#ifdef __USE_BSD
# define O_NDELAY	O_NONBLOCK
#endif


/* Mask for file access modes.  This is system-dependent in case
   some system ever wants to define some other flavor of access.  */
#define	O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)

/* Values for the second argument to `fcntl'.  */
#define	F_DUPFD	  	0	/* Duplicate file descriptor.  */
#define	F_GETFD		1	/* Get file descriptor flags.  */
#define	F_SETFD		2	/* Set file descriptor flags.  */
#define	F_GETFL		3	/* Get file status flags.  */
#define	F_SETFL		4	/* Set file status flags.  */
#define	F_GETLK		5	/* Get record locking info.  */
#define	F_SETLK		6	/* Set record locking info.  */
#define	F_SETLKW	7	/* Set record locking info, wait.  */
#if defined __USE_BSD || defined __USE_XOPEN2K
# define F_GETOWN	8	/* Get owner (receiver of SIGIO).  */
# define F_SETOWN	9	/* Set owner (receiver of SIGIO).  */
#endif

/* File descriptor flags used with F_GETFD and F_SETFD.  */
#define	FD_CLOEXEC	1	/* Close on exec.  */

#ifdef __USE_GNU
# define F_DUPFD_CLOEXEC 1030	/* Duplicate file descriptor with
				   close-on-exit set.  */
#endif

#include <bits/types.h>

/* The structure describing an advisory lock.  This is the type of the third
   argument to `fcntl' for the F_GETLK, F_SETLK, and F_SETLKW requests.  */
struct flock
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.  */
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
    long int  l_start;	/* Offset where the lock begins.  */
    long int  l_len;	/* Size of the locked area; zero means until EOF.  */
    short int l_pid;	/* Process holding the lock.  */
  };

/* Values for the `l_type' field of a `struct flock'.  */
#define	F_RDLCK	O_RDONLY	/* Read lock.  */
#define	F_WRLCK	O_WRONLY	/* Write lock.  */
#define	F_UNLCK	3		/* Remove lock.  */

/* Advise to `posix_fadvise'.  */
#ifdef __USE_XOPEN2K
# define POSIX_FADV_NORMAL	0 /* No further special treatment.  */
# define POSIX_FADV_RANDOM	1 /* Expect random page references.  */
# define POSIX_FADV_SEQUENTIAL	2 /* Expect sequential page references.  */
# define POSIX_FADV_WILLNEED	3 /* Will need these pages.  */
# define POSIX_FADV_DONTNEED	4 /* Don't need these pages.  */
# define POSIX_FADV_NOREUSE	5 /* Data will be accessed once.  */
#endif


/* file sharing modes (not POSIX) */
#define O_COMPAT	0x00	/* old TOS compatibility mode */
#define O_DENYRW	0x10	/* deny both reads and writes */
#define O_DENYW		0x20
#define O_DENYR		0x30
#define O_DENYNONE	0x40	/* don't deny anything */
#define O_SHMODE	0x70	/* mask for file sharing mode */
#define O_SYNC		0x00	/* sync after writes (not implemented) */


/* smallest valid gemdos handle
 * note handle is only word (16 bit) negative, not long negative,
 * and since Fopen etc are declared as returning long in osbind.h
 * the sign-extension will not happen -- thanks ers
 */
#ifdef __MSHORT__
#define __SMALLEST_VALID_HANDLE (-3)
#else
#define __SMALLEST_VALID_HANDLE (0)
#endif
