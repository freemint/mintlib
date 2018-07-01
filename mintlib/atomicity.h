/* Low-level functions for atomic operations.  Stub version.
   Copyright (C) 1997 Free Software Foundation, Inc.
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

#ifndef _ATOMICITY_H
#define _ATOMICITY_H	1

#include <inttypes.h>

#if defined(__mc68020__) || defined(__mc68030__) || defined(__mc68040__) || defined(__mc68060__)
# include "atomicity-68020.h"
#else
static inline int
__attribute__ ((unused))
exchange_and_add (uint32_t *mem, int val)
{
  int result = *mem;
  *mem += val;
  return result;
}

static inline void
__attribute__ ((unused))
atomic_add (uint32_t *mem, int val)
{
  *mem += val;
}

static inline int
__attribute__ ((unused))
compare_and_swap (long int *p, long int oldval, long int newval)
{
  if (*p != oldval)
    return 0;

  *p = newval;
  return 1;
}
#endif

#endif /* atomicity.h */
