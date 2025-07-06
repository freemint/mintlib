/* must use MiNTs 32bit time_t type when dumping state */
#define time_tz int
#include "localtime.c"
#include "strftime.c"


int main(int argc, char **argv)
{
	const char *filename;
	struct state *sp;
	int err;
	FILE *out = stdout;
	int i, n;
	struct tm *tm;
	char buf[128];

	if (argc < 2)
		return EXIT_FAILURE;
	filename = argv[1];
	sp = calloc(1, sizeof *sp);
	err = tzload(filename, sp, TZLOAD_TZSTRING);
	if (err != 0)
	{
		fprintf(stderr, "%s: %s\n", filename, strerror(err));
		return EXIT_FAILURE;
	}

	fprintf(out, "static const struct state =\n{\n");
	fprintf(out, "  %d,  /* leapcnt */\n", sp->leapcnt);
	fprintf(out, "  %d,  /* timecnt */\n", sp->timecnt);
	fprintf(out, "  %d,  /* typecnt */\n", sp->typecnt);
	fprintf(out, "  %d,  /* charcnt */\n", sp->charcnt);
	fprintf(out, "  %d,  /* goback */\n", sp->goback);
	fprintf(out, "  %d,  /* goahead */\n", sp->goahead);

	fprintf(out, "  {  /* ats */\n");
	for (i = 0; i < TZ_MAX_TIMES; )
	{
		time_t val;
		
		if ((i % 1) == 0)
			fprintf(out, "    ");
		val = sp->ats[i];
		if (val <= INT32_MIN)
			fprintf(out, "%ldL - 1", (long)INT32_MIN + 1);
		else
			fprintf(out, "%ldL", (long)val);
		tm = gmtime(&val);
		if (tm == NULL)
		{
			strcpy(buf, "gmtime failed");
		} else
		{
			strftime(buf, sizeof(buf), "%a %b %e %H:%M:%S %Z %Y", tm);
		}
		++i;
		if (i == 320) /* minimum TZ_MAX_TIMES */
		{
			fprintf(out, "  /* %s */\n#if TZ_MAX_TIMES > 320\n    ,\n", buf);
		} else
		{
			if (i == TZ_MAX_TIMES)
				fprintf(out, "  /* %s */\n", buf);
			else
				fprintf(out, (i % 1) == 0 ? ", /* %s */\n" : ", /* %s */", buf);
		}
	}
	fprintf(out, "#endif\n  },\n");

	fprintf(out, "  {  /* types */\n");
	for (i = 0; i < TZ_MAX_TIMES; )
	{
		if ((i % 16) == 0)
			fprintf(out, "    ");
		fprintf(out, "%u", sp->types[i]);
		++i;
		if (i == 320) /* minimum TZ_MAX_TIMES */
		{
			fprintf(out, "\n#if TZ_MAX_TIMES > 320\n    ,\n");
		} else
		{
			if (i == TZ_MAX_TIMES)
				fprintf(out, "\n");
			else
				fprintf(out, "%s", (i % 16) == 0 ? ",\n" : ", ");
		}
	}
	fprintf(out, "#endif\n  },\n");
	
	fprintf(out, "  {  /* ttis */\n");
	for (i = 0; i < TZ_MAX_TYPES; )
	{
		if ((i % 2) == 0)
			fprintf(out, "    ");
		fprintf(out, "{ %ld, %u, %u, %u, %u }", (long)sp->ttis[i].tt_utoff, sp->ttis[i].tt_desigidx, sp->ttis[i].tt_isdst, sp->ttis[i].tt_ttisstd, sp->ttis[i].tt_ttisut);
		++i;
		if (i == 20) /* minimum TZ_MAX_TYPES */
		{
			fprintf(out, "\n#if TZ_MAX_TYPES > 20\n    ,\n");
		} else
		{
			if (i == TZ_MAX_TYPES)
				fprintf(out, "\n");
			else
				fprintf(out, "%s", (i % 2) == 0 ? ",\n" : ", ");
		}
	}
	fprintf(out, "#endif\n  },\n");
	
	fprintf(out, "  {  /* chars */\n");
	n = (int)(sizeof(sp->chars) / sizeof(sp->chars[0]));
	for (i = 0; i < n; )
	{
		if (sp->chars[i] == '\0')
			break;
		fprintf(out, "    ");
		while (i < n && sp->chars[i] != '\0')
		{
			fprintf(out, "'%c', ", sp->chars[i]);
			++i;
		}
		fprintf(out, "'\\0'");
		++i;
		if (i >= n)
			fprintf(out, "\n");
		else
			fprintf(out, ",\n");
	}
	while (i < n)
	{
		if ((i % 4) == 0)
			fprintf(out, "    ");
		fprintf(out, "'\\0'");
		++i;
		if (i >= n)
			fprintf(out, "\n");
		else
			fprintf(out, "%s", (i % 4) == 0 ? ",\n" : ", ");
	}
	fprintf(out, "  },\n");
	
	fprintf(out, "  {  /* lsis */\n");
	for (i = 0; i < TZ_MAX_LEAPS; )
	{
		if ((i % 4) == 0)
			fprintf(out, "    ");
		fprintf(out, "{ %ld, %ld }", (long)sp->lsis[i].ls_trans, (long)sp->lsis[i].ls_corr);
		++i;
		if (i == TZ_MAX_LEAPS)
			fprintf(out, "\n");
		else
			fprintf(out, "%s", (i % 4) == 0 ? ",\n" : ", ");
	}
	fprintf(out, "  }\n");
	
	fprintf(out, "};\n");
	
	free(sp);
	
	return EXIT_SUCCESS;
}
