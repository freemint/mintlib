/* from the TOS GCC library */
/* malloc, free, realloc: dynamic memory allocation */
/* 5/2/92 sb -- modified for Heat-n-Serve C to accomodate its 16-bit size_t */
/* 5/5/92 sb -- calloc() gets its own file to reduce library drag */

#include <stddef.h>
#include <string.h>

extern void *__malloc __P ((size_t __n));
extern void *__calloc __P ((size_t __n, size_t __s));

void *
__calloc (size_t n, size_t sz)
{
	register void *r;
	register size_t total;

	total = n * sz;

	r = __malloc (total);
	if (r != NULL)
		__bzero (r, total);

	return r;
}
weak_alias (__calloc, calloc)
