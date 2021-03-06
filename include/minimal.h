
#ifndef _MINIMAL_H
#define _MINIMAL_H

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

int errno;

#ifndef __MINT__
int _console_dev = 2;

extern __EXITING __exit (long) __NORETURN; /* def in crt0.c */
int raise (int sig);
void _exit (int status);

void _exit(int status) { __exit((long)status); }

int raise (int sig) { return 0; }

#else

extern __EXITING _exit (int) __NORETURN;
#define __exit _exit

#endif /* __MINT__ */

void exit (int status);
void _main (long argc, char **argv, char **environ);
void __main (void);


__EXITING exit (int status) { __exit(status); }

void __main (void) { }

void _main (long argc, char **argv, char **environ)
{
	/* Avoid prototyping main, it will conflict with user's version */
	extern int main ();
	exit(main((int)argc, argv, environ));
}

__END_DECLS

#endif /* _MINIMAL_H */
