/* hohmuth 1-Nov-92, derived from strlwr.c */
#include <ctype.h>
#include <string.h>

char *strupr(string)
register char *string;
{
    register char *p = string;

    if(p)
    {
        while(*string)
        {
            if(islower(*string))
                *string = toupper(*string);
            ++string;
        }
    }
    return(p);
}
