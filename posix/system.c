/*  system.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/*  Emulation (that is called in absence of a shell) was written by 
    Eric R. Smith.  The POSIX-compliant branch is inspired by the
    GNU libc.  
    
    Somebody should check if the POSIX branch works under MagiC.  */

#include <process.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>
#include <mint/osbind.h>

#include "lib.h"

extern char** environ;  /* In crtinit.c.  */

/* We cache the results of our inquiries regarding "/bin/sh" and $SHELL.  */
static int posix_system;
static int initialized = 0;  /* If non-zero the value in posix_system is valid.  */
static char* shell_path;
static char* shell_name;
static int system_hack(const char* s);

/* Execute LINE as a shell command, returning its status.  */
int system (line)
     register const char* line;
{
  int status = 0;
  int save;
  pid_t pid;
  struct sigaction sa, intr, quit;
  sigset_t block, omask;

  if (line == NULL)
    return 1;

  /* Check what kind of function to use.  */
  if (!initialized) {
    initialized = 1;
    
    if (access ("/bin/sh", X_OK) == 0) {
      /* We can use the Posix version.  */
      shell_path = "/bin/sh";
      shell_name = "sh";
      posix_system = 1;
    } else {
      /* /bin/sh is not executable.  We give it another try.  */
      char* cur;
      
      shell_path = getenv ("SHELL");
      if (shell_path) {
        cur = shell_path;
        
        /* Now following poor man's basename.  */
        while (*cur) cur++;
        cur--;
        while (*cur && *cur != '/' && *cur != '\\') cur--;        
        if (*cur == '\\' || *cur == '/') cur++;
        shell_name = cur;
        posix_system = 1;
      } else {
        posix_system = 0;
      }
    }
  }

  if (!posix_system)
    return (system_hack (line));

  sa.sa_handler = SIG_IGN;
  sa.sa_flags = 0;
  sigemptyset (&sa.sa_mask);

  if (sigaction (SIGINT, &sa, &intr) < 0)
    return -1;
  if (sigaction (SIGQUIT, &sa, &quit) < 0) {
    save = errno;
    (void) sigaction (SIGINT, &intr, (struct sigaction *) NULL);
    __set_errno (save);
    return -1;
  }

  sigemptyset (&block);
  sigaddset (&block, SIGCHLD);
  save = errno;
  if (sigprocmask (SIG_BLOCK, &block, &omask) < 0) {
    if (errno == ENOSYS) {
            __set_errno (save);
    } else {
	    save = errno;
	    (void) sigaction (SIGINT, &intr, (struct sigaction *) NULL);
	    (void) sigaction (SIGQUIT, &quit, (struct sigaction *) NULL);
            __set_errno (save);
	    return -1;
	  }
  }

  pid = vfork ();
  if (pid == (pid_t) 0) {
    /* Child side.  */
    const char *new_argv[4];
    new_argv[0] = shell_name;
    new_argv[1] = "-c";
    new_argv[2] = line;
    new_argv[3] = NULL;

    /* Restore the signals.  */
    (void) sigaction (SIGINT, &intr, (struct sigaction *) NULL);
    (void) sigaction (SIGQUIT, &quit, (struct sigaction *) NULL);
    (void) sigprocmask (SIG_SETMASK, &omask, (sigset_t *) NULL);

    /* Exec the shell.  */
    (void) execve (shell_path, (char *const *) new_argv, environ);
    _exit (127);
  } else if (pid < (pid_t) 0) {
    /* The fork failed.  */
    status = -1;
  } else {
    /* Parent side.  */
    if (waitpid (pid, &status, 0) != pid)
      status = -1;
  }

  save = errno;
  if ((sigaction (SIGINT, &intr, (struct sigaction *) NULL) |
       sigaction (SIGQUIT, &quit, (struct sigaction *) NULL) |
       sigprocmask (SIG_SETMASK, &omask, (sigset_t *) NULL)) != 0) {
    if (errno == ENOSYS)
            __set_errno (save);
    else
	    return -1;
  }

  return status;
}

/* Emulation code following.  */
#define isquote(c) ((c) == '\"' || (c) == '\'' || (c) == '`')
#define ARG_ERR	   ( (Argentry *) -1L )

/* struct. used to build a list of arguments for the command */

typedef struct argentry {
	struct argentry *next;
	char	string[1];
} Argentry;

static Argentry *_argalloc (const char *s);
static void _argfree (Argentry *p);
static Argentry *_parseargs (const char *s);

/* allocate an Argentry that will hold the string "s" */

