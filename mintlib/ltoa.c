#include <string.h>
#include "lib.h"

#ifdef __STRICT_ANSI__
#  ifdef __STDC__
    char * strrev(char *);
#  else
    extern char * strrev();
#  endif
#endif

char	_numstr[] = "0123456789ABCDEF";

char *_ultoa(n, buffer, radix)
	register unsigned long n;
	register char *buffer;
	register int radix;
	{
	register char *p = buffer;

	do
		{
		*p++ = _numstr[n % radix];	/* grab each digit */
		}
		while((n /= radix) > 0);
	*p = '\0';
	return(strrev(buffer));			/* reverse and return it */
	}

char *_ltoa(n, buffer, radix)
	register long n;
	register char *buffer;
	int radix;
	{
	register char *p = buffer;

	if (n < 0)
		{
		*p++ = '-';
		n = -n;
		}
      _ultoa(n, p, radix);
	return(buffer);
	}

#if 0
char *_itoa(n, buffer, radix)
	int n;
	char *buffer;
	int radix;
	{
         return(_ltoa(((long) n), buffer, radix));
	}
#endif
