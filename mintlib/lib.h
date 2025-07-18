/*
 * library-specific stuff
 */
#ifndef _LIB_H
#define _LIB_H

#include <mint/basepage.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>	/* for FILE.   */
#include <time.h>	/* for time_t.  */
#include <support.h>
#include <sys/stat.h>	/* For struct stat.  */

/*
 * cast away const-ness.
 * sometimes needed when the api requires a non-const return type
 */
#ifndef NO_CONST
#  ifdef __GNUC__
#	 define NO_CONST(p) __extension__({ union { const void *cs; void *s; } x; x.cs = p; x.s; })
#  else
#	 define NO_CONST(p) ((void *)(p))
#  endif
#endif

#if defined(__MSHORT__) || defined(__FASTCALL__)
#define NEED_SIGNAL_TRAMPOLINE 1
void __CDECL __signal_trampoline (long, long);
#else
#define NEED_SIGNAL_TRAMPOLINE 0
#endif

/* Write formatted output to STREAM from argument list ARG using
   fputc like function PUTFUNCTION.  This is provided for binary
   compatibility with older versions.  */
__EXTERN int _doprnt __P ((int (*__putfunction) (int, FILE*), 
			   FILE* __stream, const char* __format, 
			   __gnuc_va_list __arg));

int	_scanf (FILE *, int (*)(FILE *), int (*)(int, FILE *), const char *, __gnuc_va_list);
int	_enoent (const char *);

void	_crtinit	(void);
void	_main		(long, char **, char **);
void	_acc_main	(void);
void	_setstack	(char *);

/* automagically called, either on entry to main(), or by use of .init_array */
void __main (void);

void	_monstartup	(void *lowpc, void *highpc);


/* mintlib/globals.c */

extern int __mint;
extern long __has_no_ssystem;
extern int __libc_enable_secure;
extern int __libc_unix_names;

extern char _rootdir;

extern clock_t _childtime;

extern BASEPAGE *_base;
extern char **environ;
extern long __libc_argc;
extern char **__libc_argv;

extern void *_heapbase;
extern short _split_mem;

extern long _stksize;
extern char *_StkLim;
extern long _initial_stack;


extern short _app;
extern unsigned long _PgmSize;

extern char *program_invocation_name;
extern char *program_invocation_short_name;

typedef void (*ExitFn)(void);
extern ExitFn *_at_exit;
extern int _num_at_exit;

/* signal/initsig.c */

extern sighandler_t _sig_handler[NSIG];
extern long _sigmask;
extern long _sigpending;

/* unix/open.c */

extern int __current_umask;


