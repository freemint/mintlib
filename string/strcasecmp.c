/* derived from strcmp from Henry Spencer's stringlib */
/* modified by ERS */
/* i-changes by Alexander Lehmann */

#include <string.h>
#include <ctype.h>

/*
 * stricmp - compare string s1 to s2 without case sensitivity
 *           result is equivalent to strcmp(strupr(s1),s2)),
 *           but doesn't change anything
 */

int                             /* <0 for <, 0 for ==, >0 for > */
__strcasecmp(scan1, scan2)
register const char *scan1;
register const char *scan2;
{
        register char c1, c2;

        if (!scan1)
                return scan2 ? -1 : 0;
        if (!scan2) return 1;

        do {
                c1 = *scan1++; c1=toupper(c1);
                c2 = *scan2++; c2=toupper(c2);
        } while (c1 && c1 == c2);

        /*
         * The following case analysis is necessary so that characters
         * which look negative collate low against normal characters but
         * high against the end-of-string NUL.
         */
        if (c1 == c2)
                return(0);
        else if (c1 == '\0')
                return(-1);
        else if (c2 == '\0')
                return(1);
        else
                return(c1 - c2);
}

weak_alias (__strcasecmp, strcasecmp)
weak_alias (__strcasecmp, stricmp)
weak_alias (__strcasecmp, strcmpi)
