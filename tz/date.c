/* Display or set the current time and date.  */

/* Copyright 1985, 1987, 1988 The Regents of the University of California.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
   3. Neither the name of the University nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
   SUCH DAMAGE.  */

#include "private.h"
#if HAVE_ADJTIME || HAVE_SETTIMEOFDAY
#include "sys/time.h"
#endif
#include "locale.h"
#include "utmp.h"						/* for OLD_TIME (or its absence) */
#if HAVE_UTMPX_H
#include "utmpx.h"
#endif
#include <getopt.h>

#ifndef OTIME_MSG
#define OTIME_MSG "old time"
#endif
#ifndef NTIME_MSG
#define NTIME_MSG "new time"
#endif

static int retval = EXIT_SUCCESS;

static void checkfinal(const char *, int, time_t, time_t);
static time_t convert(const char *, int, time_t);
static void display(const char *, time_t);
static void dogmt(void);
static void errensure(void);
static void iffy(time_t, time_t, const char *, const char *);
static const char *nondigit(const char *);
static void oops(const char *);
static void reset(time_t, int);
static int sametm(const struct tm *, const struct tm *);
static void timeout(FILE *, const char *, const struct tm *);
static void usage(void) __attribute__ ((__noreturn__));
static void wildinput(const char *, const char *, const char *);

int main(int, char **);

