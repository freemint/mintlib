/*
 * Copyright (c) 1985, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)gethostnamadr.c	6.48 (Berkeley) 1/10/93";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <netdb.h>
#include <resolv.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <net/if.h>             /* for struct ifconf */
#include <sockios.h>		/* for SIOC* */

#ifdef __MINT__
#include <support.h>		/* for gethostname() */
#define strcasecmp(a,b)		stricmp(a,b)
#define strncasecmp(a,b,c)	strnicmp(a,b,c)
#endif

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	64
#endif

#define	MAXALIASES	35
#define	MAXADDRS	35
#define MAXTRIMDOMAINS  4
#define HOSTDB		_PATH_HOSTS

#define SERVICE_NONE	0
#define SERVICE_BIND	1
#define SERVICE_HOSTS	2
#define SERVICE_NIS	3
#define SERVICE_MAX	3

#define CMD_ORDER	"order"
#define CMD_TRIMDOMAIN	"trim"
#define CMD_HMA		"multi"
#define CMD_SPOOF	"nospoof"
#define CMD_SPOOFALERT	"alert"
#define CMD_REORDER	"reorder"
#define CMD_ON		"on"
#define CMD_OFF		"off"
#define CMD_WARN	"warn"
#define CMD_NOWARN	"warn off"

#define ORD_BIND	"bind"
#define ORD_HOSTS	"hosts"
#define ORD_NIS		"nis"

#define ENV_HOSTCONF	"RESOLV_HOST_CONF"
#define ENV_SERVORDER	"RESOLV_SERV_ORDER"
#define ENV_SPOOF	"RESOLV_SPOOF_CHECK"
#define ENV_TRIM_OVERR	"RESOLV_OVERRIDE_TRIM_DOMAINS"
#define ENV_TRIM_ADD	"RESOLV_ADD_TRIM_DOMAINS"
#define ENV_HMA		"RESOLV_MULTI"
#define ENV_REORDER	"RESOLV_REORDER"

#define TOKEN_SEPARATORS " ,;:"

static int service_order[SERVICE_MAX + 1];
static int service_done = 0;

static char *h_addr_ptrs[MAXADDRS + 1];

static struct hostent host;
static char *host_aliases[MAXALIASES];
static char hostbuf[BUFSIZ+1];
static struct in_addr host_addr;
static FILE *hostf = NULL;
static char hostaddr[MAXADDRS];
static char *host_addrs[2];
static int stayopen = 0;
static int hosts_multiple_addrs = 0;
static int spoof = 0;
static int spoofalert = 0;
static int reorder = 0;
static char *trimdomain[MAXTRIMDOMAINS];
static char trimdomainbuf[BUFSIZ];
static int numtrimdomains = 0;
#ifndef __MINT__
char *strpbrk();
extern char *strstr(), *strtok(), *getenv();
#else
#include <stdlib.h>
#endif

#ifdef NIS
static struct hostent *_getnishost();
#endif

#if PACKETSZ > 1024
#define	MAXPACKET	PACKETSZ
#else
#define	MAXPACKET	1024
#endif

typedef union {
    HEADER hdr;
    u_char buf[MAXPACKET];
} querybuf;

typedef union {
    long al;
    char ac;
} align;

int h_errno;

static void
dotrimdomain (char *c)
{
	/* assume c points to the start of a host name; trim off any 
	   domain name matching any of the trimdomains */
	int d,l1,l2;
	
	for(d=0;d<numtrimdomains;d++){
		l1=strlen(trimdomain[d]);
		l2=strlen(c);
		if(l2>l1 && !strcasecmp(c+l2-l1,trimdomain[d]))
			*(c+(strlen(c)-l1))='\0';
	}
}

static struct hostent *
trim_domains (struct hostent *h)
{
	if(numtrimdomains){
		int i;
		dotrimdomain(h->h_name);
		for(i=0;h->h_aliases[i];i++)
			dotrimdomain(h->h_aliases[i]);
	}
	return(h);
}

/* reorder_addrs -- by Tom Limoncelli
	Optimize order of an address list.

	gethostbyaddr() usually returns a list of addresses in some
	arbitrary order.  Most programs use the first one and throw the
	rest away.  This routine attempts to find a "best" address and
	swap it into the first position in the list.  "Best" is defined
	as "an address that is on a local subnet".  The search ends after
	one "best" address is found.  If no "best" address is found,
	nothing is changed.

	On first execution, a table is built of interfaces, netmasks,
	and mask'ed addresses.  This is to speed up future queries but
	may require you to reboot after changing internet addresses.
	(doesn't everyone reboot after changing internet addresses?)

	This routine should not be called if gethostbyaddr() is about
	to return only one address.

*/

