/* from Henry Spencer's stringlib */
/* check for NULL string added by ERS */

#include <stddef.h>
#include <stdlib.h>

extern const wchar_t *_wnull;

/*
 * wcscpy - copy string src to dst
 */
wchar_t *				/* dst */
wcscpy(dst, src)
wchar_t *dst;
const wchar_t *src;
{
	register wchar_t *dscan = dst;
	register const wchar_t *sscan = src;

	if (sscan == NULL) sscan = _wnull;
	while ((*dscan++ = *sscan++))
		continue;
	return(dst);
}

/*
 * wcsncpy - copy at most n characters of string src to dst
 */
wchar_t *				/* dst */
wcsncpy(dst, src, n)
wchar_t *dst;
const wchar_t *src;
size_t n;
{
	register wchar_t *dscan;
	register const wchar_t *sscan;
	register long count;

	dscan = dst;
	if ((sscan = src) == NULL)
		sscan = _wnull;
	count = n;
	while (--count >= 0 && (*dscan++ = *sscan++))
		continue;
	while (--count >= 0)
		*dscan++ = *_wnull;
	return(dst);
}
