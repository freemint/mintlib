/*  gethostid.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <guido@freemint.de>
    Copyright (C) 2001 Colin C Tinker <colint@cvsf325.marconicomms.com>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

/* $Id */

#include <netdb.h>             /* for INADDR_NONE & hostent */
#include <netinet/in.h>        /* for gethostbyname         */
#include <sys/utsname.h>       /* for uname                 */
#include <stdlib.h>            /* for NULL                  */

long int
__gethostid (void)
{
  /* temporary space for uname() response */
  struct utsname uts_name;

  /* temporary space for host entry */
  struct hostent* hp = NULL;

  /* get caller's nodename */
  if (uname(&uts_name) == 0)
  {
    /* convert nodename to IP address */
    hp = gethostbyname(uts_name.nodename);
  }

  /* return IP address if there is one, else error */
  return hp ? htonl(*(u_long *)hp->h_addr) : INADDR_NONE;
}
weak_alias (__gethostid, gethostid)
