#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>

/* Modified by Guido Flohr <guido@freemint.de>:
 * - Really check something.
 */
 
int
main (int argc, char *argv[])
{

  DIR * dirp;
  long int save3 = 0;
  int i = 0;
  struct dirent *dp;
  FILE* buf1;
  FILE* buf2;
  char* bp1;
  char* bp2;
  size_t size1;
  size_t size2;
  
  dirp = opendir(".");
  if (dirp == NULL) 
    {
      perror ("opendir");
      exit (1);
    }
  
  buf1 = open_memstream (&bp1, &size1);
  buf2 = open_memstream (&bp2, &size2);
  if (buf1 == NULL || buf2 == NULL)
    {
      perror ("open_memstream");
      exit (1);
    }
    
  for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp))
    {
      /* save position 3 (after fourth entry) */
      if (i++ == 3)
	save3 = telldir(dirp);

      if (i >= 5)
        fprintf (buf1, "%s ", dp->d_name);
        
      printf("%s\n", dp->d_name);

      /* stop at 400 (just to make sure dirp->__offset and dirp->__size are
	 scrambled */
      if (i == 400)
	break;
    }

  printf("going back past 4-th entry...\n");

  /* go back to saved entry */
  seekdir (dirp, save3);


  /* print remaining files (3-last) */
  i = 0;
  for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp))
    {
      printf("%s\n", dp->d_name);
      i++;
      fprintf (buf2, "%s ", dp->d_name);
      if (i == 400)
        break;
    }

  fflush (buf1);
  fflush (buf2);
  
  if (strcmp (bp1, bp2))
    {
      fflush (stdout);
      fprintf (stderr, "*** buffers differ:\n");
      fprintf (stderr, "buffer 1: %s\n", bp1);
      fprintf (stderr, "buffer 2: %s\n", bp2);
      return 1;
    }
    
  closedir (dirp);
  exit(0);
}
