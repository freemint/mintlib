/* 
 * statfs.h -- structure for statfs() call.
 */

#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <bits/types.h>

struct statfs {
  long f_type;		/* type of info, zero for now */
  long f_bsize;		/* fundamental file system block size */
  long f_blocks;	/* total blocks in file system */
  long f_bfree;		/* free blocks */
/*
 * Remaining fields are here for BSD compatibility, but they aren't really
 * used for a standard TOS-ish filesystem
 */
  long f_bavail;	/* free blocks available to non-super-user */
  long f_files;		/* total file nodes in file system */
  long f_ffree;		/* free file nodes in fs */
  __fsid_t f_fsid;	/* file system id */
  long f_spare[7];	/* spare for later */
};

__EXTERN int	statfs	__PROTO((const char *path, struct statfs *buf));
__EXTERN int	__statfs	__PROTO((const char *path, struct statfs *buf));

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_STATFS_H */
