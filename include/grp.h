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
#if defined __USE_XOPEN && !defined __gid_t_defined
typedef __gid_t gid_t;
# define __gid_t_defined 1
#endif

struct group
{
  char *gr_name;    /* The name of the group        */
  __gid_t gr_gid;    /* The numerical group ID       */
  char **gr_mem;    /* array of member names        */
  char *gr_passwd;/* The encrypted group password */
};

#if defined (__USE_SVID) || defined (__USE_MISC) || defined (__USE_BSD)
/* Rewind the group-file stream.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
void setgrent(void);

/* Close the group-file stream.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
void endgrent(void);

/* Read an entry from the group-file stream, opening it if necessary.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
struct group * getgrent(void);
#endif /* SVID or misc or BSD */

#ifdef __USE_SVID
/* Read a group entry from STREAM.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
struct group *fgetgrent(FILE *f);
#endif /* __USE_SVID */

#ifdef __USE_GNU
/* Write the given entry onto the given stream.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
int putgrent (const struct group *__restrict __p,
		     FILE *__restrict __f);
#endif

/* Search for an entry with a matching group ID.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
struct group * getgrgid(__gid_t gid);

/* Search for an entry with a matching group name.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
struct group * getgrnam(const char *name);

#ifdef __USE_POSIX

# ifdef __USE_MISC
/* Reasonable value for the buffer sized used in the reentrant
   functions below.  But better use `sysconf'.  */
#  define NSS_BUFLEN_GROUP	1024
# endif

/* Reentrant versions of some of the functions above.

   PLEASE NOTE: the `getgrent_r' function is not (yet) standardized.
   The interface may change in later versions of this library.  But
   the interface is designed following the principals used for the
   other reentrant functions so the chances are good this is what the
   POSIX people would choose.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */

# ifdef __USE_GNU
int getgrent_r (struct group *__restrict __resultbuf,
		       char *__restrict __buffer, size_t __buflen,
		       struct group **__restrict __result);
# endif

/* Search for an entry with a matching group ID.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
int getgrgid_r (__gid_t __gid, struct group *__restrict __resultbuf,
		       char *__restrict __buffer, size_t __buflen,
		       struct group **__restrict __result);

/* Search for an entry with a matching group name.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  */
int getgrnam_r (const char *__restrict __name,
		       struct group *__restrict __resultbuf,
		       char *__restrict __buffer, size_t __buflen,
		       struct group **__restrict __result);

# ifdef	__USE_MISC
/* Read a group entry from STREAM.  This function is not standardized
   an probably never will.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
int fgetgrent_r (FILE *__restrict __stream,
			struct group *__restrict __resultbuf,
			char *__restrict __buffer, size_t __buflen,
			struct group **__restrict __result);
# endif

#endif	/* POSIX or reentrant */


#ifdef __USE_BSD
/* Set the group set for the current user to GROUPS (N of them).  */
int setgroups(size_t __count, const __gid_t* __groups) __THROW;

/* Store at most *NGROUPS members of the group set for USER into
   *GROUPS.  Also include GROUP.  The actual number of groups found is
   returned in *NGROUPS.  Return -1 if the if *NGROUPS is too small.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
int getgrouplist(const char *__user, __gid_t __group, __gid_t *__groups, int *__ngroups);

/* Initialize the group set for the current user
   by reading the group database and using all groups
   of which USER is a member.  Also include GROUP.

   This function is not part of POSIX and therefore no official
   cancellation point.  But due to similarity with an POSIX interface
   or due to the implementation it is a cancellation point and
   therefore not marked with __THROW.  */
int initgroups(const char* __user, __gid_t __groups);
#endif

__END_DECLS

#endif /* _GRP_H */