/* Hal Stern (June 1992) of Sun claimed that more than 4 ethernets in a
Sun 4/690 would not work.  This variable is set to 10 to accomodate our
version of reality */
#define MAXINTERFACES (10)

static void
reorder_addrs (struct hostent *h)
{
	static struct {
		char iname[16];
		u_long address, netmask;
		} itab[MAXINTERFACES], *itp;
	static int numitab = -1;	/* number of used entries in itab */
	register struct in_addr **r; /* pointer to entry in address list */
	struct in_addr tmp; /* pointer to entry in address list */
	register int cnt;

	/***	itab[] contains masked addresses and netmask of each interface.
			numitab is -1 : table is empty.
			numitab is 0  : should never happen.
			numitab is 1,2,3,... :  number of valid entries in the table.
	***/
	if (!numitab) return;	/* no entries in table */
	if (numitab==-1) { /* build the table */
		int fd, err;
		struct ifconf ifs;
		struct ifreq ifbuf[MAXINTERFACES], *p;
		register struct sockaddr_in *q;
		u_long address, netmask;
		int endp;

		/* open a socket */
        fd = socket(PF_INET, SOCK_DGRAM, 0);
		if (fd==-1) return;

		/**** get information about the first MAXINTERFACES interfaces ****/
		/* set up the ifconf structure */
        ifs.ifc_len = MAXINTERFACES * sizeof(struct ifreq);
        ifs.ifc_buf = (caddr_t) ifbuf;
        /* get a list of interfaces */
		err = ioctl(fd, SIOCGIFCONF, &ifs);
		if (err == -1) return;

		/**** cycle through each interface & get netmask & address ****/
		endp = ifs.ifc_len / sizeof(struct ifreq);
		itp = itab;
		for (p = ifs.ifc_req; endp; p++, endp--) {
			strcpy( itp->iname , p->ifr_name); /* copy interface name */

			err = ioctl(fd, SIOCGIFNETMASK, p); /* get netmask */
            if (err == -1) continue;	/* error? skip this interface */
            q = (struct sockaddr_in *) &(p->ifr_addr);
			if (q->sin_family == AF_INET) netmask=q->sin_addr.s_addr;
			else continue;	/* not internet protocol? skip this interface */

			err = ioctl(fd, SIOCGIFADDR, p); /* get address */
            if (err == -1) continue;	/* error? skip this interface */
            q = (struct sockaddr_in *) &(p->ifr_addr);
			if (q->sin_family == AF_INET) address=q->sin_addr.s_addr;
			else continue;	/* not internet protocol? skip this interface */

			/* store the masked address and netmask in the table */
			address = address & netmask;	/* pre-mask the address */
			if (!address) continue;	/* funny address? skip this interface */
			itp->address = address;
			itp->netmask = netmask;

			if (numitab == -1) numitab = 0;	 /* first time through */
			itp++; numitab++;
		}
		/**** clean up ****/
		close(fd);
		/**** if we still don't have a table, leave */
		if (!numitab) return;
	}

	/**** loop through table for each (address,interface) combo ****/
	for ( r = (struct in_addr **) (h->h_addr_list); *r; r++) {	/* loop through the addresses */
		for ( itp = itab, cnt=numitab; cnt; itp++,cnt--) {	/* loop though the interfaces */
			if (( (*r)->s_addr & itp->netmask) == itp->address) {	/* compare */
				/* We found a match.  Swap it into [0] */
				bcopy( ((struct in_addr **) (h->h_addr_list))[0],    &tmp, sizeof(tmp));
				bcopy( (*r),    ((struct in_addr **) (h->h_addr_list))[0], sizeof(tmp));
				bcopy( &tmp,                                      (*r), sizeof(tmp));

				return;	/* found one, don't need to continue */
			}
		} /* interfaces */
	} /* addresses */
}

