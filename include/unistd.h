/*
 *	POSIX Standard: 2.10 Symbolic Constants		<unistd.h>
 */

#ifndef _UNISTD_H
#define _UNISTD_H

#ifndef _FEATURES_H
#include <features.h>
#endif

__BEGIN_DECLS

/* These may be used to determine what facilities are present at compile time.
   Their values can be obtained at run time from `sysconf'.  */

/* POSIX Standard approved as ISO/IEC 9945-1 as of August, 1988 and
   extended by POSIX-1b (aka POSIX-4) and POSIX-1c (aka POSIX threads).  */
#define	_POSIX_VERSION	199506L

/* These are not #ifdef __USE_POSIX2 because they are
   in the theoretically application-owned namespace.  */

/* POSIX Standard approved as ISO/IEC 9945-2 as of December, 1993.  */
#define	_POSIX2_C_VERSION	199209L

/* The utilities on GNU systems also correspond to this version.  */
#define _POSIX2_VERSION	199209L

/* If defined, the implementation supports the
   C Language Bindings Option.  */
#define	_POSIX2_C_BIND	1

/* If defined, the implementation supports the
   C Language Development Utilities Option.  */
#define	_POSIX2_C_DEV	1

/* If defined, the implementation supports the
   Software Development Utilities Option.  */
#define	_POSIX2_SW_DEV	1

/* If defined, the implementation supports the
   creation of locales with the localedef utility.  */
#define _POSIX2_LOCALEDEF       1

/* X/Open version number to which the library conforms.  It is selectable.  */
#ifdef __USE_UNIX98
# define _XOPEN_VERSION	500
#else
# define _XOPEN_VERSION	4
#endif

/* Commands and utilities from XPG4 are available.  */
#define _XOPEN_XCU_VERSION	4

/* We are compatible with the old published standards as well.  */
#define _XOPEN_XPG2	1
#define _XOPEN_XPG3	1
#define _XOPEN_XPG4	1

/* The X/Open Unix extensions are available.  */
#define _XOPEN_UNIX	1

/* Encryption is present.  */
#define	_XOPEN_CRYPT	1

/* The enhanced internationalization capabilities according to XPG4.2
   are present.  */
#define	_XOPEN_ENH_I18N	1

/* The legacy interfaces are also available.  */
#define _XOPEN_LEGACY	1


