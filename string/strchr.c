/* from Henry Spencer's stringlib */
/* modified by ERS */
/* Modified by Guido.  */
#include <string.h>

#undef index
#undef strchr
#undef __strchr

/*
 * strchr - find first occurrence of a character in a string
 */
char *				/* found char, or NULL if none */
__strchr(s, charwanted)
const char *s;
register int charwanted;
{
	register char c;

	/*
	 * The odd placement of the two tests is so NUL is findable.
	 */
	while ((c = *s++) != (char) charwanted)
		if (c == 0) return NULL;
	return((char *)--s);
}
weak_alias (__strchr, strchr)
weak_alias (__strchr, index)
