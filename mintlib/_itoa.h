/*  _itoa.h -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemnint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _ITOA_H
#define _ITOA_H

#ifndef	_FEATURES_H
# include <features.h>
#endif

#include <support.h>

/* Convert VALUE into ASCII in base BASE (2..36).
   Write backwards starting the character just before BUFLIM.
   Return the address of the first (left-to-right) character in the number.
   Use upper case letters iff UPPER_CASE is nonzero.  */

extern __inline char * __attribute__ ((unused))
_itoa_word (unsigned long value, char *buflim,
	    unsigned int base, int upper_case)
{
  extern const char _itoa_upper_digits[];
  extern const char _itoa_lower_digits[];
  const char* digits = upper_case ? _itoa_upper_digits : _itoa_lower_digits;
  char *bp = buflim;

  switch (base)
    {
#define SPECIAL(Base)							      \
    case Base:								      \
      do								      \
	*--bp = digits[value % Base];					      \
      while ((value /= Base) != 0);					      \
      break

      SPECIAL (10);
      SPECIAL (16);
      SPECIAL (8);
    default:
      do
	*--bp = digits[value % base];
      while ((value /= base) != 0);
    }
  return bp;
}

extern __inline char * __attribute__ ((unused))
_fitoa_word (unsigned long value, char *buf, unsigned int base, int upper_case)
{
  char tmpbuf[sizeof value * 4];	/* Worst case length: base 2.  */
  char* cp = _itoa_word (value, tmpbuf + sizeof value * 4, base, upper_case);
  while (cp < tmpbuf + sizeof value * 4)
    *buf++ = *cp++;
  return buf;
}

extern __inline char * __attribute__ ((unused))
_fitoa (unsigned long long value, char *buf, unsigned int base, int upper_case)
{
  char tmpbuf[sizeof value * 4];	/* Worst case length: base 2.  */
  char* cp = _itoa (value, tmpbuf + sizeof value * 4, base, upper_case);
  while (cp < tmpbuf + sizeof value * 4)
    *buf++ = *cp++;
  return buf;
}

#endif /* not _ITOA_H.  */
