/* from the TOS GCC library */
/* malloc, free, realloc: dynamic memory allocation */
/* 5/2/92 sb -- modified for Heat-n-Serve C to accomodate its 16-bit size_t */
/* 5/5/92 sb -- realloc() gets its own file to reduce library drag */

#include <stddef.h>	/* for size_t */
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "lib.h"
#include "malloc_int.h"


void *
__realloc (void *r, size_t n)
{
	struct mem_chunk *p;
	long sz;

	/* obscure features:
	 * 
	 * realloc(NULL,n) is the same as malloc(n)
	 * realloc(p, 0) is the same as free(p)
	 */
	if (!r)
		return __malloc(n);

	if (n == 0) {
		__free(r);
		return NULL;
	}

	p = ((struct mem_chunk *) r) - 1;
	sz = (n + sizeof(struct mem_chunk) + (MALLOC_ALIGNMENT - 1)) & ~(MALLOC_ALIGNMENT - 1);

	if (p->size > (sz + ((2 * sizeof(struct mem_chunk) + (MALLOC_ALIGNMENT - 1)) & ~(MALLOC_ALIGNMENT - 1))))
	{
		/* resize down */
		void *newr;

		newr = __malloc(n);
		if (newr)
		{
			memcpy(newr, r, n);
			__free(r);

			r = newr;
		}
		/* else
		 * malloc failed; can be safely ignored as the new block
		 * is smaller
		 */
	}
	else if (p->size < sz)
	{
		/* block too small, get new one */
		struct mem_chunk *q, *s, *t;

		q = &_mchunk_free_list;
		t = _mchunk_free_list.next;
		while (t && t < p)
		{
			q = t;
			t = t->next;
		}

		/* merge after if possible */
		s = (struct mem_chunk * )(((long) p) + p->size);
		if (t && s >= t && p->size + t->size >= sz
		    && t->valid != VAL_BORDER)
		{
			assert(s == t);

			p->size += t->size;
			q->next = t->next;
			t->size = 0;
			t->next = NULL;
		}
		else
		{
			void *newr;

			newr = __malloc(n);
			if (newr)
			{
				memcpy(newr, r, p->size - sizeof(struct mem_chunk));
				__free(r);
			}
			r = newr;
		}
	}

	return (void *) r;
}
weak_alias (__realloc, realloc)
