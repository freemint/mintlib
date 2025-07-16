/* Declarations of socket constants, types, and functions.
   Copyright (C) 1991,92,94,95,96,97,98,99,2000 Free Software Foundation, Inc.
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

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#ifndef	_SYS_SOCKET_H
#define	_SYS_SOCKET_H	1

#ifndef	_FEATURES_H
# include <features.h>
#endif

#include <sys/uio.h>
#define	__need_size_t
#include <stddef.h>


__BEGIN_DECLS

/* This operating system-specific header file defines the SOCK_*, PF_*,
   AF_*, MSG_*, SOL_*, and SO_* constants, and the `struct sockaddr',
   `struct msghdr', and `struct linger' types.  */
#include <bits/socket.h>

#ifdef __USE_BSD
/* This is the 4.3 BSD `struct sockaddr' format, which is used as wire
   format in the grotty old 4.3 `talk' protocol.  */
struct osockaddr
  {
    unsigned short int sa_family;
    unsigned char sa_data[14];
  };
#endif

/* The following constants should be used for the second parameter of
   `shutdown'.  */
enum
{
  SHUT_RD = 0,		/* No more receptions.  */
#define SHUT_RD		SHUT_RD
  SHUT_WR,		/* No more transmissions.  */
#define SHUT_WR		SHUT_WR
  SHUT_RDWR		/* No more receptions or transmissions.  */
#define SHUT_RDWR	SHUT_RDWR
};

/* This is the type we use for generic socket address arguments.

   With GCC 2.7 and later, the funky union causes redeclarations or
   uses with any of the listed types to be allowed without complaint.
   G++ 2.7 does not support transparent unions so there we want the
   old-style declaration, too.  */
#if defined __cplusplus || !__GNUC_PREREQ (2, 7) || !defined __USE_GNU
# define __SOCKADDR_ARG		struct sockaddr *__restrict
# define __CONST_SOCKADDR_ARG	__const struct sockaddr *
#else
/* Add more `struct sockaddr_AF' types here as necessary.  */
# define __SOCKADDR_ALLTYPES \
  __SOCKADDR_ONETYPE (sockaddr) \
  __SOCKADDR_ONETYPE (sockaddr_in) \
  __SOCKADDR_ONETYPE (sockaddr_un)

# define __SOCKADDR_ONETYPE(type) struct type *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES
	      } __SOCKADDR_ARG __attribute__ ((__transparent_union__));
# undef __SOCKADDR_ONETYPE
# define __SOCKADDR_ONETYPE(type) __const struct type *__restrict __##type##__;
typedef union { __SOCKADDR_ALLTYPES
	      } __CONST_SOCKADDR_ARG __attribute__ ((__transparent_union__));
# undef __SOCKADDR_ONETYPE
#endif


/* Create a new socket of type TYPE in domain DOMAIN, using
   protocol PROTOCOL.  If PROTOCOL is zero, one is chosen automatically.
   Returns a file descriptor for the new socket, or -1 for errors.  */
extern int socket (int __domain, int __type, int __protocol) __THROW;

/* Create two new sockets, of type TYPE in domain DOMAIN and using
   protocol PROTOCOL, which are connected to each other, and put file
   descriptors for them in FDS[0] and FDS[1].  If PROTOCOL is zero,
   one will be chosen automatically.  Returns 0 on success, -1 for errors.  */
extern int socketpair (int __domain, int __type, int __protocol,
		       int __fds[2]) __THROW;

/* Give the socket FD the local address ADDR (which is LEN bytes long).  */
extern int bind (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
     __THROW;

/* Put the local address of FD into *ADDR and its length in *LEN.  */
extern int getsockname (int __fd, __SOCKADDR_ARG __addr,
			socklen_t *__restrict __len) __THROW;

/* Open a connection on socket FD to peer at ADDR (which LEN bytes long).
   For connectionless socket types, just set the default address to send to
   and the only address from which to accept transmissions.
   Return 0 on success, -1 for errors.  */
extern int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len)
     __THROW;

