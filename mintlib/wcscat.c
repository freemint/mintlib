/* from Henry Spencer's stringlib */
/* check for src==NULL added by ERS */

#include <stddef.h>
#include <stdlib.h>

/*
 * wcscat - append string src to dst
 */
wchar_t *				/* dst */
wcscat(dst, src)
wchar_t *dst;
const wchar_t *src;
{
	register wchar_t *dscan;
	register const wchar_t *sscan;

	if ((sscan = src) != NULL)
	{
	    for (dscan = dst; *dscan; dscan++)
		continue;
	    while ((*dscan++ = *sscan++) != 0)
			continue;
	}
	return(dst);
}

/*
 * wcsncat - append at most n characters of string src to dst
 */
wchar_t *				/* dst */
wcsncat(dst, src, n)
wchar_t *dst;
const wchar_t *src;
size_t n;
{
	register wchar_t *dscan, c;
	register const wchar_t *sscan;
	register long count;

	if(((sscan = src) != NULL) && (n > 0))
	{
	    for (dscan = dst; *dscan; dscan++)
		continue;
	    count = n;
	    while (((c = *sscan++) != 0) && --count >= 0)
		*dscan++ = c;
	    *dscan = 0;
	}
	return(dst);
}
