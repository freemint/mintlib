/*  gethostid.c -- MiNTLib.
    Copyright (C) 1999 Guido Flohr <gufl0000@stud.uni-sb.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

long int
gethostid (void)
{
  struct hostent* hp;
  static char hname[MAXHOSTNAMELEN];

  if (gethostname (hname, sizeof (hname) < 0))
    return INADDR_NONE;
  if (!(hp = gethostbyname (hname)))
    return INADDR_NONE;
  return *(u_long *) hp->h_addr;
}
