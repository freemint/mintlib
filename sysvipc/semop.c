/* Copyright (C) 1995, 1996, 1997, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, August 1995.

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
#include <mintbind.h>

__typeof__(semop) __semop;

/* Perform user-defined atomical operation of array of semaphores.  */

int
__semop (int semid, struct sembuf *sops, size_t nsops)
{
	int ret;
	
	ret = Psemop (semid, sops, nsops);
	if (ret < 0) {
		__set_errno (-ret);
		return -1;
	}
	return ret;
}

weak_alias (__semop, semop)
