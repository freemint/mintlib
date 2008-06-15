/* popen(): open a file handle to a process. Works only under MiNT.
 * Written by Eric R. Smith, based on the TOS version by Kai-Uwe Bloem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>
#include <mint/mintbind.h>
#include <sys/types.h>
#include "lib.h"

struct _pipe {
	int	pid;		/* process id of child			*/
	FILE	*pfile;		/* created file descriptor		*/
	struct _pipe	*pnext;	/* next pipe in the list.		*/
};

static struct _pipe *__pipes = NULL;	/* head of pipe list	*/

FILE *
popen (const char *command, const char *type)
{
	struct _pipe *p;	/* the new pipe's list entry	*/
	short pipfd[2];		/* pipe file handles */
	int savefd;		/* saved file descriptor for parent */
	int kidfd;		/* file descriptor changed in child */
				/* 1 for "r", 0 for "w" */	

	char const *shell;
	FILE *pipefile = 0;
	long r;

	if (__mint == 0) {
		__set_errno (ENOSYS);
		return NULL;
	}

	shell = getenv("SHELL");
	if (!shell)
		shell = "/bin/sh";

	/* get space for the new pipe. If we can't get it then that's that */
	p = (struct _pipe *) malloc(sizeof(struct _pipe));
	if (p == NULL) return (FILE *)0;

	/* initialize the new pipe entry */
	kidfd = (*type == 'r') ? 1 : 0;

	r = Fdup (kidfd);
	savefd = (int) r;
	/* get those close-on-exec flags right...
	   (well just do fork/exec would be easier :-)	-nox */

	if (r < 0 || (r = Fcntl (savefd, 1L, F_SETFD)) < 0 ||
	    (r = Fpipe(pipfd)) < 0) {		/* can't create pipe?? */
		free(p);
		__set_errno (-r);
		return NULL;
	}

	/* other side of the pipe should be closed in the child */
	(void) Fcntl(pipfd[1 - kidfd], (long) 1, F_SETFD);
	Fforce(kidfd, pipfd[kidfd]);
	Fclose(pipfd[kidfd]);
	p->pid = spawnlp(P_NOWAIT, shell, shell, "-c", command, (char *)0);
	Fforce(kidfd, savefd);
	Fclose(savefd);

	if (p->pid > 0) {	/* command ran all right */
	/* note: 1-kidfd tells us which handle to use in the parent */
		pipefile = fdopen(pipfd[1 - kidfd], type);
	}

	if (pipefile) {
		p->pfile = pipefile;
		p->pnext = __pipes;
		__pipes = p;
	}
	else {
		/* carefully release all resources */
		Fclose (pipfd[1 - kidfd]);
		if (p->pid > 0)	/* just in case... */
		  waitpid (p->pid, (int *) NULL, 0);
		free(p);
	}
	return pipefile;
}

/* close a pipe created by popen().
 */
int pclose(fp)
FILE	*fp;
{
	struct _pipe	*p,		/* the pipe's list element	*/
			**q;		/* predecessor of p in the list	*/
	int	status = -1;		/* return status of the command	*/

	/* search the pipe list for a pipe matching the FILE descriptor	*/
	for (p = __pipes, q = &__pipes;  p && p->pfile != fp;
	     q = &p->pnext, p = p->pnext);
	if (p == NULL)		/* Never had a popen() for this file...	*/
		return status;	/* this pclose call makes no sense !	*/

	fclose(p->pfile);	/* close the connection		*/

/* now wait for the command to finish */
	waitpid (p->pid, &status, 0);

	/* remove the pipe from the list */
	*q = p->pnext;

	/* Now free the pipe entry */
	free(p);

	return status;
}
