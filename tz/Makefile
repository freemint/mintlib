# tz/Makefile -- MiNTLib.
# Copyright (C) 1999, 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

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
YEARISTYPE = $(srcdir)/yearistype

TZDEFS = -DHAVE_ADJTIME=0 -DHAVE_GETTEXT=0 -DHAVE_LONG_DOUBLE=0 \
-DHAVE_SETTIMEOFDAY=2 -DHAVE_STRERROR=1 -DTM_GMTOFF=tm_gmtoff \
-DTM_ZONE=tm_zone -Dunix -DNOID

zic = $(srcdir)/zic
ZIC = $(zic) $(ZFLAGS)

sbin_PROGRAMS = zic zdump tzselect
bootsbin_PROGRAMS = tzinit

TZCOBJS = zic.o scheck.o ialloc.o stack.o
TZDOBJS = zdump.o ialloc.o stack.o
TZIOBJS = tzinit.o

MANS = tzfile.5 tzselect.8 zic.8 zdump.8 tzinit.8
DOCS = README README.1st Theory $(MANS) Makefile
PRIMARY_YDATA =	africa antarctica asia australasia \
		europe northamerica southamerica
YDATA =	$(PRIMARY_YDATA) pacificnew etcetera factory backward
NDATA =	systemv
SDATA =	solar87 solar88 solar89
TDATA =	$(YDATA) $(NDATA) $(SDATA)
TABDATA = iso3166.tab zone.tab
DATA = $(YDATA) $(NDATA) $(SDATA) $(TABDATA) leapseconds yearistype.sh
MISC = usno1988 usno1989 usno1989a usno1995 usno1997 \
	Arts.htm WWW.htm gccdiffs checktab.awk

DEFS-zic.c = $(TZDEFS)
DEFS-scheck.c = $(TZDEFS)
DEFS-ialloc.c = $(TZDEFS)
DEFS-zdump.c = $(TZDEFS)
DEFS-tzinit.c = $(TZDEFS)
CFLAGS-zic.c = -I$(top_srcdir)/time
CFLAGS-scheck.c = -I$(top_srcdir)/time
CFLAGS-ialloc.c = -I$(top_srcdir)/time
CFLAGS-zdump.c = -I$(top_srcdir)/time
CFLAGS-tzinit.c = -I$(top_srcdir)/time

all-here: zic zdump tzselect yearistype tzinit zonelist

ifdef CROSS
NOTZ=yes
endif
ifeq (REDO,none)
NOTZ=yes
endif

ifndef NOTZ
install: all-here zoneswarning zones
	$(ZIC) -y $(YEARISTYPE) \
		-d $(TZDIR) -l $(LOCALTIME) -p $(POSIXRULES)
	-rm -f $(TZDIR)/iso3166.tab $(TZDIR)/zone.tab
	$(INSTALL) -m 644 iso3166.tab zone.tab $(TZDIR)/.
	$(mkinstalldirs) $(sbindir)
	for file in $(sbin_PROGRAMS); do \
		$(INSTALL) -m 755 $$file $(sbindir); \
		echo "$(INSTALL) -m 755 $$file $(sbindir)"; \
	done
	$(mkinstalldirs) $(bootsbindir)
	for file in $(bootsbin_PROGRAMS); do \
		$(INSTALL) -m 755 $$file $(bootsbindir); \
		echo "$(INSTALL) -m 755 $$file $(bootsbindir)"; \
	done

zoneswarning:
	@echo "WARNING: Compiling and installing the time zone database"
	@echo "may take some time.  Have a cup of coffee!"
	
uninstall:
	rm -rf $(TZDIR)
	for file in $(sbin_PROGRAMS); do \
		echo "rm -f $(sbindir)/$$file"; \
		rm -f $(sbindir)/$$file; \
	done
	for file in $(bootsbin_PROGRAMS); do \
		echo "rm -f $(bootsbindir)/$$file"; \
		rm -f $(bootsbindir)/$$file; \
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
	  $(mkinstalldirs) $$mandir; \
	done; \
	for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  $(INSTALL) -m 644 $$manpage $(mandir)/man$$section; \
	  echo "$(INSTALL) -m 644 $$manpage $(mandir)/man$$section"; \
	done;

uninstall-man:
	@for manpage in $(MANS); do \
	  section=`echo $$manpage | sed 's,^.*\\.,,'`; \
	  echo "rm -f $(mandir)/man$$section/$$manpage"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.gz"; \
	  echo "rm -f $(mandir)/man$$section/$$manpage.Z"; \
	  rm -f $(mandir)/man$$section/$$manpage; \
	  rm -f $(mandir)/man$$section/$$manpage.gz; \
	  rm -f $(mandir)/man$$section/$$manpage.Z; \
	done
	
else
install zones-warning uninstall uninstall-lib: cross-warning

install-man:

cross-warning:
	@echo "Not installing time zone database when cross-compiling."

.PHONY: install uninstall

endif

zdump: $(TZDOBJS) $(CRT0) $(libs)
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZDOBJS) -o $@ $(LIBS)

zic: $(TZCOBJS) $(CRT0) $(libs) yearistype
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZCOBJS) -o $@ $(LIBS)

tzinit: $(TZIOBJS) $(CRT0) $(libs)
	$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZIOBJS) -o $@ $(LIBS)

ifndef CROSS
yearistype: yearistype.sh
	cp yearistype.sh yearistype
	chmod +x yearistype

posix_only: zic $(TDATA)
	$(ZIC) -y $(YEARISTYPE) -d $(TZDIR) -L /dev/null $(TDATA)

right_only: zic leapseconds $(TDATA)
	$(ZIC) -y $(YEARISTYPE) -d $(TZDIR) -L leapseconds $(TDATA)

other_two: zic leapseconds $(TDATA)
	$(ZIC) -y $(YEARISTYPE) -d $(TZDIR)/posix -L /dev/null $(TDATA)
	$(ZIC) -y $(YEARISTYPE) \
		-d $(TZDIR)/right -L leapseconds $(TDATA)

posix_right: posix_only other_two

right_posix: right_only other_two

none:

zones: cleandb $(REDO)

cleandb:
	$(mkinstalldirs) $(TZDIR)
	
tzselect: tzselect.ksh
	sed \
		-e 's|AWK=[^}]*|AWK=$(AWK)|g' \
		-e 's|TZDIR=[^}]*|TZDIR=$(TZDIR)|' \
		<$? >$@
	chmod +x $@

else
zones:
	@echo "Not installing time zone database when cross-compiling."

tzselect yearistype:
	touch $@
endif

install-include: # Do nothing here.

check_tables: checktab.awk $(PRIMARY_YDATA)
	$(AWK) -f checktab.awk $(PRIMARY_YDATA)

zonenames: $(TDATA)
	@awk '/^Zone/ { print $$2 } /^Link/ { print $$3 }' $(TDATA)

zonelist: $(TDATA)
	$(MAKE) zonenames >$@

-include $(top_srcdir)/phony