int main(const int argc, char *argv[])
{
	const char *format;
	const char *value;
	const char *cp;
	int ch;
	int dousg;
	int aflag = FALSE;
	int dflag = FALSE;
	int nflag = FALSE;
	int tflag = FALSE;
	int rflag = FALSE;
	int minuteswest;
	int dsttime;
	double adjust;
	time_t now;
	time_t t;
	intmax_t secs;
	char *endarg;

	INITIALIZE(dousg);
	INITIALIZE(minuteswest);
	INITIALIZE(dsttime);
	INITIALIZE(adjust);
#if HAVE_SETLOCALE
	setlocale(LC_ALL, "");
#endif
#ifdef ENABLE_NLS
	bindtextdomain(TZ_DOMAIN, TZ_DOMAINDIR);
	textdomain(TZ_DOMAIN);
#ifdef HAVE_BIND_TEXTDOMAIN_CODESET
	bind_textdomain_codeset(TZ_DOMAIN, GETTEXT_CODESET);
#endif
#endif
	t = now = time(NULL);
	format = value = NULL;
	while ((ch = getopt(argc, argv, "ucr:nd:t:a:")) != EOF && ch != -1)
	{
		switch (ch)
		{
		case 'u':						/* do it in UT */
		case 'c':
			dogmt();
			break;
		case 'r':						/* seconds since 1970 */
			if (rflag)
			{
				fprintf(stderr, _("date: error: multiple -%c's used"), 'r');
				usage();
			}
			rflag = TRUE;
			errno = 0;
			secs = strtoimax(optarg, &endarg, 0);
			if (*endarg || optarg == endarg)
				errno = EINVAL;
			else if (!(TIME_T_MIN <= secs && secs <= TIME_T_MAX))
				errno = ERANGE;
			if (errno)
			{
				char const *e = strerror(errno);
				fprintf(stderr, _("date: %s: %s\n"), optarg, e);
				errensure();
				exit(retval);
			}
			t = secs;
			break;
		case 'n':						/* don't set network */
			nflag = TRUE;
			break;
		case 'd':						/* daylight saving time */
			if (dflag)
			{
				fprintf(stderr, _("date: error: multiple -%c's used"), 'd');
				usage();
			}
			dflag = TRUE;
			cp = optarg;
			dsttime = atoi(cp);
			if (*cp == '\0' || *nondigit(cp) != '\0')
				wildinput(_("-t value"), optarg, _("must be a non-negative number"));
			break;
		case 't':						/* minutes west of UTC */
			if (tflag)
			{
				fprintf(stderr, _("date: error: multiple -%c's used"), 't');
				usage();
			}
			tflag = TRUE;
			cp = optarg;
			minuteswest = atoi(cp);
			if (*cp == '+' || *cp == '-')
				++cp;
			if (*cp == '\0' || *nondigit(cp) != '\0')
				wildinput(_("-d value"), optarg, _("must be a number"));
			break;
		case 'a':						/* adjustment */
			if (aflag)
			{
				fprintf(stderr, _("date: error: multiple -%c's used"), 'a');
				usage();
			}
			aflag = TRUE;
			cp = optarg;
			adjust = atof(cp);
			if (*cp == '+' || *cp == '-')
				++cp;
			if (*cp == '\0' || strcmp(cp, ".") == 0)
				wildinput(_("-a value"), optarg, _("must be a number"));
			cp = nondigit(cp);
			if (*cp == '.')
				++cp;
			if (*nondigit(cp) != '\0')
				wildinput(_("-a value"), optarg, _("must be a number"));
			break;
		default:
			usage();
			break;
		}
	}
	while (optind < argc)
	{
		cp = argv[optind++];
		if (*cp == '+')
		{
			if (format == NULL)
			{
				format = cp + 1;
			} else
			{
				fprintf(stderr, _("date: error: multiple formats in command line\n"));
				usage();
			}
		} else if (value == NULL && !rflag)
		{
			value = cp;
		} else
		{
			fprintf(stderr, _("date: error: multiple values in command line\n"));
			usage();
		}
	}
	if (value != NULL)
	{
		/*
		 ** This order ensures that "reasonable" twelve-digit inputs
		 ** (such as 120203042006) won't be misinterpreted
		 ** even if time_t's range all the way back to the thirteenth
		 ** century.  Do not change the order.
		 */
		t = convert(value, (dousg = TRUE), now);
		if (t == -1)
			t = convert(value, (dousg = FALSE), now);
		if (t == -1)
		{
			/*
			 ** Out of range values,
			 ** or time that falls in a DST transition hole?
			 */
			if ((cp = strchr(value, '.')) != NULL)
			{
				/*
				 ** Ensure that the failure of
				 ** TZ=America/New_York date 8712312359.60
				 ** doesn't get misdiagnosed.  (It was
				 ** TZ=America/New_York date 8712311859.60
				 ** when the leap second was inserted.)
				 ** The normal check won't work since
				 ** the given time is valid in UTC.
				 */
				if (atoi(cp + 1) >= SECSPERMIN)
					wildinput(_("time"), value, _("out of range seconds given"));
			}
			dogmt();
			t = convert(value, FALSE, now);
			if (t == -1)
				t = convert(value, TRUE, now);
			wildinput(_("time"), value,
					  (t == -1) ? _("out of range value given") : _("time skipped when clock springs forward"));
		}
	}
	/*
	 ** Entire command line has now been checked.
	 */
	if (aflag)
	{
#if HAVE_ADJTIME
		struct timeval tv;

		tv.tv_sec = (int) adjust;
		tv.tv_usec = (int) ((adjust - tv.tv_sec) * 1000000L);
		if (adjtime(&tv, NULL) != 0)
			oops("adjtime");
#endif
#if !HAVE_ADJTIME
		reset(now + adjust, nflag);
#endif
		/*
		 ** Sun silently ignores everything else; we follow suit.
		 */
		exit(retval);
	}
	if (dflag || tflag)
	{
#if HAVE_SETTIMEOFDAY == 2
		struct timezone tz;
		struct timeval tv;

		if (!dflag || !tflag)
			if (gettimeofday(&tv, &tz) != 0)
				oops("gettimeofday");
		if (dflag)
			tz.tz_dsttime = dsttime;
		if (tflag)
			tz.tz_minuteswest = minuteswest;
		if (settimeofday(NULL, &tz) != 0)
			oops("settimeofday");
#endif /* HAVE_SETTIMEOFDAY == 2 */
#if HAVE_SETTIMEOFDAY != 2
		(void) dsttime;
		(void) minuteswest;
		fprintf(stderr, _("date: warning: kernel doesn't keep -d/-t information, option ignored\n"));
#endif /* HAVE_SETTIMEOFDAY != 2 */
	}

	if (value)
	{
		reset(t, nflag);
		checkfinal(value, dousg, t, now);
		t = time(NULL);
	}

	display(format, t);
	return retval;
}

static void dogmt(void)
{
	static int once;

	if (!once)
	{
		if (setenv("TZ", "GMT0", 1) != 0)
		{
			perror(_("Memory exhausted"));
			errensure();
			exit(retval);
		}
		once = 1;
	}
}

#ifdef OLD_TIME

/*
** We assume we're on a System-V-based system,
** should use stime,
** should write System-V-format utmp entries,
** and don't have network notification to worry about.
*/

#include "fcntl.h"						/* for O_WRONLY, O_APPEND */

