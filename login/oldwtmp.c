/*
 * BSD style wtmp updating routine Version 1.0 (c) S.R.Usher 1991.
 * Modified 910126 dpg: uses non-buffered file ops, like utmp.c
 */

/* Now obsolete.  */
#define _OLD_UTMP

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <utmp.h>

link_warning (_write_wtmp,
	      "using `_write_wtmp' is obsolete and dangerous")

void _write_wtmp(line, name, host, time)
const char *line, *name, *host;
unsigned long time;
{
	int fd;
	struct utmp entry;

	if ((fd = open(WTMP_FILE, O_WRONLY | O_APPEND)) < 0)
	{
#ifdef DEBUG
		perror("_write_wtmp");
#endif
		return;
	}

/*
 * Note, doing this in this order means that it doesn't matter about the Null
 * bytes strncpy adds the the strings if they are greater than 8/16 bytes!
 */

	strncpy(entry.ut_line, line, 8);
	strncpy(entry.ut_name, name, 8);
	strncpy(entry.ut_host, host, 16);
	entry.ut_time = time;

	write(fd, &entry, (unsigned) sizeof(struct utmp));

	close(fd);
}

