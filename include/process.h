/* defines for spawnve, etc. */

#ifndef _PROCESS_H
#define _PROCESS_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define P_WAIT		0
#define P_NOWAIT	1
#define P_OVERLAY	2

__EXTERN int	spawnv	__PROTO((int, const char *, char *const *));
__EXTERN int	spawnve	__PROTO((int, const char *, char *const *, char *const *));
__EXTERN int	_spawnve __PROTO((int, const char *, char *const *, char *const *));
__EXTERN int	spawnvp	__PROTO((int, const char *, char *const *));
__EXTERN int	spawnle	__PROTO((int, const char *, ...));
__EXTERN int	spawnl	__PROTO((int, const char *, ...));
__EXTERN int	spawnlp	__PROTO((int, const char *, ...));

#ifdef __cplusplus
}
#endif

#endif /* _PROCESS_H */
