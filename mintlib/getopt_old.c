/*
 *      GETOPT.C
 *      System V like command line option parser
 */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* !  This function is a modified version of getopt() `stolen' from   ! */
/* !  the public domain electronic mail system ELM version 2.3        ! */
/* !    (C) Copyright 1986, 1987, by Dave Taylor                      ! */
/* !    (C) Copyright 1988, 1989, 1990, USENET Community Trust        ! */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/* If your software can accept the terms and conditions of the GNU
   General Public License you should use the GNU getopt version instead,
   preferably even getopt_long because this facilitates the user
   interface.  */
   
#include <stdio.h>
#include <string.h>
#define _AVOID_GPL  /* This will rename FUNC to __FUNC_old.  */
#include <unistd.h>

int  opterr = 1;                /* Error handling flag  */
int  optind = 1;                /* Index in argv        */
int  optopt;                    /* Current option       */
char *optarg;                   /* Option argument      */

int getopt(int argc, char * const *argv, const char* opts)
{
  static int stringptr = 1;
  char *cp;
  int c;

  if(stringptr == 1) {
    if(optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0') {
      return(EOF);
    } else if( !strcmp(argv[optind], "--")) {
      optind++;
      return(EOF);
    }
  }
  optopt = c = argv[optind][stringptr];
  if(c == ':' || (cp = strchr(opts, c)) == NULL) {
    if(opterr)
      (void) fprintf(stderr, "%s: illegal option -- %c\n", argv[0], c);
    else if(argv[optind][++stringptr] == '\0') {
      optind++;
      stringptr = 1;
    }
    return('?');
  }
  if(*++cp == ':') {
    if(argv[optind][stringptr+1] != '\0')
      optarg = &argv[optind++][stringptr+1];
    else if(++optind >= argc) {
      if(opterr)
       (void) fprintf(stderr, "%s: option requires an argument -- %c\n",
                      argv[0], c);
      stringptr = 1;
      return('?');
    }
    else
      optarg = argv[optind++];
    stringptr = 1;
  }
  else {
    if(argv[optind][++stringptr] == '\0') {
      stringptr = 1;
      optind++;
    }
    optarg = NULL;
  }
  return(c);

} /* getopt() */

