/* Copyright (C) 1991-2013 Free Software Foundation, Inc.
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
   <http://www.gnu.org/licenses/>.  */

/* Modified for MiNTLib by Guido Flohr, <guido@freemint.de>.  */

#include <stdio.h>
#include <printf.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <sys/param.h>

#ifndef COMPILE_WPRINTF
# define CHAR_T		char
# define UCHAR_T	unsigned char
# define INT_T		int
# define L_(Str)	Str
# define ISDIGIT(Ch)	isdigit (Ch)
# define ISASCII(Ch)	isascii (Ch)
# define MBRLEN(Cp, L, St) mbrlen (Cp, L, St)

# ifdef USE_IN_LIBIO
#  define PUT(F, S, N)	_IO_sputn (F, S, N)
#  define PAD(Padchar)							      \
  if (width > 0)							      \
    done += _IO_padn (s, Padchar, width)
# else
#  define PUTC(C, F)	putc (C, F)
ssize_t __printf_pad __P ((FILE *, char pad, size_t n));
# define PAD(Padchar)							      \
  if (width > 0)							      \
    { if (__printf_pad (s, Padchar, width) == -1)			      \
	return -1; else done += width; }
# endif
#else
# define vfprintf	vfwprintf
# define CHAR_T		wchar_t
# define UCHAR_T	uwchar_t
# define INT_T		wint_t
# define L_(Str)	L##Str
# define ISDIGIT(Ch)	iswdigit (Ch)

# ifdef USE_IN_LIBIO
# define PUT(F, S, N)	_IO_sputn (F, S, N)
# define PAD(Padchar)							      \
  if (width > 0)							      \
    done += _IO_wpadn (s, Padchar, width)
# else
#  define PUTC(C, F)	wputc (C, F)
ssize_t __wprintf_pad __P ((FILE *, wchar_t pad, size_t n));
# define PAD(Padchar)							      \
  if (width > 0)							      \
    { if (__wprintf_pad (s, Padchar, width) == -1)			      \
	return -1; else done += width; }
# endif
#endif

#define DONT_NEED_READ_INT
#include "printf-parse.h"


size_t
parse_printf_format (const char *fmt, size_t n, int *argtypes)
{
  size_t nargs;			/* Number of arguments.  */
  size_t max_ref_arg;		/* Highest index used in a positional arg.  */
  struct printf_spec spec;
  const unsigned char *f = (const unsigned char *) fmt;

  nargs = 0;
  max_ref_arg = 0;

  /* Search for format specifications.  */
  for (f = find_spec (f); *f != '\0'; f = spec.next_fmt)
    {
      /* Parse this spec.  */
      nargs += parse_one_spec (f, nargs, &spec, &max_ref_arg);

      /* If the width is determined by an argument this is an int.  */
      if (spec.width_arg != -1 && (size_t) spec.width_arg < n)
	argtypes[spec.width_arg] = PA_INT;

      /* If the precision is determined by an argument this is an int.  */
      if (spec.prec_arg != -1 && (size_t) spec.prec_arg < n)
	argtypes[spec.prec_arg] = PA_INT;

      if ((size_t) spec.data_arg < n)
	switch (spec.ndata_args)
	  {
	  case 0:		/* No arguments.  */
	    break;
	  case 1:		/* One argument; we already have the type.  */
	    argtypes[spec.data_arg] = spec.data_arg_type;
	    break;
	  default:
	    /* We have more than one argument for this format spec.  We must
               call the arginfo function again to determine all the types.  */
	    (void) (*__printf_arginfo_table[spec.info.spec])
	      (&spec.info, n - spec.data_arg, &argtypes[spec.data_arg],
	       &spec.size);
	    break;
	  }
    }

  return MAX (nargs, max_ref_arg);
}
