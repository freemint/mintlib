#include <stdio.h>
#include <string.h>
#include <errno.h>

#define NUMFILES 500
char *files[NUMFILES];

int
main (int argc, char *argv[])
{
  FILE *fp;
  int i;
  int status = 0;
  
  for (i = 0; i < NUMFILES; i++) {
    files[i] = tempnam (NULL, "file");
    if (files[i] == NULL) {
      printf ("tempnam failed\n");
      exit (1);
    }
    printf ("file: %s\n", files[i]);
    fp = fopen (files[i], "w");
    fclose (fp);
  }

  for (i = 0; i < NUMFILES; i++) {
    if (remove (files[i]) != 0) {
      printf ("remove failed on file %s: %s\n", files[i], strerror (errno));
      status = 1;
    }
  }

  exit (status);
}
