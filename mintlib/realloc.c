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

__EXTERN void *_malloc __PROTO((unsigned long));
__EXTERN void _bzero __PROTO((void *, unsigned long));
void *_realloc __PROTO((void *, unsigned long));

#ifdef __GNUC__
asm(".stabs \"_realloc\",5,0,0,__realloc"); /* dept of clean tricks */
#endif

void * _realloc(_r, n)
void *_r;
unsigned long n;
{
  struct mem_chunk *p, *q, *r = (struct mem_chunk *) _r;
  long sz;

/* obscure features: realloc(NULL,n) is the same as malloc(n)
 *  		     realloc(p, 0) is the same as free(p)
 */
  if (!r)
	return _malloc(n);
  if (n == 0) {
	free(_r);
	return NULL;
  }
  p = r - 1;
  sz = (n + sizeof(struct mem_chunk) + 7) & ~7;

  if (p->size > sz + ((sizeof (struct mem_chunk) + 7) & ~7))
	{			/* block too big, split in two */
	q = (struct mem_chunk * )(((long) p) + sz);
	q->size = p->size - sz;
        q->valid = VAL_ALLOC;
	free(q + 1);
	p->size = sz;
	}
    else 
  if (p->size < sz)
    {			/* block too small, get new one */
    struct mem_chunk *s, *t;
    q = &_mchunk_free_list;
    t = _mchunk_free_list.next;
    while (t != NULL && t < p)
      {
      q = t;
      t = t->next;
      }

    /* merge after if possible */
    s = (struct mem_chunk * )(((long) p) + p->size);
    if (t != NULL && s >= t && p->size + t->size >= sz
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
      q = (struct mem_chunk * )_malloc(n);
      if (q != NULL)
	{
	n = p->size - sizeof(struct mem_chunk);
	_bcopy(r, q, n);
        free(r);	/* free r only if we got a new block */
        }
      /* else we could try to mlalloc the rest and hope that we can merge */
      r = q;
    }
  }
  /* else current block will do just fine */
  return((void * )r);
}

#ifndef __GNUC__
void * realloc(_r, n)
void *_r;
size_t n;
{
  return _realloc(_r, (unsigned long) n);
}
#endif
