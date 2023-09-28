#ifndef	_SYS_STATVFS_H
#define	_SYS_STATVFS_H

__BEGIN_DECLS

#include <bits/statvfs.h>

int statvfs (const char *, struct statvfs *);
#if 0
int fstatvfs (int, struct statvfs *);
#endif

__END_DECLS

#endif
