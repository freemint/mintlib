/* Determine directory for shm/sem files.  Generic POSIX version.
   Copyright (C) 2014-2023 Free Software Foundation, Inc.
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
#include <errno.h>
#include <string.h>
#include "semaphoreP.h"

int __shm_get_name(struct shmdir_name *result, const char *name, int sem_prefix)
{
	size_t namelen;

	while (name[0] == '/')
		++name;
	namelen = strlen(name);
	if (namelen == 0 || strchr(name, '/') != NULL || namelen > SEM_NAME_MAX)
	{
		__set_errno(EINVAL);
		return -1;
	}

	/* do not allow system reserved names */
	if (name[0] == '_')
	{
		__set_errno(ENOENT);
		return -1;
	}

	strcpy(result->name, SHMDIR);
	if (sem_prefix)
		strcat(result->name, "sem.");
	strcat(result->name, name);

	return 0;
}
