/* Copyright (C) 1998, 1999 Free Software Foundation, Inc.
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
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#include <sys/socket.h>

#include <netinet/in.h>
#include <sys/un.h>

int
__libc_sa_len (sa_family_t af)
{
  switch (af)
    {
    case AF_INET:
      return sizeof (struct sockaddr_in);
    case AF_LOCAL:
      return sizeof (struct sockaddr_un);
    }
  return 0;
}
