/* header file for POSIX directory access routines */

#ifndef _SYS_DIRENT_H
#define _SYS_DIRENT_H 1

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#ifndef _TYPES_H
# ifdef __TURBOC__
#  include <sys\types.h>
# else
#  include <sys/types.h>
# endif
#endif

#ifndef NAME_MAX
# include <limits.h>
#endif

#ifdef __MINT__
# ifndef _OSTRUCT_H
#  include <ostruct.h>
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _LIB_NAME_MAX
#  define _LIB_NAME_MAX NAME_MAX
#endif

struct dirent {
       long            d_ino;          /* garbage under TOS */
       off_t           d_off;          /* position in directory  */
       short           d_reclen;       /* for us, length of d_name */
#ifndef __MINT__
/* the following (except for d_name) are unique to TOS */
       struct dirent   *d_next;        /* ptr to next struct dirent in list */
       unsigned char   d_attribute;    /* file modes from Fsfirst()  */
       unsigned short  d_time, d_date; /* TOS date and time for file */
       long            d_size;         /* file size */
       char            d_name[1];
#else
       char            d_name[NAME_MAX+1];
#endif
};

#ifndef __MINT__
typedef struct _DIR {
       struct dirent *D_list;          /* list of directory entries */
       struct dirent *D_curpos;        /* current position in list  */
       char          *D_path;          /* path to this directory    */
       struct _DIR   *D_nxtdir;        /* next DIR in opendir chain */
} DIR;

#else

typedef struct _DIR {
	short	status;		/* status of the search so far: */
#define _INSEARCH	0	/* need to call Fsnext for a new entry */
#define _STARTSEARCH	1	/* Fsfirst called once, successfully */
#define _NMFILE		2	/* no more files in directory */
	_DTA	dta;		/* TOS DTA for this directory */
	char	*dirname;	/* directory of the search (used under
				   TOS for rewinddir) */
	struct dirent buf;	/* dirent struct for this directory */
	long	handle;		/* Dreaddir handle */
} DIR;

#endif /* __MINT__ */

#ifndef __MINT__
#define __DIRENTSIZ(x) (sizeof(struct dirent) + (x) + 1)
#else
#define __DIRENTSIZ(x) (sizeof(struct dirent))
#endif

/* allow BSD emulation via sys/dir.h */

#ifdef _SYS_DIR_H
#define direct		dirent
#define d_fileno	d_ino
#define d_namlen	d_reclen

#define DIRSIZ(dp) 	__DIRENTSIZ((dp)->d_namlen)
#define MAXNAMLEN	_LIB_NAME_MAX
#endif

__EXTERN DIR *		opendir	__PROTO((const char *dirname));
__EXTERN struct dirent *readdir	__PROTO((DIR *dirp));
__EXTERN struct dirent *__readdir	__PROTO((DIR *dirp));
#if defined __USE_POSIX || defined __USE_MISC
/* Reentrant version of `readdir'.  Return in RESULT a pointer to the
   next entry.  */
__EXTERN int readdir_r __PROTO ((DIR *__dirp, struct dirent *__entry,
			         struct dirent **__result));
#endif /* not __USE_POSIX and not __USE_MISC */
__EXTERN void		rewinddir __PROTO((DIR *dirp));
__EXTERN int		closedir  __PROTO((DIR *dirp));
__EXTERN off_t	telldir	__PROTO((DIR *dirp));
__EXTERN void	seekdir	__PROTO((DIR *dirp, off_t loc));
__EXTERN int	alphasort __PROTO((struct dirent **, struct dirent **));

#ifdef __cplusplus
}
#endif

#endif /* _SYS_DIRENT_H */
