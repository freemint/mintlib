/* from Henry Spencer's stringlib */
/* check for NULL string added by ERS */

#include <string.h>
#undef strcpy

/*
 * strcpy - copy string src to dst
 */
char *strcpy(char *dst, const char *src)
{
#ifdef __OPTIMIZE__
	return __inline_strcpy(dst, src);
#else
	char *dscan = dst;
	const char *sscan = src;

	while ((*dscan++ = *sscan++) != '\0')
		continue;
	return dst;
#endif
}
