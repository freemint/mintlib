#ifndef _GRP_H
#define _GRP_H

#ifndef _FEATURES_H
#include <features.h>
#endif

#if defined(__USE_SVID) || defined (__USE_GNU)
#ifndef _STDIO_H
#define __need_FILE
#include <stdio.h>
#endif
#endif /* SVID or GNU*/

#include <bits/types.h>

#define __need_size_t
#include <stddef.h>

__BEGIN_DECLS

/* For the Single Unix specification we must define this type here.  */
#if defined __USE_XOPEN && !defined gid_t
typedef __gid_t gid_t;
# define gid_t gid_t
#endif

struct group
{
  char *gr_name;    /* The name of the group        */
  __gid_t gr_gid;    /* The numerical group ID       */
  char **gr_mem;    /* array of member names        */
  char *gr_passwd;/* The encrypted group password */
};

#if defined (__USE_SVID) || defined (__USE_MISC) || defined (__USE_BSD)
__EXTERN void   setgrent __P ((void));
__EXTERN void   endgrent __P ((void));
__EXTERN struct group * getgrent __P ((void));
#endif /* SVID or misc or BSD */

#ifdef __USE_SVID
__EXTERN struct group * fgetgrent __P ((FILE *f));
#endif /* __USE_SVID */

__EXTERN struct group * getgrgid __P ((int gid));
__EXTERN struct group * getgrnam __P ((const char *name));

#ifdef __USE_BSD
__EXTERN int initgroups __P ((const char* __user, __gid_t __groups));
__EXTERN int setgroups __P ((size_t __count, __gid_t* __groups));
#endif
__EXTERN int __initgroups __P ((const char* __user, __gid_t __groups));
__EXTERN int __setgroups __P ((size_t __count, __gid_t* __groups));

__END_DECLS

#endif /* _GRP_H */
