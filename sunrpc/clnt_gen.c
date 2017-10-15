/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
/*
 * Copyright (C) 1987, Sun Microsystems, Inc.
 */

#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <rpc/rpc.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <netdb.h>

struct hostent * __gethostbyname (const char *name);
struct protoent * __getprotobyname (const char *name);

/*
 * Generic client creation: takes (hostname, program-number, protocol) and
 * returns client handle. Default options are set, which the user can
 * change using the rpc equivalent of ioctl()'s.
 */
CLIENT *
clnt_create (const char *hostname, u_long prog, u_long vers,
	     const char *proto)
{
  struct hostent *h;
#ifndef __MINT__
  struct hostent hostbuf, *h;
  size_t hstbuflen;
  char *hsttmpbuf;
#endif
  struct protoent *p;
#ifndef __MINT__
  struct protoent protobuf;
  size_t prtbuflen;
  char *prttmpbuf;
  int herr;
#endif
  struct sockaddr_in sin;
  struct sockaddr_un sun;
  int sock;
  struct timeval tv;
  CLIENT *client;

  if (strcmp (proto, "unix") == 0)
    {
      memset((char *)&sun, 0, sizeof (sun));
      sun.sun_family = AF_UNIX;
      strcpy (sun.sun_path, hostname);
      sock = RPC_ANYSOCK;
      client = clntunix_create (&sun, prog, vers, &sock, 0, 0);
      if (client == NULL)
	return NULL;
#if 0
      /* This is not wanted.  This would disable the user from having
	 a timeout in the clnt_call() call.  Only a call to cnlt_control()
	 by the user should set the timeout value.  */
      tv.tv_sec = 25;
      tv.tv_usec = 0;
      clnt_control (client, CLSET_TIMEOUT, (char *)&tv);
#endif
      return client;
    }

#ifndef __MINT__
  hstbuflen = 1024;
  hsttmpbuf = __alloca (hstbuflen);
  while (__gethostbyname_r (hostname, &hostbuf, hsttmpbuf, hstbuflen,
			    &h, &herr) != 0
	 || h == NULL)
    if (herr != NETDB_INTERNAL || errno != ERANGE)
      {
	rpc_createerr.cf_stat = RPC_UNKNOWNHOST;
	return NULL;
      }
    else
      {
	/* Enlarge the buffer.  */
	hstbuflen *= 2;
	hsttmpbuf = __alloca (hstbuflen);
      }
#else
  h = __gethostbyname (hostname);
  if (h == NULL)
    {
	rpc_createerr.cf_stat = RPC_UNKNOWNHOST;
	return NULL;
    }
#endif

  if (h->h_addrtype != AF_INET)
    {
      /*
       * Only support INET for now
       */
      rpc_createerr.cf_stat = RPC_SYSTEMERROR;
      rpc_createerr.cf_error.re_errno = EAFNOSUPPORT;
      return NULL;
    }
  sin.sin_family = h->h_addrtype;
  sin.sin_port = 0;
  memset(sin.sin_zero, 0, sizeof (sin.sin_zero));
  memcpy((char *) &sin.sin_addr, h->h_addr, h->h_length);

#ifndef __MINT__
  prtbuflen = 1024;
  prttmpbuf = __alloca (prtbuflen);
  while (__getprotobyname_r (proto, &protobuf, prttmpbuf, prtbuflen, &p) != 0
	 || p == NULL)
    if (errno != ERANGE)
      {
	rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
	rpc_createerr.cf_error.re_errno = EPFNOSUPPORT;
	return NULL;
      }
    else
      {
	/* Enlarge the buffer.  */
	prtbuflen *= 2;
	prttmpbuf = __alloca (prtbuflen);
      }
#else
  p = __getprotobyname (proto);
  if (p == NULL)
    {
	rpc_createerr.cf_stat = RPC_UNKNOWNPROTO;
	rpc_createerr.cf_error.re_errno = EPFNOSUPPORT; 
	return NULL;
    }
#endif

  sock = RPC_ANYSOCK;
  switch (p->p_proto)
    {
    case IPPROTO_UDP:
      tv.tv_sec = 5;
      tv.tv_usec = 0;
      client = clntudp_create (&sin, prog, vers, tv, &sock);
      if (client == NULL)
	{
	  return NULL;
	}
#if 0
      /* This is not wanted.  This would disable the user from having
	 a timeout in the clnt_call() call.  Only a call to cnlt_control()
	 by the user should set the timeout value.  */
      tv.tv_sec = 25;
      clnt_control (client, CLSET_TIMEOUT, (char *)&tv);
#endif
      break;
    case IPPROTO_TCP:
      client = clnttcp_create (&sin, prog, vers, &sock, 0, 0);
      if (client == NULL)
	{
	  return NULL;
	}
#if 0
      /* This is not wanted.  This would disable the user from having
	 a timeout in the clnt_call() call.  Only a call to cnlt_control()
	 by the user should set the timeout value.  */
      tv.tv_sec = 25;
      tv.tv_usec = 0;
      clnt_control (client, CLSET_TIMEOUT, (char *)&tv);
#endif
      break;
    default:
      rpc_createerr.cf_stat = RPC_SYSTEMERROR;
      rpc_createerr.cf_error.re_errno = EPFNOSUPPORT;
      return (NULL);
    }
  return client;
}
