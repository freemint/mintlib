/* from Henry Spencer's stringlib */
/* modified by ERS */

#include <stddef.h>
#include <stdlib.h>

/*
 * wcscmp - compare string s1 to s2
 */

int				/* <0 for <, 0 for ==, >0 for > */
wcscmp(scan1, scan2)
register const wchar_t *scan1;
register const wchar_t *scan2;
{
	register wchar_t c1, c2;

	if (scan1 == NULL)
		return scan2 == NULL ? 0 : -1;
	if (scan2 == NULL) return 1;

	do {
		c1 = *scan1++; c2 = *scan2++;
	} while (c1 && c1 == c2);

	/*
	 * The following case analysis is necessary so that characters
	 * which look negative collate low against normal characters but
	 * high against the end-of-string NUL.
	 */
	if (c1 == c2)
		return(0);
	else if (!c1)
		return(-1);
	else if (!c2)
		return(1);
	else
		return(c1 - c2);
}

/*
 * wcsncmp - compare at most n characters of string s1 to s2
 */

int				/* <0 for <, 0 for ==, >0 for > */
wcsncmp(scan1, scan2, n)
register const wchar_t *scan1;
register const wchar_t *scan2;
size_t n;
{
	register wchar_t c1, c2;
	register long count;

	if (scan1 == NULL) {
		return scan2 == NULL ? 0 : -1;
	}
	if (scan2 == NULL) return 1;
	count = n;
	do {
		c1 = *scan1++; c2 = *scan2++;
	} while (--count >= 0 && c1 && c1 == c2);

	if (count < 0)
		return(0);

	/*
	 * The following case analysis is necessary so that characters
	 * which look negative collate low against normal characters but
	 * high against the end-of-string NUL.
	 */
	if (c1 == c2)
		return(0);
	else if (!c1)
		return(-1);
	else if (!c2)
		return(1);
	else
		return(c1 - c2);
}
