/* @(#)getrpcent.c	2.2 88/07/29 4.0 RPCSRC */
#if !defined(lint) && defined(SCCSIDS)
static  char sccsid[] = "@(#)getrpcent.c 1.9 87/08/11  Copyr 1984 Sun Micro";
#endif

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
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#include <stdio.h>
#include <sys/types.h>
#include <rpc/rpc.h>
#include <netdb.h>
#include <sys/socket.h>

extern void __setrpcent (int __stayopen) __THROW;
extern void __endrpcent (void) __THROW;
extern struct rpcent *__getrpcbyname (__const char *__name) __THROW;
extern struct rpcent *__getrpcbynumber (int __number) __THROW;
extern struct rpcent *__getrpcent (void) __THROW;

/*
 * Internet version.
 */
struct rpcdata {
	FILE	*rpcf;
	char	*current;
	int	currentlen;
	int	stayopen;
#define	MAXALIASES	35
	char	*rpc_aliases[MAXALIASES];
	struct	rpcent rpc;
	char	line[BUFSIZ+1];
	char	*domain;
} *rpcdata;

static char RPCDB[] = "/etc/rpc";

static struct rpcdata *
_rpcdata(void)
{
	register struct rpcdata *d = rpcdata;

	if (d == 0) {
		d = (struct rpcdata *)calloc(1, sizeof (struct rpcdata));
		rpcdata = d;
	}
	return (d);
}

struct rpcent *
__getrpcbynumber (int number)
{
	register struct rpcdata *d = _rpcdata();
	register struct rpcent *p;
//	int reason;
//	char adrstr[16], *val = NULL;
//	int vallen;

	if (d == 0)
		return (0);
	__setrpcent(0);
	while ((p = __getrpcent())) {
		if (p->r_number == number)
			break;
	}
	__endrpcent();
	return (p);
}
weak_alias (__getrpcbynumber, getrpcbynumber)

struct rpcent *
__getrpcbyname (const char *name)
{
	struct rpcent *rpc;
	char **rp;

	__setrpcent(0);
	while((rpc = __getrpcent())) {
		if (strcmp(rpc->r_name, name) == 0)
			return (rpc);
		for (rp = rpc->r_aliases; *rp != NULL; rp++) {
			if (strcmp(*rp, name) == 0)
				return (rpc);
		}
	}
	__endrpcent();
	return (NULL);
}
weak_alias (__getrpcbyname, getrpcbyname)

void
__setrpcent (int f)
{
	register struct rpcdata *d = _rpcdata();

	if (d == 0)
		return;
	if (d->rpcf == NULL)
		d->rpcf = fopen(RPCDB, "r");
	else
		rewind(d->rpcf);
	if (d->current)
		free(d->current);
	d->current = NULL;
	d->stayopen |= f;
}
weak_alias (__setrpcent, setrpcent)

void
__endrpcent (void)
{
	register struct rpcdata *d = _rpcdata();

	if (d == 0)
		return;
	if (d->current && !d->stayopen) {
		free(d->current);
		d->current = NULL;
	}
	if (d->rpcf && !d->stayopen) {
		fclose(d->rpcf);
		d->rpcf = NULL;
	}
}
weak_alias (__endrpcent, endrpcent)

static struct rpcent *interpret (char *val, int len);

struct rpcent *
__getrpcent (void)
{
//	struct rpcent *hp;
//	int reason;
//	char *key = NULL, *val = NULL;
//	int keylen, vallen;
	register struct rpcdata *d = _rpcdata();

	if (d == 0)
		return(NULL);
	if (d->rpcf == NULL && (d->rpcf = fopen(RPCDB, "r")) == NULL)
		return (NULL);
	if (fgets(d->line, BUFSIZ, d->rpcf) == NULL)
		return (NULL);
	return interpret(d->line, strlen(d->line));
}
weak_alias (__getrpcent, getrpcent)

static struct rpcent *
interpret (char *val, int len)
{
	register struct rpcdata *d = _rpcdata();
	char *p;
	register char *cp, **q;

	if (d == 0)
		return NULL;
	strncpy(d->line, val, len);
	p = d->line;
	d->line[len] = '\n';
	if (*p == '#')
		return (__getrpcent());
	cp = index(p, '#');
	if (cp == NULL)
	{
		cp = index(p, '\n');
		if (cp == NULL)
			return (__getrpcent());
	}
	*cp = '\0';
	cp = index(p, ' ');
	if (cp == NULL)
	{
		cp = index(p, '\t');
		if (cp == NULL)
			return (__getrpcent());
	}
	*cp++ = '\0';
	/* THIS STUFF IS INTERNET SPECIFIC */
	d->rpc.r_name = d->line;
	while (*cp == ' ' || *cp == '\t')
		cp++;
	d->rpc.r_number = atoi(cp);
	q = d->rpc.r_aliases = d->rpc_aliases;
	cp = index(p, ' ');
	if (cp != NULL)
		*cp++ = '\0';
	else
	{
		cp = index(p, '\t');
		if (cp != NULL)
			*cp++ = '\0';
	}
	while (cp && *cp) {
		if (*cp == ' ' || *cp == '\t') {
			cp++;
			continue;
		}
		if (q < &(d->rpc_aliases[MAXALIASES - 1]))
			*q++ = cp;
		cp = index(p, ' ');
		if (cp != NULL)
			*cp++ = '\0';
		else
	    {
			cp = index(p, '\t');
			if (cp != NULL)
				*cp++ = '\0';
		}
	}
	*q = NULL;
	return (&d->rpc);
}
