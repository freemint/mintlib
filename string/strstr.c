/* from Henry Spencer's stringlib */
/* Bugfix by Guido: Handle empty strings correctly.  */
#include <string.h>

#undef strstr

/*
 * strstr - find first occurrence of wanted in s
 */

char *				/* found string, or NULL if none */
strstr(s, wanted)
const char *s;
const char *wanted;
{
	register const char *scan;
	register size_t len;
	register char firstc;

	if (!*s) {
		if (*wanted)
			return NULL;
		else
			return (char*) s;
	} else if (!*wanted) {
		return (char*) s;
	}
	
	/*
	 * The odd placement of the two tests is so "" is findable.
	 * Also, we inline the first char for speed.
	 * The ++ on scan has been moved down for optimization.
	 */
	firstc = *wanted;
	len = strlen(wanted);
	for (scan = s; *scan != firstc || strncmp(scan, wanted, len) != 0; )
		if (*scan++ == '\0')
			return(NULL);
	return((char *)scan);
}