static void
init_services (void)
{
	char *cp, *dp, buf[BUFSIZ];
	register int cc = 0;
	FILE *fd;
	char *tdp = trimdomainbuf;
	char *hostconf;

	if(NULL==(hostconf=getenv(ENV_HOSTCONF))){
		hostconf=_PATH_HOSTCONF;
	}
	if ((fd = (FILE *)fopen(hostconf, "rt")) == NULL) {
				/* make some assumptions */
		service_order[0] = SERVICE_HOSTS;
		service_order[1] = SERVICE_BIND;
		service_order[2] = SERVICE_NONE;
	} else {
		while (fgets(buf, BUFSIZ, fd) != NULL) {
			if ((cp = rindex(buf, '\n')) != NULL)
				*cp = '\0';
			if (buf[0] == '#')
				continue;

#define checkbuf(b, cmd) (!strncasecmp(b, cmd, strlen(cmd)))
#define bad_config_format(cmd) \
    fprintf(stderr, "resolv+: %s: \"%s\" command incorrectly formatted.\n", hostconf, cmd);

			if (checkbuf(buf, CMD_ORDER)) {
				cp = strpbrk(buf, " \t");
				if (!cp) 
                                {
                                    bad_config_format(CMD_ORDER);
                                } else 
                                {
                                    do {
					while (*cp == ' ' || *cp == '\t')
						cp++;
					dp = strpbrk(cp, TOKEN_SEPARATORS);
					if (dp) *dp = '\0';
					if (checkbuf(cp, ORD_BIND))
						service_order[cc++] = SERVICE_BIND;
					else if (checkbuf(cp, ORD_HOSTS))
						service_order[cc++] = SERVICE_HOSTS;
					else if (checkbuf(cp, ORD_NIS))
						service_order[cc++] = SERVICE_NIS;
					else
                                        {
                                            bad_config_format(CMD_ORDER);
                                            fprintf(stderr, "resolv+: \"%s\" is an invalid keyword\n", cp);
                                            fprintf(stderr, "resolv+: valid keywords are: %s, %s and %s\n",
                                                   ORD_BIND, ORD_HOSTS, ORD_NIS);
                                        }
                                        
					if (dp) cp = ++dp;
                                    } while (dp != NULL);
                                    if (cc == 0) 
                                    {
                                        bad_config_format(CMD_ORDER);
                                        fprintf(stderr, "resolv+: search order not specified or unrecognized keyword, host resolution will fail.\n");
                                    }
                                }
                                        
			} else if (checkbuf(buf, CMD_HMA)) {
                            if ((cp = strpbrk(buf, " \t"))) 
                            {
				while (*cp == ' ' || *cp == '\t') cp++;
				if (checkbuf(cp, CMD_ON))
					hosts_multiple_addrs = 1;
                            } else
                                bad_config_format(CMD_HMA);
                                
			} else if (checkbuf(buf, CMD_SPOOF)) {
                            if ((cp = strpbrk(buf, " \t")) ) 
                            {
				while (*cp == ' ' || *cp == '\t') cp++;
				if (checkbuf(cp, CMD_ON))
					spoof = 1;
                            } else
                                bad_config_format(CMD_SPOOF);

			} else if (checkbuf(buf, CMD_SPOOFALERT)) {
                            if ((cp = strpbrk(buf, " \t"))) 
                            {
				while (*cp == ' ' || *cp == '\t') cp++;
				if (checkbuf(cp, CMD_ON))
					spoofalert = 1;
                            } else
                                bad_config_format(CMD_SPOOFALERT);
                            
			} else if (checkbuf(buf, CMD_REORDER)) {
				if ((cp = strpbrk(buf, " \t"))) {
				while (*cp == ' ' || *cp == '\t') cp++;
				if (checkbuf(cp, CMD_ON))
					reorder = 1;
				} else
					bad_config_format(CMD_REORDER);

			} else if (checkbuf(buf, CMD_TRIMDOMAIN)) {
				if(numtrimdomains<MAXTRIMDOMAINS){
                                    if ((cp = strpbrk(buf, " \t")) ) 
                                    {
					while (*cp == ' ' || *cp == '\t') cp++;
                                        if (cp) 
                                        {
                                            (void) strcpy(tdp,cp);	
                                            trimdomain[numtrimdomains++]=tdp;
                                            tdp += strlen(cp)+1;
                                        } else
                                            bad_config_format(CMD_TRIMDOMAIN);
                                    } else
                                        bad_config_format(CMD_TRIMDOMAIN);
				}
			}
		}
		
		service_order[cc] = SERVICE_NONE;
		fclose(fd);
	}
	/* override service_order if environment variable */
	if(NULL!=(cp=getenv(ENV_SERVORDER))){
		cc=0;
		if(NULL!=(cp=strtok(cp, TOKEN_SEPARATORS))){
			do{
				if(checkbuf(cp, ORD_BIND))
					service_order[cc++] = SERVICE_BIND;
				else if (checkbuf(cp, ORD_HOSTS))
					service_order[cc++] = SERVICE_HOSTS;
				else if (checkbuf(cp, ORD_NIS))
					service_order[cc++] = SERVICE_NIS;
			} while((cp=strtok(NULL, TOKEN_SEPARATORS)));
		service_order[cc] = SERVICE_NONE;
		}
	}
	/* override spoof if environment variable */
	if(NULL!=(cp=getenv(ENV_SPOOF))){
		if(checkbuf(cp, CMD_WARN)){
			spoof=1;
			spoofalert=1;
		} else if (checkbuf(cp, CMD_OFF)){
			spoof=0;
			spoofalert=0;
		} else if (checkbuf(cp, CMD_NOWARN)){
			spoof=1;
			spoofalert=0;
		} else {
			spoof=1;
		}
	}

	/* override hma if environment variable */
	if(NULL!=(cp=getenv(ENV_HMA))) {
		if(checkbuf(cp, CMD_ON)) {
			hosts_multiple_addrs=1;
		} else {
			hosts_multiple_addrs=0;
		}
	}
	
	/* override reorder if environment variable */
	if ((cp = getenv(ENV_REORDER)) != NULL) {
		if (checkbuf(cp, CMD_ON)) {
			reorder = 1;
		} else {
			reorder = 0;
		}
	}

	/* add trimdomains from environment variable */
	if(NULL!=(cp=getenv(ENV_TRIM_ADD))){
		if(NULL!=(cp=strtok(cp, TOKEN_SEPARATORS))){
			do{
				if(numtrimdomains<MAXTRIMDOMAINS){
					(void)strcpy(tdp, cp);
					trimdomain[numtrimdomains++]=tdp;
					tdp += strlen(cp)+1;
				}
			} while((cp=strtok(NULL, TOKEN_SEPARATORS)));
		}
	}

	/* override trimdomains from environment variable */
	if(NULL!=(cp=getenv(ENV_TRIM_OVERR))){
		numtrimdomains=0;
		tdp=trimdomainbuf;
		if(NULL!=(cp=strtok(cp, TOKEN_SEPARATORS))){
			do{
				if(numtrimdomains<MAXTRIMDOMAINS){
					(void)strcpy(tdp, cp);
					trimdomain[numtrimdomains++]=tdp;
					tdp += strlen(cp)+1;
				}
			} while((cp=strtok(NULL, TOKEN_SEPARATORS)));
		}
	}
	
	service_done = 1;
}

