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

#include <stdlib.h>
#include <mint/mintbind.h>
#include <errno.h>
#include <time.h>
#include "semaphoreP.h"

static inline void __sem_open_init(struct new_sem *sem, unsigned value)
{
	sem->value = value << SEM_VALUE_SHIFT;
	sem->nwaiters = 0;

	/* This always is a shared semaphore.  */
	sem->private = 1;
}
