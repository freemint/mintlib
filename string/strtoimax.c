/* Convert string to maximal integer.
   Copyright (C) 1997 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>, 1997.

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

#include <inttypes.h>
#include <stdlib.h>

# ifndef __strtoll_internal_defined
__extension__
extern long long int __strtoll_internal __P ((__const char *__restrict __nptr,
					      char **__restrict __endptr,
					      int __base, int __group));
#  define __strtoll_internal_defined	1
# endif

intmax_t
strtoimax (const char *__restrict nptr, char **__restrict endptr, int base)
{
  return __strtoll_internal (nptr, endptr, base, 0);
}