/* Put the address of the peer connected to socket FD into *ADDR
   (which is *LEN bytes long), and its actual length into *LEN.  */
extern int getpeername (int __fd, __SOCKADDR_ARG __addr,
			socklen_t *__restrict __len) __THROW;


/* Send N bytes of BUF to socket FD.  Returns the number sent or -1.  */
extern int send (int __fd, __const void *__buf, size_t __n, int __flags)
     __THROW;

/* Read N bytes into BUF from socket FD.
   Returns the number read or -1 for errors.  */
extern int recv (int __fd, void *__buf, size_t __n, int __flags)
     __THROW;

/* Send N bytes of BUF on socket FD to peer at address ADDR (which is
   ADDR_LEN bytes long).  Returns the number sent, or -1 for errors.  */
extern int sendto (int __fd, __const void *__buf, size_t __n,
		   int __flags, __CONST_SOCKADDR_ARG __addr,
		   socklen_t __addr_len) __THROW;

/* Read N bytes into BUF through socket FD.
   If ADDR is not NULL, fill in *ADDR_LEN bytes of it with tha address of
   the sender, and store the actual size of the address in *ADDR_LEN.
   Returns the number of bytes read or -1 for errors.  */
extern int recvfrom (int __fd, void *__restrict __buf, size_t __n, int __flags,
		     __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len)
     __THROW;


/* Send a message described MESSAGE on socket FD.
   Returns the number of bytes sent, or -1 for errors.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
# ifndef __USE_TIME_BITS64
extern int sendmsg (int __fd, __const struct msghdr *__message, int __flags);

/* Receive a message as described by MESSAGE from socket FD.
   Returns the number of bytes read or -1 for errors.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
extern int recvmsg (int __fd, struct msghdr *__message, int __flags);
#else
extern int __REDIRECT(sendmsg, (int __fd, const struct msghdr *__message,
				     int __flags),
			   __sendmsg64);
extern int __REDIRECT (recvmsg,
			   (int __fd, struct msghdr *__message, int __flags),
			   __recvmsg64);
#endif


/* Put the current value for socket FD's option OPTNAME at protocol level LEVEL
   into OPTVAL (which is *OPTLEN bytes long), and set *OPTLEN to the value's
   actual length.  Returns 0 on success, -1 for errors.  */
extern int getsockopt (int __fd, int __level, int __optname,
		       void *__restrict __optval,
		       socklen_t *__restrict __optlen) __THROW;

/* Set socket FD's option OPTNAME at protocol level LEVEL
   to *OPTVAL (which is OPTLEN bytes long).
   Returns 0 on success, -1 for errors.  */
extern int setsockopt (int __fd, int __level, int __optname,
		       __const void *__optval, socklen_t __optlen) __THROW;


/* Prepare to accept connections on socket FD.
   N connection requests will be queued before further requests are refused.
   Returns 0 on success, -1 for errors.  */
extern int listen (int __fd, unsigned int __n) __THROW;

/* Await a connection on socket FD.
   When a connection arrives, open a new socket to communicate with it,
   set *ADDR (which is *ADDR_LEN bytes long) to the address of the connecting
   peer and *ADDR_LEN to the address's actual length, and return the
   new socket's descriptor, or -1 for errors.  */
extern int accept (int __fd, __SOCKADDR_ARG __addr,
		   socklen_t *__restrict __addr_len)
     __THROW;

/* Shut down all or part of the connection open on socket FD.
   HOW determines what to shut down:
     SHUT_RD   = No more receptions;
     SHUT_WR   = No more transmissions;
     SHUT_RDWR = No more receptions or transmissions.
   Returns 0 on success, -1 for errors.  */
extern int shutdown (int __fd, int __how) __THROW;


/* FDTYPE is S_IFSOCK or another S_IF* macro defined in <sys/stat.h>;
   returns 1 if FD is open on an object of the indicated type, 0 if not,
   or -1 for errors (setting errno).  */
extern int isfdtype (int __fd, int __fdtype) __THROW;

__END_DECLS

#endif /* sys/socket.h */
