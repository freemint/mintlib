
#include <ctype.h>

#undef	toupper /* note that in gcc we have a safe version of these, */
#undef  tolower	/* but its better to leave these as routines in case */
		/* some code uses these as function pointers --  i   */
		/* have seen code that does.			     */

int 
toupper (int c)
{
	return _toupper (c);
}

int 
tolower (int c)
{
	return _tolower (c);
}

#undef _toupper
#undef _tolower

strong_alias (toupper, _toupper)
strong_alias (tolower, _tolower)
