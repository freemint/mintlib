/* dummy implementations for strcoll and strxfrm, that doesn't know about
   locales */

#include <string.h>

size_t strxfrm(char *dest, const char *src, size_t n)
{
	size_t l = strlen(src);
	if (n > l)
		strcpy(dest, src);
	return l;
}
