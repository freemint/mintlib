# tz/Makefile -- MiNTLib.
# Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

#
# currently also duplicated at top of private.h; FIXME
#
TZVERSION = 2018e
TZ_BUGEMAIL = tz@iana.org
PKGVERSION = mintlib

SHELL = /bin/sh

SUBDIRS = 

srcdir = .
top_srcdir = ..
subdir = tz

dont_install_libs = yes

include $(top_srcdir)/configvars

default: all

include $(top_srcdir)/bindist
include $(top_srcdir)/rules

# FIXME: Tests still missing.
TESTS = dummy
include $(top_srcdir)/checkrules

# Override test flags.
cflags =
type = 

-include /etc/sparemint/timezone
ifdef TIMEZONE
  LOCALTIME = $(TIMEZONE)
  POSIXRULES = $(TIMEZONE)
endif
	
# Since "." may not be in PATH...
YEARISTYPE = ./yearistype

zic = ./zic
ZIC = $(zic) $(ZFLAGS)

sbin_PROGRAMS = zic zdump tzselect
bootsbin_PROGRAMS = tzinit

TZCOBJS = zic.o
TZDOBJS = zdump.o
TZIOBJS = tzinit.o

MANS = tzfile.5 tzselect.8 zic.8 zdump.8 tzinit.8
DOCS = README README.1st Theory $(MANS) Makefile

# If you want out-of-scope and often-wrong data from the file 'backzone', use
#	PACKRATDATA=	backzone
# To omit this data, use
#	PACKRATDATA=

PACKRATDATA = 

# For backward-compatibility links for old zone names, use
#	BACKWARD=	backward
# If you also want the link US/Pacific-New, even though it is confusing
# and is planned to be removed from the database eventually, use
#	BACKWARD=	backward pacificnew
# To omit these links, use
#	BACKWARD=

BACKWARD=	backward

# Choose source data features.  To get new features right away, use:
#	DATAFORM=	vanguard
# To wait a while before using new features, to give downstream users
# time to upgrade zic (the default), use:
#	DATAFORM=	main
# To wait even longer for new features, use:
#	DATAFORM=	rearguard
DATAFORM=		main

PRIMARY_YDATA =	africa antarctica asia australasia \
		europe northamerica southamerica
YDATA =	$(PRIMARY_YDATA) pacificnew etcetera factory $(BACKWARD) $(PACKRATDATA)
NDATA =	systemv
#SDATA =	solar87 solar88 solar89
TDATA =	$(YDATA) $(NDATA) $(SDATA)
ZONETABLES=	zone1970.tab zone.tab
TABDATA = iso3166.tab $(TZDATA_TEXT) $(ZONETABLES)
LEAP_DEPS =	$(srcdir)/leapseconds.awk $(srcdir)/leap-seconds.list
TZDATA_ZI_DEPS=	ziguard.awk zishrink.awk $(TDATA) $(PACKRATDATA)
DSTDATA_ZI_DEPS= ziguard.awk $(TDATA) $(PACKRATDATA)
TDATA_TO_CHECK=	$(YDATA) $(NDATA) $(srcdir)/backward $(srcdir)/pacificnew
MISC = usno1988 usno1989 usno1989a usno1995 usno1997 \
	Arts.htm WWW.htm gccdiffs checktab.awk

# The date program contained here is not used.
# The one in /usr/bin is from coreutils
EXTRA_DIST += date.1 date.c

EXTRA_DIST += newctime.3 newstrftime.3 newtzset.3 time2posix.3

all-here: zic zdump tzselect yearistype tzinit zonelist

ifdef CROSS
NOTZ=yes
endif
ifeq (REDO,none)
NOTZ=yes
endif

ifndef NOTZ
install: all-here zoneswarning zones
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR) -l $(LOCALTIME) -p $(POSIXRULES)
	-rm -f $(DESTDIR)$(TZDIR)/iso3166.tab $(DESTDIR)$(TZDIR)/zone.tab
	$(INSTALL) -m 644 iso3166.tab zone.tab $(DESTDIR)$(TZDIR)/.
	$(mkinstalldirs) $(DESTDIR)$(sbindir)
	for file in $(sbin_PROGRAMS); do \
		echo "$(INSTALL) -m 755 $$file $(sbindir)"; \
		$(INSTALL) -m 755 $$file $(DESTDIR)$(sbindir); \
	done
	$(mkinstalldirs) $(DESTDIR)$(bootsbindir)
	for file in $(bootsbin_PROGRAMS); do \
		echo "$(INSTALL) -m 755 $$file $(bootsbindir)"; \
		$(INSTALL) -m 755 $$file $(DESTDIR)$(bootsbindir); \
	done

