/* Copyright (C) 1995, 1996, 1997, 1998
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

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#ifndef _SYS_SEM_H
# error "Never include <bits/sem.h> directly; use <sys/sem.h> instead."
#endif

#ifndef _BITS_TYPES_H
# include <bits/types.h>
#endif

/* Flags for `semop'.  */
#define SEM_UNDO	0x1000		/* undo the operation on exit */

/* Commands for `semctl'.  */
#define GETPID		11		/* get sempid */
#define GETVAL		12		/* get semval */
#define GETALL		13		/* get all semval's */
#define GETNCNT		14		/* get semncnt */
#define GETZCNT		15		/* get semzcnt */
#define SETVAL		16		/* set semval */
#define SETALL		17		/* set all semval's */


/* Data structure describing a set of semaphores.  */
struct semid_ds
{
  struct ipc_perm sem_perm;		/* operation permission struct */
  unsigned short int sem_nsems;		/* number of semaphores in set */
#ifdef __USE_TIME_BITS64
  __time64_t sem_otime;			/* last semop() time */
  __time64_t sem_ctime;			/* last time changed by semctl() */
#else
  __int32_t __sem_otime_high;
  __time_t sem_otime;			/* last semop() time */
  __int32_t __sem_ctime_high;
  __time_t sem_ctime;			/* last time changed by semctl() */
#endif
  unsigned long int __unused3;
  unsigned long int __unused4;
};

/* The user should define a union like the following to use it for arguments
   for `semctl'.

   union semun
   {
     int val;				<= value for SETVAL
     struct semid_ds *buf;		<= buffer for IPC_STAT & IPC_SET
     unsigned short int *array;	<= array for GETALL & SETALL
     struct seminfo *__buf;		<= buffer for IPC_INFO
   };

   Previous versions of this file used to define this union but this is
   incorrect.  One can test the macro _SEM_SEMUN_UNDEFINED to see whether
   one must define the union or not.  */
#define _SEM_SEMUN_UNDEFINED	1
