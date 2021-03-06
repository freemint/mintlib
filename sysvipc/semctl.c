/* Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, August 1995.

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

#include <sys/sem.h>
#include <errno.h>
#include <stdarg.h>
#include <mintbind.h>

__typeof__(semctl) __semctl;

/* Define a `union semun' suitable for Linux here.  */
union semun
{
  int val;			/* value for SETVAL */
  struct semid_ds *buf;		/* buffer for IPC_STAT & IPC_SET */
  unsigned short int *array;	/* array for GETALL & SETALL */
  struct seminfo *__buf;	/* buffer for IPC_INFO */
};

int
__semctl (int semid, int semnum, int cmd, ...)
{
	int ret;
	union semun arg;
	va_list ap;
	
	va_start (ap, cmd);
	arg = va_arg (ap, union semun);
	va_end (ap);
	
	ret = Psemctl (semid, semnum, cmd, &arg);
	if (ret < 0) {
		__set_errno (-ret);
		return -1;
	}
	return ret;
}

weak_alias (__semctl, semctl)
