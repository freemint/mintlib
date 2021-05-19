/* Internal definitions and declarations for UTMP functions.
   Copyright (C) 1996 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@cygnus.com>
   and Paul Janzen <pcj@primenet.com>, 1996.

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

#ifndef _UTMP_PRIVATE_H
#define _UTMP_PRIVATE_H	1

#include <utmp.h>

/* The structure describing the functions in a backend.  */
struct utfuncs
{
  int (*setutent) (void);
  int (*getutent_r) (struct utmp *, struct utmp **);
  int (*getutid_r) (const struct utmp *, struct utmp *, struct utmp **);
  int (*getutline_r) (const struct utmp *, struct utmp *, struct utmp **);
  struct utmp *(*pututline) (const struct utmp *);
  void (*endutent) (void);
  int (*updwtmp) (const char *, const struct utmp *);
};

/* The tables from the services.  */
extern struct utfuncs __libc_utmp_file_functions;
extern struct utfuncs __libc_utmp_unknown_functions;

/* Currently selected backend.  */
extern struct utfuncs *__libc_utmp_jump_table;

/* Current file name.  */
extern const char *__libc_utmp_file_name;

#endif /* utmp-private.h */
