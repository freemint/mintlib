#include <stddef.h>
#include <string.h>
#include <assert.h>

#undef ODD
#define ODD(x) ((int)((long)(x) & 1L))

/*
 * compare n bytes efficientlty
 *
 * odd/even handled correctly
 *
 *   ++jrb  bammi@dsrgsun.ces.cwru.edu
 */

#define INC(x, size) x = (const void *)(((const char *)(x)) + (size))

int __bcmp(src, dst, n)
const void * src;
const void * dst;
register size_t n;
{

    assert ((src != NULL) && (dst != NULL));

    if((src != dst) && (n > 0))
    {
	register size_t l, w;
	
	switch(ODD(src) + ODD(dst))
	{
	  case 2: /* ODD ODD */
	    if (*(const char *)dst != *(const char *)src)
		return 1;
            INC(src, 1);
	    INC(dst, 1);
	    n--;
	    /* fall thru */
	    
	  case 0: /* EVEN EVEN */
	    l = (n >> 2); /* # of longs */
	    n -= (l << 2);
	    w = (n >> 1); /* # of words */
	    n -= (w << 1); /* n == # of residual bytes */
	    while(l--) {
		if (*((const long *)dst) != *((const long *)src))
			return 1;
		INC(dst, sizeof(long));
		INC(src, sizeof(long));
	    }
	    while(w--) {
		if( *((const short *)dst) != *((const short *)src) )
		    return 1;
		INC(dst, sizeof(short));
		INC(src, sizeof(short));
	    }
	    /* fall thru */
	  case 1: /* ODD/EVEN or EVEN/ODD */
	    while(n--) {
		if( *(const char *)dst != *(const char *)src )
		    return 1;
		INC(dst, 1);
		INC(src, 1);
	    }
	}
    }
     return 0;
}
weak_alias (__bcmp, bcmp)
