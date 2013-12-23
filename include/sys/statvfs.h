#ifndef	_SYS_STATVFS_H
#define	_SYS_STATVFS_H

#include <bits/statvfs.h>

int statvfs (const char *, struct statvfs *);
#if 0
int fstatvfs (int, struct statvfs *);
#endif

#endif
