#define time_tz int
#include "localtime.c"


int main(int argc, char **argv)
{
	struct state *sp;
	int i;
	int err;

	sp = calloc(1, sizeof *sp);
	for (i = 1; i < argc; i++)
	{
		const char *filename = argv[i];

		memset(sp, 0, sizeof(*sp));
		err = tzload(filename, sp, TZLOAD_TZSTRING);
		if (err)
		{
			fprintf(stderr, "%s: %s\n", filename, strerror(err));
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
