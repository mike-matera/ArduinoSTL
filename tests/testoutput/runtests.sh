#!/bin/bash

RETURNVALUE=0

for x in *.good ; do
	TEST=$(basename ${x} .good)
	if [ -x ../${TEST} ] ; then
		if [ -f ${TEST}.input ] ; then
			LD_LIBRARY_PATH="../../src" ../${TEST} < ${TEST}.input > ${TEST}.test
		else
			LD_LIBRARY_PATH="../../src" ../${TEST} > ${TEST}.test
		fi
		cmp ${TEST}.good ${TEST}.test
		if [ "$?" -eq "1" ]
		then
			printf "%-25sFAILED\n" ${TEST}
			RETURNVALUE=1
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
		if [ "$?" -eq "1" ]
		then
			printf "%-25sFAILED\n" ${TEST}-old
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