/* Get values of POSIX options:

   If these symbols are defined, the corresponding features are
   always available.  If not, they may be available sometimes.
   The current values can be obtained with `sysconf'.

   _POSIX_JOB_CONTROL		Job control is supported.
   _POSIX_SAVED_IDS		Processes have a saved set-user-ID
   				and a saved set-group-ID.
   _POSIX_REALTIME_SIGNALS	Real-time, queued signals are supported.
   _POSIX_PRIORITY_SCHEDULING	Priority scheduling is supported.
   _POSIX_TIMERS		POSIX.4 clocks and timers are supported.
   _POSIX_ASYNCHRONOUS_IO	Asynchronous I/O is supported.
   _POSIX_PRIORITIZED_IO	Prioritized asynchronous I/O is supported.
   _POSIX_SYNCHRONIZED_IO	Synchronizing file data is supported.
   _POSIX_FSYNC			The fsync function is present.
   _POSIX_MAPPED_FILES		Mapping of files to memory is supported.
   _POSIX_MEMLOCK		Locking of all memory is supported.
   _POSIX_MEMLOCK_RANGE		Locking of ranges of memory is supported.
   _POSIX_MEMORY_PROTECTION	Setting of memory protections is supported.
   _POSIX_MESSAGE_PASSING	POSIX.4 message queues are supported.
   _POSIX_SEMAPHORES		POSIX.4 counting semaphores are supported.
   _POSIX_SHARED_MEMORY_OBJECTS	POSIX.4 shared memory objects are supported.
   _POSIX_THREADS		POSIX.1c pthreads are supported.
   _POSIX_THREAD_ATTR_STACKADDR	Thread stack address attribute option supported.
   _POSIX_THREAD_ATTR_STACKSIZE	Thread stack size attribute option supported.
   _POSIX_THREAD_SAFE_FUNCTIONS	Thread-safe functions are supported.
   _POSIX_THREAD_PRIORITY_SCHEDULING
				POSIX.1c thread execution scheduling supported.
   _POSIX_THREAD_PRIO_INHERIT	Thread priority inheritance option supported.
   _POSIX_THREAD_PRIO_PROTECT	Thread priority protection option supported.
   _POSIX_THREAD_PROCESS_SHARED	Process-shared synchronization supported.
   _POSIX_PII			Protocol-independent interfaces are supported.
   _POSIX_PII_XTI		XTI protocol-indep. interfaces are supported.
   _POSIX_PII_SOCKET		Socket protocol-indep. interfaces are supported.
   _POSIX_PII_INTERNET		Internet family of protocols supported.
   _POSIX_PII_INTERNET_STREAM	Connection-mode Internet protocol supported.
   _POSIX_PII_INTERNET_DGRAM	Connectionless Internet protocol supported.
   _POSIX_PII_OSI		ISO/OSI family of protocols supported.
   _POSIX_PII_OSI_COTS		Connection-mode ISO/OSI service supported.
   _POSIX_PII_OSI_CLTS		Connectionless ISO/OSI service supported.
   _POSIX_POLL			Implementation supports `poll' function.
   _POSIX_SELECT		Implementation supports `select' and `pselect'.

   _XOPEN_REALTIME		X/Open realtime support is available.
   _XOPEN_REALTIME_THREADS	X/Open realtime thread support is available.
   _XOPEN_SHM			Shared memory interface according to XPG4.2.

   _XBS5_ILP32_OFF32		Implementation provides environment with 32-bit
				int, long, pointer, and off_t types.
   _XBS5_ILP32_OFFBIG		Implementation provides environment with 32-bit
				int, long, and pointer and off_t with at least
				64 bits.
   _XBS5_LP64_OFF64		Implementation provides environment with 32-bit
				int, and 64-bit long, pointer, and off_t types.
   _XBS5_LPBIG_OFFBIG		Implementation provides environment with at
				least 32 bits int and long, pointer, and off_t
				with at least 64 bits.

   If any of these symbols is defined as -1, the corresponding option is not
   true for any file.  If any is defined as other than -1, the corresponding
   option is true for all files.  If a symbol is not defined at all, the value
   for a specific file can be obtained from `pathconf' and `fpathconf'.

   _POSIX_CHOWN_RESTRICTED	Only the super user can use `chown' to change
   				the owner of a file.  `chown' can only be used
				to change the group ID of a file to a group of
				which the calling process is a member.
   _POSIX_NO_TRUNC		Pathname components longer than
   				NAME_MAX generate an error.
   _POSIX_VDISABLE		If defined, if the value of an element of the
				`c_cc' member of `struct termios' is
				_POSIX_VDISABLE, no character will have the
				effect associated with that element.
   _POSIX_SYNC_IO		Synchronous I/O may be performed.
   _POSIX_ASYNC_IO		Asynchronous I/O may be performed.
   _POSIX_PRIO_IO		Prioritized Asynchronous I/O may be performed.

   Support for the Large File Support interface is not generally available.
   If it is available the following constants are defined to one.
   _LFS64_LARGEFILE		Low-level I/O supports large files.
   _LFS64_STDIO			Standard I/O supports large files.
   */

#include <bits/posix_opt.h>

/* The environment definitions from Unix98.  */
#ifdef __USE_UNIX98
/* By default we have 32-bit wide `int', `long int', pointers and `off_t'.  */
# define _XBS5_ILP32_OFF32	1

/* We optionally provide an environment with the above size but an 64-bit
   side `off_t'.  Therefore we don't define _XBS5_ILP32_OFFBIG.  */

/* We can never provide environments with 64-bit wide pointers.  */
# define _XBS5_LP64_OFF64	-1
# define _XBS5_LPBIG_OFFBIG	-1
#endif

/* Standard file descriptors.  */
#define	STDIN_FILENO	0	/* Standard input.  */
#define	STDOUT_FILENO	1	/* Standard output.  */
#define	STDERR_FILENO	2	/* Standard error output.  */


/* All functions that are not declared anywhere else.  */

#include <bits/types.h>

#ifndef	ssize_t
typedef __ssize_t ssize_t;
# define ssize_t ssize_t
#endif

#define	__need_size_t
#define __need_NULL
#include <stddef.h>

#ifdef __USE_XOPEN
/* The Single Unix specification says that some more types are
   available here.  */
# ifndef gid_t
typedef __gid_t gid_t;
#  define gid_t gid_t
# endif

# ifndef uid_t
typedef __uid_t uid_t;
#  define uid_t uid_t
# endif

