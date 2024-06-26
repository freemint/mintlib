/*
 * Routines for reading information from /etc/group.
 * Written by Eric Smith, based on Arnold Robbins' public domain
 * getpwent routines (see getpw.c).
 */

/*
  Revised by Hildo Biersma (boender@dutiws.twi.tudelft.nl)
  Revision 1 (January 31, 1993): include fgetgrent()
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>

static char const *grpfile = "/etc/group";  /* default group file */
static FILE *filep = NULL;

static struct group curentry;   /* static data to return */

static int nextent (FILE *fp);

/* Rewind the group file to allow repeated searches */
void setgrent(void)
{
  if (filep != NULL)
    rewind (filep);
  else if ((filep = fopen (grpfile, "rt")) == NULL)
  {
#ifdef VERBOSE
    fprintf (stderr,
      "setgrent: %s non-existant or unreadable.\n", grpfile);
#endif
  }
} /* End of setgrent() */

/* Close the group file when processing is complete */
void endgrent(void)
{
  if (filep != NULL)
  {
    fclose (filep);
    filep = NULL;
  }
} /* End of endgrent() */

/* Get the next group structure in the file */
struct group *getgrent(void)
{
  if (filep == NULL)
    setgrent();
  if (filep == NULL)
    return NULL;

  if (nextent(filep) == 0)
    return(NULL);
  else
    return(&curentry);
} /* End of getgrent() */

/* Get first group with matching numerical group ID from file */
struct group *getgrgid(gid_t gid)
{
  setgrent();

  while (nextent(filep) != 0)
    if (curentry.gr_gid == gid)
      return(&curentry);

  return(NULL);
} /* End of getgrid() */

/* Get first group with matching group name from file */
struct group *getgrnam(const char *name)
{
  setgrent();

  while (nextent(filep) != 0)
    if (strcmp (curentry.gr_name, name) == 0)
      return (&curentry);

  return(NULL);
} /* End of getgrnam() */

/* Read the next group structure from a given file */
struct group *fgetgrent(FILE *f)
{
  if (f == NULL)
    return(NULL); /* Failure */
    
  if (nextent(f) != 0)
    return(&curentry); /* Success */

  return(NULL); /* Failure */
} /* End of fgetgrent() */

#define MAX_MEMBERS 128   /* max. number of members in a group */

static char savbuf[512];
static char *memb[MAX_MEMBERS];

static int nextent(FILE *fp)
{
  char *cp;
  int i;

  if (fp == NULL)
    setgrent();
  if (fp == NULL)
    return(0);

  if (fgets(savbuf, (int)sizeof(savbuf), fp) != NULL)
  {
    for (cp = savbuf; *cp && *cp != ':'; cp++)
      ;
    curentry.gr_name = savbuf;
    *cp++ = '\0';
    curentry.gr_passwd = cp;
    for (; *cp && *cp != ':'; cp++)
      ;
    *cp++ = '\0';
    curentry.gr_gid = strtoul (cp, NULL, 10);
    for (; *cp && *cp != ':'; cp++)
      ;

    *cp++ = '\0';

    i = 0;
    while( *cp )
    {
      if (i >= MAX_MEMBERS-1)
        break;
      for (; *cp == ' '; cp++)
        ;
      memb[i++] = cp;
      for(; *cp && *cp != ',' && *cp != '\n'; cp++)
        ;
      if (*cp == '\n')
        *cp = 0;
      else if (*cp)
        *cp++ = 0;
    }
    memb[i] = NULL;
    curentry.gr_mem = memb;
    return(1);
  }
  return(0);
} /* End of nextent() */

#ifdef TEST
int
main (int argc, char **argv)
{
  struct group *gr;
  char **m;

  if (argc > 1) {
    grpfile = argv[1];
  }

  setgrent ();
  while ((gr = getgrent ()) != NULL)
  {
    printf ("%s:[%s] %lu\n",
      gr->gr_name,
      gr->gr_passwd,
      (unsigned long)gr->gr_gid);
    for (m = gr->gr_mem; *m; m++) {
      printf("\t%s\n", *m);
    }
  }
  endgrent ();

  if (gr = getgrnam ("mail")) {
    printf ("%s:[%s] %lu\n",
      gr->gr_name,
      gr->gr_passwd,
      (unsigned long)gr->gr_gid);
    for (m = gr->gr_mem; *m; m++) {
      printf("\t%s\n", *m);
    }
  }
  if (gr = getgrgid (1)) {
    printf ("%s:[%s] %lu\n",
      gr->gr_name,
      gr->gr_passwd,
      (unsigned long)gr->gr_gid);
    for (m = gr->gr_mem; *m; m++) {
      printf("\t%s\n", *m);
    }
  }
  return 0;
}
#endif
