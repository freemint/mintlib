/* from Dale Schumacher's dLibs library */

/* if you chage the behaviour so that it does not reverse in-place
 * please change mktemp.c too (it assumes rev is in-place)
 */

#include <string.h>

char *strrev(string)
	char *string;
	{
	register char *p = string, *q, c;

	if(*(q = p))		/* non-empty string? */
		{
		while(*++q)
			;
		while(--q > p)
			{
			c = *q;
			*q = *p;
			*p++ = c;
			}
		}
	return(string);
	}
