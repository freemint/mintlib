
#ifndef _MALLOC_H
#define _MALLOC_H 1

#ifndef _FEATURES_H
# include <features.h>
#endif

#ifndef _ALLOCA_H
# include <alloca.h>
#endif

#define __need_size_t
#include <stddef.h>

__BEGIN_DECLS

__EXTERN void *malloc __P ((size_t __n));
__EXTERN void free __P ((void* __param));
__EXTERN void *realloc __P ((void *__r, size_t __n));
__EXTERN void *calloc __P ((size_t __n, size_t __size));
__EXTERN void _malloczero __P ((int __yes));
__EXTERN void _mallocChunkSize __P ((size_t __size));

__EXTERN void *_malloc __P ((unsigned long __n));
__EXTERN void *_realloc __P ((void *_r, unsigned long __n));
__EXTERN void *_calloc __P ((unsigned long n, unsigned long __size));

__EXTERN void *sbrk __P ((size_t __size));
__EXTERN void *lsbrk __P ((long __size));
__EXTERN void *_sbrk __P ((long __size));

__END_DECLS
  
#endif /* _MALLOC_H */
