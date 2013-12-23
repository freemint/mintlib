#ifndef	_SYS_STATVFS_H
#define	_SYS_STATVFS_H

#include <bits/statvfs.h>

int statvfs (const char *, struct statvfs *);
#if 0
int fstatvfs (int, struct statvfs *);
#endif

#define ST_RDONLY 1
#define ST_NOSUID 2
#define ST_NODEV  4
#define ST_NOEXEC 8
#define ST_SYNCHRONOUS 16
#define ST_MANDLOCK    64
#define ST_WRITE       128
#define ST_APPEND      256
#define ST_IMMUTABLE   512
#define ST_NOATIME     1024
#define ST_NODIRATIME  2048

#endif
