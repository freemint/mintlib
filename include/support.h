/*
 * support.h
 *  prototypes for miscellaneous functions in the library
 *		++jrb
 */
#ifndef _SUPPORT_H
#define _SUPPORT_H

#ifndef	_FEATURES_H
# include <features.h>
#endif

#include <time.h>	/* for time_t */

__BEGIN_DECLS

int	_unx2dos __PROTO((const char *, char *, size_t));
int	_dos2unx __PROTO((const char *, char *, size_t));

int	_path_dos2unx __PROTO((const char *, char *, size_t));
int	_path_unx2dos __PROTO((const char *, char *, size_t));

int	unx2dos __PROTO((const char *, char *));
int	dos2unx __PROTO((const char *, char *));

time_t	__dostime (time_t);
time_t	__unixtime (unsigned int, unsigned int);

char *	_buffindfile __PROTO((const char *, const char *,
				char const *const *, char *));

char *	_ultoa __PROTO((unsigned long, char *, int));
char *	_ltoa __PROTO((long, char *, int));
char *	_itoa __PROTO((unsigned long long int, char *, unsigned int, int));

__EXITING __exit __PROTO((long status)) __NORETURN;
__EXITING _exit __PROTO((int)) __NORETURN;

long a64l __PROTO((const char *));
char *l64a __PROTO((long));

long tfork __PROTO((int (*func)(long), long));

int _isctty __PROTO((int));

int _console_read_byte __PROTO((int));
void _console_write_byte __PROTO((int, int));

__END_DECLS

#endif /* _SUPPORT_H */
