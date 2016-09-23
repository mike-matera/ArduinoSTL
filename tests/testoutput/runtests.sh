#!/bin/sh

RETURNVALUE=0

case "$V" in
	1|2) DODIFF=1 ;;
	*) DODIFF=0 ;;
esac

for x in *.good ; do
	TEST=$(basename ${x} .good)
	if [ -x ../${TEST} ] ; then
		if [ -f ${TEST}.input ] ; then
			LD_LIBRARY_PATH="../../src" ${SIM} ../${TEST} < ${TEST}.input > ${TEST}.test
		else
			LD_LIBRARY_PATH="../../src" ${SIM} ../${TEST} > ${TEST}.test
		fi
		cmp ${TEST}.good ${TEST}.test
		if [ $? -eq 1 ] ; then
			printf "%-25sFAILED\n" ${TEST}
			RETURNVALUE=1
			[ $DODIFF -eq 1 ] && diff -a -u ${TEST}.good ${TEST}.test
		else
			printf "%-25sOK\n" ${TEST}
		fi
	else
		printf "%-25smissing/not built\n" ${TEST}
	fi
done

if [ "$1" = "DODEBUG" ] ; then
  for x in *.good ; do
  	TEST=$(basename ${x} .good)
	if [ -x ../${TEST}-old ] ; then
		if [ -f ${TEST}.input ] ; then
			../${TEST}-old < ${TEST}.input > ${TEST}-old.test
		else
			../${TEST}-old > ${TEST}-old.test
		fi
		cmp ${TEST}.good ${TEST}-old.test
		if [ $? -eq 1 ] ; then
			printf "%-25sFAILED\n" ${TEST}-old
			[ $DODIFF -eq 1 ] && diff -a -u ${TEST}.good ${TEST}-old.test
			RETURNVALUE=1
		else
			printf "%-25sOK\n" ${TEST}-old
		fi
	else
		printf "%-25smissing/not built\n" ${TEST}-old
	fi
  done
fi

exit $RETURNVALUE
