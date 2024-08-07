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

size_t mbrlen(const char *__restrict s, size_t n, mbstate_t *__restrict st)
{
	static mbstate_t internal;
	return mbrtowc(0, s, n, st ? st : &internal);
}
