/*
 *	sys/socket.h for MiNT-Net, (w) '93, kay roemer.
 */

#ifndef _SYS_SOCKET_H
#define _SYS_SOCKET_H

#ifndef _COMPILER_H
#include <compiler.h>
#endif

#include <iovec.h>

#define __need_size_t
#include <stddef.h>

/* Socket types */
#define SOCK_STREAM	1
#define SOCK_DGRAM	2
#define SOCK_RAW	3
#define SOCK_RDM	4
#define SOCK_SEQPACKET	5

/* Protocol families */
#define PF_UNSPEC	0
#define PF_UNIX		1
#define PF_INET		2
#define	PF_APPLETALK	5
#define PF_MAX		32 /* Taken from Linux */

/* Address families, same as above */
#define AF_UNSPEC	PF_UNSPEC
#define AF_UNIX		PF_UNIX
#define	AF_LOCAL	PF_UNIX
#define AF_INET		PF_INET
#define	AF_APPLETALK	PF_APPLETALK
#define AF_LINK		200
#define AF_MAX		PF_MAX

/* Flags for send/recv */
#define MSG_OOB		0x0001
#define MSG_PEEK	0x0002
#define MSG_DONTROUTE	0x0004

/* Levels for use with [s|g]etsockopt call */
#define SOL_SOCKET	0xffff

/* Options for use with [s|g]etsockopt call */
#define SO_DEBUG	1
#define SO_REUSEADDR	2
#define SO_TYPE		3
#define SO_ERROR	4
#define SO_DONTROUTE	5
#define SO_BROADCAST	6
#define SO_SNDBUF	7
#define SO_RCVBUF	8
#define SO_KEEPALIVE	9
#define SO_OOBINLINE	10
#define SO_LINGER	11
#define SO_CHKSUM	40
#define SO_DROPCONN	41

__BEGIN_DECLS

/* Structure used for SO_LINGER */
struct linger {
	long	l_onoff;
	long	l_linger;
};

/* Generic socket address */
struct sockaddr {
	short	sa_family;
	char	sa_data[14];
};

/* Structure describing a message used with sendmsg/recvmsg */
struct msghdr {
	void		*msg_name;
	size_t		msg_namelen;
	struct iovec	*msg_iov;
	size_t		msg_iovlen;
	void		*msg_accrights;
	size_t		msg_accrightslen;
};

__EXTERN int	socket		__PROTO((int, int, int));
__EXTERN int	socketpair	__PROTO((int, int, int, int[2]));
__EXTERN int	bind		__PROTO((int, struct sockaddr *, size_t));
__EXTERN int	connect		__PROTO((int, struct sockaddr *, size_t));
__EXTERN int	accept		__PROTO((int, struct sockaddr *, size_t *)); 
__EXTERN int	listen		__PROTO((int, int));
__EXTERN int	getsockname	__PROTO((int, struct sockaddr *, size_t *));
__EXTERN int	getpeername	__PROTO((int, struct sockaddr *, size_t *));
__EXTERN int	send		__PROTO((int, const void *, ssize_t, int));
__EXTERN int	recv		__PROTO((int, void *, ssize_t, int));
__EXTERN int	sendto		__PROTO((int, const void *, ssize_t, int,
					const struct sockaddr *, int));

__EXTERN int	recvfrom	__PROTO((int, void *, ssize_t, int,
					struct sockaddr *, int *));

__EXTERN int	sendmsg		__PROTO((int, const struct msghdr *, int));
__EXTERN int	recvmsg		__PROTO((int, struct msghdr *, int));
__EXTERN int	getsockopt	__PROTO((int, int, int, void *, size_t *));
__EXTERN int	setsockopt	__PROTO((int, int, int, void *, size_t));
__EXTERN int	shutdown	__PROTO((int, int));

__END_DECLS

#endif /* _SYS_SOCKET_H */
