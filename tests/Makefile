TOPDIR=../
include $(TOPDIR)Rules.mak


UFLAGS	=	-nodefaultlibs -nostdinc++ -fno-builtin -L../src
ifeq ($(IMPORT_LIBSUP),y)
ULIBS	=	-luClibc++ -lc
else
ULIBS	=	-luClibc++ -lc -lsupc++
endif

SRCS	=\
	newdel.cpp \
	io.cpp \
	vectortest.cpp \
	stringtest.cpp \
	sstreamtest.cpp \
	dequetest.cpp \
	listtest.cpp \
	maptest.cpp \
	settest.cpp \
	numerictest.cpp \
	hello.cpp \
	bitsettest.cpp


EXOBJS	=\
	listtest.o \
	maptest.o \
	settest.o \
	dequetest.o \
	stringtest.o \
	sstreamtest.o \
	vectortest.o \
	io.o \
	newdel.o \
	numerictest.o \
	hello.o \
	bitsettest.o

ALLOBJS	=	$(EXOBJS) \
		newdel.o-old \
		io.o-old \
		vectortest.o-old \
		stringtest.o-old \
		sstreamtest.o-old \
		listtest.o-old \
		dequetest.o-old \
		maptest.o-old \
		settest.o-old \
		numerictest.o-old \
		bitsettest.o-old

ALLBIN	=	newdel newdel-old \
		io io-old \
		vectortest vectortest-old \
		stringtest stringtest-old \
		sstreamtest sstreamtest-old \
		dequetest dequetest-old \
		maptest maptest-old \
		settest settest-old \
		listtest listtest-old \
		numerictest numerictest-old \
		bitsettest bitsettest-old

ALLTGT	=	bitsettest sstreamtest numerictest settest maptest dequetest listtest stringtest vectortest io newdel

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

cleanall:	cleanobjs cleanbin

hello: $(EXOBJS)
	$(CXX) -o hello hello.o $(CFLAGS) $(UFLAGS) $(LIBS) $(ULIBS)
	$(CXX) -o hello-old hello.o-old $(COFLAGS)

newdel: $(EXOBJS)
	$(CXX) -o newdel newdel.o $(CFLAGS) $(UFLAGS) $(LIBS) $(ULIBS)
	$(CXX) -o newdel-old newdel.o-old $(COFLAGS)

io: $(EXOBJS)
	$(CXX) -o io io.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o io-old io.o-old $(COFLAGS)

vectortest: $(EXOBJS)
	$(CXX) -o vectortest vectortest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o vectortest-old vectortest.o-old $(COFLAGS)

stringtest: $(EXOBJS)
	$(CXX) -o stringtest stringtest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o stringtest-old stringtest.o-old $(COFLAGS)

listtest: $(EXOBJS)
	$(CXX) -o listtest listtest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o listtest-old listtest.o-old $(COFLAGS)

excepttest: $(EXOBJS)
	$(CXX) -o excepttest excepttest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o excepttest-old excepttest.o-old $(COFLAGS)

dequetest: $(EXOBJS)
	$(CXX) -o dequetest dequetest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o dequetest-old dequetest.o-old $(COFLAGS)

maptest: $(EXOBJS)
	$(CXX) -o maptest maptest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o maptest-old maptest.o-old $(COFLAGS)

numerictest: $(EXOBJS)
	$(CXX) -o numerictest numerictest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o numerictest-old numerictest.o-old $(COFLAGS)

sstreamtest: $(EXOBJS)
	$(CXX) -o sstreamtest sstreamtest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o sstreamtest-old sstreamtest.o-old $(COFLAGS)

bitsettest: $(EXOBJS)
	$(CXX) -o bitsettest bitsettest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o bitsettest-old bitsettest.o-old $(COFLAGS)

settest: $(EXOBJS)
	$(CXX) -o settest settest.o $(CFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o settest-old settest.o-old $(COFLAGS)


.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
	$(CXX) -c $(CXXOFLAGS) -o $@-old $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<
