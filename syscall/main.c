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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "generate.h"
#include "traps.h"

#include "syscallparser.h"

static const char *myname;

#ifdef __MINT__
long _stksize = 64 * 1024;
#endif


static void generate_sysbind_h(const char *path)
{
	char outfilename[1024];
	FILE *outfile;

	snprintf(outfilename, sizeof(outfilename), "%s/sysbind.h", path);

	outfile = fopen(outfilename, "w");
	if (outfile == NULL)
	{
		perror(outfilename);
		exit(1);
	}

	print_head(outfile, myname);
	fprintf(outfile, "#ifndef _MINT_SYSBIND_H\n");
	fprintf(outfile, "#define _MINT_SYSBIND_H\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "#ifndef _FEATURES_H\n");
	fprintf(outfile, "# include <features.h>\n");
	fprintf(outfile, "#endif\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "#ifndef _MINT_OSTRUCT_H\n");
	fprintf(outfile, "# include <mint/ostruct.h>\n");
	fprintf(outfile, "#endif\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "#ifndef _MINT_TRAP1_H\n");
	fprintf(outfile, "# include <mint/trap1.h>\n");
	fprintf(outfile, "#endif\n");
	fprintf(outfile, "#ifndef _MINT_TRAP13_H\n");
	fprintf(outfile, "# include <mint/trap13.h>\n");
	fprintf(outfile, "#endif\n");
	fprintf(outfile, "#ifndef _MINT_TRAP14_H\n");
	fprintf(outfile, "# include <mint/trap14.h>\n");
	fprintf(outfile, "#endif\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "__BEGIN_DECLS\n");
	fprintf(outfile, "\n");

	fprintf(outfile, "/* GEMDOS */\n");
	fprintf(outfile, "\n");
	generate_bindings_old(outfile, gemdos_table(), 1);
	fprintf(outfile, "/* BIOS */\n");
	fprintf(outfile, "\n");
	generate_bindings_old(outfile, bios_table(), 13);
	fprintf(outfile, "/* XBIOS */\n");
	fprintf(outfile, "\n");
	generate_bindings_old(outfile, xbios_table(), 14);

	fprintf(outfile, "__END_DECLS\n");
	fprintf(outfile, "\n");
	fprintf(outfile, "#endif /* _MINT_SYSBIND_H */\n");

	fclose(outfile);
}


int
main(int argc, char **argv)
{
	int error;
	const char *infilename;
	const char *path;

	myname = *argv++;
	if (argc > 1)
	{
		FILE *f;

		infilename = *argv++;
		f = fopen(infilename, "r");
		if (f)
		{
			error = parse_syscall_description(f);
			fclose(f);
		} else
		{
			perror(infilename);
			exit(1);
		}
	} else
	{
#ifdef YYDEBUG
		yydebug = 1;
#endif
		error = parse_syscall_description(stdin);
	}
	if (argc > 2)
	{
		path = *argv++;
	} else
	{
		path = "../include/mint";
	}

	if (!error)
	{
		/* check_tab(); */

		generate_sysbind_h(path);
		generate_traps_h(path);
	}

	return error;
}
