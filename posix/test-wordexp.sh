#!/bin/sh

# Some of these tests may look a little weird.
# The first parameter to wordexp-test is what it gives to wordexp.
# The others are just there to be parameters.

#common_objpfx=$1; shift
#elf_objpfx=$1; shift
#rtld_installed_name=$1; shift

#: ${TMPDIR=${common_objpfx}posix}
: ${TMPDIR=./}
testout=$TMPDIR/wordexp-test-result

failed=0
# This is written in this funny way so that there is no trailing whitespace.
# The first line contains a space followed by a tab.
IFS=" 	\

"
export IFS

./test-wordexp '$*' > ${testout}1
cat <<"EOF" | cmp - ${testout}1 || failed=1
wordexp returned 0
we_wordv[0] = "$*"
EOF

./test-wordexp '${*}' unquoted > ${testout}2
cat <<"EOF" | cmp - ${testout}2 || failed=1
wordexp returned 0
we_wordv[0] = "${*}"
we_wordv[1] = "unquoted"
EOF

./test-wordexp '$@' unquoted > ${testout}3
cat <<"EOF" | cmp - ${testout}3 || failed=1
wordexp returned 0
we_wordv[0] = "$@"
we_wordv[1] = "unquoted"
EOF

./test-wordexp '"$* quoted"' param > ${testout}4
cat <<"EOF" | cmp - ${testout}4 || failed=1
wordexp returned 0
we_wordv[0] = ""$* quoted" param quoted"
EOF

./test-wordexp '"$@ quoted"' param > ${testout}5
cat <<"EOF" | cmp - ${testout}5 || failed=1
wordexp returned 0
we_wordv[0] = ""$@ quoted""
we_wordv[1] = "param quoted"
EOF
# Why?  Because bash does it that way..

./test-wordexp '$#' 2 3 4 5 > ${testout}6
cat <<"EOF" | cmp - ${testout}6 || failed=1
wordexp returned 0
we_wordv[0] = "5"
EOF

./test-wordexp '$2 ${3} $4' 2nd 3rd "4 th" > ${testout}7
cat <<"EOF" | cmp - ${testout}7 || failed=1
wordexp returned 0
we_wordv[0] = "2nd"
we_wordv[1] = "3rd"
we_wordv[2] = "4"
we_wordv[3] = "th"
EOF

./test-wordexp '${11}' 2 3 4 5 6 7 8 9 10 11 > ${testout}8
cat <<"EOF" | cmp - ${testout}8 || failed=1
wordexp returned 0
we_wordv[0] = "11"
EOF

./test-wordexp '"a $@ b"' c d > ${testout}9
cat <<"EOF" | cmp - ${testout}9 || failed=1
wordexp returned 0
we_wordv[0] = "a "a $@ b""
we_wordv[1] = "c"
we_wordv[2] = "d b"
EOF

./test-wordexp '${#@} ${#2} *$**' two 3 4 > ${testout}10
cat <<"EOF" | cmp - ${testout}10 || failed=1
wordexp returned 0
we_wordv[0] = "4"
we_wordv[1] = "3"
we_wordv[2] = "*${#@}"
we_wordv[3] = "${#2}"
we_wordv[4] = "*$**"
we_wordv[5] = "two"
we_wordv[6] = "3"
we_wordv[7] = "4*"
EOF

test $failed = 0 && rm ${testout}[1-9]*

exit $failed
