/* 
 * Definitions for getting information about a filesystem.
 */

#ifndef	_SYS_STATFS_H
#define	_SYS_STATFS_H	1

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

/* Get the system-specific definition of `struct statfs'.  */
#include <bits/statfs.h>

extern int statfs (__const char *__file, struct statfs *__buf) __THROW;
extern int __statfs (__const char *__file, struct statfs *__buf) __THROW;

#if 0
extern int fstatfs (int __fildes, struct statfs *__buf) __THROW;
extern int __fstatfs (int __fildes, struct statfs *__buf) __THROW;
#endif

__END_DECLS

#endif	/* sys/statfs.h */
