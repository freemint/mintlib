/* Copyright (C) 2002-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Ulrich Drepper <drepper@redhat.com>, 2002.

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
#include <stdarg.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "semaphoreP.h"


static inline void __sem_open_init(sem_t *sem, const char *name, unsigned int value)
{
	int i;
	
	sem->value = value << SEM_VALUE_SHIFT;
	sem->nwaiters = 0;

	/* This always is a shared semaphore.  */
	sem->__private = 1;
	sem->sem_id = 0;
	for (i = 0; i < SEM_NAME_MAX && *name; i++)
	{
		sem->sem_id <<= 8;
		sem->sem_id |= (unsigned char)*name;
		name++;
	}
	for (; i < SEM_NAME_MAX; i++)
		sem->sem_id <<= 8;
}


sem_t *sem_open(const char *name, int oflag, ...)
{
	struct shmdir_name dirname;
	sem_t *result;
	int fd;
#ifdef HAVE_PTHREAD_H
	int state;
#endif
	int ret;

	if (__shm_get_name(&dirname, name, 1) != 0)
	{
		return SEM_FAILED;
	}

	/* Disable asynchronous cancellation.  */
#ifdef HAVE_PTHREAD_H
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
#endif

	/* If the semaphore object has to exist simply open it.  */
	if ((oflag & O_CREAT) == 0 || (oflag & O_EXCL) == 0)
	{
	  try_again:
		fd = __open(dirname.name, (oflag & ~(O_CREAT | O_ACCMODE)) | O_NOFOLLOW | O_RDWR);

		if (fd == -1)
		{
			/* If we are supposed to create the file try this next.  */
			if ((oflag & O_CREAT) != 0 && errno == ENOENT)
				goto try_create;

			/* Return.  errno is already set.  */
		} else
		{
			/* Check whether we already have this semaphore mapped and
			   create one if necessary.  */
			result = (sem_t *) Fcntl(fd, 0, SHMGETBLK);
		}
	} else
	{
		/* We have to open a temporary file first since it must have the
		   correct form before we can start using it.  */
		mode_t mode;
		unsigned int value;
		va_list ap;
		char tmpfname[sizeof(SHMDIR) + 10] = SHMDIR "sem.XXXXXX";
		int retries;

	  try_create:
		va_start(ap, oflag);

		mode = va_arg(ap, mode_t);
		value = va_arg(ap, unsigned int);

		va_end(ap);

		if (value > SEM_VALUE_MAX)
		{
			__set_errno(EINVAL);
			result = SEM_FAILED;
			goto out;
		}

		/* Create the initial file content.  */
		result = (sem_t *) Mxalloc(sizeof(sem_t), MX_PREFTTRAM | MX_GLOBAL);
		if (result == NULL)
		{
			__set_errno(ENOMEM);
			goto out;
		}

		__sem_open_init(result, name, value);
		
		retries = 0;

#define NRETRIES 50
		for (;;)
		{
			/* We really want to use mktemp here.  We cannot use mkstemp
			   since the file must be opened with a specific mode.  The
			   mode cannot later be set since then we cannot apply the
			   file create mask.  */
			if (mktemp(tmpfname) == NULL)
			{
				result = SEM_FAILED;
				goto out;
			}

			/* Open the file.  Make sure we do not overwrite anything.  */
			fd = __open(tmpfname, O_RDWR | O_CREAT | O_EXCL, mode);
			if (fd == -1)
			{
				if (errno == EEXIST)
				{
					if (++retries < NRETRIES)
					{
						/* Restore the six placeholder bytes before the
						   null terminator before the next attempt.  */
						memcpy(tmpfname + sizeof(tmpfname) - 7, "XXXXXX", 6);
						continue;
					}

					__set_errno(EAGAIN);
				}

				result = SEM_FAILED;
				goto out;
			}

			/* We got a file.  */
			break;
		}

		/* Map the sem_t structure from the file.  */
 		ret = Fcntl(fd, result, SHMSETBLK);
		if (ret == 0)
		{
			/* Create the file.  Don't overwrite an existing file.  */
			if (__link(tmpfname, dirname.name) != 0)
			{
				/* Undo the mapping.  */
				Mfree(result);

				/* Reinitialize 'result'.  */
				result = SEM_FAILED;

				/* This failed.  If O_EXCL is not set and the problem was
				   that the file exists, try again.  */
				if ((oflag & O_EXCL) == 0 && errno == EEXIST)
				{
					/* Remove the file.  */
					__unlink(tmpfname);

					/* Close the file.  */
					close(fd);

					goto try_again;
				}
			} else
			{
				/* Insert the mapping into the search tree.  This also
				   determines whether another thread sneaked by and already
				   added such a mapping despite the fact that we created it.  */
				/* result = __sem_check_add_mapping(name, fd, result); */
				ret = Psemaphore(0, result->sem_id, 0);
		
				if (ret != 0)
				{
					__set_errno(-ret);
					Mfree(result);
					result = SEM_FAILED;
					goto out;
				}
			}
		}

		/* Now remove the temporary name.  This should never fail.  If
		   it fails we leak a file name.  Better fix the kernel.  */
		__unlink(tmpfname);
	}

	/* We don't need the file descriptor anymore.  */
	if (fd != -1)
	{
		/* Do not disturb errno.  */
		int save = errno;

		__close(fd);
		errno = save;
	}

  out:
#ifdef HAVE_PTHREAD_H
	__pthread_setcancelstate(state, NULL);
#endif

	return result;
}
