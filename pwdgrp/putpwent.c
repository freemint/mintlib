/****************************************************************/
/* Module name:   putpwent.c                                    */
/* Library name:  mintlibs for Atari ST                         */
/* Author:        Hildo Biersma (boender@dutiws.twi.tudelft.nl) */
/* Date:          January 12, 1993                              */
/* Revision:      2 (add password aging)                        */
/*                1 (first attempt, no password aging)          */
/****************************************************************/

/* FIXME: should errno be set when an error occurs, or do we    */
/*        trust errno as set by fprintf() or fflush()?          */

/*
NAME
    putpwent - write password file entry

SYNOPSIS
    #include <stdio.h>
    #include <pwd.h>
    
    int putpwent(const struct password *p, FILE *f);

DESCRIPTION
    putpwent is the inverse of getpwent. Given a pointer to a
    password structure created by getpwent (or getpwuid or
    getpwnam), putpwent writes a line on the stream f, which
    matches the format of /etc/passwd.

SEE ALSO
    getpwent

RETURN VALUES
    zero on success
    non-zero if an error was detected

NOTES
    Password ageing is supported.
    
    You are strongly discouraged to use a different way of writing
    password structures to file, as that will leave you vulnerable
    to any possible changes to the password structure or the file
    format.

AUTHOR
    Hildo Biersma, with the help of a UN*X System V man page.
*/

#include <stdio.h>
#include <pwd.h>

/* Write a line on the stream f, which matches the format of    */
/* /etc/passwd. Return non-zero on error, zero if okay.         */
int putpwent(p, f)
const struct passwd *p;
FILE *f;
{
  if ((p->pw_passwd[0] == 0x00) || !p->pw_age || (p->pw_age[0] == 0x00))
  {
    /* Do not include age field if password is empty or age field not set */
    if (fprintf(f, "%s:%s:%ld:%ld:%s:%s:%s\n",
                p->pw_name,
                p->pw_passwd,
                (long) p->pw_uid,
                (long) p->pw_gid,
                p->pw_gecos,
                p->pw_dir,
                p->pw_shell) == EOF)
      return(-1);
    else    
      return(fflush(f));
  }
  else
  {
    /* Do include age field, separated from the password by a comma */
    if (fprintf(f, "%s:%s,%s:%ld:%ld:%s:%s:%s\n",
                p->pw_name,
                p->pw_passwd,
                p->pw_age,
                (long) p->pw_uid,
                (long) p->pw_gid,
                p->pw_gecos,
                p->pw_dir,
                p->pw_shell) == EOF)
      return(-1);
    else    
      return(fflush(f));
  }
} /* End of putpwent() */
