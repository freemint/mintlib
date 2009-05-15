/* from Henry Spencer's stringlib */
#include <string.h>

/*
 * strrchr - find last occurrence of a character in a string
 */
#ifdef __GNUC__
__asm__(".stabs \"_rindex\",5,0,0,_strrchr"); /* dept of clean tricks */
#else
char *
rindex(s, charwanted)
      const char *s;
      int charwanted;
{
      return strrchr(s, charwanted);
}
#endif

char *				/* found char, or NULL if none */
strrchr(s, charwanted)
const char *s;
register int charwanted;
{
	register char c;
	register const char *place;

	place = NULL;
	while ((c = *s++) != 0)
		if (c == (char) charwanted)
			place = s - 1;
	if ((char) charwanted == '\0')
		return((char *)--s);
	return (char *)place;
}
