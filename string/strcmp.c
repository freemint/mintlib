/* from Henry Spencer's stringlib */
/* modified by ERS */
/* Fixed by Guido:  Nobody ever thought of 8 bit characters???  */

#include <string.h>
#undef strcmp

/*
 * strcmp - compare string s1 to s2
 */

int				/* <0 for <, 0 for ==, >0 for > */
strcmp(const char *scan1, const char *scan2)
{
	return __inline_strcmp(scan1, scan2);
}
