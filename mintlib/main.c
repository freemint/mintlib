/* from Dale Schumacher's dLibs */
/* heavily modified by ers and jrb */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <osbind.h>
#include <mintbind.h>
#include <memory.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <sysvars.h>
#include <limits.h>
#include <alloca.h>
#include <errno.h>

#ifdef __TURBOC__
# include <mint\ssystem.h>
# include <sys\cookie.h>
# include <sys\param.h>
#else
# include <mint/ssystem.h>
# include <sys/cookie.h>
# include <sys/param.h>
#endif

#include "lib.h"

/* NOTE: This file must not contain ANY global symbol but _main itself.
   Otherwise the user cannot provide her own version of _main if 
   weak symbols are not available.  */
extern int __mint;      /* 0 for TOS, MiNT version number in BCD format 
		           otherwise.  */
extern int _pdomain;    /* Error code of Pdomain call */
extern char _rootdir;	/* User's preferred root directory */

extern clock_t _starttime;	/* 200 HZ tick when we started the program.  */
extern clock_t _childtime;	/* Time consumed so far by our children.  */

/* Functions registered by user for calling at exit.  */
typedef void (*ExitFn) __PROTO ((void));
__EXTERN ExitFn *_at_exit;
extern int _num_at_exit;	/* Number of functions registered - 1.  */

/* Set to 1 if secure mode is advised.  */
extern int __libc_enable_secure;

/* Set to 1 if we don't have to convert filenames to Redmond style.  */
extern int __libc_unix_names;

/* Set to 0 if Ssystem is not available.  */
extern int __has_no_ssystem;

/* Supplied by the user */
__EXTERN int main __PROTO((int, char **, char **));

#if defined(__TURBOC__) && !defined(__NO_FLOAT__)
__EXTERN void _fpuinit (void); /* in PCFLTLIB.LIB */

extern long _fpuvect[10];
extern long _pfumode;
extern long _fpuctrl;
#endif

void __libc_main __PROTO((long, char **, char **));