# ifndef off_t
#  ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
#  else
typedef __off64_t off_t;
#  endif
#  define off_t off_t
# endif
# if defined __USE_LARGEFILE64 && !defined off64_t
typedef __off64_t off64_t;
#  define off64_t off64_t
# endif

# ifndef pid_t
typedef __pid_t pid_t;
#  define pid_t pid_t
# endif
#endif	/* X/Open */

#ifdef __USE_UNIX98
# ifndef intptr_t
typedef __intptr_t intptr_t;
#  define intptr_t intptr_t
# endif
#endif	/* Unix98 */

/* file access stuff */
#ifndef F_OK
# define	F_OK			0
# define	X_OK			1
# define	W_OK			2
# define	R_OK			4
#endif

#ifndef SEEK_SET
/* lseek() origins */
#define	SEEK_SET	0		/* from beginning of file */
#define	SEEK_CUR	1		/* from current location */
#define	SEEK_END	2		/* from end of file */
#endif

#if defined __USE_BSD && !defined L_SET
/* Old BSD names for the same constants; just for compatibility.  */
# define L_SET		SEEK_SET
# define L_INCR		SEEK_CUR
# define L_XTND		SEEK_END
#endif

/* sysconf() values */
#define _SC_LAST	-1	/* max limit # for sysconf - NOT POSIX */
#define _SC_MEMR_MAX	0	/* memory regions per process - NOT POSIX */
#define _SC_ARG_MAX	1	/* max length of cmdln - NOT quite POSIX */
#define _SC_OPEN_MAX	2	/* max # of open files per process - POSIX */
#define _SC_NGROUPS_MAX	3	/* max # supp gids - POSIX */
#define _SC_CHILD_MAX	4	/* max # processes/user - NOT quite POSIX */

/* pathconf() values */
#define _PC_LAST	-1	/* max limit # for pathconf - POSIX (!?) */
#define _PC_IOPEN_MAX	0	/* internal limit on open files - NOT POSIX */
#define _PC_LINK_MAX	1	/* max # of links - POSIX */
#define _PC_PATH_MAX	2	/* max len of a full pathname - POSIX */
#define _PC_NAME_MAX	3	/* max len of individual name - POSIX */
#define _PC_PIPE_BUF	4	/* bytes written atomically to fifo - POSIX */
#define _PC_NO_TRUNC	5	/* filename truncation - POSIX */
#ifdef __MINT__
#  define _MINT_PC_NAME_CASE 6  /* case-insensitive file-names */
#endif

#ifdef __MINT__
# if defined (__USE_MISC) && !defined (F_LOCK)
/* NOTE: These declarations also appear in <fcntl.h>; be sure to keep both
   files consistent.  Some systems have them there and some here, and some
   software depends on the macros being defined without including both.  */

/* `lockf' is a simpler interface to the locking facilities of `fcntl'.
   LEN is always relative to the current file position.
   The CMD argument is one of the following.  */

/* flock() commands */
#  define F_ULOCK	0	/* unlock */
#  define F_LOCK	1	/* lock */
#  define F_TLOCK	2	/* test and lock (non-blocking) */
#  define F_TEST	3	/* test */
__EXTERN int		lockf	__PROTO((int, int, long));
# endif
#endif /* __MINT__ */

/* If the license of your software does not meet the requirements of 
   GNU General Public License you cannot use the more sophisticated GNU
   versions of the getopt functions.  Define _AVOID_GPL in this case.
   Then your program will get linked against the original MiNTLib
   versions.  */
#ifdef _AVOID_GPL
# define getopt __getopt_old
# define optind __optind_old
# define opterr __opterr_old
# define optopt __optopt_old
# define optarg __optarg_old
#endif

