/*  swab.c -- MiNTLib.
    Copyright (C) 2001 Ralph Lowinski <AltF4@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* Swab pairs bytes in the first N bytes of the area pointed to by
   FROM and copy the result to TO.  The value of TO must not be in the
   range [FROM - N + 1, FROM - 1].  If N is odd the first byte in FROM
   is without partner.  */

#include <unistd.h>

void
__swab (const char* from, char* to, ssize_t n)
{
	if (n & 1) {
		*(to++) = *(from++);
		n--;
	}
	while ((n -= 2) >= 0) {
		register char c = *(from++);
		*(to++)         = *(from++);
		*(to++)         = c;
	}
}
weak_alias (__swab, swab)
