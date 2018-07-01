/*  sockets_global.h -- MiNTLib.
    Copyright (C) 2000 Frank Naumann <fnaumann@freemint.de>

    This file is part of the MiNTLib project, and may only be used
    modified and distributed under the terms of the MiNTLib project
    license, COPYMINT.  By continuing to use, modify, or distribute
    this file you indicate that you have read the license and
    understand and accept it fully.
*/

#ifndef _SOCKETS_GLOBAL_H
#define _SOCKETS_GLOBAL_H	1


extern short __libc_newsockets;

#ifdef _NETDB_H_
extern __typeof (getnameinfo) __getnameinfo;
extern __typeof (getaddrinfo) __getaddrinfo;
extern __typeof (freeaddrinfo) __freeaddrinfo;
extern __typeof (gai_strerror) __gai_strerror;
#endif

#endif /* _SOCKETS_GLOBAL_H */
