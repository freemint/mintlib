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
extern int _proto_stayopen;
extern int _net_stayopen;
extern int _serv_stayopen;

#ifdef _NETDB_H_
extern __typeof (getnameinfo) __getnameinfo;
extern __typeof (getaddrinfo) __getaddrinfo;
extern __typeof (freeaddrinfo) __freeaddrinfo;
extern __typeof (gai_strerror) __gai_strerror;
__typeof__(getprotobynumber) __getprotobynumber;
__typeof__(gethostbyname) __gethostbyname;
__typeof__(gethostbyaddr) __gethostbyaddr;
__typeof__(getnetbyname) __getnetbyname;
__typeof__(getnetent) __getnetent;

void __setprotoent (int f);
void __endprotoent (void);
struct protoent * __getprotoent (void);

void __setnetent (int f);
void __endnetent (void);

void __setservent (int f);
void __endservent (void);
struct servent * __getservent (void);

#endif

void _res_close (void);

#endif /* _SOCKETS_GLOBAL_H */
