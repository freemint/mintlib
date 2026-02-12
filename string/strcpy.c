/* from Henry Spencer's stringlib */
/* check for NULL string added by ERS */

#include <string.h>
#undef strcpy

/*
 * strcpy - copy string src to dst
 */
char *				/* dst */
strcpy(char *dst, const char *src)
{
	return __inline_strcpy(dst, src);
}
