/* tmpfile.c: create a temporary file that will be deleted when exit()
   is called.
   Written by Eric R. Smith and placed in the public domain.
*/

/* Made reentrant by Guido Flohr <guido@freemint.de>.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

static void delete_tmpfiles (void);

typedef struct {
	char	*name;
	FILE	*fp;
} FILE_RECORD;

static FILE_RECORD	*file_to_delete;
static int		numtmps = -1;

static void
delete_tmpfiles()
{
	int i;

	for (i = 0; i <= numtmps; i++)
	{
		fclose(file_to_delete[i].fp);
		remove(file_to_delete[i].name);
	}
}

FILE *tmpfile()
{
	char *junknam = malloc (L_tmpnam);
	FILE *junkfil;

	/* Don't call tmpnam because that is not reentrant.  */
	if ( ((junknam = tmpnam_r(junknam)) == NULL) || 
		((junkfil = fopen(junknam, "w+b")) == NULL ))
	{
		free(junknam);
		return NULL;
	}

	junknam = realloc (junknam, strlen (junknam) + 1);
	
/* in MiNT 0.9 and above, we can often unlink a file and continue to use
 * it; some file systems may return EACCDN for unlinking an open file,
 * in which case we use the old method of unlinking the file at exit
 */
	if (__mint >= 9) {
		if (remove(junknam) == 0)
			return junkfil;
	}

	if((++numtmps) == 0)
		file_to_delete = (FILE_RECORD *)malloc((size_t)sizeof(FILE_RECORD));
	else
		file_to_delete = (FILE_RECORD *)realloc(file_to_delete,
					(size_t)((numtmps+1) * sizeof(FILE_RECORD)));
	if(file_to_delete == (FILE_RECORD *)NULL)
	{
		fclose(junkfil);
		remove(junknam);
		free(junknam);
		numtmps -= 1;
		return NULL;	/* outa mem */
	}
/* install this in the list of temporary files to be deleted at exit */
	file_to_delete[numtmps].name = junknam;
	file_to_delete[numtmps].fp   = junkfil;

/* if this is the first, install the delete routine */
	if (numtmps == 0)
		if(atexit(delete_tmpfiles) != 0)
		{	/* atexit failed -- cleanup */
			delete_tmpfiles();
			numtmps = -1;
			free(file_to_delete[0].name);
			free(file_to_delete);
			return NULL;
		}
	return junkfil;
}
