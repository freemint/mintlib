#include <ctype.h>
#include <string.h>

char *strlwr(string)
register char *string;
{
    register char *p = string;

    if(p) 
    {
        while(*string)
        {
            if(isupper(*string))
                *string = tolower(*string);
            ++string;
        }
    }
    return(p);
}
