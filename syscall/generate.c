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

#include "generate.h"
#include "traps.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


static struct call *generate_trap(struct syscall *call, int trapnr)
{
	char buf[20];
	char *s = buf;
	struct arg *l;

	l = call->args;
	while (l)
	{
		if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
		{
			*s++ = 'l';
		} else
		{
			switch (l->type)
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
			case TYPE_OFF_T:
				*s++ = 'l';
				break;
			case TYPE_IDENT: /* pass by value not supported */
			default:
				printf("invalid type specification for %s (%s)\n",
					call->name, l->name);
				exit(1);
			}
		}

		l = l->next;
	}

	*s = '\0';
	strcpy(call->callname, buf);
	return add_trap(trapnr, buf, call->status == SYSCALL_NOCLOBBER);
}


static void print_casted_args(FILE *out, struct syscall *call)
{
	struct arg *l;

	l = call->args;
	while (l)
	{
		int skip = strcmp(l->name, "DUMMY") == 0;
		
		fprintf(out, ", ");

#if 0
		if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
		{
			fprintf(out, "(long)");
		} else
		{
			switch (l->type)
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
			case TYPE_OFF_T:
				fprintf(out, "(long)");
				break;
			default:
				printf("invalid type specification for %s (%s)\n",
					call->name, l->name);
				exit(1);
			}
		}
		fprintf(out, "(%s)", l->name);
		if (skip)
			fprintf(out, "(0)");
		else
			fprintf(out, "(%s)", l->name);
#else
		/* no need to cast here; that is already done in the trap_xxx macros */
		if (skip)
			fprintf(out, "0");
		else
			fprintf(out, "%s", l->name);
#endif

		l = l->next;
	}
}


static void generate_ret_type(FILE *out, struct syscall *call)
{
	if (call->ret && (call->ret->type != TYPE_VOID || (call->ret->flags & (FLAG_POINTER | FLAG_ARRAY))))
	{
		switch (call->ret->type)
		{
		case TYPE_VOID:
			fprintf(out, "void");
			break;
		case TYPE_INT:
		case TYPE_CHAR:
		case TYPE_SHORT:
			fprintf(out, "short");
			break;
		case TYPE_UNSIGNED:
		case TYPE_UCHAR:
		case TYPE_USHORT:
			fprintf(out, "unsigned short");
			break;
		case TYPE_LONG:
		case TYPE_OFF_T:
			fprintf(out, "long");
			break;
		case TYPE_ULONG:
			fprintf(out, "unsigned long");
			break;
		case TYPE_IDENT:
			fprintf(out, "%s", call->ret->types);
			break;
		}
		if (call->ret->flags & FLAG_POINTER)
			fprintf(out, " *");
	} else
	{
		fprintf(out, "void");
	}
}

static void generate_args(FILE *out, struct syscall *call)
{
	struct arg *l;
	
	l = call->args;
	while (l)
	{
		int skip = strcmp(l->name, "DUMMY") == 0;
		
		if (!skip)
		{
			if (l->flags & FLAG_CONST)
				fprintf(out, "const %s ", l->types);
			else
				fprintf(out, "%s ", l->types);
			
			if (l->flags & FLAG_POINTER)
				fprintf(out, "*");
			
			if (l->flags & FLAG_POINTER2)
				fprintf(out, "*");
			
			fprintf(out, "%s", l->name);
			
			if (l->flags & FLAG_ARRAY)
				fprintf(out, " [%i]", l->ar_size);
		}
					
		l = l->next;
			
		if (l && !skip)
			fprintf(out, ", ");
	}
}


void generate_bindings_proto(FILE *out, struct systab *tab, int trapnr)
{
	int i;

	(void) trapnr;
	for (i = 0; i < tab->size; i++)
	{
		struct syscall *call = tab->table[i];

		if (call && is_syscall(call))
		{
			generate_ret_type(out, call);
			fprintf(out, " %s(", call->name);

			if (call->args)
				generate_args(out, call);
			else
				fprintf(out, "void");

			fprintf(out, ");\n");
		}
	}

	fprintf(out, "\n");
}


