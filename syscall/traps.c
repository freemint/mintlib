/*
 * $Id$
 * 
 * This file belongs to FreeMiNT. It's not in the original MiNT 1.12
 * distribution. See the file CHANGES for a detailed log of changes.
 * 
 * 
 * Copyright 2000-2005 Frank Naumann <fnaumann@freemint.de>
 * All rights reserved.
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traps.h"
#include "syscallparser.h"


struct call
{
	struct call *next;
	int nr;
	char *call;
};

static struct call *root = NULL;

void
add_trap(int nr, const char *call)
{
	struct call *l;
	
	l = root;
	while (l)
	{
		if ((l->nr == nr) && !strcmp(l->call, call))
			return;
		
		l = l->next;
	}
	
	l = malloc(sizeof(*l));
	if (!l)
	{
		perror("malloc");
		exit(1);
	}
	
	l->nr = nr;
	l->call = strdup(call);
	
	if (!l->call)
	{
		perror("malloc");
		exit(1);
	}
	
	l->next = root;
	root = l;
}

static void
generate_trap_impl(FILE *out, int nr, const char *call)
{
	int size = 2;
	int len = strlen(call);
	int i;
	
	fprintf(out, "long\n");
	fprintf(out, "__trap_%i_w%s(short n", nr, call);
	
	i = 0;
	while (i < len)
	{
		if (call[i] == 'w')
			fprintf(out, ", short a%i", i);
		else if (call[i] == 'l')
			fprintf(out, ", long a%i", i);
		else
		{
			printf("wrong syscall argument: %s\n", call);
			exit(1);
		}
		
		i++;
	}
	
	fprintf(out, ")\n");
	fprintf(out, "{\n");
	
	fprintf(out, "\tregister long ret __asm__(\"d0\");\n");
	fprintf(out, "\t\n");
	fprintf(out, "\t__asm__ volatile\n");
	fprintf(out, "\t(\n");
	
	i = len - 1;
	while (i >= 0)
	{
		fprintf(out, "\t\t\"");
		
		if (call[i] == 'w')
		{
			fprintf(out, "movw");
			size += 2;
		}
		else if (call[i] == 'l')
		{
			fprintf(out, "movl");
			size += 4;
		}
		
		fprintf(out, "\t%%%i,sp@-\\n\\t\"\n", i+2);
		
		i--;
	}
	
	fprintf(out, "\t\t\"movw\t%%1,sp@-\\n\\t\"\n");
	fprintf(out, "\t\t\"trap\t#%i\\n\\t\"\n", nr);
	if (size <= 8)
		fprintf(out, "\t\t\"addql\t#%i,sp\"\n", size);
	else
		fprintf(out, "\t\t\"lea\tsp@(%i),sp\"\n", size);
	
	fprintf(out, "\t: \"=r\"(ret)                          /* outputs */\n");
	fprintf(out, "\t: \"g\"(n)");
	i = 0;
	while (i < len)
	{
		fprintf(out, ", \"r\"(a%i)", i);
		i++;
	}
	fprintf(out, "\n");
	fprintf(out, "\t: __CLOBBER_RETURN(\"d0\") \"d1\", \"d2\", \"a0\", \"a1\", \"a2\" /* clobbered regs */\n");
	fprintf(out, "\t  AND_MEMORY\n");
	fprintf(out, "\t);\n");
	fprintf(out, "\t\n");
	fprintf(out, "\treturn ret;\n");	
	
	fprintf(out, "}\n");
}

void
generate_traps(const char *path)
{
	char srcbuf[1024];
	FILE *src;
	struct call *l;
	
	snprintf(srcbuf, sizeof(srcbuf), "%s/SRCFILES.traps", path);
	
	src = fopen(srcbuf, "w+");
	if (!src)
	{
		perror("fopen");
		exit(1);
	}
	
	fprintf(src, "TRAPS = \\\n");
	
	l = root;
	while (l)
	{
		char buf[1024];
		FILE *f;
		
		fprintf(src, "\ttrap_%i_w%s.c", l->nr, l->call);
		snprintf(buf, sizeof(buf), "%s/trap_%i_w%s.c", path, l->nr, l->call);
		
		f = fopen(buf, "w+");
		if (!f)
		{
			perror("fopen");
			exit(1);
		}
		
		print_head(f, "gen-syscall");
		fprintf(f, "#include <mint/trap.h>\n");
		fprintf(f, "#include <compiler.h>\n");
		fprintf(f, "\n");
		
		generate_trap_impl(f, l->nr, l->call);
		
		fclose(f);
		l = l->next;
		
		if (l) fprintf(src, " \\\n");
	}
	
	fprintf(src, "\n");
	fclose(src);
}

static void
generate_trap_proto(FILE *out, int nr, const char *call)
{
	int len = strlen(call);
	int i;
	
	fprintf(out, "long __trap_%i_w%s(short", nr, call);
	
	i = 0;
	while (i < len)
	{
		if (call[i] == 'w')
			fprintf(out, ", short");
		else if (call[i] == 'l')
			fprintf(out, ", long");
		else
		{
			printf("wrong syscall argument: %s\n", call);
			exit(1);
		}
		
		i++;
	}
	
	fprintf(out, ");\n");
}

void
generate_trap_h(const char *path)
{
	char buf[1024];
	FILE *f;
	struct call *l;
	
	snprintf(buf, sizeof(buf), "%s/trap.h", path);
	
	f = fopen(buf, "w+");
	if (!f)
	{
		perror("fopen");
		exit(1);
	}
	
	print_head(f, "gen-syscall");
	fprintf (f, "#ifndef _trap_h\n");
	fprintf (f, "#define _trap_h\n\n");
	fprintf (f, "\n");
	
	l = root;
	while (l)
	{
		generate_trap_proto(f, l->nr, l->call);
		
		l = l->next;
	}
	
	fprintf (f, "\n");
	fprintf (f, "\n#endif /* _trap_h */\n");
	fclose(f);
}
