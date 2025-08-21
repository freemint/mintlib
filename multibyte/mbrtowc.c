/* 
 * This code was written by Rich Felker in 2010; no copyright is claimed.
 * This code is in the public domain. Attribution is appreciated but
 * unnecessary.
 */

#include <stdlib.h>
#include <inttypes.h>
#include <wchar.h>
#include <errno.h>

#include "internal.h"

size_t mbrtowc(wchar_t *__restrict wc, const char *__restrict src, size_t n, mbstate_t *__restrict st)
{
	static mbstate_t internal_state;
	unsigned c;
	const unsigned char *s = (const void *)src;
	const unsigned N = n;
	wchar_t dummy;

	if (!st) st = &internal_state;
	c = st->__value.__wch;
	
	if (!s) {
		if (c) goto ilseq;
		return 0;
	} else if (!wc) wc = &dummy;

	if (!n) return -2;
	if (!c) {
		if (*s < 0x80) return !!(*wc = *s);
		if (*s-SA > SB-SA) goto ilseq;
		c = bittab[*s++-SA]; n--;
	}

	if (n) {
		if (OOB(c,*s)) goto ilseq;
loop:
		c = (c<<6) | (*s++-0x80); n--;
		if (!(c&(1U<<31))) {
			st->__value.__wch = 0;
			*wc = c;
			return N-n;
		}
		if (n) {
			if (*s-0x80u >= 0x40) goto ilseq;
			goto loop;
		}
	}

	st->__value.__wch = c;
	return -2;
ilseq:
	st->__value.__wch = 0;
	errno = EILSEQ;
	return -1;
}
