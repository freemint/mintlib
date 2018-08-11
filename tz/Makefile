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

ifeq ($(CROSS),yes)

zic = ./zic_for_build$(EXEEXT_FOR_BUILD)
OBJS_FOR_BUILD = localtime_for_build.o asctime_for_build.o strftime_for_build.o

zic_for_build$(EXEEXT_FOR_BUILD): zic_for_build.o $(OBJS_FOR_BUILD)
	$(AM_V_LD)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(LDFLAGS_FOR_BUILD) -o $@ $^
zdump = ./zdump_for_build$(EXEEXT_FOR_BUILD)
zdump_for_build$(EXEEXT_FOR_BUILD): zdump_for_build.o $(OBJS_FOR_BUILD)
	$(AM_V_LD)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(LDFLAGS_FOR_BUILD) -o $@ $^
zic_for_build.o: zic.c
	$(AM_V_CC)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) -c -o $@ $<
zdump_for_build.o: zdump.c
	$(AM_V_CC)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) -c -o $@ $<
localtime_for_build.o: localtime.c
	$(AM_V_CC)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) -c -o $@ $<
asctime_for_build.o: asctime.c
	$(AM_V_CC)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) -c -o $@ $<
strftime_for_build.o: strftime.c
	$(AM_V_CC)$(CC_FOR_BUILD) $(CFLAGS_FOR_BUILD) $(CPPFLAGS_FOR_BUILD) -c -o $@ $<
else

zic = ./zic

endif

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

install: all-here zones
ifneq ($(TZREDO),none)
	@for f in $(TABDATA); do rm -f $(DESTDIR)$(TZDIR)/$$f; done
	$(INSTALL) -m 644 $(TABDATA) $(DESTDIR)$(TZDIR)/.
endif
	$(mkinstalldirs) $(DESTDIR)$(sbindir)
	@for file in $(sbin_PROGRAMS); do \
		echo "$(INSTALL) -m 755 $$file $(sbindir)"; \
		$(INSTALL) -m 755 $$file $(DESTDIR)$(sbindir); \
	done
	$(mkinstalldirs) $(DESTDIR)$(bootsbindir)
	@for file in $(bootsbin_PROGRAMS); do \
		echo "$(INSTALL) -m 755 $$file $(bootsbindir)"; \
		$(INSTALL) -m 755 $$file $(DESTDIR)$(bootsbindir); \
	done

zoneswarning:
	@echo "WARNING: Compiling and installing the time zone database"
	@echo "may take some time.  Have a cup of coffee!"
	
localtime-posixrules: $(zic) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR) -l $(LOCALTIME) -p $(POSIXRULES)
	@rm -f $(DESTDIR)$(TZDIR)/localtime
	@ln -s /etc/localtime $(DESTDIR)$(TZDIR)/localtime
	@if test $(LOCALTIME) = Factory; then \
	  echo "=========================================================" ;\
	  echo "WARNING: Installed tz database with localtime set to" ;\
	  echo "dummy timezone \`Factory'.  Run \`zic -l' with the" ;\
	  echo "correct timezone later or re-install after editing" ;\
	  echo "the \`LOCALTIME' variable in \`$(top_srcdir)/configvars." ;\
	  echo "=========================================================" ;\
	fi
	@rm -f $(DESTDIR)$(TZDIR)/posixrules
	@ln -s localtime $(DESTDIR)$(TZDIR)/posixrules
	@if test $(POSIXRULES) = America/New_York -o $(POSIXRULES) = Factory; then \
	  echo "=========================================================" ;\
	  echo "WARNING: Installed tz database with posixrules set to" ;\
	  echo "dummy timezone \`Factory'.  Run \`zic -p' with the" ;\
	  echo "correct timezone later or re-install after editing" ;\
	  echo "the \`POSIXRULES' variable in \`$(top_srcdir)/configvars." ;\
	  echo "=========================================================" ;\
	fi

uninstall:
	rm -rf $(DESTDIR)$(TZDIR)
	@for file in $(sbin_PROGRAMS); do \
		echo "rm -f $(sbindir)/$$file"; \
		rm -f $(DESTDIR)$(sbindir)/$$file; \
	done
	@for file in $(bootsbin_PROGRAMS); do \
		echo "rm -f $(bootsbindir)/$$file"; \
		rm -f $(DESTDIR)$(bootsbindir)/$$file; \
	done
	
uninstall-include:
uninstall-lib:

install-man:
	@sections=""; \
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
	
zdump: $(TZDOBJS) $(CRT0) $(libs)
	$(AM_V_LD)$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZDOBJS) -o $@ $(LIBS)

zic: $(TZCOBJS) $(CRT0) $(libs)
	$(AM_V_LD)$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZCOBJS) -o $@ $(LIBS)

tzinit: $(TZIOBJS) $(CRT0) $(libs)
	$(AM_V_LD)$(CC) $(LDFLAGS) $(TESTLDFLAGS) $(CRT0) $(TZIOBJS) -o $@ $(LIBS)

tzredo-posix_only: $(zic) $(TDATA) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR) -L /dev/null $(TDATA)

tzredo-right_only: $(zic) leapseconds $(TDATA) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR) -L leapseconds $(TDATA)

other_two: $(zic) leapseconds $(TDATA) yearistype
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR)/posix -L /dev/null $(TDATA)
	$(ZIC) -y $(YEARISTYPE) -d $(DESTDIR)$(TZDIR)/right -L leapseconds $(TDATA)

tzredo-posix_right: tzredo-posix_only other_two

tzredo-right_posix: tzredo-right_only other_two

tzredo-none:
	@( \
	  echo "*********************************"; \
	  echo "Not installing timezone database "; \
	  echo "*********************************"; \
	  echo ""; \
	  echo "create it on the target system using"; \
	  echo ""; \
	  ZIC="./zic$(EXEEXT) $(ZFLAGS)"; \
	  echo "For using right rules only, counting leap seconds:"; \
	  echo "$${ZIC} -y $(YEARISTYPE) -d $(TARGET_TZDIR) -L leapseconds $(TDATA)"; \
	  echo ""; \
	  echo "For using posix rules only, not counting leap seconds:"; \
	  echo "$${ZIC} -y $(YEARISTYPE) -d $(TARGET_TZDIR) -L /dev/null $(TDATA)"; \
	  echo ""; \
	  echo "For using both sets, with leap seconds counted normally:"; \
	  echo "$${ZIC} -y $(YEARISTYPE) -d $(TARGET_TZDIR) -L leapseconds $(TDATA)"; \
	  echo "ln -s $(TZDIR_BASENAME) $(TARGET_TZDIR)-leaps"; \
	  echo "$${ZIC} -y $(YEARISTYPE) -d $(TARGET_TZDIR)-posix -L /dev/null $(TDATA)"; \
	  echo ""; \
	  echo "For using both sets, with leap seconds not counted normally:"; \
	  echo "$${ZIC} -y $(YEARISTYPE) -d $(TARGET_TZDIR) -L /dev/null $(TDATA)"; \
	  echo "ln -s $(TZDIR_BASENAME) $(TARGET_TZDIR)-posix"; \
	  echo "$${ZIC} -y $(YEARISTYPE) -d $(TARGET_TZDIR)-leaps -L leapseconds $(TDATA)"; \
	  echo "*********************************"; \
        ) >&2

ifeq ($(TZREDO),none)

zones: tzredo-$(TZREDO)
	@:

else

zones: zoneswarning cleandb tzredo-$(TZREDO) localtime-posixrules

endif


cleandb:
	$(mkinstalldirs) $(DESTDIR)$(TZDIR)
	
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
