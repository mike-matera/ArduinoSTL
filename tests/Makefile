TOPDIR=../
include $(TOPDIR)Rules.mak

#COFLAGS = -fno-rtti -fno-exceptions -static

CXXOFLAGS = -O0

ifeq ($(IMPORT_LIBSUP),y)
ULIBS = -luClibc++ -lc
else
ULIBS = -luClibc++ -lc -lsupc++
endif


UCXX	= $(CXX) -nodefaultlibs -nostdinc++ -fno-builtin -I../include -L../src

UFLAGS	=	-L../src

SRCS	=\
	newdel.cpp \
	io.cpp \
	vectortest.cpp \
	stringtest.cpp \
	sstreamtest.cpp \
	dequetest.cpp \
	listtest.cpp \
	maptest.cpp \
	mmaptest.cpp \
	settest.cpp \
	numerictest.cpp \
	bitsettest.cpp \
	algotest.cpp \
	stacktest.cpp \
	streamitertest.cpp \
	fstreamtest.cpp \
	wchartest.cpp


EXOBJS	=\
	listtest.o \
	maptest.o \
	mmaptest.o \
	settest.o \
	dequetest.o \
	stringtest.o \
	sstreamtest.o \
	vectortest.o \
	io.o \
	newdel.o \
	numerictest.o \
	bitsettest.o \
	algotest.o \
	stacktest.o \
	streamitertest.o \
	fstreamtest.o \
	wchartest.o

ALLOBJS	=	$(EXOBJS) \
		newdel.o-old \
		io.o-old \
		vectortest.o-old \
		stringtest.o-old \
		sstreamtest.o-old \
		listtest.o-old \
		dequetest.o-old \
		maptest.o-old \
		mmaptest.o-old \
		settest.o-old \
		numerictest.o-old \
		bitsettest.o-old \
		algotest.o-old \
		stacktest.o-old \
		streamitertest.o-old \
		fstreamtest.o-old \
		wchartest.o-old

ALLBIN	=	newdel newdel-old \
		io io-old \
		vectortest vectortest-old \
		stringtest stringtest-old \
		sstreamtest sstreamtest-old \
		dequetest dequetest-old \
		maptest maptest-old \
		mmaptest mmaptest-old \
		settest settest-old \
		listtest listtest-old \
		numerictest numerictest-old \
		bitsettest bitsettest-old \
		algotest algotest-old \
		stacktest stacktest-old \
		streamitertest streamitertest-old \
		fstreamtest fstreamtest-old \
		wchartest wchartest-old

ALLTGT	=	streamitertest \
		stacktest \
		algotest \
		bitsettest \
		sstreamtest \
		numerictest \
		settest \
		mmaptest \
		maptest \
		dequetest \
		listtest \
		stringtest \
		vectortest \
		io \
		newdel \
		fstreamtest \
		wchartest

ifeq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
SRCS    += excepttest.cpp
EXOBJS	+= excepttest.o
ALLOBJS	+= excepttest.o excepttest.o-old
ALLBIN	+= excepttest excepttest-old
ALLTGT	+= excepttest
endif


# User defines:

all:	$(ALLTGT)

objs:	$(ALLOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin
	$(MAKE) -C testoutput clean
	rm -f fstreamtest.out
	rm -f fstreamtest2.out

cleanall:	cleanobjs cleanbin

test:	all
	$(MAKE) -C testoutput test

newdel: $(EXOBJS)
	$(UCXX) -o newdel newdel.o $(CXXFLAGS) $(UFLAGS) $(LIBS) $(ULIBS)
	$(CXX) -o newdel-old newdel.o-old $(COFLAGS)

io: $(EXOBJS)
	$(UCXX) -o io io.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o io-old io.o-old $(COFLAGS)

vectortest: $(EXOBJS)
	$(UCXX) -o vectortest vectortest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o vectortest-old vectortest.o-old $(COFLAGS)

stringtest: $(EXOBJS)
	$(UCXX) -o stringtest stringtest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o stringtest-old stringtest.o-old $(COFLAGS)

listtest: $(EXOBJS)
	$(UCXX) -o listtest listtest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o listtest-old listtest.o-old $(COFLAGS)

excepttest: $(EXOBJS)
	$(UCXX) -o excepttest excepttest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o excepttest-old excepttest.o-old $(COFLAGS)

dequetest: $(EXOBJS)
	$(UCXX) -o dequetest dequetest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o dequetest-old dequetest.o-old $(COFLAGS)

maptest: $(EXOBJS)
	$(UCXX) -o maptest maptest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o maptest-old maptest.o-old $(COFLAGS)

numerictest: $(EXOBJS)
	$(UCXX) -o numerictest numerictest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o numerictest-old numerictest.o-old $(COFLAGS)

sstreamtest: $(EXOBJS)
	$(UCXX) -o sstreamtest sstreamtest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o sstreamtest-old sstreamtest.o-old $(COFLAGS)

bitsettest: $(EXOBJS)
	$(UCXX) -o bitsettest bitsettest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o bitsettest-old bitsettest.o-old $(COFLAGS)

settest: $(EXOBJS)
	$(UCXX) -o settest settest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o settest-old settest.o-old $(COFLAGS)

mmaptest: $(EXOBJS)
	$(UCXX) -o mmaptest mmaptest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o mmaptest-old mmaptest.o-old $(COFLAGS)

algotest: $(EXOBJS)
	$(UCXX) -o algotest algotest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o algotest-old algotest.o-old $(COFLAGS)

stacktest: $(EXOBJS)
	$(UCXX) -o stacktest stacktest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o stacktest-old stacktest.o-old $(COFLAGS)

streamitertest: $(EXOBJS)
	$(UCXX) -o streamitertest streamitertest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o streamitertest-old streamitertest.o-old $(COFLAGS)

fstreamtest: $(EXOBJS)
	$(UCXX) -o fstreamtest fstreamtest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o fstreamtest-old fstreamtest.o-old $(COFLAGS)

wchartest: $(EXOBJS)
	$(UCXX) -o wchartest wchartest.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o wchartest-old wchartest.o-old $(COFLAGS)



.cpp.o:
	$(UCXX) -c $(CXXFLAGS) -o $@ $<
	$(CXX) -c $(CXXOFLAGS) -o $@-old $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<
