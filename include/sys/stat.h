
#ifndef _SYS_STAT_H
#define _SYS_STAT_H 1

#ifndef _COMPILER_H
# include <compiler.h>
#endif

#ifndef _SYS_TYPES_H
# include <sys/types.h>
#endif

__BEGIN_DECLS

struct __st_mtim {
	unsigned long tv_nsec;
};
	
/* This is what Fstat wants and what we use in the library.  */
struct stat {
  dev_t st_dev;			/* Device.  */
  ino_t  st_ino;		/* File serial number.  */
  mode_t st_mode;	        /* File mode.  */
  nlink_t st_nlink;		/* (Hard) link count.  */
  uid_t st_uid;		        /* User ID of the file's owner.  */
  gid_t st_gid;			/* Group ID of the file's group.  */
  dev_t	st_rdev;		/* Device number, if device.  */
  long  __st_high_atime;
  time_t st_atime;		/* Time of last access, UTC.  */
  struct __st_mtim st_atim;
  long  __st_high_mtime;
  time_t st_mtime;		/* Time of last access, UTC.  */
  struct __st_mtim st_mtim;
  long  __st_high_ctime;
  time_t st_ctime;		/* Time of last status change, UTC.  */
  struct __st_mtim st_ctim;
  unsigned long __st_hi_size;	/* Upper 4 bytes of st_size.  */
  off_t st_size;		/* File size, in bytes.  */
  unsigned long __st_hi_blocks; /* Upper 4 bytes of st_blocks.  */
  off_t	st_blocks;		/* Number of 512-bytes blocks allocated.  */
  unsigned long int st_blksize;	/* Optimal blocksize for I/O.  */
  unsigned long	int st_flags;	/* User defined flags for file.  */
  unsigned long	int st_gen;	/* File generation number.  */
  long int __res[7];
};

#if defined(__USE_BSD) || defined(__USE_MISC)
#define	S_IFMT			0170000
/* In case the presence of this macro causes difficulties, you can avoid
 * them with an additional define.
 */
#ifndef _NO_UNIX_SOCKETS
# define S_IFSOCK		0010000
#endif
#define	S_IFCHR			0020000
#define	S_IFDIR			0040000
#define S_IFBLK			0060000
#define	S_IFREG			0100000
#define S_IFIFO			0120000
#define S_IMEM			0140000
#define	S_IFLNK			0160000
#endif

#ifndef _NO_UNIX_SOCKETS
# define S_ISSOCK(m)		(((m) & S_IFMT) == S_IFSOCK)
#endif
#define S_ISCHR(m)		(((m) & S_IFMT) == S_IFCHR)
#define S_ISDIR(m)		(((m) & S_IFMT) == S_IFDIR)
#define S_ISBLK(m)		(((m) & S_IFMT) == S_IFBLK)
#define S_ISREG(m)		(((m) & S_IFMT) == S_IFREG)
#define S_ISFIFO(m)		(((m) & S_IFMT) == S_IFIFO)
#define S_ISMEM(m)		(((m) & S_IFMT) == S_IMEM)
#ifdef __USE_BSD
#define S_ISLNK(m)		(((m) & S_IFMT) == S_IFLNK)
#endif

#define S_IRWXU			0700
#define S_IRWXG			0070
#define S_IRWXO			0007

#define	S_ISUID			04000
#define	S_ISGID			02000
#if defined(__USE_BSD) || defined(__USE_MISC)
/* Save swapped text after use (sticky bit).  This is pretty well obsolete.  */
#define	S_ISVTX			01000
#endif

/* file access modes for user, group, and other*/
#define S_IRUSR			0400
#define S_IWUSR			0200
#define S_IXUSR			0100
#define S_IRGRP			0040
#define S_IWGRP			0020
#define S_IXGRP			0010
#define S_IROTH			0004
#define S_IWOTH			0002
#define S_IXOTH			0001

#if defined(__USE_MISC) && defined(__USE_BSD)
/* Historical macros.  */
#define	S_IREAD			S_IRUSR
#define	S_IWRITE		S_IWUSR
#define	S_IEXEC			S_IXUSR
#endif

#ifdef	__USE_BSD
/* Macros for common mode bit masks.  */
#define	ACCESSPERMS (S_IRWXU|S_IRWXG|S_IRWXO) /* 0777 */
#define	ALLPERMS (S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)/* 07777 */
#define	DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)/* 0666 */

#define S_BLKSIZE	512	/* Block size for `st_blocks'.  */
#endif

/* Function declarations.  */
__EXTERN int	chmod	__PROTO((const char *, mode_t));
__EXTERN int	fstat	__PROTO((int, struct stat *));
#if defined(__USE_BSD) || defined(__USE_XOPEN_EXTENDED)
__EXTERN int	lstat	__PROTO((const char *, struct stat *));
#endif
__EXTERN int	mkdir	__PROTO((const char *, mode_t));
__EXTERN int	mkfifo	__PROTO((const char *, mode_t));
__EXTERN int	stat	__PROTO((const char *, struct stat *));
__EXTERN int	umask	__PROTO((int));

/* Set file access permissions of the file FD is open on to MODE.  */
#if defined (__USE_BSD) || defined (__USE_XOPEN_EXTENDED)
__EXTERN int fchmod __PROTO ((int __fd, mode_t __mode));
#endif

/* Create a device file named PATH, with permission and special bits MODE
   and device number DEV (which can be constructed from major and minor
   device numbers with the `makedev' macro above).  
   
   This is theory.  In fact this doesn't work yet with MiNT and this
   function is a dummy.  */
#if defined(__USE_MISC) || defined(__USE_BSD) || defined(__USE_XOPEN_EXTENDED)
extern int mknod __P ((__const char *__path,
		       mode_t __mode, dev_t __dev));
#endif

#ifdef _USE_GNU
__EXTERN mode_t getumask __PROTO ((void));
#endif

__END_DECLS

#endif /* _STAT_H */
