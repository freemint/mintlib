#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
main (int argc, char* argv[])
{
	FILE* tmp;
	int i;
	int status = 0;
	
	if (argc != 2) {
		fprintf (stderr, "need exactly one argument\n");
		return 1;
	}
	
	if (access (P_tmpdir, W_OK) != 0) {
		fprintf (stderr, 
		         "Cannot do test due to missing write access to `%s': %s\n",
		         strerror (errno));
		return 1;
	}
	
	for (i = 0; i < 100; i++) {
		tmp = tmpfile ();
		if (tmp == NULL) {
			perror ("tmpfile");
			status = 1;
			continue;
		}
	
		if (fprintf (tmp, "%s", argv[1]) <= 0) {
			perror ("fwrite");
			status = 1;
		}
		
		if (fclose (tmp) != 0) {
			perror ("fclose");
			status = 1;
		}
	}
	
	return status;
}
