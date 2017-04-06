[![Build Status](https://travis-ci.org/mikrosk/mintlib.svg?branch=master)](https://travis-ci.org/mikrosk/mintlib)

This is the MiNTLib.  The MiNTLib is the standard libc for FreeMiNT.
It will also work to some extent on non-MiNT systems, it tries its 
best to emulate MiNT-calls on these systems.

On FreeMiNT systems the MiNTLib provides a programming interface that
is close to real *nix systems.  It will either emulate system calls
or map them into GEMDOS- resp. FreeMiNT-calls.

The file LICENSES tells you what you are allowed to do with the MiNTLib
and what you are not allowed to do.  If you plan to use the MiNTLib in
a commercial way you have to read that file thoroughly.  You are a 
commercial user if you sell a product that is build with the help of 
the MiNTLib.  You are also a commercial user if you demand or expect
some financial equivalent for your product, no matter if you call your
special license agreement "shareware", "trialware", "fairware" or
whatevr.  The name doesn't matter, as soon as you ask for money, you
are a commercial user.

Read the file ChangeLog if you want to know in detail what has changed 
since MiNTLib patchlevel 49.  Read the file NEWS if you want a brief
overview of new features.  The file AUTHORS contains a list of people
that have contributed code to the MiNTLib or have sacrificed their
time in another way to keep the project going.  The file BUGS contains
a (not exhaustive) list of known bugs, shortcomings, caveats of the
MiNTLib.  FAQ answers some frequently asked questions.

Before you install the MiNTLib, please read the file INSTALL.  It will
give you detailed information for that issue.  The file configvars should
actually be the only file you have to edit if you want to tailor the
MiNTLib buildprocess to your needs, see INSTALL for details.

If you want to contribute code or bugfixes to the MiNTLib you are welcome.
Please read the file HACKING before you start editing!

All files not mentioned are not intended for the end-user.  They are 
mainly help files for the individual Makefiles in the subdirectories.
Don't edit them.

Have fun with the MiNTLib!

Guido <guido@freemint.de>
