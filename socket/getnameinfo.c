/*
 *	getnameinfo() emulation for MiNT-Net, (c) 2018, Thorsten Otto.
 */
#include "lib.h"
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include "sockets_global.h"

#ifndef min
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif


int __getnameinfo(
	const struct sockaddr *sa,
	socklen_t addrlen,
	char *host,
	socklen_t hostlen,
	char *serv,
	socklen_t servlen,
	int flags)
{
	int serrno = errno;
	int ok;
	struct hostent *h = NULL;
	char domain[256];

	if (flags & ~(NI_NUMERICHOST | NI_NUMERICSERV | NI_NOFQDN | NI_NAMEREQD | NI_DGRAM))
		return EAI_BADFLAGS;

	if (sa == NULL || addrlen < sizeof(sa_family_t))
		return EAI_FAMILY;

	if (sa->sa_family == AF_LOCAL)
	{
		/* valid */ ;
	} else if (sa->sa_family == AF_INET)
	{
		if (addrlen < sizeof(struct sockaddr_in))
			return EAI_FAMILY;
	} else if (sa->sa_family == AF_INET6)
	{
		if (addrlen < sizeof(struct sockaddr_in6))
			return EAI_FAMILY;
	} else
	{
		return EAI_FAMILY;
	}

	ok = 0;
	if (host != NULL && hostlen > 0)
	{
		switch (sa->sa_family)
		{
		case AF_INET:
		case AF_INET6:
			if (!(flags & NI_NUMERICHOST))
			{
				if (sa->sa_family == AF_INET6)
					h = gethostbyaddr((const void *)
									  &(((const struct sockaddr_in6 *) sa)->sin6_addr),
									  sizeof(struct in6_addr), AF_INET6);
				else
					h = gethostbyaddr((const void *)
									  &(((const struct sockaddr_in *) sa)->sin_addr), sizeof(struct in_addr), AF_INET);

				if (h)
				{
					char *c;

					if ((flags & NI_NOFQDN) &&
						getdomainname(domain, sizeof(domain)) == 0 &&
						(c = strstr(h->h_name, domain)) != NULL &&
						c != h->h_name &&
						(*(--c) == '.'))
					{
						hostlen = min(hostlen, (size_t) (c - h->h_name));
						strncpy(host, h->h_name, hostlen);
					} else
					{
						strncpy(host, h->h_name, hostlen);
					}
					ok = 1;
				}
			}

			if (!ok)
			{
				const char *c;

				if (flags & NI_NAMEREQD)
				{
					errno = serrno;
					return EAI_NONAME;
				}
				if (sa->sa_family == AF_INET6)
				{
					const struct sockaddr_in6 *sin6p;

					sin6p = (const struct sockaddr_in6 *) sa;
					c = inet_ntop(AF_INET6, (const void *) &sin6p->sin6_addr, host, hostlen);
				} else
				{
					c = inet_ntop(AF_INET, (const void *)
								  &(((const struct sockaddr_in *) sa)->sin_addr), host, hostlen);
				}
				if (c == NULL)
				{
					errno = serrno;
					return EAI_SYSTEM;
				}
				ok = 1;
			}
			break;

		case AF_LOCAL:
			if (!(flags & NI_NUMERICHOST))
			{
				struct utsname utsname;

				if (uname(&utsname) == 0)
				{
					strncpy(host, utsname.nodename, hostlen);
					break;
				}
			}

			if (flags & NI_NAMEREQD)
			{
				errno = serrno;
				return EAI_NONAME;
			}

			strncpy(host, "localhost", hostlen);
			break;

		default:
			return EAI_FAMILY;
		}
	}

	if (serv && servlen > 0)
	{
		if (sa->sa_family == AF_LOCAL)
		{
			strncpy(serv, ((const struct sockaddr_un *) sa)->sun_path, servlen);
		} else
		{								/* AF_INET || AF_INET6 */
			if (!(flags & NI_NUMERICSERV))
			{
				struct servent *s;

				s = getservbyport(((const struct sockaddr_in *) sa)->sin_port, flags & NI_DGRAM ? "udp" : "tcp");
				if (s)
				{
					strncpy(serv, s->s_name, servlen);
					ok = 1;
				}
			}
			if (!ok)
			{
				if (snprintf(serv, servlen, "%u", ntohs(((const struct sockaddr_in *) sa)->sin_port)) >= (int)servlen)
					return EAI_OVERFLOW;
			}
		}
	}

	if (host && hostlen > 0)
		host[hostlen - 1] = 0;
	if (serv && servlen > 0)
		serv[servlen - 1] = 0;
	errno = serrno;
	return 0;
}
weak_alias(__getnameinfo, getnameinfo)
