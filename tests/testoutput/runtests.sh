#!/bin/bash


#Test of newdel

LD_LIBRARY_PATH="../../src" ../newdel > newdel.test
cmp newdel.good newdel.test
if [ "$?" -eq "1" ]
then
	echo "newdel test           FAILED"
	exit 1;
else
	echo "newdel test           OK"
fi


#Test of io

LD_LIBRARY_PATH="../../src" ../io < io.input > io.test
cmp io.good io.test
if [ "$?" -eq "1" ]
then
	echo "io test               FAILED"
	exit 1;
else
	echo "io test               OK"
fi


#Test of excepttest

LD_LIBRARY_PATH="../../src" ../excepttest > excepttest.test
cmp excepttest.good excepttest.test
if [ "$?" -eq "1" ]
then
	echo "excepttest test       FAILED"
	exit 1;
else
	echo "excepttest test       OK"
fi


#Test of vectortest

LD_LIBRARY_PATH="../../src" ../vectortest > vectortest.test
cmp vectortest.good vectortest.test
if [ "$?" -eq "1" ]
then
	echo "vectortest test       FAILED"
	exit 1;
else
	echo "vectortest test       OK"
fi


#Test of stringtest

LD_LIBRARY_PATH="../../src" ../stringtest < stringtest.input > stringtest.test
cmp stringtest.good stringtest.test
if [ "$?" -eq "1" ]
then
	echo "stringtest test       FAILED"
	exit 1;
else
	echo "stringtest test       OK"
fi

#Test of dequetest

LD_LIBRARY_PATH="../../src" ../dequetest > dequetest.test
cmp dequetest.good dequetest.test
if [ "$?" -eq "1" ]
then
	echo "dequetest test        FAILED"
	exit 1;
else
	echo "dequetest test        OK"
fi


#Test of listtest

LD_LIBRARY_PATH="../../src" ../listtest > listtest.test
cmp listtest.good listtest.test
if [ "$?" -eq "1" ]
then
	echo "listtest test         FAILED"
	exit 1;
else
	echo "listtest test         OK"
fi


#Test of maptest

LD_LIBRARY_PATH="../../src" ../maptest > maptest.test
cmp maptest.good maptest.test
if [ "$?" -eq "1" ]
then
	echo "maptest test          FAILED"
	exit 1;
else
	echo "maptest test          OK"
fi



#Test of mmaptest

LD_LIBRARY_PATH="../../src" ../mmaptest > mmaptest.test
cmp mmaptest.good mmaptest.test
if [ "$?" -eq "1" ]
then
	echo "mmaptest test         FAILED"
	exit 1;
else
	echo "mmaptest test         OK"
fi


#Test of settest

LD_LIBRARY_PATH="../../src" ../settest > settest.test
cmp settest.good settest.test
if [ "$?" -eq "1" ]
then
	echo "settest test          FAILED"
	exit 1;
else
	echo "settest test          OK"
fi



#Test of stacktest

LD_LIBRARY_PATH="../../src" ../stacktest > stacktest.test
cmp stacktest.good stacktest.test
if [ "$?" -eq "1" ]
then
	echo "stacktest test        FAILED"
	exit 1;
else
	echo "stacktest test        OK"
fi


#Test of sstreamtest

LD_LIBRARY_PATH="../../src" ../sstreamtest > sstreamtest.test
cmp sstreamtest.good sstreamtest.test
if [ "$?" -eq "1" ]
then
	echo "sstreamtest test      FAILED"
	exit 1;
else
	echo "sstreamtest test      OK"
fi


#Test of fstreamtest

LD_LIBRARY_PATH="../../src" ../fstreamtest > fstreamtest.test
cmp fstreamtest.good fstreamtest.test
if [ "$?" -eq "1" ]
then
	echo "fstreamtest test      FAILED"
	exit 1;
else
	echo "fstreamtest test      OK"
fi



#Test of bitsettest

LD_LIBRARY_PATH="../../src" ../bitsettest > bitsettest.test
cmp bitsettest.good bitsettest.test
if [ "$?" -eq "1" ]
then
	echo "bitsettest test       FAILED"
	exit 1;
else
	echo "bitsettest test       OK"
fi



