/* from Henry Spencer's stringlib */
/* revised by ERS */
/* Fixed by Guido (we need unsigned char!).  */

#include <string.h>

#undef strncmp

#if __GNUC_PREREQ(7, 0)
# pragma GCC diagnostic ignored "-Wnonnull-compare"
#endif

/*
 * strncmp - compare at most n characters of string s1 to s2
 */

int				/* <0 for <, 0 for ==, >0 for > */
strncmp(scan1, scan2, n)
register const char *scan1;
register const char *scan2;
size_t n;
{
	register unsigned char c1, c2;
	register long count;  /* FIXME!!! Has to be size_t but that requires
				a rewrite (Guido).  */

	if (!scan1) {
		return scan2 ? -1 : 0;
	}
	if (!scan2) return 1;
	count = n;
	do {
		c1 = (unsigned char) *scan1++; c2 = (unsigned char) *scan2++;
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
	else if (c1 == '\0')
		return(-1);
	else if (c2 == '\0')
		return(1);
	else
		return(c1 - c2);
}
