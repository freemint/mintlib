#include <string.h>
#undef strlen

/*
 * strlen - length of string (not including NUL)
 */
size_t
strlen(const char *scan)
{
	return __inline_strlen(scan);
}
