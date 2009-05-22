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

#include "generate.h"
#include "traps.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


static void
generate_trap(struct syscall *call, char *buf, int trapnr)
{
	char *s = buf;
	struct arg *l;

	l = call->args;
	while (l)
	{
		if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
		{
			*s++ = 'l';
		}
		else switch (l->type)
		{
			case TYPE_INT:
			case TYPE_CHAR:
			case TYPE_SHORT:
			case TYPE_UNSIGNED:
			case TYPE_UCHAR:
			case TYPE_USHORT:
				*s++ = 'w';
				break;
			case TYPE_LONG:
			case TYPE_ULONG:
				*s++ = 'l';
				break;
			default:
				printf("invalid type specification for %s (%s)\n",
					call->name, l->name);
				exit(1);
		}

		l = l->next;
	}

	*s = '\0';
	add_trap(trapnr, buf);
}

static void
print_casted_args(FILE *out, struct syscall *call)
{
	struct arg *l;

	l = call->args;
	while (l)
	{
		fprintf(out, ", ");

		if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
		{
			fprintf(out, "(long)");
		}
		else switch (l->type)
		{
			case TYPE_INT:
			case TYPE_CHAR:
			case TYPE_SHORT:
			case TYPE_UNSIGNED:
			case TYPE_UCHAR:
			case TYPE_USHORT:
				fprintf(out, "(short)");
				break;
			case TYPE_LONG:
			case TYPE_ULONG:
				fprintf(out, "(long)");
				break;
			default:
				printf("invalid type specification for %s (%s)\n",
					call->name, l->name);
				exit(1);
		}
		fprintf(out, "%s", l->name);

		l = l->next;
	}
}

void
generate_bindings_proto(FILE *out, struct systab *tab, int trapnr)
{
	int i;

	for (i = 0; i < tab->size; i++)
	{
		struct syscall *call = tab->table[i];

		if (call && is_syscall(call))
		{
			fprintf(out, "long __%s", call->name);

			fprintf(out, "(");

			if (call->args)
				generate_args(out, call->args, "", 1, ", ");
			else
				fprintf(out, "void");

			fprintf(out, ");\n");
		}
	}

	fprintf(out, "\n");
}

void
generate_bindings_impl(FILE *out, struct systab *tab, int trapnr)
{
	int i;

	fprintf(out, "/* forward declarations */\n");
	for (i = 0; i < tab->size; i++)
	{
		struct syscall *call = tab->table[i];

		if (call && is_syscall(call))
		{
			struct arg *l;

			l = call->args;
			while (l)
			{
				if (l->flags & FLAG_STRUCT
				    || l->flags & FLAG_UNION)
				{
					fprintf(out, "%s;\n", l->types);
				}

				l = l->next;
			}
		}
	}
	fprintf(out, "\n");

	for (i = 0; i < tab->size; i++)
	{
		struct syscall *call = tab->table[i];

		if (call && is_syscall(call))
		{
			char trap[128];

			fprintf(out, "static inline long __%s", call->name);
			fprintf(out, "(");

			if (call->args)
				generate_args(out, call->args, "", 1, ", ");
			else
				fprintf(out, "void");

			fprintf(out, ")\n");
			fprintf(out, "{ ");

			generate_trap(call, trap, trapnr);

			fprintf(out, "return __trap_%i_w%s", trapnr, trap);
			fprintf(out, "(0x%x", i);

			print_casted_args(out, call);

			fprintf(out, "); }\n\n");
		}
	}
}

void
generate_bindings_old(FILE *out, struct systab *tab, int trapnr)
{
	int i;

	for (i = 0; i < tab->size; i++)
	{
		struct syscall *call = tab->table[i];

		if (call && is_syscall(call))
		{
			char trap[128];
			struct arg *l;
			char arg;

			fprintf(out, "#define %s(", call->name);
			arg = 'a';
			l = call->args;
			while (l)
			{
				int skip = (strcmp(l->name, "DUMMY") == 0);

				if (!skip)
					fprintf(out, "%c", arg);

				++arg;
				l = l->next;

				if (l && !skip) fprintf(out, ",");
			}
			fprintf(out, ") ");

			generate_trap(call, trap, trapnr);

			fprintf(out, "(long)trap_%i_w%s", trapnr, trap);
			fprintf(out, "(0x%x", i);

			arg = 'a';
			l = call->args;
			while (l)
			{
				int skip = (strcmp(l->name, "DUMMY") == 0);

				fprintf(out, ",");

				if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
				{
					fprintf(out, "(long)");
				}
				else switch (l->type)
				{
					case TYPE_INT:
					case TYPE_CHAR:
					case TYPE_SHORT:
					case TYPE_UNSIGNED:
					case TYPE_UCHAR:
					case TYPE_USHORT:
						fprintf(out, "(short)");
						break;
					case TYPE_LONG:
					case TYPE_ULONG:
						fprintf(out, "(long)");
						break;
					default:
						printf("invalid type specification for %s (%s)\n",
							call->name, l->name);
						exit (1);
				}

				if (skip)
					fprintf(out, "0");
				else
					fprintf(out, "%c", arg);

				++arg;
				l = l->next;
			}
			fprintf(out, ")");
			fprintf(out, "\n");
		}
	}

	fprintf(out, "\n");
}
