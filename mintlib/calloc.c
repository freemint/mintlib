/* from the TOS GCC library */
/* malloc, free, realloc: dynamic memory allocation */
/* 5/2/92 sb -- modified for Heat-n-Serve C to accomodate its 16-bit size_t */
/* 5/5/92 sb -- calloc() gets its own file to reduce library drag */

#include <compiler.h>
#include <stddef.h>	/* for size_t */
#include <memory.h>
#include <string.h>

__EXTERN void *_malloc __PROTO((unsigned long));
__EXTERN void *_calloc __PROTO((unsigned long, unsigned long));

#ifdef __GNUC__
asm(".stabs \"_calloc\",5,0,0,__calloc"); /* dept of clean tricks */
#endif

void * _calloc(n, sz)
unsigned long n, sz;
{
  void *r;
  unsigned long total;

  total = n * sz;
  if ((r = _malloc(total)) != NULL) {
	_bzero(r, total);
  }
  return(r);
}

#ifndef __GNUC__
void * calloc(n, sz)
size_t n, sz;
{
  return _calloc((unsigned long) n, (unsigned long) sz);
}
#endif
