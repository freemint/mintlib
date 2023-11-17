/* Convert a floating-point number to string.
   Copyright (C) 2016-2023 Free Software Foundation, Inc.
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

/* Modified for MiNTLib by Thorsten Otto.  */

/* Generic implementation for strfrom functions.  The implementation is generic
   for several floating-point types (e.g.: float, double), so that each
   function, such as strfromf and strfroml, share the same code, thus avoiding
   code duplication.  */

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <printf.h>
#include "lib.h"

# define CHAR_T		char
# define UCHAR_T	unsigned char
# define INT_T		int
# define L_(Str)	Str
# define ISDIGIT(Ch)	isdigit (Ch)
# define STR_LEN(Str)	strlen (Str)
#include "stdio/printf-parse.h"

/* This function aims to work around conversions of float -NAN
   to double returning NAN instead of the correct -NAN in some
   architectures.  */
static inline double __attribute__ ((always_inline))
keep_sign_conversion (float flt)
{
  return flt;
}

/* This function will be called if the buffer overruns.  The error flag
   will be set so that the function can report the error condition to
   the caller.  */
static
void __vsnprintf_output (FILE* stream, int c)
{
  /* We use the last character as an overflow, as we end up writing the 
   * \0 end terminator there anyway. The function will now be POSIX compliant
   * and return the amount of data that would have been written.
   */
  if (stream->__bufp == stream->__put_limit)
    stream->__bufp--;
}

int
STRFROM (char *dest, size_t size, const char *format, FLOAT val)
{
  /* Single-precision values need to be stored in a double type, because
     __printf_fp_l and __printf_fphex do not accept the float type.  */
  union {
    double flt;
    FLOAT value;
  } fpnum;
  const void *fpptr;
  FILE f;
  int done;

  /* Variables to control the output format.  */
  int precision = -1; /* printf_fp and printf_fphex treat this internally.  */
  int specifier;
  struct printf_info info;

  fpptr = &fpnum;

  /* Single-precision values need to be converted into double-precision,
     because __printf_fp and __printf_fphex only accept double and long double
     as the floating-point argument.  */
  if (__builtin_types_compatible_p (FLOAT, float))
    fpnum.flt = keep_sign_conversion (val);
  else
    fpnum.value = val;

  /* Check if the first character in the format string is indeed the '%'
     character.  Otherwise, abort.  */
  if (*format == '%')
    format++;
  else
    abort ();

  /* The optional precision specification always starts with a '.'.  If such
     character is present, read the precision.  */
  if (*format == '.')
    {
      format++;

      /* Parse the precision.  */
      if (ISDIGIT (*format))
	precision = read_int ((const UCHAR_T **)&format);
      /* If only the period is specified, the precision is taken as zero, as
	 described in ISO/IEC 9899:2011, section 7.21.6.1, 4th paragraph, 3rd
	 item.  */
      else
	precision = 0;
    }

  /* Now there is only the conversion specifier to be read.  */
  switch (*format)
    {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'f':
    case 'F':
    case 'g':
    case 'G':
      specifier = *format;
      break;
    default:
      abort ();
    }

  /* Prepare the format specification for printf_fp.  */
  memset (&info, '\0', sizeof (info));

  /* The functions strfromd and strfromf pass a floating-point number with
     double precision to printf_fp, whereas strfroml passes a floating-point
     number with long double precision.  The following line informs printf_fp
     which type of floating-point number is being passed.  */
  info.is_long_double = __builtin_types_compatible_p (FLOAT, long double);

  /* Similarly, the function strfromf128 passes a floating-point number in
     _Float128 format to printf_fp.  */
#if __HAVE_DISTINCT_FLOAT128
  info.is_binary128 = __builtin_types_compatible_p (FLOAT, _Float128);
#endif

  /* Set info according to the format string.  */
  info.prec = precision;
  info.spec = specifier;

  /* Prepare the FILE.  */
  memset ((void *) &f, 0, sizeof (f));
  f.__magic = _IOMAGIC;
  f.__mode.__write = 1;
  f.__bufp = f.__buffer = (char *) dest;
  f.__bufsize = size;
  f.__put_limit = f.__buffer + f.__bufsize;
  f.__get_limit = f.__buffer;
  /* After the buffer is full (MAXLEN characters have been written),
     any more characters written will go to the last character in the
     buffer, and we'll overwrite with the NULL terminator later. */
  f.__room_funcs.__output = __vsnprintf_output;
  f.__room_funcs.__input = __default_room_functions.__input;
  f.__io_funcs.__write = NULL;
  f.__seen = 1;

  if (info.spec != 'a' && info.spec != 'A')
    done = __printf_fp(&f, &info, &fpptr);
  else
    done = __printf_fphex(&f, &info, &fpptr);

  /* if the buffer overflowed we'll be at __put_limit, so decrement for null */
  if (f.__bufp == f.__put_limit)
    f.__bufp--;

  *f.__bufp = '\0';

  return done;
}