void generate_bindings_impl(FILE *out, struct systab *tab, int trapnr)
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
				/* FIXME: filter out duplicates already used in previous calls */
				if ((l->flags & FLAG_STRUCT) || (l->flags & FLAG_UNION))
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
			struct call *trap;

			fprintf(out, "static inline ");
			generate_ret_type(out, call);
			fprintf(out, " %s(", call->name);

			if (call->args)
				generate_args(out, call);
			else
				fprintf(out, "void");

			fprintf(out, ")\n");
			fprintf(out, "{\n");

			trap = generate_trap(call, trapnr);

			fprintf(out, "\t");
			if (call->ret && (call->ret->type != TYPE_VOID || (call->ret->flags & (FLAG_POINTER | FLAG_ARRAY))))
				fprintf(out, "return ");
			fprintf(out, "__trap_%i_w%s%s(0x%x", trapnr, trap->call, trap->noclobber ? "_noclobber" : "", i);

			print_casted_args(out, call);

			fprintf(out, ");\n}\n\n");
		}
	}
}


void generate_bindings_old(FILE *out, struct systab *tab, int trapnr)
{
	int i;

	for (i = 0; i < tab->size; i++)
	{
		struct syscall *call = tab->table[i];

		if (call && is_syscall(call))
		{
			struct call *trap;
			struct arg *l;
			char arg;

			fprintf(out, "#define %s(", call->name);
			arg = 'a';
			l = call->args;
			while (l)
			{
				int skip = strcmp(l->name, "DUMMY") == 0;

				if (!skip)
					fprintf(out, "%c", arg);

				++arg;
				l = l->next;

				if (l && !skip) fprintf(out, ",");
			}
			fprintf(out, ") ");

			trap = generate_trap(call, trapnr);

			if (call->ret)
			{
				fprintf(out, "(");
				switch (call->ret->type)
				{
				case TYPE_VOID:
					fprintf(out, "void");
					break;
				case TYPE_INT:
				case TYPE_CHAR:
				case TYPE_SHORT:
					fprintf(out, "short");
					break;
				case TYPE_UNSIGNED:
				case TYPE_UCHAR:
				case TYPE_USHORT:
					fprintf(out, "unsigned short");
					break;
				case TYPE_LONG:
					fprintf(out, "long");
					break;
				case TYPE_ULONG:
					fprintf(out, "unsigned long");
					break;
				case TYPE_OFF_T:
					fprintf(out, "off_t");
					break;
				case TYPE_IDENT:
					fprintf(out, "%s", call->ret->types);
					break;
				default:
					printf("invalid type specification for %s (%s)\n",
						call->name, call->ret->name);
					exit (1);
				}
				if (call->ret->flags & FLAG_POINTER)
					fprintf(out, " *");
				fprintf(out, ")");
			}

			fprintf(out, "trap_%i_w%s%s(0x%x", trapnr, trap->call, trap->noclobber ? "_noclobber" : "", i);

			arg = 'a';
			l = call->args;
			while (l)
			{
				int skip = (strcmp(l->name, "DUMMY") == 0);

				fprintf(out, ",");

				if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
				{
					fprintf(out, "(long)");
				} else
				{
					switch (l->type)
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
					case TYPE_OFF_T:
						fprintf(out, "(long)");
						break;
					default:
						printf("invalid type specification for %s (%s)\n",
							call->name, l->name);
						exit (1);
					}
				}

				if (skip)
					fprintf(out, "0");
				else
					fprintf(out, "(%c)", arg);

				++arg;
				l = l->next;
			}
			fprintf(out, ")");
			fprintf(out, "\n");
		}
	}

	fprintf(out, "\n");
}
