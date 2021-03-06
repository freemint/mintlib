/* Copyright (C) 1997, 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* Modified by Guido Flohr <guido@freemint.de>:
   - Find cat in $PATH and not only in /bin.  */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* catname = NULL;
#define DEFAULT_CAT "/bin/cat"
extern char* _buffindfile (const char* fname, char* fpath,
                           char* const *fext, char buf[]);

#include <limits.h>
char buf[PATH_MAX];

void
write_data (FILE *stream)
{
  int i;
  for (i=0; i<100; i++)
    fprintf (stream, "%d\n", i);
  if (ferror (stream))
    {
      fprintf (stderr, "Output to stream failed.\n");
      exit (1);
    }
}

void
read_data (FILE *stream)
{
  int i, j;

  for (i=0; i<100; i++)
    {
      if (fscanf (stream, "%d\n", &j) != 1 || j != i)
	{
	  if (ferror (stream))
	    perror ("fscanf");
	  puts ("Test FAILED!");
	  exit (1);
	}
    }
}

int
main (void)
{
  FILE *output, *input;
  int wstatus, rstatus;
  char* path;
  char* cmd = NULL;
  
  /* We must remove this entry to assure the `cat' binary does not use
     the perhaps incompatible new shared libraries.  */
  unsetenv ("LD_LIBRARY_PATH");

  /* Find a cat binary.  */
  if ((path = getenv ("PATH")) != NULL)
      catname = _buffindfile ("cat", path, NULL, buf);

  if (catname == NULL)
    catname = DEFAULT_CAT;
  else
    /* Arrrrgh, ...  */
    {
      char* ptr = catname;
      while (*ptr != '\0')
        {
          if (*ptr == '\\')
            *ptr = '/';
          ptr++;
        }
    }
  
  if (asprintf (&cmd, "%s >/tmp/tstpopen.tmp", catname) < 0)
    {
      perror ("asprintf");
      return 1;
    }
    
  output = popen (cmd, "w");
  if (output == NULL)
    {
      perror ("popen");
      puts ("Test FAILED!");
      exit (1);
    }
  write_data (output);
  wstatus = pclose (output);
  printf ("writing pclose returned %d\n", wstatus);
  if (asprintf (&cmd, "%s /tmp/tstpopen.tmp", catname) < 0)
    {
      perror ("asprintf");
      return 1;
    }
    
  input = popen (cmd, "r");
  if (input == NULL)
    {
      perror ("/tmp/tstpopen.tmp");
      puts ("Test FAILED!");
      exit (1);
    }
  read_data (input);
  rstatus = pclose (input);
  printf ("reading pclose returned %d\n", rstatus);

  remove ("/tmp/tstpopen.tmp");

  __set_errno (0);
  output = popen (catname, "m");
  if (output != NULL)
    {
      puts ("popen called with illegal mode does not return NULL");
      puts ("Test FAILED!");
      exit (1);
    }
  if (errno != EINVAL)
    {
      puts ("popen called with illegal mode does not set errno to EINVAL");
      puts ("Test FAILED!");
      exit (1);
    }

  puts (wstatus | rstatus  ? "Test FAILED!" : "Test succeeded.");
  exit (wstatus | rstatus);
}
