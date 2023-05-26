/* Copyright (C) 2002-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Adapted to MiNTLib by Thorsten Otto */

#include <stdlib.h>
#include <errno.h>
#include <mint/mintbind.h>
#include "semaphoreP.h"


int sem_close(sem_t *sem_ptr)
{
/*
	if (sem_ptr == SEM_FAILED)
	{
		__set_errno(EINVAL);
		return -1;
	}
*/

	Mfree(sem_ptr);

	return 0;
}
