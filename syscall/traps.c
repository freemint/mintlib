/*
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
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traps.h"
#include "syscallparser.h"


static struct call *root = NULL;

struct call *add_trap(int nr, const char *call, int noclobber)
{
	struct call *l;

	l = root;
	while (l)
	{
		if (l->nr == nr && l->noclobber == noclobber && strcmp(l->call, call) == 0)
		{
			return l;
		}

		l = l->next;
	}

	l = malloc(sizeof(*l));
	if (!l)
	{
		perror("malloc");
		exit(1);
	}

	l->nr = nr;
	l->noclobber = noclobber;
	strcpy(l->call, call);

	l->next = root;
	root = l;
	return l;
}

static void
generate_trap_impl(FILE *out, const struct call *l, int macro)
{
	const char *macro0 = macro ? " \\" : "";
	int size = 2;
	const char *call = l->call;
	int len = strlen(call), split_flag = 0;
	int i;

	assert(len <= 9);

	if (len > 8)
		split_flag = 1;

	if (macro)
	{
		fprintf(out, "#define trap_%i_w%s%s(n", l->nr, call, l->noclobber ? "_noclobber" : "");
	}
	else
	{
		fprintf(out, "long\n");
		fprintf(out, "__trap_%i_w%s%s(short n", l->nr, call, l->noclobber ? "_noclobber" : "");
	}

	i = 0;
	while (i < len)
	{
		const char *type = NULL;

		if (call[i] == 'w')
			type = "short";
		else if (call[i] == 'l')
			type = "long";

		if (!type)
		{
			printf("wrong syscall argument: %s\n", call);
			exit(1);
		}

		if (macro)
			fprintf(out, ",%c", 'a'+i);
		else
			fprintf(out, ", %s %c", type, 'a'+i);

		++i;
	}

	fprintf(out, ")%s\n", macro0);

	if (macro)
	{
		fprintf(out, "__extension__%s\n", macro0);
		fprintf(out, "({%s\n", macro0);
	}
	else
	{
		fprintf(out, "{\n");
	}

	fprintf(out, "\tregister long __retvalue __asm__(\"d0\");%s\n", macro0);

	if (macro)
	{
		i = 0;
		while (i < len)
		{
			const char *type = NULL;

			fprintf(out, "\t");

			if (call[i] == 'w')
				type = "short";
			else if (call[i] == 'l')
				type = "long";

			assert(type);

			fprintf(out, "%s _%c = (%s)(%c);%s\n", type, 'a'+i, type, 'a'+i, macro0);

			++i;
		}
	}

	fprintf(out, "\t%s\n", macro0);
	fprintf(out, "\t__asm__ volatile%s\n", macro0);
	fprintf(out, "\t(%s\n", macro0);

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

		fprintf(out, "\t%%%i,%%%%sp@-\\n\\t\"%s\n", i + 2 - split_flag, macro0);

		--i;
	}

	fprintf(out, "\t\t\"movw\t%%%i,%%%%sp@-%s\"%s\n", split_flag ? 0 : 1, split_flag ? "" : "\\n\\t", macro0);

	if (!split_flag)
	{
		fprintf(out, "\t\t\"trap\t#%i\\n\\t\"%s\n", l->nr, macro0);
		if (size <= 8)
			fprintf(out, "\t\t\"addql\t#%i,%%%%sp\"%s\n", size, macro0);
		else
			fprintf(out, "\t\t\"lea\t%%%%sp@(%i),%%%%sp\"%s\n", size, macro0);

		fprintf(out, "\t: \"=r\"(__retvalue) /* outputs */%s\n", macro0);
	}
	else
		fprintf(out, "\t: /* outputs */%s\n", macro0);

	fprintf(out, "\t: \"g\"(n)");
	i = 0;
	while (i < len)
	{
		fprintf(out, ", \"r\"(%s%c)", macro ? "_" : "", 'a'+i);
		++i;
	}
	fprintf(out, " /* inputs  */%s\n", macro0);

	if (!split_flag)
	{
		fprintf(out, "\t: __CLOBBER_RETURN(\"d0\")");
		if (!l->noclobber)
			fprintf(out, " \"d1\", \"d2\", \"a0\", \"a1\", \"a2\",");
		fprintf(out, " \"cc\" /* clobbered regs */%s\n", macro0);
		fprintf(out, "\t  AND_MEMORY%s\n", macro0);
	}

	fprintf(out, "\t);%s\n", macro0);

	if (split_flag)
	{
		fprintf(out, "\t%s\n", macro0);
		fprintf(out, "\t__asm__ volatile%s\n", macro0);
		fprintf(out, "\t(%s\n", macro0);
		fprintf(out, "\t\t\"trap\t#%i\\n\\t\"%s\n", l->nr, macro0);
		fprintf(out, "\t\t\"lea\t%%%%sp@(%i),%%%%sp\"%s\n", size, macro0);
		fprintf(out, "\t: \"=r\"(__retvalue) /* outputs */%s\n", macro0);
		fprintf(out, "\t: /* inputs */%s\n", macro0);
		fprintf(out, "\t: __CLOBBER_RETURN(\"d0\")");
		if (!l->noclobber)
			fprintf(out, " \"d1\", \"d2\", \"a0\", \"a1\", \"a2\",");
		fprintf(out, " \"cc\" /* clobbered regs */%s\n", macro0);
		fprintf(out, "\t  AND_MEMORY%s\n", macro0);
		fprintf(out, "\t);%s\n", macro0);
	}

	if (macro)
	{
		fprintf(out, "\t__retvalue;%s\n", macro0);
		fprintf(out, "})\n");
	}
	else
	{
		fprintf(out, "\t\n");
		fprintf(out, "\treturn __retvalue;\n");
		fprintf(out, "}\n");
	}
}

