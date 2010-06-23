/*
   89/03/02: ERS: added the "mode" argument for MS-DOS/Unix
   compatibility. Added prototypes for GNU C.

   fixed spawnve: the original didn't pass the command tail
   correctly, nor did it handle errno right. Also, this version
   passes args in the environment as well as the command line,
   using the ARGV= mechanism supported by crt0.s

   Written 89/01/10 by ERS. Original version Copyright (c) 1988 by
   Memorial University of Newfoundland. This version is based upon
   that original, but is substantially different. (In fact, there
   probably isn't a single line of the original left.)

   Adapted 90/06/25 by ERS to MiNT.

   08 Apr 93 hohmuth
	added support for ARGV standard extension allowing empty arguments

   uo, 3.5.93, throw away some static characterarrays (path[] and
   cmd[]).

   10 Jul 1993 ole
   added emulation for script execution.
   This feature is controlable by the Environment variable "UNIXMODE".
   The switch 's' in UNIXMODE says that executable text files with a
   hash as their first character are interpretable.
   Files which have only '#'  as their first character are interpreted
   using /bin/sh
   Files which have i.e '#!/usr/bin/awk -f' as their first character
   are interpreted with "/usr/bin/awk -f <file>"

   17 Sep 1993 schwab
   cleaned up emulation code for script execution.
   File is only interpretable if first two bytes are "#!".
   Don't modify errno if there is no error.
*/

#include <stdarg.h>
#include <process.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <support.h>

#include <sys/param.h>
#include <mint/mintbind.h>

#include "lib.h"


#define TOS_ARGS 126

/* comment this out, if you don't want script execution */
#define HASH_BANG

#ifdef HASH_BANG

static char const *const extensions[] = { "ttp", "prg", "tos", NULL };

static int interpret_script (int mode, const char *path, const char *,
			     char *const *argv, char *const *envp);

static int
interpret_script(mode, path, _path, argv, envp)
	int		mode;
	const char *path;
	const char *_path;
	char	*const *argv;
	char	*const *envp;
{
	char	tmppath[PATH_MAX];
	char	*shell;
	char	*shellargs;
	char	**shellargv;
	int		nargcount;
	int		fd;
	int		argcount;
	int		i, rv;
	char buf[1024], *bufp, *argp;
	long r;

	/* path is already converted to dos */
	if ((fd = (int)Fopen(path, 0)) < 0)
	  {
	    __set_errno (-fd);
	    return -1;
	  }

	r = Fread (fd, (long) sizeof (buf) - 1L, buf);
	Fclose (fd);
	if (r < 0)
	  {
	    __set_errno (-r);
	    return -1;
	  }
	buf[r] = 0;

	if (buf[0] == '#' && buf[1] == '!')
	  {
	    /* skip blanks */
	    bufp = buf + 2;
	    while (*bufp == '\t' || *bufp == ' ')
	      bufp++;

	    /* read filename */
	    shell = bufp;
	    while (*bufp && *bufp != ' ' && *bufp != '\t'
		   && *bufp != '\r' && *bufp != '\n')
	      bufp++;

	    if (*bufp && *bufp != '\r' && *bufp != '\n')
	      *bufp++ = 0;
	    /* else the null will be added below */

	    /* 
	     * read arguments if any
	     */
	    argp = shellargs = bufp;
	    nargcount = 0;
	    i = 0;
	    while (*bufp && *bufp != '\r' && *bufp != '\n')
	      {
		/* skip blanks */
		while (*bufp == ' ' || *bufp == '\t')
		  bufp++;

		if (*bufp == '\r' || *bufp == '\n')
		  break;

		while (*bufp && *bufp != ' ' && *bufp != '\t'
		       && *bufp != '\r' && *bufp != '\n')
		  *argp++ = *bufp++;
		*argp++ = '\0';
		nargcount++;
	      }
	    *argp = '\0';
		
	    if (*shell)
	      {
		shell = _buffindfile (shell, getenv("PATH"), extensions, tmppath);
		if (!shell)
		  {
		    __set_errno (ENOENT);
		    return -1;	/* file not found */
		  }

		/* count old args */
		for (i = 0; argv[i] != 0; i++);
		argcount = i;

		shellargv = (char **)Malloc((argcount + nargcount + 2) * sizeof(char *));
		if (!shellargv) {
		  __set_errno (ENOMEM);
		  return -1;
		}

		i = 0;
		shellargv[i++] = shell;
		while(*shellargs != '\0') {
		  shellargv[i++] = shellargs;
		  while (*shellargs++ != '\0');
		}

		/* use the full pathname of the script instead of argv[0] */
		shellargv[i++] = (char *) _path;
		while (*++argv != NULL)
		  shellargv[i++] = *argv;
		shellargv[i] = NULL;

		rv = _spawnve(mode, shell, shellargv, envp);
		(void)Mfree(shellargv);
		return rv;
	      }
	  }

	__set_errno (ENOEXEC);
	return -1;
}

