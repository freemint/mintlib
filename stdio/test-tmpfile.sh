#! /bin/sh

MAGIC="Magic number is $$"

./test-tmpfile "$MAGIC" || exit 1

# Now search through all temporary directory for orphans.
tempdirs=`echo "$TMP /tmp /usr/tmp $TEMP $TMPDIR" | tr ' ' '\n' \
	| sort | uniq | tr '\n' ' '`

status=0
for dir in $tempdirs; do
	test -d $dir || continue
	for file in $dir/*; do
		test ! -f $file && continue
		grep -q '^'"$MAGIC"'$' $file 2>/dev/null
		retval=$?
		if test $retval = 0; then
			status=1
			echo "test-tmpfile left orphan $file" 1>&2
		fi
	done
done

exit $status
