/* from Dale Schumacher's dLibs */
/* heavily modified by ers and jrb */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <alloca.h>
#include <errno.h>

#include <mint/cookie.h>
#include <mint/mintbind.h>
#include <mint/ssystem.h>
#include <mint/sysvars.h>
#include <sys/param.h>
#include <sys/stat.h>

#include "lib.h"

/* NOTE: This file must not contain ANY global symbol but _main itself.
   Otherwise the user cannot provide her own version of _main if 
   weak symbols are not available.  */

/* Supplied by the user */
extern int main (int, char **, char **);

/* in defmode.c or defined by user */
extern __io_mode __default_mode__;

/* Initialize a stream with the correct text or binary mode.  */
static void
init_stream_mode(FILE* stream)
{
	int fd;
	struct stat st;
	int result;
	
	/* By default, the standard streams use binary mode.
	 * This is especially important for the pipes and the console.
	 */
	
	__set_binmode(stream, 1);
	
	fd = fileno(stream);
	if (fd < 0)
		return;
		
	if (!__mint && isatty(fd))
	{
		/* The current implementation of the TOS console needs textmode.  */
		__set_binmode(stream, 0);
		return;
	}
	
	result = fstat(fd, &st);
	if (result < 0)
		return;
		
	/* If the standard stream is redirected to a regular file,
	 * use the mode requested by the user via the UNIXMODE variable.
	 */
	if (S_ISREG(st.st_mode))
		__set_binmode(stream, __default_mode__.__binary);
}

void
__libc_main (long _argc, char **_argv, char **_envp)
{
	register int i;
	char *s, *pconv;
	long l;

	char *p, *tmp;
	size_t len, cnt;
	
	_num_at_exit = 0;
	__set_errno (0);

	__libc_enable_secure = 1;
	__libc_unix_names = 0;

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

	/* Check if we are suid or guid.  We simply use the bare operating
	 * system calls because we only check for differences.  If it fails
	 * once it will always fail.
	 */
   	if ((Pgeteuid () == Pgetuid ()) && (Pgetegid () == Pgetgid ()))
	     	__libc_enable_secure = 0;
     
	/* initialize UNIXMODE stuff. Note that this library supports only
	 * a few of the UNIXMODE variables, namely "b" (binary mode default)
	 * and "r<c>" (default root directory). And "s" for scriptability.
	 */
#if 1
 	if (__libc_enable_secure) {
		/* Don't do any TOS nonsense in secure mode.  */
		__default_mode__.__binary = 1;
		/* _rootdir = 'u'; */
	} else
#endif
	/* For UNIXMODE we currently have to live with the security
	 * hole imposed by getenv().
	 *
	 * See spawn.c for scriptability check.
	 */
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

	/* if we're running under MiNT, and the current drive is U:, then this
	 * must be our preferred drive
	 */
	if (!_rootdir && __mint >= 9) {
		if (Dgetdrv() == 'U'-'A')
			_rootdir = 'u';
	}

	/* If running under some recent MiNT there is no reason to convert 
	 * all filenames to redmond style with drive letter and backslashes.
	 * I assume here that this is not necessary for MiNT >1.12.  Correct?
	 * Can't we assume earlier versions?
	 */
 	if (__mint > 0x10c && _rootdir && Dgetdrv() == _rootdir - 'a')
		__libc_unix_names = 1;

	/* clear isatty status for dumped programs */
	for (i = 0; i < __NHANDLES; i++)
		__open_stat[i].status = FH_UNKNOWN;

	/* if stderr is not re-directed to a file, force 2 to console
	 * (UNLESS we've been run from a shell we trust, i.e. one that supports
	 *  the official ARGV scheme, in which case we leave stderr be).
	 */
	if(!*_argv[0] && isatty (2))
		(void) Fforce(2, -1);

#if 0
/* fna: see in globals.c the
 *      new static initialization
 */
	stdin = fdopen (0, "r");
	stdout = fdopen (1, "w");
	stderr = fdopen (2, "r+");
	
	if (stdin == NULL || stdout == NULL || stderr == NULL) {
		Fwrite (2, strlen (program_invocation_name),
		        program_invocation_name);
		Fwrite (2, sizeof ": " - 1,
		        ": ");
		Fwrite (2, sizeof "virtual memory exhausted\r\n" - 1,
		        "virtual memory exhausted\r\n");
		_exit (1);
	}
#endif
	
	/* XXX guido, I'm not sure how to static initialize that */
	setvbuf (stdin, NULL, _IOFBF, 0);
	setvbuf (stdout, NULL, _IOLBF, 0);
	setvbuf (stderr, NULL, _IONBF, 0);
	
	if (!isatty (1)) {
		/* If redirected, make stdout fully buffered.  */
		setvbuf (stdout, NULL, _IOFBF, 0);
	}
	
	/* Set the standard streams with the the correct text or binary mode.  */
	init_stream_mode(stdin);
	init_stream_mode(stdout);
	init_stream_mode(stderr);

#if 0
/* used in limits.h, stdio.h */
#define	_NFILE		(32)		/* maximum number of open streams */

	/* FIXME:  Handle streams for fd 3-5.  */
 	for (i = 3; i < _NFILE; i++, f++) {
 		/* clear flags, if this is a dumped program */
		f->_flag = 0;
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
		if (!strncmp(pconv, "PCONVERT=", 9)) {
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
				  _envp[i] = malloc(size);
				  strncpy(_envp[i], s, len);
				  _path_dos2unx(s + len, _envp[i] + len, size - len);
				  _envp[i] = realloc(_envp[i], strlen(_envp[i]) + 1);
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
			  _envp[i] = malloc(size);
			  strncpy(_envp[i], s, 5);
			  _path_dos2unx(s + 5, _envp[i] + 5, size - 5);
			  _envp[i] = realloc(_envp[i], strlen(_envp[i]) + 1);
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
