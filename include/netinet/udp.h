/*
 *	netinet/udp.h for MintNet, (w) '94, Kay Roemer.
 */

#ifndef _NETINET_UDP_H
#define _NETINET_UDP_H

#ifndef	_FEATURES_H
# include <features.h>
#endif

__BEGIN_DECLS

struct udphdr {
	unsigned short	uh_sport;	/* source port */
	unsigned short	uh_dport;	/* destination port */
	unsigned short	uh_ulen;	/* datagram length */
	unsigned short	uh_sum;		/* checksum */
};

__END_DECLS

#endif /* _NETINET_UDP_H */