static void reset(const time_t newt, int nflag)
{
	int fid;
	time_t oldt;
	static struct
	{
		struct utmp before;
		struct utmp after;
	} s;

#if HAVE_UTMPX_H
	static struct
	{
		struct utmpx before;
		struct utmpx after;
	} sx;
#endif

	(void)nflag;
	/*
	 ** Wouldn't it be great if stime returned the old time?
	 */
	time(&oldt);
	if (stime(&newt) != 0)
		oops("stime");
	s.before.ut_type = OLD_TIME;
	s.before.ut_time = oldt;
	strcpy(s.before.ut_line, OTIME_MSG);
	s.after.ut_type = NEW_TIME;
	s.after.ut_time = newt;
	strcpy(s.after.ut_line, NTIME_MSG);
	fid = open(WTMP_FILE, O_WRONLY | O_APPEND);
	if (fid < 0)
		oops(_("log file open"));
	if (write(fid, (char *) &s, sizeof s) != sizeof s)
		oops(_("log file write"));
	if (close(fid) != 0)
		oops(_("log file close"));
#if !HAVE_UTMPX_H
	pututline(&s.before);
	pututline(&s.after);
#endif /* !HAVE_UTMPX_H */
#if HAVE_UTMPX_H
	sx.before.ut_type = OLD_TIME;
	sx.before.ut_tv.tv_sec = oldt;
	strcpy(sx.before.ut_line, OTIME_MSG);
	sx.after.ut_type = NEW_TIME;
	sx.after.ut_tv.tv_sec = newt;
	strcpy(sx.after.ut_line, NTIME_MSG);
#ifndef SUPPRESS_WTMPX_FILE_UPDATE
	/* In Solaris 2.5 (and presumably other systems),
	   `date' does not update /var/adm/wtmpx.
	   This must be a bug.  If you'd like to reproduce the bug,
	   define SUPPRESS_WTMPX_FILE_UPDATE to be nonzero.  */
	fid = open(WTMPX_FILE, O_WRONLY | O_APPEND);
	if (fid < 0)
		oops(_("log file open"));
	if (write(fid, (char *) &sx, sizeof sx) != sizeof sx)
		oops(_("log file write"));
	if (close(fid) != 0)
		oops(_("log file close"));
#endif
	pututxline(&sx.before);
	pututxline(&sx.after);
#endif /* HAVE_UTMPX_H */
}

#endif /* defined OLD_TIME */


#ifndef OLD_TIME

/*
** We assume we're on a BSD-based system,
** should use settimeofday,
** should write BSD-format utmp entries (using logwtmp),
** and may get to worry about network notification.
** The "time name" changes between 4.3-tahoe and 4.4;
** we include sys/param.h to determine which we should use.
*/

#ifndef TIME_NAME
#include "sys/param.h"
#ifdef BSD4_4
#define TIME_NAME	"date"
#endif
#ifndef BSD4_4
#define TIME_NAME	""
#endif
#endif

#include "syslog.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#define TSPTYPES
#include "protocols/timed.h"

#if HAVE_SETTIMEOFDAY == 1
#define settimeofday(t, tz) (settimeofday)(t)
#endif

#ifdef TSP_SETDATE
static int netsettime(struct timeval);
#endif

static void reset(const time_t newt, int nflag)
{
	const char *username;
	static struct timeval tv;			/* static so tv_usec is 0 */

	(void)nflag;
	username = getlogin();
	if (username == NULL || *username == '\0')	/* single-user or no tty */
		username = "root";
	tv.tv_sec = newt;
#ifdef TSP_SETDATE
	if (nflag || !netsettime(tv))
#endif
	{
		/*
		 ** "old" entry is always written, for compatibility.
		 */
		logwtmp("|", TIME_NAME, "");
		if (settimeofday(&tv, NULL) == 0)
		{
			logwtmp("{", TIME_NAME, "");	/* } */
			syslog(LOG_AUTH | LOG_NOTICE, _("date set by %s"), username);
		} else
		{
			oops("settimeofday");
		}
	}
}

#endif /* !defined OLD_TIME */

static void wildinput(const char *const item, const char *const value, const char *const reason)
{
	fprintf(stderr, _("date: error: bad command line %s \"%s\", %s\n"), item, value, reason);
	usage();
}

static void errensure(void)
{
	if (retval == EXIT_SUCCESS)
		retval = EXIT_FAILURE;
}

