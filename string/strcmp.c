/* from Henry Spencer's stringlib */
/* modified by ERS */
/* Fixed by Guido:  Nobody ever thought of 8 bit characters???  */

#define strcmp __inline_strcmp
#include <string.h>
#undef strcmp

int	strcmp(const char *scan1, const char *scan2);

/*
 * strcmp - compare string s1 to s2
 */

/* <0 for <, 0 for ==, >0 for > */
int	strcmp(const char *scan1, const char *scan2)
{
#ifdef __OPTIMIZE__
	return __inline_strcmp(scan1, scan2);
#else
	do {
		c1 = *scan1++;
		c2 = *scan2++;
	} while (c1 && c1 == c2);
	return c1 - c2;
#endif
}
