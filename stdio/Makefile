# stdio/Makefile -- MiNTLib.
# Copyright (C) 2000 Guido Flohr <guido@freemint.de>
#
# This file is part of the MiNTLib project, and may only be used
# modified and distributed under the terms of the MiNTLib project
# license, COPYMINT.  By continuing to use, modify, or distribute
# this file you indicate that you have read the license and
# understand and accept it fully.

SHELL = /bin/sh

srcdir = .
top_srcdir = ..
subdir = stdio

SUBDIRS =

have_check = yes

include $(top_srcdir)/configvars

# Make install-libs work.
LIBS = 

default: all

all-here:

dont_install_libs = yes
include $(top_srcdir)/rules $(top_srcdir)/phony

TESTS = bug1 bug2 bug3 bug4 bug5 bug6 bug7 bug8 bug9 bug10 bug11 bug12 \
doprnt errnobug ferror fformat fileno fseek fwrite getln glue iformat \
llformat obstream popen printf printfsz rdwr scanf scanf1 scanf2 \
scanf3 scanf4 scanf5 scanf6 scanf7 scanf8 scanf9 scanf10 scanf11 scanf12 \
stdiomisc temp tmpfile tmpnam ungetc wc-printf xbug

include $(top_srcdir)/checkrules

check-local:

install-include:

uninstall-include:

install-man:

uninstall-man:

