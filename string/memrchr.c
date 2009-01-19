#include <stddef.h>
#include <string.h>

/*
 * memrchr - search for a byte (backwards)
 */

void *
memrchr(s, ucharwanted, size)
const void * s;
int ucharwanted;
size_t size;
{
	register const char *scan;
	register size_t n;

	scan = (const char *) (s + size - 1);
	for (n = size; n > 0; n--)
		if (*scan == (char) ucharwanted)
			return((void *)scan);
		else
			scan--;

	return(NULL);
}