static const char *ATTRIBUTE_PURE nondigit(const char *cp)
{
	while (is_digit(*cp))
		++cp;
	return cp;
}

static void usage(void)
{
	fprintf(stderr, _("date: usage: date [-u] [-c] [-r seconds] [-n]"
					 " [-d dst] [-t min-west] [-a sss.fff]" " [[yyyy]mmddhhmm[yyyy][.ss]] [+format]\n"));
	errensure();
	exit(retval);
}

static void oops(const char *const string)
{
	int e = errno;

	fprintf(stderr, _("date: error: "));
	errno = e;
	perror(string);
	errensure();
	display(NULL, time(NULL));
	exit(retval);
}

static void display(const char *format, time_t now)
{
	struct tm *tmp;

	tmp = localtime(&now);
	if (!tmp)
	{
		fprintf(stderr, _("date: error: time out of range\n"));
		errensure();
		return;
	}
	timeout(stdout, format ? format : "%+", tmp);
	putchar('\n');
	fflush(stdout);
	fflush(stderr);
	if (ferror(stdout) || ferror(stderr))
	{
		fprintf(stderr, _("date: error: couldn't write results\n"));
		errensure();
	}
}

#define INCR	1024

static void timeout(FILE *fp, const char *format, const struct tm *tmp)
{
	char *cp;
	size_t result;
	size_t size;
	struct tm tm;

	if (*format == '\0')
		return;
	if (!tmp)
	{
		fprintf(stderr, _("date: error: time out of range\n"));
		errensure();
		return;
	}
	tm = *tmp;
	tmp = &tm;
	size = INCR;
	cp = malloc(size);
	for (;;)
	{
		if (cp == NULL)
		{
			fprintf(stderr, _("date: error: can't get memory\n"));
			errensure();
			exit(retval);
		}
		cp[0] = '\1';
		result = strftime(cp, size, format, tmp);
		if (result != 0 || cp[0] == '\0')
			break;
		size += INCR;
		cp = realloc(cp, size);
	}
	(void) fwrite(cp, 1, result, fp);
	free(cp);
}

static int sametm(const struct tm *const atmp, const struct tm *const btmp)
{
	return atmp->tm_year == btmp->tm_year &&
		atmp->tm_mon == btmp->tm_mon &&
		atmp->tm_mday == btmp->tm_mday &&
		atmp->tm_hour == btmp->tm_hour &&
		atmp->tm_min == btmp->tm_min &&
		atmp->tm_sec == btmp->tm_sec;
}

/*
** convert --
**	convert user's input into a time_t.
*/

#define ATOI2(ar)	(ar[0] - '0') * 10 + (ar[1] - '0'); ar += 2;

static time_t convert(const char *const value, const int dousg, const time_t t)
{
	const char *cp;
	const char *dotp;
	int cent, year_in_cent, month, hour, day, mins, secs;
	struct tm tm, outtm, *tmp;
	time_t outt;

	tmp = localtime(&t);
	if (!tmp)
		return -1;
	tm = *tmp;
#define DIVISOR	100
	year_in_cent = tm.tm_year % DIVISOR + TM_YEAR_BASE % DIVISOR;
	cent = tm.tm_year / DIVISOR + TM_YEAR_BASE / DIVISOR + year_in_cent / DIVISOR;
	year_in_cent %= DIVISOR;
	if (year_in_cent < 0)
	{
		year_in_cent += DIVISOR;
		--cent;
	}
	month = tm.tm_mon + 1;
	day = tm.tm_mday;
	hour = tm.tm_hour;
	mins = tm.tm_min;
	secs = 0;

	dotp = strchr(value, '.');
	for (cp = value; *cp != '\0'; ++cp)
		if (!is_digit(*cp) && cp != dotp)
			wildinput(_("time"), value, _("contains a nondigit"));

	if (dotp == NULL)
	{
		dotp = strchr(value, '\0');
	} else
	{
		cp = dotp + 1;
		if (strlen(cp) != 2)
			wildinput(_("time"), value, _("seconds part is not two digits"));
		secs = ATOI2(cp);
	}

	cp = value;
	switch (dotp - cp)
	{
	default:
		wildinput(_("time"), value, _("main part is wrong length"));
		break;
	case 12:
		if (!dousg)
		{
			cent = ATOI2(cp);
			year_in_cent = ATOI2(cp);
		}
		month = ATOI2(cp);
		day = ATOI2(cp);
		hour = ATOI2(cp);
		mins = ATOI2(cp);
		if (dousg)
		{
			cent = ATOI2(cp);
			year_in_cent = ATOI2(cp);
		}
		break;
	case 8:							/* mmddhhmm */
		month = ATOI2(cp);
		/* fall through */
	case 6:							/* ddhhmm */
		day = ATOI2(cp);
		/* fall through */
	case 4:							/* hhmm */
		hour = ATOI2(cp);
		mins = ATOI2(cp);
		break;
	case 10:
		if (!dousg)
		{
			year_in_cent = ATOI2(cp);
		}
		month = ATOI2(cp);
		day = ATOI2(cp);
		hour = ATOI2(cp);
		mins = ATOI2(cp);
		if (dousg)
		{
			year_in_cent = ATOI2(cp);
		}
		break;
	}

	tm.tm_year = cent * 100 + year_in_cent - TM_YEAR_BASE;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = mins;
	tm.tm_sec = secs;
	tm.tm_isdst = -1;
	outtm = tm;
	outt = mktime(&outtm);
	return sametm(&tm, &outtm) ? outt : -1;
}

