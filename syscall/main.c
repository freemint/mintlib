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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "generate.h"
#include "traps.h"

#include "syscallparser.h"


#ifdef __MINT__
long _stksize = 64 * 1024;
#endif


int
main(int argc, char **argv)
{
	const char *myname = *argv++;
	int error;
	
	if (*argv == NULL)
	{
#if YYDEBUG != 0
		yydebug = 1;
#endif
		error = parse_syscall_description(NULL);
	}
	else
	{
		FILE *f;
		
		f = fopen(*argv, "rt");
		if (f)
		{
			error = parse_syscall_description(f);
			fclose(f);
		}
		else
		{
			perror(*argv);
			exit(1);
		}
	}
	
	if (!error)
	{
		FILE *f;
		
		/* check_tab(); */
		
		f = fopen("../include/mint/sysbind.h", "w");
		if (!f)
		{
			perror("sysbind.h");
			exit(1);
		}
		
		print_head(f, myname);
		fprintf(f, "#ifndef _sysbind_h\n");
		fprintf(f, "#define _sysbind_h\n\n");
		fprintf(f, "#include <sys/types.h>\n");
		fprintf(f, "#include <mint/trap.h>\n");
		fprintf(f, "\n");
		fprintf(f, "\n");
		
		generate_bindings_old(f, gemdos_table(), 1);
		generate_bindings_old(f, bios_table(), 13);
		generate_bindings_old(f, xbios_table(), 14);
		
		fprintf(f, "\n#endif /* _sysbind_h */\n");
		fclose(f);
		
		generate_trap_h("../include/mint");
		generate_traps(".");
	}
	
	return error;
}
