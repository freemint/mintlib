/*
 * Mint version by Kay Roemer.
 */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)pty.c	5.6 (Berkeley) 5/10/91";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <grp.h>
#include <osbind.h>
#include <mintbind.h>

#include <limits.h>
#include "lib.h" /* _dos2unx */


int
openpty(amaster, aslave, name, termp, winp)
	int *amaster, *aslave;
	char *name;
	struct termios *termp;
	struct winsize *winp;
{
	static char line[] = "u:\\pipe\\ttyXX";
	static char link[] = "u:\\dev\\ttyXX";
#define PTYCHAR1	(sizeof (line)-3)
#define PTYCHAR2	(sizeof (line)-2)
#define LINKCHAR1	(sizeof (link)-3)
#define LINKCHAR2	(sizeof (link)-2)
	register const char *cp1, *cp2;
	register int master, slave, ttygid;
	struct group *gr;

	if ((gr = getgrnam("tty")) != NULL)
		ttygid = gr->gr_gid;
	else
		ttygid = -1;

	for (cp1 = "pqrs"; *cp1; cp1++) {
		line[PTYCHAR1] = *cp1;
		for (cp2 = "0123456789abcdef"; *cp2; cp2++) {
			struct stat st;

			line[PTYCHAR2] = *cp2;
			if (stat (line, &st) == 0) continue;
			if ((master = Fcreate (line,
			    FA_SYSTEM|FA_HIDDEN)) < 0) {
				__set_errno (ENOENT);
				return -1;
			} else {
				(void) chown(line, getuid(), ttygid);
				(void) chmod(line, S_IRUSR|S_IWUSR|S_IWGRP);
				if ((slave = open(line, O_RDWR | O_NOCTTY, 0)) != -1) {
					/* tesche: we're not interested in whether the link already existed or not */
					link[LINKCHAR1] = *cp1;
					link[LINKCHAR2] = *cp2;
					(void)Fsymlink(line, link);

					*amaster = master;
					*aslave = slave;
					if (name)
						_dos2unx (link, name, PATH_MAX); /* XXX */
					if (termp)
						(void) tcsetattr(slave, 
							TCSAFLUSH, termp);
					if (winp)
						(void) ioctl(slave, TIOCSWINSZ, 
							(char *)winp);
					return (0);
				}
				(void) close(master);
			}
		}
	}
	__set_errno (ENOENT);	/* out of ptys */
	return (-1);
}

int
forkpty(amaster, name, termp, winp)
	int *amaster;
	char *name;
	struct termios *termp;
	struct winsize *winp;
{
	int master, slave, pid;
	extern int login_tty (int);

	if (openpty(&master, &slave, name, termp, winp) == -1)
		return (-1);
	switch (pid = fork()) {
	case -1:
		return (-1);
	case 0:
		/* 
		 * child
		 */
		(void) close(master);
		login_tty(slave);
		return (0);
	}
	/*
	 * parent
	 */
	*amaster = master;
	(void) close(slave);
	return (pid);
}
