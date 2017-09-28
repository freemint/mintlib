/* from Henry Spencer's stringlib */
#include <string.h>
#undef strlen

#if __GNUC_PREREQ(7, 0)
# pragma GCC diagnostic ignored "-Wnonnull-compare"
#endif

/*
 * strlen - length of string (not including NUL)
 */
size_t
strlen(scan)
register const char *scan;
{
	register const char *start = scan+1;

	if (!scan) return 0;
	while (*scan++ != '\0')
		continue;
	return (size_t)((long)scan - (long)start);
}