/* status of open files (for isatty, et al.) */
struct __open_file
{
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

FILE *_fopen_i (const char *, const char *, FILE *);

/* Maybe not the best place for this... */
/* This is what Fxattr expects.  */
struct xattr
{
	unsigned short st_mode;
	long           st_ino;	/* must be 32 bits */
	unsigned short st_dev;	/* must be 16 bits */
	short          st_rdev;	/* not supported by the kernel */
	unsigned short st_nlink;
	unsigned short st_uid;	/* must be 16 bits */
	unsigned short st_gid;	/* must be 16 bits */
	long           st_size;
	long           st_blksize;
	long           st_blocks;
	unsigned long  st_mtime;
	unsigned long  st_atime;
	unsigned long  st_ctime;
	short          st_attr;
	short res1;		/* reserved for future kernel use */
	long res2[2];
};

/* mintlib/inode.c */
extern ino_t __inode;

long __sys_stat(const char *path, struct stat *st, int lflag, int exact);
long __sys_fstat(short fd, struct stat *st, int exact);

int __quickstat(const char *_path, struct stat *st, int lflag);
int __do_stat(const char *_path, struct stat *st, int lflag);
int __do_fstat(int fd, struct stat *st, int exact);
int __do_lock(int fd, int cmd, long size, int whence);

int __do_chown16 (const char *_name, uid_t uid, gid_t gid, int follow_links);

/* fopen.c */
int __getmode (const char *mode, __io_mode *mptr);
/* Defined in sysd-stdio.c.  */
int __stdio_reopen (const char *filename, __io_mode mode, void **cookieptr, __io_close_fn closefn);

void __stdio_check_funcs (FILE *);

/* Prototype for helper functions.  */
int __fxprintf (FILE *__fp, const char *__fmt, ...) __attribute__ ((__format__ (__printf__, 2, 3)));
void __stdio_init_stream(FILE *);

#ifdef _PRINTF_H
int __printf_fp (FILE *fp, const struct printf_info *info, const void *const *args);
int __printf_fphex (FILE *, const struct printf_info *, const void *const*);
#endif

int __open_v (const char *_filename, int iomode, va_list argp);

/*
 * 64bit time_t support
 */
struct utimbuf64;
struct timezone;

#define MAX_TZ_OFFSET (50400UL)
/* a bit of safety, so that adding the timezone does not overflow, either */
#define TIME32_MAX (2147483647UL - MAX_TZ_OFFSET)

__time64_t __time64(__time64_t *__timer) __THROW;
double __difftime64(__time64_t *__time1, __time64_t __time0) __THROW __attribute__ ((__const__));
__time64_t __mktime64(struct tm *__tp) __THROW;
struct tm *__gmtime64(const __time64_t *__timer) __THROW;
struct tm *__gmtime64_r (const __time64_t *__restrict __timer, struct tm *__restrict __tp) __THROW;
struct tm *__localtime64(const __time64_t *__timer) __THROW;
struct tm *__localtime64_r(const __time64_t *__timer, struct tm *__restrict __tp) __THROW;
char *__ctime64(const __time64_t *__timer) __THROW;
char *__ctime64_r(const __time64_t *__timer, char *__restrict __buf) __THROW;
__time64_t __timegm64(struct tm *__tp) __THROW;
__time64_t __timelocal64(struct tm *__tp) __THROW;
int __gettimeofday64(struct timeval64 *__restrict __tv, struct timezone *__restrict __tz) __THROW __nonnull ((1));
int __settimeofday64(const struct timeval64 *__restrict __tv, const struct timezone *__restrict __tz) __THROW __nonnull ((1));
int __stime64(const __time64_t *now) __THROW;
int __adjtime64(__const struct timeval64 *__delta, struct timeval64 *__olddelta) __THROW;
int __utime64(const char *__file, const struct utimbuf64 *__file_times) __THROW __nonnull ((1));
int __utimes64(const char *__file, const struct timeval64 __tvp[2]) __THROW __nonnull ((1));
int __futimes64(int __fd, const struct timeval64 __tvp[2]) __THROW;
int __nanosleep64(const struct timespec64 *__requested_time, struct timespec64 *__remaining);
int __clock_getres64(clockid_t __clock_id, struct timespec64 *__res) __THROW;
int __clock_gettime64(clockid_t __clock_id, struct timespec64 *__tp) __THROW __nonnull((2));
int __clock_settime64(clockid_t __clock_id, const struct timespec64 *__tp) __THROW __nonnull((2));
int __clock_nanosleep_time64(clockid_t __clock_id, int __flags, const struct timespec64 *__req, struct timespec64 *__rem);

#ifdef _SYS_TIME_H
int __getitimer64(__itimer_which_t __which, struct itimerval64 *__value) __THROW;
int __setitimer64(__itimer_which_t __which, const struct itimerval64 *__restrict __new, struct itimerval64 *__restrict __old) __THROW;
#endif

#ifdef _SYS_TIMEB_H
int __ftime64(struct timeb64 *timebuf);
#endif

#ifdef _SYS_RESOURCE_H
struct rusage64;
int __getrusage64(__rusage_who_t __who, struct rusage64 *__usage) __THROW;
static __inline void __rusage_to_rusage64(struct rusage64 *data, struct rusage *data32)
{
	data->ru_utime.tv_sec = data32->ru_utime.tv_sec;
	data->ru_utime.tv_usec = data32->ru_utime.tv_usec;
	data->ru_stime.tv_sec = data32->ru_stime.tv_sec;
	data->ru_stime.tv_usec = data32->ru_stime.tv_usec;
	data->ru_maxrss = data32->ru_maxrss;
	data->ru_ixrss = data32->ru_ixrss;
	data->ru_idrss = data32->ru_idrss;
	data->ru_isrss = data32->ru_isrss;
	data->ru_minflt = data32->ru_minflt;
	data->ru_majflt = data32->ru_majflt;
	data->ru_nswap = data32->ru_nswap;
	data->ru_inblock = data32->ru_inblock;
	data->ru_oublock = data32->ru_oublock;
	data->ru_msgsnd = data32->ru_msgsnd;
	data->ru_msgrcv = data32->ru_msgrcv;
	data->ru_nsignals = data32->ru_nsignals;
	data->ru_nvcsw = data32->ru_nvcsw;
	data->ru_nivcsw = data32->ru_nivcsw;
}
#ifdef _WAIT_H
pid_t __wait3_time64(__WP __stat_loc, int __options, struct rusage64 *__usage) __THROW;
pid_t __wait4_time64(pid_t __pid, __WP __stat_loc, int __options, struct rusage64 *__usage) __THROW;
#endif
#endif

#ifdef _SYS_SELECT_H
int __select64(int __nfds, __fd_set *__readfds, __fd_set *__writefds, __fd_set *__exceptfds, struct timeval64 *__timeout);
int __pselect64(int __nfds, __fd_set *__readfds, __fd_set *__writefds, __fd_set *__exceptfds, const struct timespec64 *__timeout, const __sigset_t *__sigmask);
#endif

#ifdef _SYS_POLL_H
int __ppoll64(struct pollfd *__fds, nfds_t __nfds, const struct timespec64 *__timeout, const __sigset_t *__ss);
#endif

#ifdef _SYS_MSG_H
int __msgctl64(int __msqid, int __cmd, struct msqid_ds64 *__buf) __THROW;
#endif

#ifdef _SYS_SEM_H
int __semctl64(int __semid, int __semnum, int __cmd, ...) __THROW;
#endif

#ifdef _SEMAPHORE_H
int __sem_timedwait64(sem_t *__restrict __sem, const struct timespec64 *__restrict __abstime) __nonnull ((1, 2));
int __sem_clockwait64(sem_t *__restrict __sem, clockid_t clock, const struct timespec64 *__restrict __abstime) __nonnull ((1, 3));
#endif

#if defined(_SIGNAL_H) && 0 /* siginfo_t NYI */
int __sigtimedwait64(const sigset_t *__restrict __set, siginfo_t *__restrict __info, const struct timespec64 *__restrict __timeout) __nonnull ((1));
#endif

#endif /* _LIB_H */
