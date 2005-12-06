/*  tzinit.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include <getopt.h>
#include <error.h>

#include <mint/mintbind.h>
#include <mint/ssystem.h>

static int verbose = 1;

static const struct option long_options[] =
{
  { "gmt", no_argument, NULL, 'u' },
  { "help", no_argument, NULL, 'h' },
  { "localtime", no_argument, NULL, 'l' },
  { "no-timezone", no_argument, NULL, 'n' },
  { "no-tz", no_argument, NULL, 'n' },
  { "quiet", no_argument, NULL, 's' },
  { "silent", no_argument, NULL, 's' },
  { "tz", required_argument, NULL, 't' },
  { "timezone", required_argument, NULL, 't' },
  { "utc", no_argument, NULL, 'u' },
  { "verbose", no_argument, NULL, 'v' },
  { "version", no_argument, NULL, 'V' },
  { 0, 0, 0, 0 }
};

static void show_help (void);
static void show_version (void);
static void show_usage (void);

static int do_utc = 0;
static int do_local = 0;
static int no_tz = 0;
static int do_tz = 0;
static char* newtz = NULL;

int main (argc, argv)
    int argc;
    char* argv[];
{
  int the_option;
  struct timezone tz;
  struct tm* tm;
  time_t now;
  
  while ((the_option = getopt_long (argc, argv, "hlst:uVv", 
                                    long_options, NULL)) != EOF)
    {
      switch (the_option)
        {
          case 0:  /* Long option that just sets a flag.  */
            break;
      
          case 'h':
            show_help ();
            break;
        
          case 'l':
            do_local = 1;
            if (do_utc)
              {
                error (EXIT_SUCCESS, 0, ("\
The options `-u' and `-l' are mutually exclusive."));
                show_usage ();
              }
            break;
              
          case 's':
            verbose = 0;
            break;
          
          case 't':
            do_tz = 1;
            if (no_tz)
              {
                error (EXIT_SUCCESS, 0, ("\
The options `-n' and `-t' are mutually exclusive."));
                show_usage ();
              }
            newtz = optarg;
            break;
            
          case 'n':
            no_tz = 1;
            if (do_tz)
              {
                error (EXIT_SUCCESS, 0, ("\
The options `-n' and `-t' are mutually exclusive."));
                show_usage ();
              }
            if (putenv ("TZ") != 0)
              error (EXIT_FAILURE, errno, "can\'t unset TZ envariable");
            break;
            
          case 'u':
            do_utc = 1;
            if (do_local)
              {
                error (EXIT_SUCCESS, 0, ("\
The options `-u' and `-l' are mutually exclusive."));
                show_usage ();
              }
            break;
              
          case 'V':
            show_version ();
      
          case 'v':
            verbose = 1;
            break;
            
          default:
            show_usage ();
        }
    }
  
  /* Check if Ssystem is available.  */
  __set_errno (-Ssystem (-1, 0, 0));
  if (errno != 0)
    error (EXIT_FAILURE, errno, ("Ssystem kernel facility not available"));
  
  /* If timezone was set on the command line, set it now.  */
  if (newtz != NULL)
    {
      char* tzenv = malloc (strlen (newtz) + 4);
      
      if (tzenv == NULL)
        error (EXIT_FAILURE, 0, "virtual memory exhausted");

      sprintf (tzenv, "TZ=%s", newtz);
      
      if (putenv (tzenv) != 0)
        error (EXIT_FAILURE, errno, "can\'t set TZ environment variable");
        
      tzset ();
    }
  
  if (do_utc || do_local)
    {
      int clockmode = do_utc ? 0 : 1;
      
      /* Now set the kernel timezone.  */
      now = time (NULL);
      if (now == (time_t) -1)
        {
          /* It is not necessarily sufficient to check if time returns -1
             because that is also a valid return value for Dec 31, 1969,
             23:59:59.  But we are in the nineties now and if we get this
             value there has something necessarily gone wrong.  */
           error (EXIT_FAILURE, errno, "can\'t get current time.\n");
        }
  
      tm = localtime (&now);
      if (tm == NULL)
          error (EXIT_FAILURE, errno, "can\'t convert to localtime.\n");

      tz.tz_minuteswest = tm->TM_GMTOFF / (-60);
      tz.tz_dsttime = tm->tm_isdst;
  
      if (Tsettimeofday (NULL, &tz) != 0)
        error (EXIT_FAILURE, errno, "settimeofday failed");

      /* Department of unclean tricks (setting errno).  */
      __set_errno (-Ssystem (S_CLOCKUTC, clockmode, 0));
      if (errno != 0)
        error (EXIT_FAILURE, errno, "can\'t set kernel clock mode");
      __set_errno (0);
  }
  
  /* If nothing to do, display current settings.  */
  if (verbose)
    {
      time_t now = time (NULL);
      struct tm* tm = localtime (&now);
      int gmtoff = tm->TM_GMTOFF;
      int sec_east = gmtoff % 60;
      int hrs_east = tm->TM_GMTOFF / 3600;
      int min_east = 60 * (gmtoff - sec_east - 3600 * hrs_east);
      
      printf ("Current date and time: %s", asctime (tm));
      printf ("Time zone in use: %s\n", tm->TM_ZONE);
      printf ("East of Greenwich Mean Time: %d:%02d:%02d\n", 
          hrs_east, min_east, sec_east);
      printf ("Kernel clock mode: %s\n", Ssystem (S_CLOCKUTC, -1, 0) ? 
              "localtime" : "UTC");
    }
    
  return EXIT_SUCCESS;
}

static 
void show_help ()
{
  printf ("\
Usage: %s [OPTIONS] ...\n\
Arguments that are mandatory to short options are mandatory to long\n\
options too.\n\
\n\
  -h, --help             display this help page and exit\n\
  -l, --localtime        set kernel clock to localtime mode\n\
  -s, --silent, --quiet  don\'t display any informative messages\n\
  -t, --timezone=TIMEZONE, --tz=TIMEZONE\n\
                         set timezone to TIMEZONE (instead of reading\n\
                         the environment)\n\
  -n, --no-timezone, --no-tz\n\
                         remove an eventually existing setting for the\n\
                         variable TZ from the environment\n\
  -u, --utc, --gmt       set kernel clock mode to UTC mode\n\
  -V, --version          display version information and exit\n\
  -v, --verbose          display verbose information (default)\n\
\n\
Set or examine kernel time-keeping variables.\n", program_invocation_name);

  exit (EXIT_SUCCESS);
}

static
void show_version ()
{
  if (program_invocation_short_name == NULL 
      || program_invocation_short_name[0] == '\0')
    program_invocation_short_name = "tzinit";
    
  if (__MINTLIB_REVISION__ != 0)
    printf ("%s - MiNTLib version %d.%d.%d\n", program_invocation_short_name,
        __MINTLIB_MAJOR__, __MINTLIB_MINOR__, __MINTLIB_REVISION__);
  else
    printf ("%s - MiNTLib version %d.%d.%d\n", program_invocation_short_name,
        __MINTLIB_MAJOR__, __MINTLIB_MINOR__, __MINTLIB_REVISION__);
  
  printf ("\
Copyright (C) 1999 Guido Flohr <guido@freemint.de>\n\
This program is free software, see the sources for copying conditions.\n\
There is no warranty, not even for merchantibility or fitness for a\n\
particular purpose.\n");
  exit (EXIT_SUCCESS);
}

static
void show_usage ()
{
  fflush (stdout);
  fprintf (stderr, "Try `%s --help' for more information.\n",
      program_invocation_name);
  exit (EXIT_FAILURE);
}
