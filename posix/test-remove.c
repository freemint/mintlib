#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int
main (int argc, char* argv[])
{
	char* tmp;
	FILE* file;
	struct stat sb;
	int failed = 0;
	
	/* First test if remove removes an ordinary file.  */
	tmp = tmpnam (NULL);
	
	if (tmp == NULL) {
		perror ("tmpnam");
		return 1;
	}
	
	if ((file = fopen (tmp, "wx")) == NULL) {
		perror ("fopen");
		return 1;
	}
	if (fclose (file) != 0) {
		perror ("fclose");
		return 1;
	}

	if (remove (tmp) != 0) {
		perror ("remove");
		return 1;
	}
	
	if (stat (tmp, &sb) == 0) {
		fprintf (stderr, "*** failed to remove file `%s'", tmp);
		failed++;
	} else
		printf ("test 1 passed\n");
		
	/* Test 2, remove a directory.  */
	tmp = tmpnam (NULL);
	
	if (tmp == NULL) {
		perror ("tmpnam");
		return 1;
	}
	
	if (mkdir (tmp, 0644) != 0) {
		perror ("mkdir");
		return 1;
	}
	
	if (remove (tmp) != 0) {
		perror ("remove");
		return 1;
	}
	
	if (stat (tmp, &sb) == 0) {
		fprintf (stderr, "*** failed to remove directory `%s'", tmp);
		failed++;
	}
	else
		printf ("test 2 passed\n");

	return failed ? 1 : 0;
}
