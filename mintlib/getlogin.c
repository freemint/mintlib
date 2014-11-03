/* getlogin: return the user's login name.
 * Written by Eric R. Smith and placed in the public domain.
 */

#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

static char *logname = NULL;

char *
getlogin (void)
{
	char tmplogname[80];
	struct passwd *temp;

	if (logname)
		return logname;

	*tmplogname = '\0';

	/* first try the /etc/passwd file */
	temp = getpwuid (getuid ());

	if (temp) {
		strncpy (tmplogname, temp->pw_name, sizeof (tmplogname) - 1);
		tmplogname[sizeof (tmplogname) - 1] = '\0';
	}

	/* if that didn't work, try the environment */
	if (!*tmplogname && getenv ("USER")) {
		strncpy (tmplogname, getenv ("USER"), sizeof (tmplogname) - 1);
		tmplogname[sizeof (tmplogname) - 1] = '\0';
	}

	/* finally, give up */
	if (!*tmplogname)
		strcpy (tmplogname, "user");

	logname = malloc ((strlen (tmplogname) + 1));
	if (logname)
		strcpy (logname, tmplogname);

	return logname;
}
