#include "localtime.c"


int main(int argc, char **argv)
{
	struct state *sp;
	int i, max;
	int per_line;
	FILE *out = stdout;
	
	if (argc != 2)
		return EXIT_FAILURE;
	setenv("TZ", argv[1], 1);
	tzset();
	
	sp = lclptr;
	fprintf(out, "{\n");
	fprintf(out, "  %d,  /* leapcnt */\n", sp->leapcnt);
	fprintf(out, "  %d,  /* timecnt */\n", sp->timecnt);
	fprintf(out, "  %d,  /* typecnt */\n", sp->typecnt);
	fprintf(out, "  %d,  /* charcnt */\n", sp->charcnt);
	fprintf(out, "  %d,  /* goback */\n", sp->goback);
	fprintf(out, "  %d,  /* goahead */\n", sp->goahead);

	fprintf(out, "  {  /* ats */\n");
	per_line = 4;
	max = TZ_MAX_TIMES;
	for (i = 0; i < max; )
	{
		long v;
		
		if ((i % per_line) == 0)
			fprintf(out, "    ");
		v = (long)sp->ats[i];
		if (v == LONG_MIN)
			fprintf(out, "%ldL - 1", v + 1);
		else
			fprintf(out, "%ldL", v);
		i++;
		if (i < max)
			putc(',', out);
		putc((i % per_line) == 0 || i == max ? '\n' : ' ', out);
	}
	fprintf(out, "  },\n");

	fprintf(out, "  {  /* types */\n");
	per_line = 16;
	max = TZ_MAX_TIMES;
	for (i = 0; i < max; )
	{
		if ((i % per_line) == 0)
			fprintf(out, "    ");
		fprintf(out, "%d", sp->types[i]);
		i++;
		if (i < max)
			putc(',', out);
		putc((i % per_line) == 0 || i == max ? '\n' : ' ', out);
	}
	fprintf(out, "  },\n");

	fprintf(out, "  {  /* ttis */\n");
	per_line = 2;
	max = TZ_MAX_TYPES;
	for (i = 0; i < max; )
	{
		if ((i % per_line) == 0)
			fprintf(out, "    ");
		fprintf(out, "{ %ld, %d, %d, %d, %d }", (long)sp->ttis[i].tt_utoff, sp->ttis[i].tt_desigidx, sp->ttis[i].tt_isdst, sp->ttis[i].tt_ttisstd, sp->ttis[i].tt_ttisut);
		i++;
		if (i < max)
			putc(',', out);
		putc((i % per_line) == 0 || i == max ? '\n' : ' ', out);
	}
	fprintf(out, "  },\n");

	fprintf(out, "  {  /* chars */\n");
	per_line = 4;
	max = TZ_MAX_CHARS + 1;
	for (i = 0; i < max; )
	{
		unsigned char c;
		
		if ((i % per_line) == 0)
			fprintf(out, "    ");
		c = sp->chars[i];
		if (c >= 0x20 && c < 0x7f)
			fprintf(out, "'%c'", c);
		else
			fprintf(out, "'\\%03o'", c);
		i++;
		if (i < max)
			putc(',', out);
		putc((i % per_line) == 0 || i == max ? '\n' : ' ', out);
	}
	fprintf(out, "  },\n");

	fprintf(out, "  {  /* lsis */\n");
	per_line = 4;
	max = TZ_MAX_LEAPS;
	for (i = 0; i < max; )
	{
		if ((i % per_line) == 0)
			fprintf(out, "    ");
		fprintf(out, "{ %ld, %ld }", (long)sp->lsis[i].ls_trans, (long)sp->lsis[i].ls_corr);
		i++;
		if (i < max)
			putc(',', out);
		putc((i % per_line) == 0 || i == max ? '\n' : ' ', out);
	}
	fprintf(out, "  }\n");
	fprintf(out, "};\n");
	
	fflush(out);
	
	return EXIT_SUCCESS;
}