#endif /* HASH_BANG */

int
_spawnve(mode, _path, argv, envp)
int	mode;
const char	*_path;
char	*const *argv;
char	*const *envp;
{
	char		pathbuf[PATH_MAX];
	char*		path = (char*) _path;
	char		cmd[TOS_ARGS + 1];
	size_t		cmlen;
	size_t		enlen = 0;
	size_t		left, min_left;
	const char	*p;
	char		*s, *t;
	char		*env;
	long		rval;
	const char *pconv, *pc, *tmp;
	size_t len, cnt;
	int i, done;
#ifdef HASH_BANG
	char *const *_envp;
	char *const *_argv;
#endif

	if (mode != P_WAIT && mode != P_OVERLAY && mode != P_NOWAIT) {
		__set_errno (EINVAL);
		return -1;
	}
	 
	if (!__libc_unix_names)
	  {
	    path = pathbuf;
	    (void)_unx2dos (_path, path, sizeof (pathbuf)); /* convert filename, if necessary */
	  }
	if (!envp)
		envp = environ;

#ifdef HASH_BANG
		_envp = envp;
		_argv = argv;
#endif

/* try to find PCONVERT environment variable */
	for (i = 0; (pconv = envp[i]) != 0; i++) {
		if (! strncmp(pconv, "PCONVERT=", 9)) {
			pconv += 9;
			break;
		}
	}

/* count up space needed for environment */
	for(cmlen = 0; argv[cmlen]; cmlen++)
		enlen += strlen(argv[cmlen]) + 1;
	enlen += 64;	/* filler for stuff like ARGV= and zeros, 
			 * minibuffer for empty param index conversion 
			 */
	min_left = enlen;
	for(cmlen = 0; envp[cmlen]; cmlen++)
		enlen += strlen(envp[cmlen]) + 1;
	enlen += 1024;	/* buffer for _unx2dos */

try_again:
	if ((env = (char *)Malloc((long)enlen)) == NULL) {
		__set_errno (ENOMEM);
		return -1;
	}
	left = enlen;
	s = env;

	while ((p = *envp) != 0) {
/*
 * NOTE: in main.c, we converted environment variables which contain paths into
 * POSIX form. Here, we convert back into gulam form. Note that the
 * new variable can be longer than the old, so space _is_ a problem.
 */
		done = 0;
		
		if (pconv) {

			pc = pconv;
			while (*pc) {
				
				tmp = pc; len = 0;
				while (*tmp && *tmp != ',') {
					tmp++; len++;
				}
				
				if (! strncmp(p, pc, len) && p[len] == '=') {
					len++;
					tmp = p + len;		/* tmp now after '=' */	
					cnt = 1;
					while (*tmp) {		/* count words */
						if (*tmp == ':')
							cnt++;
						tmp++;
					}

					/* cnt * 2 is maximum enlargement when calling
					 * _path_unx2dos. Make this agree with _unx2dos
					 * in unx2dos.c
					 */
					if (left - (strlen(p) + cnt * 2 + 1) < min_left)
						goto need_more_core;
						
					strncpy(s, p, len);
					_path_unx2dos(p + len, s + len,
						      left - len);

					while (*s) {
						s++; left--;
					}
					s++; left--;
					
					done = 1;
					break;	
				}
				
				if (! *tmp) break;
				pc = tmp + 1;
			}
		}
		else if (!strncmp(p, "PATH=", 5)) {
			strncpy(s, p, 5); s += 5; p += 5; left -= 5;

			tmp = p;		/* tmp now after '=' */	
			cnt = 1;
			while (*tmp) {		/* count words */
				if (*tmp == ':')
					cnt++;
				tmp++;
			}

			/* cnt * 2 is maximum enlargement when calling
			 * _path_unx2dos. Make this agree with _unx2dos
			 * in unx2dos.c
			 */
			if (left - (strlen(p) + cnt * 2 + 1) < min_left)
				goto need_more_core;
						
			_path_unx2dos(p, s, left);

			while (*s) {
				s++; left--;
			}
			s++; left--;
		
			done = 1;
		}			
		
		if (! done) {
			/* copy variable without any conversion */
			while (*p) {
				*s++ = *p++;
				if (--left <= min_left) {
need_more_core:
					/* oh dear, we don't have enough core...
					 * so we Mfree what we already have, and try again with
					 * some more space.
					 */
					Mfree(env);
					enlen += 1024;
					goto try_again;
				}
			}
			*s++ = 0;
			left--;
		}

		envp++;
	}
	
	strcpy(s, "ARGV=");
	s += 6; /* s+=sizeof("ARGV=") */

	if (argv && *argv) {
		unsigned long null_params = 0;
		int digits, i;
		unsigned long idx, val;
		char *const *ap;
		
		/* communicate empty arguments thru ARGV= value
		 */
		for (ap = argv, idx = 0; 
		     *ap;
		     ap++, idx++)
		{
			if (! **ap) {
				/* empty argument found
				 */
				if (! null_params) {
					strcpy(s-1, "NULL:");
					s += 4;	/* s now points after "NULL:" */
					left -= 6;
				} else {
					*s++ = ',' ;
				}
				null_params++;
								    
				/* convert index of zero param to ascii
				 */
				if (idx == 0) {
					*s++ = '0';
					digits = 1;
				} else {
					digits = 0;
					val = idx;
					while (val) {
						for (i = digits; i > 0; i--)
							s[i] = s[i - 1];
						*s = "0123456789"[val % 10];
						val /= 10;
						digits++;
					}
					s += digits;
				}
				
				left -= digits + 2; /* 2 = sizeof( ',' in NULL:
						     		 * list + ' ' we put in place
								     * of empty params
								     */
				if (left < min_left)
					goto need_more_core;
			}
		}

		if (null_params) {
			*s++ = 0;		/* finish "NULL:" list */
		}

		/* copy argv[0] first (because it doesn't go into 
		 * the command line)
		 */
		p = *argv;
		if (! *p) {		/* if empty argument */
			*s++ = ' ';	/* replace by space */
		} else {
			 do {
				*s++ = *p++;
			 } while (*p);
		}
		*s++ = '\0';
	}

	__bzero(t = cmd, sizeof(cmd));

/* s points at the environment's copy of the args */
/* t points at the command line copy to be put in the basepage */

	cmlen = 0;
	if (argv && *argv) {
		t++;
		while (*++argv) {
			p = *argv;
			if (! *p) {	/* if empty argument */
			 	*s++ = ' ';	/* replace by space */
	       			/* write '' in TOS cmdlin
	       			 */
			 	if (cmlen < TOS_ARGS) {
			 		*t++ = '\''; cmlen++;
			 	}
			 	if (cmlen < TOS_ARGS) {
			 		*t++ = '\''; cmlen++;
			 	}
			} else {
				 do {
					if (cmlen < TOS_ARGS) {
						*t++ = *p; cmlen++;
					}
					*s++ = *p++;
				 } while (*p);
			}
			if (cmlen < TOS_ARGS && *(argv+1)) {
				*t++ = ' '; cmlen++;
			}
			*s++ = '\0';
		}
/*                *cmd = (char) cmlen;  NOT ANY MORE */
	}

	/* tie off environment */
	*s++ = '\0';
	*s = '\0';

	/* signal Extended Argument Passing */
	*cmd = 0x7f;

/* MiNT and MicroRTX support background processes with Pexec(100,...) */
/* MiNT and MagiC 6.10 supports overlays with Pexec(200,...) */

	if (mode == P_NOWAIT) cmlen = 100;
	else if (mode == P_OVERLAY) cmlen = 200;
	else cmlen = 0;

	rval = Pexec((int)cmlen, path, cmd, env);

	if (rval < 0)
	{
#ifdef HASH_BANG
		if (rval == -ENOEXEC) {
			/*
			 * Always check the environment here, don't remove.
			 * If UNIXMODE isn't set we run scripts by default
			 * otherwise, check the 's' flag for activation.
			 */
			char *unixmode = getenv("UNIXMODE");
			if (!unixmode || (unixmode && strchr(unixmode, 's'))) {
				(void)Mfree(env);
				return interpret_script(mode, path, _path, _argv, _envp);
			}
		}
#endif
		__set_errno (-rval);
		rval = -1;
	}
	else if (mode == P_OVERLAY)
	/* note that we get here only if MiNT is not active! */
		_exit((int)rval);
	(void)Mfree(env);
	return (int) rval;
}

#ifdef TEST
int
main (int argc, char **argv, char **envp)
{
	if (argc == 2) {
		if (spawnve(P_WAIT, argv[1], &argv[1], envp) < 0) {
			perror("spawn failed");
			return errno;
		}
		return 0;
	}
	return 1;
}
#endif