zoneswarning:
	@echo "WARNING: Compiling and installing the time zone database"
	@echo "may take some time.  Have a cup of coffee!"
	
uninstall:
	rm -rf $(DESTDIR)$(TZDIR)
	for file in $(sbin_PROGRAMS); do \
		echo "rm -f $(sbindir)/$$file"; \
		rm -f $(DESTDIR)$(sbindir)/$$file; \
	done
	for file in $(bootsbin_PROGRAMS); do \
		echo "rm -f $(bootsbindir)/$$file"; \
		rm -f $(DESTDIR)$(bootsbindir)/$$file; \
	done
	
uninstall-include:
uninstall-lib:

install-man:
	sections=""; \
	for manpage in $(MANS); do \
	  sections="$$sections $(mandir)/man`echo $$manpage | sed 's,^.*\\.,,'`"; \
	done; \
	mandirs=`echo $$sections | sort | uniq`; \
	for mandir in $$mandirs; do \
	  $(mkinstalldirs) $(DESTDIR)$$mandir; \
	done; \
	for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  echo "$(INSTALL) -m 644 $$manpage $(mandir)/man$$section"; \
	  $(INSTALL) -m 644 $$manpage $(DESTDIR)$(mandir)/man$$section; \
	done;

uninstall-man:
	@for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  echo "rm -f $(mandir)/man$$section/$$manpage"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.gz"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.Z"; \
	  rm -f $(DESTDIR)$(mandir)/man$$section/$$manpage; \
	  rm -f $(DESTDIR)$(mandir)/man$$section/$$manpage.gz; \
	  rm -f $(DESTDIR)$(mandir)/man$$section/$$manpage.Z; \
	done
	
else
install zones-warning uninstall uninstall-lib: cross-warning

install-man:

cross-warning:
	@echo "Not installing time zone database when cross-compiling."

.PHONY: install uninstall

endif

zdump: $(TZDOBJS) $(CRT0) $(libs)
	$(AM_V_LD)$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZDOBJS) -o $@ $(LIBS)

zic: $(TZCOBJS) $(CRT0) $(libs)
	$(AM_V_LD)$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZCOBJS) -o $@ $(LIBS)

tzinit: $(TZIOBJS) $(CRT0) $(libs)
	$(AM_V_LD)$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZIOBJS) -o $@ $(LIBS)

ifndef CROSS

posix_only: zic $(TDATA) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR) -L /dev/null $(TDATA)

right_only: zic leapseconds $(TDATA) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR) -L leapseconds $(TDATA)

other_two: zic leapseconds $(TDATA) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR)/posix -L /dev/null $(TDATA)
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR)/right -L leapseconds $(TDATA)

posix_right: posix_only other_two

right_posix: right_only other_two

none:

zones: cleandb $(REDO)

cleandb:
	$(mkinstalldirs) $(DESTDIR)$(TZDIR)
	
else
zones:
	@echo "Not installing time zone database when cross-compiling."

endif

yearistype: $(srcdir)/yearistype.sh
	cp $< $@
	chmod +x $@

leapseconds:	$(LEAP_DEPS)
		$(AWK) -f $(srcdir)/leapseconds.awk $(srcdir)/leap-seconds.list >$@.out
		mv $@.out $@

tzselect: $(srcdir)/tzselect.ksh
	sed \
		-e 's|AWK=[^}]*|AWK=$(AWK)|g' \
		-e 's|TZDIR=[^}]*|TZDIR=$(TZDIR)|' \
		-e 's|\(TZVERSION\)=.*|\1=$(TZVERSION)|' \
		<$< >$@
	chmod +x $@

install-include: # Do nothing here.

check_tables: $(srcdir)/checktab.awk $(PRIMARY_YDATA)
	$(AWK) -f $(srcdir)/checktab.awk $(PRIMARY_YDATA)

# This file has a version comment that attempts to capture any tailoring
# via BACKWARD, DATAFORM, PACKRATDATA, and REDO.
tzdata.zi:	$(DATAFORM).zi zishrink.awk
		$(AM_V_GEN)
		$(AM_V_at)LC_ALL=C $(AWK) \
		    -v dataform='$(DATAFORM)' \
		    -v deps='$(DSTDATA_ZI_DEPS) zishrink.awk' \
		    -v redo='$(REDO)' \
		    -v version="$(TZVERSION)" \
		    -f zishrink.awk \
		    $(DATAFORM).zi >$@.out
		$(AM_V_at)mv $@.out $@

MAKE_ZONENAMES = $(AWK) '/^Z/ { print $$2 } /^L/ { print $$3 }' tzdata.zi

zonenames: tzdata.zi
	@$(MAKE_ZONENAMES)

zonelist: tzdata.zi
	$(MAKE_ZONENAMES) >$@

-include $(top_srcdir)/phony
