/* Copyright (C) 1995-1999, 2000 Free Software Foundation, Inc.
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

#ifndef _SYS_SHM_H
#define _SYS_SHM_H	1

#ifndef	_FEATURES_H
# include <features.h>
#endif

#define __need_size_t
#include <stddef.h>

/* Get common definition of System V style IPC.  */
#ifndef _SYS_IPC_H
# include <sys/ipc.h>
#endif

/* Define types required by the standard.  */
#define __need_time_t
#include <time.h>

__BEGIN_DECLS

/* Get system dependent definition of `struct shmid_ds' and more.  */
#include <bits/shm.h>

#ifdef __USE_XOPEN
# ifndef __pid_t_defined
typedef __pid_t pid_t;
#  define __pid_t_defined
# endif
#endif	/* X/Open */

/* Segment low boundary address multiple.  */
#define SHMLBA		(__getpagesize ())
extern int __getpagesize (void) __THROW __attribute__ ((__const__));


/* The following System V style IPC functions implement a shared memory
   facility.  The definition is found in XPG4.2.  */

/* Shared memory control operation.  */
extern int shmctl (int __shmid, int __cmd, struct shmid_ds *__buf) __THROW;

/* Get shared memory segment.  */
extern int shmget (key_t __key, size_t __size, int __shmflg) __THROW;

/* Attach shared memory segment.  */
extern void *shmat (int __shmid, __const void *__shmaddr, int __shmflg)
     __THROW;

/* Detach shared memory segment.  */
extern int shmdt (__const void *__shmaddr) __THROW;

__END_DECLS

#endif /* sys/shm.h */