static struct hostent *
getanswer (querybuf *answer, int anslen, int iquery)
{
	register HEADER *hp;
	register u_char *cp;
	register int n;
	u_char *eom;
	char *bp, **ap;
	int type, class, buflen, ancount, qdcount;
	int haveanswer, getclass = C_ANY;
	char **hap;

	eom = answer->buf + anslen;
	/*
	 * find first satisfactory answer
	 */
	hp = &answer->hdr;
	ancount = ntohs(hp->ancount);
	qdcount = ntohs(hp->qdcount);
	bp = hostbuf;
	buflen = sizeof(hostbuf);
	cp = answer->buf + sizeof(HEADER);
	if (qdcount) {
		if (iquery) {
			if ((n = dn_expand((u_char *)answer->buf,
			    (u_char *)eom, (u_char *)cp, (u_char *)bp,
			    buflen)) < 0) {
				h_errno = NO_RECOVERY;
				return ((struct hostent *) NULL);
			}
			cp += n + QFIXEDSZ;
			host.h_name = bp;
			n = strlen(bp) + 1;
			bp += n;
			buflen -= n;
		} else
			cp += __dn_skipname(cp, eom) + QFIXEDSZ;
		while (--qdcount > 0)
			cp += __dn_skipname(cp, eom) + QFIXEDSZ;
	} else if (iquery) {
		if (hp->aa)
			h_errno = HOST_NOT_FOUND;
		else
			h_errno = TRY_AGAIN;
		return ((struct hostent *) NULL);
	}
	ap = host_aliases;
	*ap = NULL;
	host.h_aliases = host_aliases;
	hap = h_addr_ptrs;
	*hap = NULL;
#if BSD >= 43 || defined(h_addr)	/* new-style hostent structure */
	host.h_addr_list = h_addr_ptrs;
#endif
	haveanswer = 0;
	while (--ancount >= 0 && cp < eom) {
		if ((n = dn_expand((u_char *)answer->buf, (u_char *)eom,
		    (u_char *)cp, (u_char *)bp, buflen)) < 0)
			break;
		cp += n;
		type = _getshort(cp);
 		cp += sizeof(u_short);
		class = _getshort(cp);
 		cp += sizeof(u_short) + sizeof(u_long);
		n = _getshort(cp);
		cp += sizeof(u_short);
		if (type == T_CNAME) {
			cp += n;
			if (ap >= &host_aliases[MAXALIASES-1])
				continue;
			*ap++ = bp;
			n = strlen(bp) + 1;
			bp += n;
			buflen -= n;
			continue;
		}
		if (iquery && type == T_PTR) {
			if ((n = dn_expand((u_char *)answer->buf,
			    (u_char *)eom, (u_char *)cp, (u_char *)bp,
			    buflen)) < 0)
				break;
			cp += n;
			host.h_name = bp;
			return(&host);
		}
		if (iquery || type != T_A)  {
#ifdef DEBUG
			if (_res.options & RES_DEBUG)
				printf("unexpected answer type %d, size %d\n",
					type, n);
#endif
			cp += n;
			continue;
		}
		if (haveanswer) {
			if (n != host.h_length) {
				cp += n;
				continue;
			}
			if (class != getclass) {
				cp += n;
				continue;
			}
		} else {
			host.h_length = n;
			getclass = class;
			host.h_addrtype = (class == C_IN) ? AF_INET : AF_UNSPEC;
			if (!iquery) {
				host.h_name = bp;
				bp += strlen(bp) + 1;
			}
		}

		bp += sizeof(align) - ((u_long)bp % sizeof(align));

		if (bp + n >= &hostbuf[sizeof(hostbuf)]) {
#ifdef DEBUG
			if (_res.options & RES_DEBUG)
				printf("size (%d) too big\n", n);
#endif
			break;
		}
		bcopy(cp, *hap++ = bp, n);
		bp +=n;
		cp += n;
		haveanswer++;
	}
	if (haveanswer) {
		*ap = NULL;
#if BSD >= 43 || defined(h_addr)	/* new-style hostent structure */
		*hap = NULL;
#else
		host.h_addr = h_addr_ptrs[0];
#endif
		return (&host);
	} else {
		h_errno = TRY_AGAIN;
		return ((struct hostent *) NULL);
	}
}

