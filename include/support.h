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

__EXTERN int _unx2dos __PROTO((const char *, char *, size_t));
__EXTERN int _dos2unx __PROTO((const char *, char *, size_t));
__EXTERN int unx2dos __PROTO((const char *, char *));
__EXTERN int dos2unx __PROTO((const char *, char *));
__EXTERN void _set_unixmode __PROTO((char *));
__EXTERN void _uniquefy __PROTO((char *));

__EXTERN int spawnve __PROTO((int, const char *, char *const *, char *const *));

__EXTERN int console_input_status __PROTO((int));
__EXTERN unsigned int console_read_byte __PROTO((int));
__EXTERN void console_write_byte __PROTO((int, int));

__EXTERN time_t dostime __PROTO((time_t));
__EXTERN time_t __unixtime __PROTO((unsigned, unsigned));

__EXTERN char *_buffindfile __PROTO((const char *, const char *,
					char const *const *, char *));

__EXTERN char *_ultoa __PROTO((unsigned long, char *, int));
__EXTERN char *_ltoa __PROTO((long, char *, int));
#if 0
/* This would now have a fourth argument FLAG that indicates whether
   case should be obeyed or not.  Use _ultoa or _ltoa instead.  */
__EXTERN char *_itoa __PROTO((int, char *, int));
#endif

__EXTERN long get_sysvar __PROTO((void *));
__EXTERN void set_sysvar_to_long __PROTO((void *, long));

__EXTERN __EXITING __exit __PROTO((long status)) __NORETURN;
__EXTERN __EXITING _exit __PROTO((int)) __NORETURN;

__EXTERN void monstartup __PROTO((void *, void *));
__EXTERN void monitor __PROTO((void *, void *, void *, unsigned long, unsigned int));
__EXTERN void moncontrol __PROTO((long));
__EXTERN void _mcleanup __PROTO((void));
__EXTERN int profil __PROTO((void *, unsigned long, unsigned long, int));

__EXTERN long a64l __PROTO((const char *));
__EXTERN char *l64a __PROTO((long));

__EXTERN long tfork __PROTO((int (*func)(long), long));

__EXTERN int _isctty __PROTO((int));

__EXTERN int _console_read_byte __PROTO((int));
__EXTERN void _console_write_byte __PROTO((int, int));
__EXTERN int _text_read __PROTO((int, char *, int));
__EXTERN int _text_write __PROTO((int, const char *, int));

__END_DECLS

#endif /* _SUPPORT_H */
