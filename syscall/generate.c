/*
 * This file belongs to FreeMiNT. It's not in the original MiNT 1.12
 * distribution. See the file CHANGES for a detailed log of changes.
 * 
 * 
 * Copyright 2000, 2001, 2002 Frank Naumann <fnaumann@freemint.de>
 * All rights reserved.
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
 * 
 * begin:	2000-01-01
 * last change:	2000-03-07
 * 
 * Author:	Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * changes since last version:
 * 
 * known bugs:
 * 
 * todo:
 * 
 * optimizations:
 * 
 */

#include "generate.h"
#include "traps.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>


static int
list_length(LIST *l)
{
	int length = 0;
	
	while (l)
	{
		length++;
		l = l->next;
	}
	
	return length;
}

static void
generate_args(FILE *out, LIST *l, const char *pre, const char *post, int flags)
{
	while (l)
	{
		fprintf(out, "%s%s", pre, l->types);
		
		if (l->flags & FLAG_POINTER)
			fprintf(out, " *");
		else if (!(flags & 0x2))
			fprintf(out, " ");
		
		if (!(flags & 0x2))
			fprintf(out, "%s", l->name);
		
		if (l->flags & FLAG_ARRAY)
			fprintf(out, "[%i]", l->ar_size);
			
		if (l->next || (flags & 0x1))
			fprintf(out, "%s", post);
		
		l = l->next;
	}
}

void
generate_bindings_proto(FILE *out, SYSTAB *tab)
{
	int i;
	
	for (i = 0; i < tab->size; i++)
	{
		SYSCALL *call = tab->table[i];
		
		if (call && strcmp(call->name, "RESERVED"))
		{
			fprintf(out, "long __%c%s", toupper (call->class), call->name);
			
			fprintf(out, "(");
			
			if (call->args)
				generate_args (out, call->args, "", ", ", 0x2);
			else
				fprintf(out, "void");
			
			fprintf(out, ");\n");
		}
	}
	
	fprintf(out, "\n");
}

void
generate_bindings_impl(FILE *out, SYSTAB *tab)
{
	int i;
	
	for (i = 0; i < tab->size; i++)
	{
		SYSCALL *call = tab->table[i];
		
		if (call && strcmp(call->name, "RESERVED"))
		{
			char trap[128]; char *s = trap;
			LIST *l;
			
			fprintf(out, "static long __%c%s", toupper (call->class), call->name);
			
			fprintf(out, "(");
			
			if (call->args)
				generate_args (out, call->args, "", ", ", 0x0);
			else
				fprintf(out, "void");
			
			fprintf(out, ")\n");
			fprintf(out, "{ ");
			
			fprintf(out, "return __trap_1_w");
			
			l = call->args;
			while (l)
			{
				if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
				{
					fprintf(out, "l");
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
						fprintf(out, "w");
						*s++ = 'w';
						break;
					case TYPE_LONG:
					case TYPE_ULONG:
						fprintf(out, "l");
						*s++ = 'l';
						break;
					default:
						printf("invalid type specification for %c%s (%s)\n",
							call->class, call->name, l->name);
						exit (1);
				}
				
				l = l->next;
			}
			
			*s = '\0';
			add_trap(1, trap);
			
			fprintf(out, "(0x%x", i);
			
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
						printf("invalid type specification for %c%s (%s)\n",
							call->class, call->name, l->name);
						exit (1);
				}
				fprintf(out, "%s", l->name);
				
				l = l->next;
			}
			
			fprintf(out, "); }\n\n");
		}
	}
}
	
void
generate_bindings_old(FILE *out, SYSTAB *tab)
{
	int i;
	
	for (i = 0; i < tab->size; i++)
	{
		SYSCALL *call = tab->table[i];
		
		if (call && strcmp(call->name, "RESERVED"))
		{
			LIST *l;
			char arg;
			
			fprintf(out, "#define %c%s(", toupper (call->class), call->name);
			arg = 'a';
			l = call->args;
			while (l)
			{
				fprintf(out, "%c", arg);
				
				arg++;
				l = l->next;
				
				if (l) fprintf(out, ",");
			}
			fprintf(out, ") ");
			
			fprintf(out, "__trap_1_w");
			l = call->args;
			while (l)
			{
				if ((l->flags & FLAG_POINTER) || (l->flags & FLAG_ARRAY))
				{
					fprintf(out, "l");
				}
				else switch (l->type)
				{
					case TYPE_INT:
					case TYPE_CHAR:
					case TYPE_SHORT:
					case TYPE_UNSIGNED:
					case TYPE_UCHAR:
					case TYPE_USHORT:
						fprintf(out, "w");
						break;
					case TYPE_LONG:
					case TYPE_ULONG:
						fprintf(out, "l");
						break;
					default:
						printf("invalid type specification for %c%s (%s)\n",
							call->class, call->name, l->name);
						exit (1);
				}
				
				l = l->next;
			}
			
			fprintf(out, "(0x%x", i);
			arg = 'a';
			l = call->args;
			while (l)
			{
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
						printf("invalid type specification for %c%s (%s)\n",
							call->class, call->name, l->name);
						exit (1);
				}
				
				fprintf(out, "%c", arg);
				
				arg++;
				l = l->next;
			}
			fprintf(out, ")");
			
			
			fprintf(out, "\n");
		}
	}
	
	fprintf(out, "\n");
}
