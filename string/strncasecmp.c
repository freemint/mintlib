/* derived from strncmp from Henry Spencer's stringlib */
/* revised by ERS */
/* i-changes by Alexander Lehmann */

#include <string.h>
#include <ctype.h>

/*
 * strnicmp - compare at most n characters of string s1 to s2 without case
 *           result is equivalent to strcmp(strupr(s1),s2)),
 *           but doesn't change anything
 */

int                             /* <0 for <, 0 for ==, >0 for > */
__strncasecmp(scan1, scan2, n)
register const char *scan1;
register const char *scan2;
size_t n;
{
        register unsigned char c1, c2;
        register long count;

        if (!scan1) {
                return scan2 ? -1 : 0;
        }
        if (!scan2) return 1;
        count = n;
        do {
                c1 = (unsigned char) *scan1++; c1=toupper(c1);
                c2 = (unsigned char) *scan2++; c2=toupper(c2);
        } while (--count >= 0 && c1 && c1 == c2);

        if (count < 0)
                return(0);

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
weak_alias (__strncasecmp, strncasecmp)
weak_alias (__strncasecmp, strnicmp)
weak_alias (__strncasecmp, strncmpi)
