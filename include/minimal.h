#ifndef _MINIMAL_H
#define _MINIMAL_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#ifndef _OSBIND_H
#include <osbind.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int errno;
#ifndef __MINT__
int _console_dev = 2;
#endif

#ifndef __MINT__

__EXTERN __EXITING __exit __PROTO((long)) __NORETURN; /* def in crt0.c */
int 	  raise	__PROTO((int sig));
void	 _exit  __PROTO((int status));

void _exit(status)
	int status;
{
    __exit((long)status);
}

int
raise(sig)
int sig;
{
	return 0;
}

#else

__EXTERN __EXITING _exit __PROTO((int)) __NORETURN;
#define __exit _exit

#endif /* __MINT__ */

void	 _init_signal __PROTO((void));
void	  exit  __PROTO((int status));
void	 _main  __PROTO((long argc, char **argv, char **environ));
void __main __PROTO ((void));


void
_init_signal()
{
}

__EXITING
exit(status)
	int status;
{
	__exit(status);
}

void __main ()
{
}

void _main(argc, argv, environ)
	long argc;
	char **argv;
	char **environ;
{
	/* Avoid prototyping main, it will conflict with user's version */
	__EXTERN int main ();
	exit(main((int)argc, argv, environ));
}

#ifdef __cplusplus
}
#endif

#endif /* _MINIMAL_H */
