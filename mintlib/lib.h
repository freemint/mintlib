/*
 * library-specific stuff
 */
#ifndef _LIB_H
#define _LIB_H

#include <stdarg.h>
#include <stdio.h>	/* for FILE.   */
#include <time.h>	/* for time_t.  */
#include <sys/stat.h>	/* For struct stat.  */

extern int __mint;
extern int __libc_enable_secure;
extern int __libc_unix_names;

int	_unx2dos (const char *, char *, size_t);
int	_dos2unx (const char *, char *, size_t);
int	_path_dos2unx (const char *, char *, size_t);
int	_path_unx2dos (const char *, char *, size_t);

int	_console_read_byte (int);
void	_console_write_byte (int, int);

time_t	__dostime (time_t);
time_t	__unixtime (unsigned int, unsigned int);

char *	_itoa (int, char *, int);
char *	_ltoa (long, char *, int);
char *	_ultoa (unsigned long, char *, int);

int	_doprnt (int (*)(int, FILE *), FILE *, const char *, __gnuc_va_list);
int	_scanf (FILE *, int (*)(FILE *), int (*)(int, FILE *), const char *, __gnuc_va_list);
int	_enoent (const char *);

long	get_sysvar (void *var);
void	set_sysvar_to_long (void *var, long val);

void	_main		(long, char **, char **);
void	_init_signal	(void);
void 	_monstartup	(void *lowpc, void *highpc);
void	__mcleanup	(void);
void	_moncontrol	(long);
void	_setstack	(char *);
void	_crtinit	(void);
void	_acc_main	(void);
void	__exit		(long status) __NORETURN;

/* 5/5/92 sb -- definitions needed in malloc.c and realloc.c */
struct mem_chunk 
{
	long valid;
#define VAL_FREE  0xf4ee0abcL
#define VAL_ALLOC 0xa11c0abcL
#define VAL_BORDER 0xb04d0abcL

	struct mem_chunk *next;
	unsigned long size;
};
#define ALLOC_SIZE(ch) (*(long *) ((char *) (ch) + sizeof (*(ch))))
#define BORDER_EXTRA ((sizeof (struct mem_chunk) + sizeof (long) + 7) & ~7)

/* linked list of free blocks */
extern struct mem_chunk _mchunk_free_list;

/* status of open files (for isatty, et al.) */
struct __open_file {
	short	status;		/* whether or not it's a tty */
	short	flags;		/* if a tty, its flags */
	short	check_eagain;	/* < 0 uninitialized
				 * = 0 don't need workaround 
				 * > 0 need workaround */
};
#define __NHANDLES 40

/* NOTE: this array is indexed by (__OPEN_INDEX(fd)) */
extern struct __open_file __open_stat[];

#define __OPEN_INDEX(x)	(((short)(x)) + 3)

#define FH_UNKNOWN	0
#define FH_ISATTY	1
#define FH_ISAFILE	2

/*
 * macro for converting a long in DOS format to one in Unix format. "x"
 * _must_ be an lvalue!
 */
# define __UNIXTIME(x) (x = __unixtime (((unsigned short *) &x)[0], \
					((unsigned short *) &x)[1]))

FILE *_fopen_i (const char *, const char *, FILE *);

/* Maybe not the best place for this... */
/* This is what Fxattr expects.  */
struct xattr
{
  unsigned short st_mode;
  long st_ino;		/* must be 32 bits */
  unsigned short st_dev;	/* must be 16 bits */
  short	st_rdev;	/* not supported by the kernel */
  unsigned short st_nlink;
  unsigned short st_uid;	/* must be 16 bits */
  unsigned short st_gid;	/* must be 16 bits */
  long st_size;
  long st_blksize;
  long st_blocks;
  unsigned long st_mtime;
  unsigned long st_atime;
  unsigned long st_ctime;
  short st_attr;
  short	res1;		/* reserved for future kernel use */
  long res2[2];
};

long Fstat (const char *path, struct stat *st, int lflag, int exact);
long Ffstat (short fd, struct stat *st, int exact);

int __quickstat (const char *_path, struct stat *st, int lflag);
int __do_stat (const char *_path, struct stat *st, int lflag);
int __do_fstat (int fd, struct stat *st, int exact);
int __do_lock (int fd, int cmd, long size, int whence);


#endif /* _LIB_H */
