#include <stddef.h>	/* for size_t */
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/param.h>
#include "lib.h"
#include "malloc_int.h"


/*
 * noinline because we need the symbol below
 */
static __attribute_noinline__ void *__libc_memalign(size_t alignment, size_t size)
{
	void *mem;

	/* If we need less alignment than we give anyway, just relay to malloc. */
	if (alignment <= MALLOC_ALIGNMENT)
	{
		mem = __malloc(size);
	} else
	{
		mem = __malloc(size + alignment - 1);
		/*
		 * if the memory is not properly aligned,
		 * move the memchunk preceeding it up,
		 * and mark it as not malloced,
		 * since out current implementation of free() does not allow to pass
		 * arbitrary addresses inside the malloced area
		 */
		if (mem != NULL && ((unsigned long)mem & (alignment - 1)) != 0)
		{
			struct mem_chunk *p;

			mem = (char *)(((unsigned long)mem + alignment - 1) & ~(alignment - 1));
			p = (struct mem_chunk *)mem;
			/* move back to uncover the mem_chunk */
			p--; /* there it is! */

			/*
			 * FIXME: this will leak the memory, since it cannot be freed()
			 */
			p->valid = VAL_ALLOC + 1;
			p->next = 0;
			p->size = size;
		}
	}
	return mem;
}
strong_alias (__libc_memalign, __memalign)
weak_alias (__libc_memalign, memalign)
/* For ISO C11. */
weak_alias(__libc_memalign, aligned_alloc)


__typeof__(posix_memalign) __posix_memalign;

int __posix_memalign(void **memptr, size_t alignment, size_t size)
{
	void *mem;

	/* Test whether the SIZE argument is valid.  It must be a power of
	   two multiple of sizeof (void *).  */
	if ((alignment % sizeof (void *)) != 0 ||
		!powerof2(alignment / sizeof (void *)) ||
		alignment == 0)
		return EINVAL;

	mem = __libc_memalign(alignment, size);
	if (mem != NULL)
	{
		*memptr = mem;
		return 0;
    }

	return ENOMEM;
}
weak_alias(__posix_memalign, posix_memalign)
