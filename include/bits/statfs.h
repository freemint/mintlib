
#ifndef _SYS_STATFS_H
# error "Never include <bits/statfs.h> directly; use <sys/statfs.h> instead."
#endif

#include <bits/types.h>  /* for __fsid_t */

struct statfs
{
  long f_type;		/* type of info, zero for now */
  long f_bsize;		/* fundamental file system block size */
  long f_blocks;	/* total blocks in file system */
  long f_bfree;		/* free blocks */
  long f_bavail;	/* free blocks available to non-super-user */
  long f_files;		/* total file nodes in file system */
  long f_ffree;		/* free file nodes in fs */
  __fsid_t f_fsid;	/* file system id */
#if 1
  long f_spare[7];	/* spare for later */
#else
  long f_namelen;
  long f_spare[6];	/* spare for later */

/* Tell code we have this member.  */
#define _STATFS_F_NAMELEN

#endif
};
