/*  pwd.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _PWD_H
#define _PWD_H
/* File to describe password file fields.  */

#ifndef _FEATURES_H
# include <features.h>
#endif

#if defined(__USE_SVID) || defined(__USE_GNU)
# ifndef _STDIO_H
# define __need_FILE
#  include <stdio.h>
# endif
#endif

__BEGIN_DECLS

#include <bits/types.h>

#define __need_size_t
#include <stddef.h>

#ifdef __USE_XOPEN
/* The Single Unix specification says that some more types are
   available here.  */
# ifndef gid_t
typedef __gid_t gid_t;
#  define gid_t gid_t
# endif

# ifndef uid_t
typedef __uid_t uid_t;
#  define uid_t uid_t
# endif
#endif

struct passwd
{
  char    *pw_name;    /* Username.  */
  char    *pw_passwd;  /* Encrypted password.  */
  __uid_t  pw_uid;      /* Numerical user ID.  */
  __gid_t  pw_gid;      /* Numerical primary group ID.  */
  char    *pw_age;     /* Password aging information if available.  */
  char    *pw_comment; /* Duplicate of pw_gecos.  */
  char    *pw_gecos;   /* Real name resp. gecos (comment) field.  */
  char    *pw_dir;     /* Home directory.  */
  char    *pw_shell;   /* Login shell.  */
};

__EXTERN struct passwd	*getpwnam __P ((const char *));
__EXTERN struct passwd	*getpwuid __P ((__uid_t));

#if defined(__USE_SVID) || defined(__USE_MISC)
__EXTERN int		getpw		__P ((__uid_t, char *));
#endif

#if defined (__USE_SVID) || defined (__USE_MISC) || defined (__USE_XOPEN_EXTENDED)
__EXTERN void		setpwent	__P ((void));
__EXTERN void		endpwent	__P ((void));
__EXTERN struct passwd	*getpwent	__P ((void));
#endif

#ifdef __USE_BSD
/* FIXME:  This is just a guess. Where does setpwfile belong?  */
__EXTERN void		setpwfile	__P ((char *));
#endif

#ifdef __USE_SVID
__EXTERN struct passwd	*fgetpwent	__P ((FILE *));
__EXTERN int		putpwent __P ((const struct passwd *, FILE *));
#endif

# if defined __USE_SVID || defined __USE_MISC || defined __USE_XOPEN_EXTENDED
__EXTERN int getpwent_r __PROTO ((struct passwd* __resultbuf, char* __buffer, 
		                  size_t __buflen, struct passwd** __result));
# endif

#if defined __USE_POSIX || defined __USE_MISC
__EXTERN int getpwuid_r __PROTO ((__uid_t __uid, struct passwd* __resultbuf, 
                                  char* __buffer, size_t __buflen, 
                                  struct passwd** __result));

__EXTERN int getpwnam_r __PROTO ((const char* __name, struct passwd* __resultbuf,
			          char* __buffer, size_t __buflen,
			          struct passwd** __result));
#endif


# ifdef	__USE_SVID
/* Read an entry from STREAM.  This function is not standardized and
   probably never will.  */
__EXTERN int fgetpwent_r __PROTO ((FILE* __stream, struct passwd* __resultbuf,
			     char* __buffer, size_t __buflen,
			     struct passwd** __result));
# endif

#ifdef __cplusplus
}
#endif

#endif /* _PWD_H */
