/* getlogin: return the user's login name.
 * Written by Eric R. Smith and placed in the public domain.
 */

#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

static char *logname = NULL;

char *getlogin()
{
        struct passwd *temp;
	char tmplogname[80];

	if(logname != NULL)
		return logname;

	*tmplogname = '\0';

/* first try the /etc/passwd file */
        temp = getpwuid(getuid());

        if (temp) {
          strncpy(tmplogname, temp->pw_name, (size_t)79);
	  tmplogname[79] = '\0';
	}

/* if that didn't work, try the environment */
        if (!*tmplogname && getenv("USER")) {
                strncpy(tmplogname, getenv("USER"), (size_t)79);
		tmplogname[79] = '\0';
        }

/* finally, give up */
        if (!*tmplogname)
                strcpy(tmplogname, "user");
	if((logname = (char *)malloc((size_t)(strlen(tmplogname)+1))) == NULL)
		return (char *)NULL;
        return strcpy(logname, tmplogname);
}
