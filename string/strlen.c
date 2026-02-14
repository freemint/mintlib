#define strlen __inline_strlen
#include <string.h>
#undef strlen

size_t strlen(const char *scan);

/*
 * strlen - length of string (not including NUL)
 */
size_t strlen(const char *scan)
{
#ifdef __OPTIMIZE__
	return __inline_strlen(scan);
#else
	const char *start = scan;

	while (*scan++ != '\0')
		continue;
	return scan - start - 1;
#endif
}