__EXTERN __EXITING _exit	__PROTO((int)) __NORETURN;
__EXTERN int	access	__PROTO((const char *, int));
__EXTERN unsigned alarm	__PROTO((unsigned));
__EXTERN int	chdir	__PROTO((const char *));
__EXTERN int	chown	__PROTO((const char *, int, int));
__EXTERN int	close	__PROTO((int));
__EXTERN int	dup	__PROTO((int));
__EXTERN int	dup2	__PROTO((int, int));
__EXTERN int	execl	__PROTO((const char *, ...));
__EXTERN int	execle	__PROTO((const char *, ...));
__EXTERN int	execlp	__PROTO((const char *, ...));
__EXTERN int	execv	__PROTO((const char *, char *const *));
__EXTERN int	execve	__PROTO((const char *, char *const *, char *const *));
__EXTERN int	execvp	__PROTO((const char *, char *const *));
__EXTERN int	fork	__PROTO((void));
__EXTERN char *	getcwd	__PROTO((char *, int));
__EXTERN __gid_t	getegid	__PROTO((void));
__EXTERN __uid_t	geteuid	__PROTO((void));
__EXTERN __gid_t	getgid	__PROTO((void));
__EXTERN int	getgroups __PROTO((int, __gid_t *));
__EXTERN char *	getlogin __PROTO((void));
__EXTERN int	getpid	__PROTO((void));
__EXTERN int	getppid	__PROTO((void));
__EXTERN __uid_t	getuid	__PROTO((void));
__EXTERN int	isatty	__PROTO((int));
__EXTERN int	link	__PROTO((const char *oldname, const char *newname));
__EXTERN __off_t	lseek	__PROTO((int, long, int));
__EXTERN int	pause	__PROTO((void));
__EXTERN int	pipe	__PROTO((int *));
__EXTERN long	pathconf __PROTO((const char *, int));
__EXTERN int	rmdir	__PROTO((const char *));
__EXTERN ssize_t read	__PROTO((int, void *, size_t));
__EXTERN int	setgid	__PROTO((int));
__EXTERN int	setuid	__PROTO((int));
__EXTERN unsigned sleep	__PROTO((unsigned int));
__EXTERN long	sysconf	__PROTO((int));

/* Return the pathname of the terminal FD is open on, or NULL on
   errors.  The returned storage is good only until the next call
   to the function.  */
__EXTERN char*	ttyname	__PROTO((int __fd));

/* Store at most BUFLEN characters of the pathname of the terminal FD
   is open on in BUF.  Return 0 on success, otherwise an error number.  */
__EXTERN int ttyname_r __PROTO((int __fd, char* __buf, size_t __buflen));
 
__EXTERN int	unlink	__PROTO((const char *));
__EXTERN ssize_t write __PROTO((int, const void *, size_t));

#if defined (__USE_BSD) || defined (__USE_XOPEN)
/* Make PATH be the root directory (the starting point for absolute
   paths).  This call is restricted to the super-user.
   NOTE: This call does NOT change the current directory!  */
__EXTERN int	chroot  __PROTO((const char* __path));

/* Put the name of the current host in no more than LEN bytes of
   NAME.  The result is null-terminated if LEN is large enough for
   the full name and the terminator.  */
__EXTERN int	gethostname __PROTO((char *__buf, size_t __len));

/* Set the name of the current host to NAME, which is LEN bytes long.
   This call is restricted to the super-user.  This is a stub function
   that will always return -1 and set errno to ENOSYS.  */
__EXTERN int    sethostname __PROTO((const char *__buf, size_t __len));

/* Get and set the NIS (aka YP) domain name, if any.  Called just like
   `gethostname'.  The NIS domain is usually the empty string when not
   using NIS.  Setting the domainn name is currently not supported
   under MiNT.  */
__EXTERN int getdomainname __PROTO((char* __name, size_t __len));
__EXTERN int setdomainname __PROTO((char* __name, size_t __len));


/* Make all changes done to FD actually appear on disk.  */
__EXTERN int fsync __PROTO ((int __fd));

/* Successive calls return the shells listed in `/etc/shells'.  */
__EXTERN char* getusershell __PROTO ((void));
__EXTERN void endusershell __PROTO ((void));  /* Discard cached info.  */
__EXTERN void setusershell __PROTO ((void));  /* Rewind and re-read the 
                                                 file.  */

/* Prompt with PROMPT and read a string from the terminal without
   echoing.  Uses /dev/tty if possible; otherwise stderr and stdin.  */
__EXTERN char *	getpass	__PROTO((const char *__prompt));

/* Put the program in the background, and dissociate from the controlling
   terminal.  If NOCHDIR is zero, do `chdir ("/")'.  If NOCLOSE is zero,
   redirects stdin, stdout, and stderr to `/dev/null'.  */
__EXTERN int daemon __PROTO ((int __nochdir, int __noclose));
#endif

#if defined (__USE_BSD) || defined (__USE_XOPEN_EXTENDED)

/* Make all changes done to all files acutally appear on disk.  */
__EXTERN int sync __PROTO ((void));

/* Return the number of bytes in a page.  This is the system's page size,
   which is not necessarily the same as the hardware page size.  */