struct hostent *
__gethostbyname (const char *name)
{
	querybuf buf;
	register const char *cp;
	register int cc;
	int n;
	struct hostent *hp;
	extern struct hostent *_gethtbyname();

	/*
	 * disallow names consisting only of digits/dots, unless
	 * they end in a dot.
	 */
	if (isdigit(name[0]))
		for (cp = name;; ++cp) {
			if (!*cp) {
				if (*--cp == '.')
					break;
				/*
				 * All-numeric, no dot at the end.
				 * Fake up a hostent as if we'd actually
				 * done a lookup.
				 */
				if (!inet_aton(name, &host_addr)) {
					h_errno = HOST_NOT_FOUND;
					return((struct hostent *) NULL);
				}
				host.h_name = (char *)name;
				host.h_aliases = host_aliases;
				host_aliases[0] = NULL;
				host.h_addrtype = AF_INET;
				host.h_length = sizeof(u_long);
				h_addr_ptrs[0] = (char *)&host_addr;
				h_addr_ptrs[1] = (char *)0;
#if BSD >= 43 || defined(h_addr)	/* new-style hostent structure */
				host.h_addr_list = h_addr_ptrs;
#else
				host.h_addr = h_addr_ptrs[0];
#endif
				return (&host);
			}
			if (!isdigit(*cp) && *cp != '.') 
				break;
		}

	if (!service_done)
		init_services();

	for (cc = 0; service_order[cc] != SERVICE_NONE &&
	     cc <= SERVICE_MAX; cc++) {
		switch (service_order[cc]) {
		case SERVICE_BIND:
			if ((n = res_search((char*) name, C_IN, T_A,
					    buf.buf, sizeof(buf))) < 0) {
#ifdef DEBUG
				if (_res.options & RES_DEBUG)
					printf("res_search failed\n");
#endif
				break;
			}
			hp = getanswer(&buf, n, 0);
			if (h_addr_ptrs[1] && reorder)
				reorder_addrs(hp);
			if (hp) 
				return trim_domains(hp);
			break;
		case SERVICE_HOSTS:
			hp = _gethtbyname(name);
			if (h_addr_ptrs[1] && reorder)
				reorder_addrs(hp);
			if (hp)
				return hp;
			h_errno = HOST_NOT_FOUND;
			break;
#ifdef NIS
		case SERVICE_NIS:
			hp = _getnishost(name, "hosts.byname");
			if (h_addr_ptrs[1] && reorder)
				reorder_addrs(hp);
			if (hp)
				return hp;
			h_errno = HOST_NOT_FOUND;
			break;
#endif /* NIS */
		}
	}
	return ((struct hostent *) NULL);
}
weak_alias (__gethostbyname, gethostbyname)

