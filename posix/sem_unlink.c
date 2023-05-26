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
#include <mint/mintbind.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "semaphoreP.h"


int sem_unlink(const char *name)
{
	int ret;
	struct shmdir_name dirname;
	sem_t *sem_ptr;

	if (__shm_get_name(&dirname, name, 1) != 0)
	{
		__set_errno(ENOENT);
		return -1;
	}

	sem_ptr = sem_open(name, O_RDONLY);
	if (sem_ptr == SEM_FAILED)
	{
		return -1;
	}

	/* Now try removing it.  */
	ret = __unlink(dirname.name);

	if (ret == 0)
	{
		Psemaphore(1, sem_ptr->sem_id, 0);

		Mfree(sem_ptr);
	}

	if (ret < 0 && errno == EPERM)
		__set_errno(EACCES);
	return ret;
}
