/*  basename.c -- MiNTLib.
    Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.	By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <string.h>
#include <libgen.h>

char *
__xpg_basename (char *filename)
{
	char *p;
	
	if (filename == NULL || filename[0] == '\0')
		/* We return a pointer to a static string containing ".".  */
		p = (char *) ".";
	else {
		char* s = strrchr (filename, '/');
		char* b = strrchr (filename, '\\');
		if (s > b)
			p = s;
		else
			p = b;

	
		if (p == NULL)
			/* There is no slash or backslash in the filename.  
			   Return the whole string.  */
			p = filename;
		else {
			if (p[1] == '\0') {
				/* We must remove trailing '/' resp. 
				   backslash.  */
				while (p > filename 
			       		&& (p[-1] == '/' || p[-1] == '\\'))
					--p;

				/* Now we can be in two situations:
				a) the string only contains slashes or
			   	backslashes, so we return a slash.
				b) p points past the last component, but 
				   we have to remove the trailing 
				   slash/backslash.  */
				if (p > filename) {
					*p-- = '\0';
					while (p > filename && p[-1] != '/' 
				       		&& p[-1] != '\\')
						--p;
				} else {
					/* The last slash we already found is 
					   the right position to return.  */
					while (p[1] != '\0')
						++p;
				}
			}
		}
	}

	return p;
}
link_warning (__xpg_basename,
	      "you are using the weird XPG version of `basename'.");
