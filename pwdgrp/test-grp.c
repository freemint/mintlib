#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static int test_getgrnam_r(const char *name)
{
  struct group groupbuf;
  char **group1mem;
  struct group *group;
  char *buf;
  long size;
  gid_t gid;
  char *end;
  
  printf ("group %s:\n", name);
  size = sysconf (_SC_GETGR_R_SIZE_MAX);
  if (size == -1) {
    fprintf (stderr, "error: could not get _SC_GETGR_R_SIZE_MAX\n");
    return 0;
  }

  buf = malloc ((size_t) size);
  if (buf == NULL) {
    fprintf (stderr, "error: malloc() failed\n");
    return 0;
  }

  gid = (gid_t)strtol(name, &end, 10);
  if (*end == '\0')
  {
    if (getgrgid_r (gid, &groupbuf, buf, (size_t) size, &group) != 0) {
      fprintf (stderr,
        "error: getgrgid_r failed with errno=%d\n", errno);
      free (buf);
      return 0;
    }
  } else
  {
    if (getgrnam_r (name, &groupbuf, buf, (size_t) size, &group) != 0) {
      fprintf (stderr,
        "error: getgrnam_r failed with errno=%d\n", errno);
      free (buf);
      return 0;
    }
  }
  
  if (group == NULL) {
    fprintf (stderr, "error: group not found: %s\n", name);
      free (buf);
    return 0;
  }

  printf ("###\tgroup->gr_gid -> %d\n", group->gr_gid);
  printf ("###\tgroup->gr_name -> %s\n", group->gr_name);
  printf ("###\tgroup->gr_passwd -> %s\n", group->gr_passwd);  
  printf ("###\tgroup->gr_mem ->\n");  

	for(group1mem = group->gr_mem; *group1mem != NULL; group1mem++)
	{
		printf ("###\t\t -> %s\n", *group1mem);
	}

  free (buf);
  return 1;
}


int
main (int argc, char *argv[])
{
  uid_t me;
  struct passwd *my_passwd;
  struct group *my_group = NULL;
  char **members;

  me = getuid ();
  my_passwd = getpwuid (me);
  if (my_passwd == NULL)
    printf ("Cannot find user entry for UID %d\n", me);
  else
    {
      printf ("My login name is %s.\n", my_passwd->pw_name);
      printf ("My uid is %d.\n", (int)(my_passwd->pw_uid));
      printf ("My home directory is %s.\n", my_passwd->pw_dir);
      printf ("My default shell is %s.\n", my_passwd->pw_shell);

      my_group = getgrgid (my_passwd->pw_gid);
      if (my_group == NULL)
	printf ("No data for group %d found\n", my_passwd->pw_gid);
      else
	{
	  printf ("My default group is %s (%d).\n",
		  my_group->gr_name, (int)(my_passwd->pw_gid));
	  printf ("The members of this group are:\n");
	  for (members = my_group->gr_mem; *members != NULL; ++members)
	    printf ("  %s\n", *members);
	}
    }

  if (my_passwd == NULL || my_group == NULL)
  	return EXIT_FAILURE;

  if (argc >= 2)
  {
  	 printf("\n");
     if (!test_getgrnam_r(argv[1]))
  	    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