__EXTERN int getpagesize __PROTO((void));

/* Truncate FILE to LENGTH bytes.  */
__EXTERN int truncate __PROTO ((const char* __file, __off_t __length));

/* Truncate the file FD is open on to LENGTH bytes.  */
__EXTERN int ftruncate __PROTO ((int fd, __off_t __length));

/* Return the maximum number of file descriptors the current process
   could possible have.  */
__EXTERN int    getdtablesize __PROTO ((void));
#endif

__EXTERN int	__bsd_getpgrp __PROTO((int));
__EXTERN int	__bsd_setpgrp __PROTO((int, int));

__EXTERN int	getloadavg __PROTO((double *, int));  /* Should it be here?  */

__EXTERN char *	getwd	__PROTO((char *));
__EXTERN int	getopt	__PROTO((int, char * const *, const char *));
__EXTERN char *	initstate __PROTO((unsigned int __seed, char *__arg_state, 
                                   int __n));

__EXTERN void	psignal	__PROTO((int, const char *));
__EXTERN long 	random	__PROTO((void));
__EXTERN long	_read	__PROTO((int, void *, unsigned long));
__EXTERN int	readlink __PROTO((const char *__filename, char *__linkto, int __siz));
__EXTERN int	__readlink __PROTO((const char *__filename, char *__linkto, int __siz));
__EXTERN void *	sbrk	__PROTO((size_t));
__EXTERN void *	_sbrk	__PROTO((long));
__EXTERN int	setegid	__PROTO((int));
__EXTERN int	seteuid	__PROTO((int));
__EXTERN int	setregid __PROTO((int, int));
__EXTERN int	setreuid __PROTO((int, int));
__EXTERN char *	setstate __PROTO((char *arg_state));
__EXTERN void	srandom	__PROTO((unsigned int seed));

__EXTERN int	symlink __PROTO((const char *oldname, const char *newname));

#ifdef __MSHORT__
/* Hm, syscall() must return int, but some of the functions it calls
   actually return long or even unsigned long.  What should we do?
   Using -mshort is not portable and so we declare syscall() in a
   non-portable way here.  */
__EXTERN long	syscall	__PROTO((int, ...));
#else
__EXTERN int	syscall __PROTO((int, ...));
#endif

__EXTERN long	tell	__PROTO((int));
__EXTERN void	usleep	__PROTO((unsigned long));
__EXTERN int	vfork	__PROTO((void));
__EXTERN long	_write	__PROTO((int, const void *, unsigned long));

#ifdef __SOZOBON__
#define lsbrk _sbrk	/* backwards compatibility, don't use */
#endif

#ifndef __FAVOR_BSD
__EXTERN __pid_t getpgrp __PROTO ((void));
__EXTERN int	setpgrp	__PROTO ((void));
#else /* Favor BSD.  */
# define getpgrp __bsd_getpgrp
# define setpgrp __bsd_setpgrp
#endif

__EXTERN int	setpgid __PROTO((__pid_t, __pid_t));
__EXTERN __pid_t	setsid __PROTO((void));
__EXTERN __pid_t	tcgetpgrp	__PROTO((int fd));
__EXTERN int	tcsetpgrp	__PROTO((int fd, __pid_t pgrp));

extern int optind;
extern int opterr;
extern char* optarg;
extern int optopt;

#if defined (__USE_BSD) || defined (__USE_XOPEN_EXTENDED)
/* Change the owner and group of the file that FD is open on.  */
__EXTERN int fchown __PROTO ((int __fd, __uid_t __owner, __gid_t __group));

#if 0
/* Change owner and group of FILE, if it is a symbolic link link the
   ownership of the symbolic link ischanged.  */
__EXTERN int lchown __PROTO ((const char* __file, __uid_t __owner,
                              __gid_t __group));
#endif
#endif

#ifdef __USE_GNU

/* Evaluate EXPRESSION, and repeat as long as it returns -1 with `errno'
   set to EINTR.  Because EINTR is fake with MiNT this is a stubs macro
   but we provide to allow writing portable code.  */

#define TEMP_FAILURE_RETRY(expression) expression

/* This variable is set nonzero at startup if the process's effective IDs
   differ from its real IDs, or it is otherwise indicated that extra
   security should be used.  */
extern int __libc_enable_secure;

#endif

#if defined(__cplusplus)
}
#endif

#endif /* _UNISTD_H */