void
__libc_main (_argc, _argv, _envp)
	long _argc;
	char **_argv, **_envp;
{
	register int i;
	char *s, *pconv;
	long l;
	extern __io_mode __default_mode__;	/* in defmode.c or defined by user */
	extern short _app;	/* tells if we're an application or acc */

	char *p, *tmp;
	size_t len, cnt;
	
	_num_at_exit = 0;
	errno = 0;

	__libc_enable_secure = 1;
	__libc_unix_names = 0;

#if defined(__TURBOC__) && !defined(__NO_FLOAT__)
	_fpuinit();
#endif

	__has_no_ssystem = Ssystem (-1, NULL, NULL);
	_starttime = get_sysvar (_hz_200);
	_childtime = 0;
/*
 * check for MiNT
 */
 	if (Getcookie (C_MiNT, &l) == C_FOUND)
 		__mint = (int) l;
 	else
 		__mint = 0;
 		
	if (_app)
		_pdomain = Pdomain(1);	/* set MiNT domain */

	/* Check hardware requirements.  */
#ifdef __M68020__
	if (Getcookie (C__CPU, &l) != C_FOUND || l < 20)
		__libc_fatal ("this program requires an m68020 cpu or higher!");
#endif
#ifdef __M68881__
	if (Getcookie (C__FPU, &l) != C_FOUND || l == 0)
		__libc_fatal ("this program requires an fpu!");
#endif

/* Check if we are suid or guid.  We simply use the bare operating
   system calls because we only check for differences.  If it fails
   once it will always fail.  */
   	if ((Pgeteuid () == Pgetuid ()) && (Pgetegid () == Pgetgid ()))
	     	__libc_enable_secure = 0;
     
/*
 * initialize UNIXMODE stuff. Note that this library supports only
 * a few of the UNIXMODE variables, namely "b" (binary mode default)
 * and "r<c>" (default root directory).
 */
#if 1
 	if (__libc_enable_secure) {
 	  /* Don't do any TOS nonsense in secure mode.  */
 	  __default_mode__.__binary = 1;
 	  /* _rootdir = 'u'; */
	} else
#endif
	/* For UNIXMODE we currently have to live with the security
	   hole imposed by getenv().  */
	if ((s = getenv("UNIXMODE")) != 0) {
		while (*s) {
			if (*s == 'b')
				__default_mode__.__binary = 1;
			else if (*s == 'r' && s[1])
				_rootdir = *++s;
			else if (*s == '.' && s[1])
				s++;	/* ignore */
			s++;
		}
	}

	if (_rootdir >= 'A' && _rootdir <= 'Z')
		_rootdir = _rootdir - 'A' + 'a';
	/* Better check for illegal settings.  */
	else if (_rootdir < 'a' || _rootdir > 'z')
		_rootdir = 0;

/*
 * if we're running under MiNT, and the current drive is U:, then this
 * must be our preferred drive
 */
	if (!_rootdir && __mint >= 9) {
		if (Dgetdrv() == 'U'-'A')
			_rootdir = 'u';
	}

/*
 * If running under some recent MiNT there is no reason to convert 
 * all filenames to redmond style with drive letter and backslashes.
 * I assume here that this is not necessary for MiNT >1.12.  Correct?
 * Can't we assume earlier versions?
 */
 	if (__mint > 0x10c && _rootdir && Dgetdrv() == _rootdir - 'a')
 	  {
 	     __libc_unix_names = 1;
 	  }
 	  
	/* clear isatty status for dumped programs */
	for (i = 0; i < __NHANDLES; i++)
	  __open_stat[i].status = FH_UNKNOWN;

/* if stderr is not re-directed to a file, force 2 to console
 * (UNLESS we've been run from a shell we trust, i.e. one that supports
 *  the official ARGV scheme, in which case we leave stderr be).
 */
	if(!*_argv[0] && isatty(2))
	    (void)Fforce(2, -1);

	stdin = fdopen (0, "r");
	stdout = fdopen (1, "w");
	stderr = fdopen (2, "r+");
	
	if (stdin == NULL || stdout == NULL || stderr == NULL) {
		extern char* program_invocation_name;
		Fwrite (2, strlen (program_invocation_name),
		        program_invocation_name);
		Fwrite (2, sizeof ": " - 1,
		        ": ");
		Fwrite (2, sizeof "virtual memory exhausted\r\n" - 1,
		        "virtual memory exhausted\r\n");
		_exit (1);
	}
	
	setvbuf (stdin, NULL, _IOFBF, 0);
	setvbuf (stdout, NULL, _IOLBF, 0);
	setvbuf (stderr, NULL, _IONBF, 0);

	/* Flag device streams.  */
	if (isatty (0)) {
		if (__mint) stdin->__mode.__binary = 1;
	}
	if (isatty (1)) {
		if (__mint) stdout->__mode.__binary = 1;
	} else {
		/* If redirected, make stdout fully buffered.  */
		setvbuf (stdout, NULL, _IOFBF, 0);
	}
	if (isatty (2)) {
		if (__mint) stderr->__mode.__binary = 1;
	}

#if 0
	/* FIXME:  Handle streams for fd 3-5.  */
 	for(i = 3; i < _NFILE; i++, f++) {
	  f->_flag = 0;		/* clear flags, if this is a dumped program */
	}
#endif

	/* Fix up environment, if necessary. All variables listed in PCONVERT
	 * are affected (by default, only PATH will be converted).
	 * The "standard" path separators for PATH are
	 * ',' and ';' in the Atari world, but POSIX mandates ':'. This
	 * conflicts with the use of ':' as a drive separator, so we
	 * also convert names like A:\foo to /dev/A/foo
	 * NOTE: this conversion must be undone in spawn.c so that
	 * old fashioned programs will understand us!
	 */

	for (i = 0; (pconv = _envp[i]) != 0; i++) {
		if (! strncmp(pconv, "PCONVERT=", 9)) {
			pconv += 9;
			break;
		}
	}

	for (i = 0; (s = _envp[i]) != 0; i++) {

		if (pconv) {

			p = pconv;
			while (*p) {
				
				tmp = p; len = 0;
				while (*tmp && *tmp != ',') {
					tmp++; len++;
				}
				
				if (!strncmp(s, p, len) && s[len] == '=') {
				  size_t size;
				  len++;
				  tmp = s + len; /* tmp now after '=' */
				  cnt = 1;
				  while (*tmp) {  /* count words */
				    if (*tmp == ';' || *tmp == ',')
				      cnt++;
				    tmp++;
				  }
				  size = tmp - s + cnt * 5;
				  _envp[i] = (char *) malloc(size);
				  strncpy(_envp[i], s, len);
				  _path_dos2unx(s + len, _envp[i] + len,
						size - len);
				  _envp[i] = (char *) realloc(_envp[i], 
						        strlen(_envp[i]) + 1);
				  break;		
				}
				
				if (! *tmp) break;
				p = tmp + 1;
			}
		}	
		else	/* ! pconv */
		{
		/* PATH is always converted */
			if (s[0] == 'P' && s[1] == 'A' && s[2] == 'T' &&
			    s[3] == 'H' && s[4] == '=')
			{
			  size_t size;
			  tmp = s + 5; /* tmp now after '=' */	
			  cnt = 1;
			  while (*tmp)
			  {
			    /* count words */
			    if (*tmp == ';' || *tmp == ',')
			      cnt++;
			    tmp++;
			  }
			  size = tmp - s + cnt * 5;
			  _envp[i] = (char *) malloc(size);
			  strncpy(_envp[i], s, 5);
			  _path_dos2unx(s + 5, _envp[i] + 5, size - 5);
			  _envp[i] = (char *) realloc(_envp[i], 
			                              strlen(_envp[i]) + 1);
			  break;
			}
		}
	}
	
	/* Start with a clean errno.  */
	__set_errno (0);
	
	/* ANSI-Draft: A return from the initial call to the main 
	 * function is equivalent to calling the exit function with
	 * the value returned by the main function as its argument. If
	 * the main function executes a return that specifies no
	 * value, the termination status returned to the host
	 * environment is undefined. [section 2.1.2.2]
	 */
	exit(main((int) _argc, _argv, _envp));
}

weak_alias (__libc_main, _main)