struct hostent *
__gethostbyaddr (const char *addr, int len, int type)
{
	int n;
	querybuf buf;
	register int cc;
	register struct hostent *hp;
	char qbuf[MAXDNAME];
	extern struct hostent *_gethtbyaddr();
	
	if (type != AF_INET)
		return ((struct hostent *) NULL);
	if (!service_done)
	  init_services();

	cc = 0;
	while (service_order[cc] != SERVICE_NONE) {
	        switch (service_order[cc]) {
		case SERVICE_BIND:
			(void)sprintf(qbuf, "%u.%u.%u.%u.in-addr.arpa",
				      ((unsigned)addr[3] & 0xff),
				      ((unsigned)addr[2] & 0xff),
				      ((unsigned)addr[1] & 0xff),
				      ((unsigned)addr[0] & 0xff));
			n = res_query(qbuf, C_IN, T_PTR, (u_char *)&buf,
				      sizeof(buf));
			if (n < 0) {
#ifdef DEBUG
				if (_res.options & RES_DEBUG)
					printf("res_query failed\n");
#endif
				break;
			}
			hp = getanswer(&buf, n, 1);
			if (hp) {
				if(spoof){
					/* Spoofing check code by
					 * Caspar Dik <casper@fwi.uva.nl> 
					 */
					char nambuf[MAXDNAME+1];
					int ntd, namelen = strlen(hp->h_name);
					char **addrs;
					
					if (namelen >= MAXDNAME)
						return (struct hostent *)NULL;
					(void) strcpy(nambuf,hp->h_name);
					nambuf[namelen] = '.';
					nambuf[namelen+1] = '\0';

					/* 
					 * turn off domain trimming,
					 * call gethostbyname(), then turn	
					 * it back on, if applicable. This
					 * prevents domain trimming from
					 * making the name comparison fail.
					 */
					ntd=numtrimdomains; 
					numtrimdomains=0;
					hp=gethostbyname(nambuf);
					numtrimdomains=ntd;
					nambuf[namelen] = 0;
					/*
					* the name must exist and the name 
					* returned by gethostbyaddr must be 
					* the canonical name and therefore 
					* identical to the name returned by 
					* gethostbyname()
					*/
					if (!hp || strcmp(nambuf, hp->h_name)){
						h_errno = HOST_NOT_FOUND;
						return (struct hostent *)NULL;
					}
					/*
					* now check the addresses
					*/
#if defined(h_addr) || BSD >= 43
					for (addrs = hp->h_addr_list; 
						*addrs; addrs++){
						if (!bcmp(addrs[0], addr, len))
							return trim_domains(hp);
					}
#else
					if (!bcmp(hp->h_addr, addr, len)))
						return trim_domains(hp);
#endif
					/* We've been spoofed */
					h_errno = HOST_NOT_FOUND;
#if 0
					if(spoofalert){
						openlog("resolv", LOG_PID,
						    LOG_AUTH);
						syslog(LOG_NOTICE,
						    "gethostbyaddr: %s != %u.%u.%u.%u, possible spoof attempt",
						    hp->h_name,
						    ((unsigned)addr[0]&0xff),
						    ((unsigned)addr[1]&0xff),
						    ((unsigned)addr[2]&0xff),
						    ((unsigned)addr[3]&0xff));
					} 
#endif
					return (struct hostent *)NULL;
				}
				hp->h_addrtype = type;
				hp->h_length = len;
				h_addr_ptrs[0] = (char *)&host_addr;
				h_addr_ptrs[1] = (char *)0;
				host_addr = *(struct in_addr *)addr;
#if BSD < 43 && !defined(h_addr)	/* new-style hostent structure */
				hp->h_addr = h_addr_ptrs[0];
#endif
				return trim_domains(hp);
			}
			h_errno = HOST_NOT_FOUND;
			break;
		case SERVICE_HOSTS:
			hp = _gethtbyaddr(addr, len, type);
			if (hp) 
				return hp;
			h_errno = HOST_NOT_FOUND;
			break;
#ifdef NIS
		case SERVICE_NIS:
			(void)sprintf(qbuf, "%u.%u.%u.%u",
				      ((unsigned)addr[0] & 0xff),
				      ((unsigned)addr[1] & 0xff),
				      ((unsigned)addr[2] & 0xff),
				      ((unsigned)addr[3] & 0xff));
			hp = _getnishost(qbuf, "hosts.byaddr");
			if (hp)
				return hp;
			h_errno = HOST_NOT_FOUND;
			break;
#endif /* NIS */
		}
		cc++;
	}
	return ((struct hostent *)NULL);
}
weak_alias (__gethostbyaddr, gethostbyaddr)

