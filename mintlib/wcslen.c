/* from Henry Spencer's stringlib */
#include <stddef.h>
#include <stdlib.h>

/*
 * wcslen - length of string (not including NUL)
 */
size_t
wcslen(scan)
register const wchar_t *scan;
{
	register const wchar_t *start = scan+1;

	if (scan == NULL) return 0;
	while (*scan++)
		continue;
	return (size_t)((long)scan - (long)start);
}