/*
** Code from here on out is either based on code provided by UCB
** or is only called just before the program exits.
*/

/*
** Check for iffy input.
*/

static void checkfinal(const char *const value, const int didusg, const time_t t, const time_t oldnow)
{
	time_t othert;
	struct tm tm, *tmp;
	struct tm othertm;
	int pass, offset;

	/*
	 ** See if there's both a USG and a BSD interpretation.
	 */
	othert = convert(value, !didusg, oldnow);
	if (othert != -1 && othert != t)
		iffy(t, othert, value, _("year could be at start or end"));
	/*
	 ** See if there's both a DST and a STD version.
	 */
	tmp = localtime(&t);
	if (!tmp)
		iffy(t, othert, value, _("time out of range"));
	othertm = tm = *tmp;
	othertm.tm_isdst = !tm.tm_isdst;
	othert = mktime(&othertm);
	if (othert != -1 && othertm.tm_isdst != tm.tm_isdst && sametm(&tm, &othertm))
		iffy(t, othert, value, _("both standard and summer time versions exist"));
	/*
	** Final check.
	**
	** If a jurisdiction shifts time *without* shifting whether time is
	** summer or standard (as Hawaii, the United Kingdom, and Saudi Arabia
	** have done), routine checks for iffy times may not work.
	** So we perform this final check, deferring it until after the time has
	** been set--it may take a while, and we don't want to introduce an unnecessary
	** lag between the time the user enters their command and the time that
	** stime/settimeofday is called.
	**
	** We just check nearby times to see if any have the same representation
	** as the time that convert returned.  We work our way out from the center
	** for quick response in solar time situations.  We only handle common cases--
	** offsets of at most a minute, and offsets of exact numbers of minutes
	** and at most an hour.
	*/
	for (offset = 1; offset <= 60; ++offset)
	{
		for (pass = 1; pass <= 4; ++pass)
		{
			if (pass == 1)
				othert = t + offset;
			else if (pass == 2)
				othert = t - offset;
			else if (pass == 3)
				othert = t + 60 * offset;
			else
				othert = t - 60 * offset;
			tmp = localtime(&othert);
			if (!tmp)
				iffy(t, othert, value, _("time out of range"));
			othertm = *tmp;
			if (sametm(&tm, &othertm))
				iffy(t, othert, value, _("multiple matching times exist"));
		}
	}
}

static void iffy(const time_t thist, const time_t thatt, const char *const value, const char *const reason)
{
	struct tm *tmp;
	int dst;

	fprintf(stderr, _("date: warning: ambiguous time \"%s\", %s.\n"), value, reason);
	tmp = gmtime(&thist);
	/*
	 ** Avoid running afoul of SCCS!
	 */
	timeout(stderr, _("Time was set as if you used\n\tdate -u %m%d%H\
%M\
%Y.%S\n"), tmp);
	tmp = localtime(&thist);
	dst = tmp ? tmp->tm_isdst : 0;
	timeout(stderr, _("to get %c"), tmp);
	fprintf(stderr, _(" (%s).  Use\n"), dst ? _("summer time") : _("standard time"));
	tmp = gmtime(&thatt);
	timeout(stderr, _("\tdate -u %m%d%H\
%M\
%Y.%S\n"), tmp);
	tmp = localtime(&thatt);
	dst = tmp ? tmp->tm_isdst : 0;
	timeout(stderr, _("to get %c"), tmp);
	fprintf(stderr, _(" (%s).\n"), dst ? _("summer time") : _("standard time"));
	errensure();
	exit(retval);
}

