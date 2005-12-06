/*  pwd.h -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

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

extern struct passwd	*getpwnam (const char *);
extern struct passwd	*getpwuid (__uid_t);

#if defined(__USE_SVID) || defined(__USE_MISC)
extern int		getpw (__uid_t, char *);
#endif

#if defined (__USE_SVID) || defined (__USE_MISC) || defined (__USE_XOPEN_EXTENDED)
extern void		setpwent (void);
extern void		endpwent (void);
extern struct passwd	*getpwent (void);
#endif

#ifdef __USE_BSD
/* FIXME:  This is just a guess. Where does setpwfile belong?  */
extern void		setpwfile (char *);
#endif

#ifdef __USE_SVID
extern struct passwd	*fgetpwent (FILE *);
extern int		putpwent (const struct passwd *, FILE *);
#endif

# if defined __USE_SVID || defined __USE_MISC || defined __USE_XOPEN_EXTENDED
extern int getpwent_r (struct passwd* __resultbuf, char* __buffer, 
		       size_t __buflen, struct passwd** __result);
# endif

#if defined __USE_POSIX || defined __USE_MISC
extern int getpwuid_r (__uid_t __uid, struct passwd* __resultbuf, 
                       char* __buffer, size_t __buflen, 
                       struct passwd** __result);

extern int getpwnam_r (const char* __name, struct passwd* __resultbuf,
		       char* __buffer, size_t __buflen,
		       struct passwd** __result);
#endif


# ifdef	__USE_SVID
/* Read an entry from STREAM.  This function is not standardized and
   probably never will.  */
extern int fgetpwent_r (FILE* __stream, struct passwd* __resultbuf,
			char* __buffer, size_t __buflen,
			struct passwd** __result);
# endif

__END_DECLS

#endif /* _PWD_H */
