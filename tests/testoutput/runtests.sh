#!/bin/bash

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
			echo "${TEST} 	FAILED"
			exit 1
		else
			echo "${TEST} 	OK"
		fi
	else
		echo "${TEST}	missing/not built"
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
			echo "${TEST}-old 	FAILED"
			exit 1
		else
			echo "${TEST}-old 	OK"
		fi
	else
		echo "${TEST}-old	missing/not built"
	fi
  done
fi