void
_sethtent (int f)
{
	if (hostf == NULL)
		hostf = fopen(_PATH_HOSTS, "rt" );
	else
		rewind(hostf);
	stayopen |= f;
}

void
_endhtent (void)
{
	if (hostf && !stayopen) {
		(void) fclose(hostf);
		hostf = NULL;
	}
}

struct hostent *
_gethtent (void)
{
	char *p;
	register char *cp, **q;

	if (hostf == NULL && (hostf = fopen(_PATH_HOSTS, "rt" )) == NULL)
		return (NULL);
again:
	if ((p = fgets(hostbuf, BUFSIZ, hostf)) == NULL)
		return (NULL);
	if (*p == '#')
		goto again;
	cp = strpbrk(p, "#\n");
	if (cp == NULL)
		goto again;
	*cp = '\0';
	cp = strpbrk(p, " \t");
	if (cp == NULL)
		goto again;
	*cp++ = '\0';
	/* THIS STUFF IS INTERNET SPECIFIC */
#if BSD >= 43 || defined(h_addr)	/* new-style hostent structure */
	host.h_addr_list = host_addrs;
#endif
	host.h_addr = hostaddr;
	*((u_long *)host.h_addr) = inet_addr(p);
	host.h_length = sizeof (u_long);
	host.h_addrtype = AF_INET;
	while (*cp == ' ' || *cp == '\t')
		cp++;
	host.h_name = cp;
	q = host.h_aliases = host_aliases;
	cp = strpbrk(cp, " \t");
	if (cp != NULL) 
		*cp++ = '\0';
	while (cp && *cp) {
		if (*cp == ' ' || *cp == '\t') {
			cp++;
			continue;
		}
		if (q < &host_aliases[MAXALIASES - 1])
			*q++ = cp;
		cp = strpbrk(cp, " \t");
		if (cp != NULL)
			*cp++ = '\0';
	}
	*q = NULL;
	return (&host);
}

/* if hosts_multiple_addrs set, then gethtbyname behaves as follows:
 *  - for hosts with multiple addresses, return all addresses, such that
 *  the first address is most likely to be one on the same net as the
 *  host we're running on, if one exists. 
 *  - like the dns version of gethostsbyname, the alias field is empty
 *  unless the name being looked up is an alias itself, at which point the
 *  alias field contains that name, and the name field contains the primary
 *  name of the host. Unlike dns, however, this behavior will still take place
 *  even if the alias applies only to one of the interfaces. 
 *  - determining a "local" address to put first is dependant on the netmask 
 *  being such that the least significant network bit is more significant 
 *  than any host bit. Only strange netmasks will violate this. 
 *  - we assume addresses fit into u_longs. That's quite internet specific.
 *  - if the host we're running on is not in the host file, the address 
 *  shuffling will not take place.
 *                     - John DiMarco <jdd@cdf.toronto.edu>
 */ 