static Argentry *_argalloc(s)
	const char *s;
{
	Argentry *x;

	x = (Argentry *) malloc((size_t)(sizeof(Argentry) + strlen(s) + 1));
	if (!x)
		return ARG_ERR;
	x->next = (Argentry *) 0;
	strcpy(x->string, s);
	return x;
}

/* free a list of Argentries */

static void _argfree(p)
	Argentry *p;
{
	Argentry *oldp;

	while (p) {
		oldp = p;
		p = p->next;
		free(oldp);
	}
}

/* parse a string into a list of Argentries. Words are defined to be
 * (1) any sequence of non-blank characters
 * (2) any sequence of characters starting with a ', ", or ` and ending
 *     with the same character. These quotes are stripped off.
 * (3) any spaces after an unquoted > or < are skipped, so
 *     "ls > junk" is parsed as 'ls' '>junk'.
 */

static Argentry *_parseargs(s)
	const char *s;
{
	Argentry *cur, *res;
	char buf[1024];
	char *t, quote;

	res = cur = _argalloc("");

	for(;;) {
		t = buf;
again:
		while (isspace(*s)) s++;
		if (!*s) break;
		if (isquote(*s)) {
			quote = *s++;
			while (*s && *s != quote)
				*t++ = *s++;
			if (*s) s++;	/* skip final quote */
		}
		else {
			while (*s && !isspace(*s)) {
				*t++ = *s++;
				if (isquote(*s))
					goto again;
			}
			if (*s && ( *(s-1) == '>' || *(s-1) == '<' ))
				goto again;
		}
		*t = 0;
		cur->next = _argalloc(buf);
		if ((cur = cur->next) == NULL)	  /* couldn't alloc() */
			return ARG_ERR;
	}
	cur->next = (Argentry *) 0;
	cur = res; res = res->next; free(cur);
	return res;
}


/* Here is system() itself.
 * FIXME: we probably should do wildcard expansion.
 * also, should errno get set here??
 */

int system_hack (s)
	const char *s;
{
	Argentry *al, *cur;
	char **argv, *p;
	int  argc, i;
	char const *infile, *outfile;
	int  infd = 0, outfd = 1, append = 0;
	int oldin = 0, oldout = 1;	/* hold the Fdup'd in, out */
	char path[PATH_MAX];
	int retval;

	if (!s)		/* check for system() supported ?? */
		return 1;
	al = _parseargs(s);		/* get a list of args */
	if (al == ARG_ERR) {		/* not enough memory */
		__set_errno (ENOMEM);
		return -1;
	}

	infile = outfile = "";

/* convert the list returned by _parseargs to the normal char *argv[] */
	argc = i = 0;
	for (cur = al; cur; cur = cur->next)
		argc++;
	if ((argv = (char **) malloc((size_t)(argc * sizeof(char *))))
		== NULL)
	{
		__set_errno (ENOMEM);
		return -1;
	}
	for (cur = al; cur; cur = cur->next) {
		p = cur->string;
		if (*p == '>') {
			outfile = p+1;
			if (*outfile == '>') {
				outfile++;
				append = 1;
			}
			else
			append = 0;
		}
		else if (*p == '<') {
			infile = p+1;
		}
		else
			argv[i++] = p;
	}
 	argv[i] = (char *)0;
 
/* now actually run the program */

	if (*infile) {
		(void)_unx2dos(infile,path, sizeof (path));
		infd = (int)Fopen(path, 0);
		if (infd < __SMALLEST_VALID_HANDLE) {
			perror(infile);
			return(2);
		}
		oldin = (int)Fdup(0);
		(void)Fforce(0, infd);
	}
	if (*outfile) {
		(void)_unx2dos(outfile,path, sizeof (path));
		if (append) {
			outfd = (int)Fopen(path, 2);
			if (outfd < __SMALLEST_VALID_HANDLE)
				outfd = (int)Fcreate(path, 0);
			else
				(void)Fseek(0L, outfd, 2);
		}
		else
			outfd = (int)Fcreate(path, 0);
		if (outfd < __SMALLEST_VALID_HANDLE) {
			perror(outfile);
			return(2);
		}
		oldout = (int)Fdup(1);
		(void)Fforce(1, outfd);
	}

	retval = spawnvp(P_WAIT, argv[0], argv);

	if (*infile) {
		(void)Fforce(0,oldin);
		(void)Fclose(oldin);
		(void)Fclose(infd);
	}
	if (*outfile) {
		(void)Fforce(1,oldout);
		(void)Fclose(oldout);
		(void)Fclose(outfd);
	}
	free(argv);
	_argfree(al);
	return retval;
}
