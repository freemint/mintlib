/* functions for manipulating the environment */
/* written by Eric R. Smith and placed in the public domain */

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "lib.h"


static void
del_env(const char *strng)
{
	char **var;
	char *name;
	size_t len = 0;

	if (!environ) return;

/* find the length of "tag" in "tag=value" */
	for (name = (char *)strng; *name && (*name != '='); name++)
		len++;

/* find the tag in the environment */
	for (var = environ; (name = *var) != NULL; var++) {
		if (!strncmp(name, strng, len) && name[len] == '=')
			break;
	}

/* if it's found, move all the other environment variables down by 1 to
   delete it
 */
	if (name) {
		while (name) {
			name = var[1];
			*var++ = name;
		}
	}
}

int
putenv(const char *strng)
{
	int i = 0;
	char **e;

	del_env(strng);

	if (!environ)
		e = malloc(2*sizeof(char *));
	else {
		while(environ[i]) i++ ;
		e = malloc((i+2)*sizeof(char *));
		if (!e) {
			return -1;
		}
		__bcopy (environ, e, (i+1)*sizeof(char *));
		free(environ);
		environ = e;
	}
	if (!e)
		return -1;

	environ = e;
	environ[i] = (char *)strng;
	environ[i+1] = 0;
	return 0;
}
