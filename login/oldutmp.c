/*
 * BSD style utmp updating routine Version 1.0 (c) S.R.Usher 1991.
 */

/* Now obsolete.  */
#define _OLD_UTMP

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>

link_warning (_write_utmp, 
	      "using `_write_utmp' is obsolete and dangerous")
	    
void _write_utmp(line, name, host, time)
const char *line, *name, *host;
unsigned long time;
{
	register int returned_val;
	int counter;
	struct utmp entry;
	int fd;

	__bzero(&entry, sizeof(struct utmp));

	if ((fd = open(UTMP_FILE, O_RDWR)) == -1)
	{
		perror("_write_utmp");
		return;
	}

	for (counter = 0; ((returned_val = read(fd, &entry, (unsigned) sizeof(struct utmp))) != -1); counter++)
	{
#ifdef DEBUG
		printf("Current line is '%s' (returned_val = %d)\n", entry.ut_line, returned_val);
#endif
		if (returned_val == 0)
			break;
		if (strncmp(line, entry.ut_line, 8) == 0)
			break;
	}

	if (lseek(fd, (long)(counter * sizeof(struct utmp)), 0) == -1)
	{
		perror("_write_utmp: lseek");
		close(fd);
		return;
	}

/*
 * Note, doing this in this order means that it doesn't matter about the Null
 * bytes strncpy adds the the strings if they are greater than 8/16 bytes!
 */
#ifdef DEBUG
	printf("counter = %d\nline = %s\nname = %s\nhost = %s\ntime = %lu\n",
		counter, line, name, host, time);
#endif
	strncpy(entry.ut_line, line, 8);
	strncpy(entry.ut_name, name, 8);
	strncpy(entry.ut_host, host, 16);
	entry.ut_time = time;

	if ((returned_val = write(fd, &entry, (unsigned) sizeof(struct utmp))) == -1)
		perror("_write_utmp: write");
	else
		if (returned_val != sizeof(struct utmp))
			fprintf(stderr, "_write_utmp: write: wrote too few bytes!\n");
#ifdef DEBUG
	printf("_write_utmp: wrote %d bytes\n", returned_val);
#endif
	close(fd);
}