#ifdef TSP_SETDATE
#define WAITACK		2					/* seconds */
#define WAITDATEACK	5					/* seconds */

/*
 * Set the date in the machines controlled by timedaemons
 * by communicating the new date to the local timedaemon.
 * If the timedaemon is in the master state, it performs the
 * correction on all slaves.  If it is in the slave state, it
 * notifies the master that a correction is needed.
 * Returns 1 on success, 0 on failure.
 */
static int netsettime(struct timeval ntv)
{
	int s, length, port, timed_ack, found, err, waittime;
	fd_set ready;
	char hostname[MAXHOSTNAMELEN];
	struct timeval tout;
	struct servent *sp;
	struct tsp msg;
	struct sockaddr_in sin, dest, from;

	sp = getservbyname("timed", "udp");
	if (sp == 0)
	{
		fputs(_("udp/timed: unknown service\n"), stderr);
		retval = 2;
		return 0;
	}
	dest.sin_port = sp->s_port;
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl(INADDR_ANY);
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		if (errno != EPROTONOSUPPORT)
			perror("date: socket");
		goto bad;
	}
	memset((char *) &sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	for (port = IPPORT_RESERVED - 1; port > IPPORT_RESERVED / 2; port--)
	{
		sin.sin_port = htons(port);
		if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) >= 0)
			break;
		if (errno != EADDRINUSE)
		{
			if (errno != EADDRNOTAVAIL)
				perror("date: bind");
			goto bad;
		}
	}
	if (port == IPPORT_RESERVED / 2)
	{
		fputs(_("date: All ports in use\n"), stderr);
		goto bad;
	}
	msg.tsp_type = TSP_SETDATE;
	msg.tsp_vers = TSPVERSION;
	if (gethostname(hostname, sizeof(hostname)))
	{
		perror("gethostname");
		goto bad;
	}
	strncpy(msg.tsp_name, hostname, sizeof(hostname));
	msg.tsp_seq = htons(0);
	msg.tsp_time.tv_sec = htonl(ntv.tv_sec);
	msg.tsp_time.tv_usec = htonl(ntv.tv_usec);
	length = sizeof(struct sockaddr_in);
	if (connect(s, &dest, length) < 0)
	{
		perror("date: connect");
		goto bad;
	}
	if (send(s, (char *) &msg, sizeof(struct tsp), 0) < 0)
	{
		if (errno != ECONNREFUSED)
			perror("date: send");
		goto bad;
	}
	timed_ack = -1;
	waittime = WAITACK;
  loop:
	tout.tv_sec = waittime;
	tout.tv_usec = 0;
	FD_ZERO(&ready);
	FD_SET(s, &ready);
	found = select(FD_SETSIZE, &ready, NULL, NULL, &tout);
	length = sizeof err;
	if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *) &err, &length) == 0 && err)
	{
		errno = err;
		if (errno != ECONNREFUSED)
			perror(_("date: send (delayed error)"));
		goto bad;
	}
	if (found > 0 && FD_ISSET(s, &ready))
	{
		length = sizeof(struct sockaddr_in);
		if (recvfrom(s, (char *) &msg, sizeof(struct tsp), 0, &from, &length) < 0)
		{
			if (errno != ECONNREFUSED)
				perror("date: recvfrom");
			goto bad;
		}
		msg.tsp_seq = ntohs(msg.tsp_seq);
		msg.tsp_time.tv_sec = ntohl(msg.tsp_time.tv_sec);
		msg.tsp_time.tv_usec = ntohl(msg.tsp_time.tv_usec);
		switch (msg.tsp_type)
		{

		case TSP_ACK:
			timed_ack = TSP_ACK;
			waittime = WAITDATEACK;
			goto loop;

		case TSP_DATEACK:
			close(s);
			return 1;

		default:
			fprintf(stderr, _("date: Wrong ack received from timed: %s\n"), tsptype[msg.tsp_type]);
			timed_ack = -1;
			break;
		}
	}
	if (timed_ack == -1)
		fputs(_("date: Can't reach time daemon, time set locally.\n"), stderr);
  bad:
	close(s);
	retval = 2;
	return 0;
}
#endif /* defined TSP_SETDATE */