struct hostent *
_gethtbyname (char *name)
{
	register struct hostent *p;
	register char **cp;
	char **hap, **lhap, *bp, *lbp;
	int htbuflen, locbuflen;
	int found=0, localfound=0;
	char localname[MAXHOSTNAMELEN];

	static char htbuf[BUFSIZ+1]; /* buffer for host addresses */
	static char locbuf[BUFSIZ+1]; /* buffer for local hosts's addresses */
	static char *ht_addr_ptrs[MAXADDRS+1];
	static char *loc_addr_ptrs[MAXADDRS+1];
	static struct hostent ht;
	static char *aliases[MAXALIASES];
	static char namebuf[MAXHOSTNAMELEN];
	
	hap = ht_addr_ptrs;
	lhap = loc_addr_ptrs;
	*hap = NULL;
	*lhap = NULL;
	bp=htbuf;
	lbp=locbuf;
	htbuflen = sizeof(htbuf);
	locbuflen = sizeof(locbuf);

	aliases[0]=NULL;
	aliases[1]=NULL;
	(void) strcpy(namebuf, name);

	(void)gethostname(localname, sizeof(localname));

	_sethtent(0);
	while ((p = _gethtent())) {
		if (strcasecmp(p->h_name, name) == 0) 
			found++;
		else 
			for (cp = p->h_aliases; *cp != 0; cp++)
				if (strcasecmp(*cp, name) == 0){ 
					found++;
					aliases[0]=name;
					(void) strcpy(namebuf, p->h_name);
				}
		if (strcasecmp(p->h_name, localname) == 0)
			localfound++;
		else
			for (cp=p->h_aliases; *cp != 0; cp++)
				if (strcasecmp(*cp, localname) == 0)
					localfound++;

		if(found){
			int n;

			if(!hosts_multiple_addrs){
				/* original behaviour requested */
				_endhtent();
				return(p);
			}
			n = p->h_length;

			ht.h_addrtype = p->h_addrtype;
			ht.h_length = p->h_length;

			if(n<=htbuflen){
				/* add the found address to the list */
				bcopy(p->h_addr_list[0], bp, n);
				*hap++=bp;
				*hap=NULL;
				bp+=n;
				htbuflen-=n;
			}
			found=0;
		}
		if(localfound){
			int n = p->h_length;
			if(n<=locbuflen){
				/* add the found local address to the list */
				bcopy(p->h_addr_list[0], lbp, n);
				*lhap++=lbp;
				*lhap=NULL;
				lbp+=n;
				locbuflen-=n;
			}
			localfound=0;
		}
	}
	_endhtent();

	if(NULL==ht_addr_ptrs[0]){
		return((struct hostent *)NULL);
	}

	ht.h_aliases = aliases; 
	ht.h_name = namebuf;

	/* shuffle addresses around to ensure one on same net as local host 
	   is first, if exists */
	{
		/* "best" address is assumed to be the one with the greatest
		   number of leftmost bits matching any of the addresses of
		   the local host. This assumes a netmask in which all net
		   bits precede host bits. Usually but not always a fair 
		   assumption. */
 
		/* portability alert: assumption: iaddr fits in u_long.
		   This is really internet specific. */
		int i,j, best=0;
		u_long bestval = (u_long)~0;
		
		for(i=0;loc_addr_ptrs[i];i++){
			for(j=0;ht_addr_ptrs[j];j++){
				/* FIXME: What is h good for?  */
				u_long t, l, h = 0;
				/* assert(sizeof(u_long)>=ht.h_length); */
				bcopy(loc_addr_ptrs[i], (char *)&t,
					ht.h_length);
				l=ntohl(t);
				bcopy(ht_addr_ptrs[j], (char *)&t, 
					ht.h_length);
				t=l^h;

				if(t<bestval){
					best=j;
					bestval=t;
				}
			}
		}
		if(best){
			char *tmp;

			/* swap first and best address */
			tmp=ht_addr_ptrs[0];
			ht_addr_ptrs[0]=ht_addr_ptrs[best];
			ht_addr_ptrs[best]=tmp;
		}
	}
	
	ht.h_addr_list = ht_addr_ptrs;
	return (&ht);
}

struct hostent *
_gethtbyaddr (const char *addr, int len, int type)
{
	register struct hostent *p;

	_sethtent(0);
	while ((p = _gethtent()))
		if (p->h_addrtype == type && !bcmp(p->h_addr, addr, len))
			break;
	_endhtent();
	return (p);
}

#ifdef NIS
static struct hostent *
_getnishost (char *name, char *map)
{
	register char *cp, **q;
	char *result;
	int resultlen;
	static struct hostent h;
	static char *domain = (char *)NULL;

	if (domain == (char *)NULL)
		if (yp_get_default_domain (&domain))
			return ((struct hostent *)NULL);

	if (yp_match(domain, map, name, strlen(name), &result, &resultlen))
		return ((struct hostent *)NULL);

	if ((cp = index(result, '\n')))
		*cp = '\0';

	cp = strpbrk(result, " \t");
	*cp++ = '\0';
#if BSD >= 43 || defined(h_addr)	/* new-style hostent structure */
	h.h_addr_list = host_addrs;
#endif
	h.h_addr = hostaddr;
	*((u_long *)h.h_addr) = inet_addr(result);
	h.h_length = sizeof(u_long);
	h.h_addrtype = AF_INET;
	while (*cp == ' ' || *cp == '\t')
		cp++;
	h.h_name = cp;
	q = h.h_aliases = host_aliases;
	cp = strpbrk(cp, " \t");
	if (cp != NULL)
		*cp++ = '\0';
	while (cp && *cp) {
		if (*cp == ' ' || *cp == '\t') {
			cp++;
			continue;
		}
		if (q < &host_aliases[MAXALIASES - 1])
			*q++ = cp;
		cp = strpbrk(cp, " \t");
		if (cp != NULL)
			*cp++ = '\0';
	}
	*q = NULL;
	return (&h);
}
#endif /* NIS */
