/* from Dale Schumacher's dLibs library */

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

/*
 * This routine is safe in the sense that it does not make
 * assumptions about sizeof(void *). Gcc assumes same as char *
 * when not -ansi, the "other" compiler just barfs.
 *
 */

void * bsearch(key, base, num, size, cmp)
	register const void * key;		/* item to search for */
	register const void * base;		/* base address */
	size_t		  num;		/* number of elements */
	register size_t   size;		/* element size in bytes */
	/* comparison function */
	register int (*cmp) (const void *, const void *);
	{
	register size_t a, b, c;
	register int dir;

#if 0
	assert ((key != NULL) && (base != NULL) && (size > 0) && (num > 0) &&
		(cmp != NULL));
#else
	if ((key == NULL) || (base == NULL) || (size == 0) || (num == 0) 
	    || (cmp == NULL))
		return NULL;
#endif

	a = 0;
	b = num - 1;
	while(a <= b)
		{
		c = (a + b) >> 1;	/* == ((a + b) / 2) */
		if ((dir = (*cmp)(key, (void *)((char *)base + (c * size)))) != 0)
			{
			if (dir < 0)
			{
			    if (c == 0)
				return(NULL);
				b = c - 1;
			}
			else /* (dir > 0) */
				a = c + 1;
			}
		else
			{
			return((void *)(((char *)base) + (c * size)));
			}
		}
	return(NULL);
	}
