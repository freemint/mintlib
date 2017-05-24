#!/bin/sh

TMP="$1"
OUT="$2"

VERSION="$(grep VERSION configvars | sed -e 's/VERSION=//;')"-"${SHORT_ID}"
make SHELL=/bin/bash CROSS=yes

make SHELL=/bin/bash CROSS=yes prefix="${TMP}" install
find "${TMP}" -type f -perm -a=x -exec m68k-atari-mint-strip -s {} \;
find "${TMP}" -type f \( -name '*.a' -o -name '*.o' \) -exec m68k-atari-mint-strip -S -x {} \;
mkdir -p "${OUT}" && cd "${TMP}" && tar cjf "${OUT}/${PROJECT}-${VERSION}.tar.bz2" *
