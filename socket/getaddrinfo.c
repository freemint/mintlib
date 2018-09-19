/*
 *	getaddrinfo() emulation for MiNT-Net, (c) 2018, Thorsten Otto.
 */
#include "lib.h"
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "sockets_global.h"
#include <arpa/inet.h>

/*
 * Converts the current herrno error value into an EAI_* error code.
 * That error code is normally returned by getnameinfo() or getaddrinfo().
 */
static int gai_error_from_herrno(void)
{
	switch (h_errno)
	{
	case HOST_NOT_FOUND:
		return EAI_NONAME;

	case NO_ADDRESS:
#if NO_ADDRESS != NO_DATA
	case NO_DATA:
#endif
		return EAI_NODATA;

	case NO_RECOVERY:
		return EAI_FAIL;

	case TRY_AGAIN:
		return EAI_AGAIN;
	}
	return EAI_SYSTEM;
}


/*
 * Internal function that builds an addrinfo struct.
 */
static struct addrinfo *makeaddrinfo(
	int af, int type, int proto,
	const struct sockaddr *addr, size_t addrlen, const char *canonname)
{
	struct addrinfo *res;
	size_t size;
	
	size = sizeof(*res) + addrlen;
	if (canonname != NULL)
		size += strlen(canonname) + 1;
	res = (struct addrinfo *) malloc(size);
	if (res != NULL)
	{
		res->ai_flags = 0;
		res->ai_family = af;
		res->ai_socktype = type;
		res->ai_protocol = proto;
		res->ai_addrlen = addrlen;
		res->ai_canonname = NULL;
		res->ai_next = NULL;
		res->ai_addr = (struct sockaddr *)(res + 1);
		
		memcpy(res->ai_addr, addr, addrlen);

		if (canonname != NULL)
		{
			res->ai_canonname = (char *)res->ai_addr + sizeof(struct addrinfo) + addrlen;
			strcpy(res->ai_canonname, canonname);
		}
	}
	
	return res;
}


static struct addrinfo *makeipv4info(int type, int proto, uint32_t ip, uint16_t port, const char *name)
{
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_SIN_LEN
	addr.sin_len = sizeof(addr);
#endif
	addr.sin_port = port;
	addr.sin_addr.s_addr = ip;

	return makeaddrinfo(AF_INET, type, proto, (struct sockaddr *) &addr, sizeof(addr), name);
}


/*
 * getaddrinfo() non-thread-safe IPv4-only implementation
 * Address-family-independent hostname to address resolution.
 *
 * This is meant for IPv6-unaware systems that do probably not provide
 * getaddrinfo(), but still have old function gethostbyname().
 *
 * Only UDP and TCP over IPv4 are supported here.
 */
int __getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res)
{
	struct addrinfo *info;
	uint32_t ip;
	uint16_t port;
	int protocol = 0;
	int flags = 0;
	const char *name = NULL;

	*res = NULL;

	if (hints != NULL)
	{
		flags = hints->ai_flags;

		if (flags & ~(AI_PASSIVE|AI_CANONNAME|AI_NUMERICHOST))
			return EAI_BADFLAGS;
		/* only accept AF_INET and AF_UNSPEC */
		if (hints->ai_family && (hints->ai_family != AF_INET))
			return EAI_FAMILY;

		/* protocol sanity check */
		switch (hints->ai_socktype)
		{
		case SOCK_STREAM:
			protocol = IPPROTO_TCP;
			break;

		case SOCK_DGRAM:
			protocol = IPPROTO_UDP;
			break;

#ifdef SOCK_RAW
		case SOCK_RAW:
#endif
		case 0:
			break;

		default:
			return EAI_SOCKTYPE;
		}
		if (hints->ai_protocol && protocol && protocol != hints->ai_protocol)
			return EAI_SERVICE;
	}

	/* default values */
	if (node == NULL)
	{
		if (flags & AI_PASSIVE)
			ip = htonl(INADDR_ANY);
		else
			ip = htonl(INADDR_LOOPBACK);
	} else if ((ip = inet_addr(node)) == INADDR_NONE)
	{
		struct hostent *entry = NULL;

		/* hostname resolution */
		if (!(flags & AI_NUMERICHOST))
			entry = gethostbyname(node);

		if (entry == NULL)
			return gai_error_from_herrno();

		if (entry->h_length != 4 || entry->h_addrtype != AF_INET)
			return EAI_FAMILY;

		ip = *((uint32_t *) entry->h_addr);
		if (flags & AI_CANONNAME)
			name = entry->h_name;
	}

	if ((flags & AI_CANONNAME) && name == NULL)
		name = node;

	/* service resolution */
	if (service == NULL)
	{
		port = 0;
	} else
	{
		unsigned long d;
		char *end;
		struct servent *sp;

		d = strtoul(service, &end, 0);
		if (!end[0]) {
			if (d > 65535)
				return (EAI_SERVICE);
			port = htons((unsigned short) d);
		} else
		{
			sp = getservbyname(service, NULL);
			if (sp == NULL)
				return (EAI_SERVICE);
			port = sp->s_port;
		}
	}

	/* building results... */
	if (protocol == 0 || protocol == IPPROTO_UDP)
	{
		info = makeipv4info(SOCK_DGRAM, IPPROTO_UDP, ip, port, name);
		if (info == NULL)
		{
			errno = ENOMEM;
			return EAI_SYSTEM;
		}
		if (flags & AI_PASSIVE)
			info->ai_flags |= AI_PASSIVE;
		*res = info;
	}
	if (protocol == 0 || protocol == IPPROTO_TCP)
	{
		info = makeipv4info(SOCK_STREAM, IPPROTO_TCP, ip, port, name);
		if (info == NULL)
		{
			errno = ENOMEM;
			return EAI_SYSTEM;
		}
		info->ai_next = *res;
		if (flags & AI_PASSIVE)
			info->ai_flags |= AI_PASSIVE;
		*res = info;
	}

	return 0;
}

weak_alias(__getaddrinfo, getaddrinfo)
