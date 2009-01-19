
#include <string.h>
#include "lib.h"

char _numstr[] = "0123456789ABCDEF";

char *
_ultoa(unsigned long n, char *buffer, int radix)
{
	register char *p = buffer;
	
	do {
		*p++ = _numstr[n % radix];	/* grab each digit */
	}
	while((n /= radix) > 0);
	
	*p = '\0';
	
	return strrev(buffer);			/* reverse and return it */
}

char *
_ltoa(long n, char *buffer, int radix)
{
	register char *p = buffer;
	
	if (n < 0)
	{
		*p++ = '-';
		n = -n;
	}
	
	_ultoa((unsigned long)n, p, radix);
	
	return buffer;
}