static void
generate_traps_as_macros(FILE *out, int nr)
{
	struct call *l;

	assert(out);

	l = root;
	while (l)
	{
		if (l->nr == nr)
		{
			generate_trap_impl(out, l, 1);
			fprintf(out, "\n");
		}

		l = l->next;
	}
}

static void generate_trap_proto(FILE *out, const struct call *l)
{
	const char *call = l->call;
	int len = strlen(call);
	int i;

	fprintf(out, "long __trap_%i_w%s%s(short", l->nr, call, l->noclobber ? "_noclobber" : "");

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

static void
generate_trap_protos(FILE *out, int nr)
{
	struct call *l;

	l = root;
	while (l)
	{
		if (l->nr == nr)
			generate_trap_proto(out, l);

		l = l->next;
	}
}

static void
generate_trap_h(const char *path, int nr)
{
	char buf[1024];
	FILE *f;

	snprintf(buf, sizeof(buf), "%s/trap%i.h", path, nr);

	f = fopen(buf, "w+");
	if (!f)
	{
		perror("fopen");
		exit(1);
	}

	print_head(f, "gen-syscall");
	fprintf(f, "#ifndef _MINT_TRAP%i_H\n", nr);
	fprintf(f, "#define _MINT_TRAP%i_H\n", nr);
	fprintf(f, "\n");
	fprintf(f, "#ifndef _COMPILER_H\n");
	fprintf(f, "#include <compiler.h>\n");
	fprintf(f, "#endif\n");
	fprintf(f, "\n");
	fprintf(f, "__BEGIN_DECLS\n");
	fprintf(f, "\n");

	if (1)
		generate_traps_as_macros(f, nr);
	else
		generate_trap_protos(f, nr);

	fprintf(f, "__END_DECLS\n");
	fprintf(f, "\n");
	fprintf (f, "#endif /* _MINT_TRAP%i_H */\n", nr);
	fclose(f);
}

void
generate_traps_h(const char *path)
{
	generate_trap_h(path, 1);
	generate_trap_h(path, 13);
	generate_trap_h(path, 14);
}
