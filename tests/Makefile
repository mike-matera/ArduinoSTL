CC  	=	gcc
CXX	=	g++
CFLAGS	=	-Os -g -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic
COFLAGS =	-Os -g -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
CXXOFLAGS=	$(COFLAGS)
INCDIRS	=	-I../include/

UFLAGS	=	-nodefaultlibs -nostdinc++ -fno-builtin -L../src
#ULIBS	=	-luClibc++ -lgcc -lc -lsupc++ -lgcc_s
ifeq ($(IMPORT_LIBSUP),y)
ULIBS	=	-luClibc++ -lc
else
ULIBS	=	-luClibc++ -lc -lsupc++
endif

TOPDIR=../
include $(TOPDIR)Rules.mak

SRCS	=\
	newdel.cpp \
	io.cpp \
	vectortest.cpp \
	stringtest.cpp \
	dequetest.cpp \
	listtest.cpp \
	maptest.cpp \
	excepttest.cpp \
	hello.cpp


EXOBJS	=\
	excepttest.o \
	listtest.o \
	maptest.o \
	dequetest.o \
	stringtest.o \
	vectortest.o \
	io.o \
	newdel.o \
	hello.o

ALLOBJS	=	$(EXOBJS) \
		newdel.o-old \
		io.o-old \
		vectortest.o-old \
		stringtest.o-old \
		listtest.o-old \
		excepttest.o-old \
		dequetest.o-old \
		maptest.o-old

ALLBIN	=	newdel newdel-old \
		io io-old \
		vectortest vectortest-old \
		stringtest stringtest-old \
		dequetest dequetest-old \
		maptest maptest-old \
		listtest listtest-old \
		excepttest excepttest-old

ALLTGT	=	maptest dequetest excepttest listtest stringtest vectortest io newdel

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
	$(CXX) -o hello hello.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(LIBS) $(ULIBS)
	$(CXX) -o hello-old hello.o-old $(COFLAGS)

newdel: $(EXOBJS)
	$(CXX) -o newdel newdel.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(LIBS) $(ULIBS)
	$(CXX) -o newdel-old newdel.o-old $(COFLAGS)

io: $(EXOBJS)
	$(CXX) -o io io.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o io-old io.o-old $(COFLAGS)

vectortest: $(EXOBJS)
	$(CXX) -o vectortest vectortest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o vectortest-old vectortest.o-old $(COFLAGS)

stringtest: $(EXOBJS)
	$(CXX) -o stringtest stringtest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o stringtest-old stringtest.o-old $(COFLAGS)

listtest: $(EXOBJS)
	$(CXX) -o listtest listtest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o listtest-old listtest.o-old $(COFLAGS)

excepttest: $(EXOBJS)
	$(CXX) -o excepttest excepttest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o excepttest-old excepttest.o-old $(COFLAGS)

dequetest: $(EXOBJS)
	$(CXX) -o dequetest dequetest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o dequetest-old dequetest.o-old $(COFLAGS)

maptest: $(EXOBJS)
	$(CXX) -o maptest maptest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o maptest-old maptest.o-old $(COFLAGS)


.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<
	$(CXX) -c $(CXXOFLAGS) -o $@-old $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCDIRS) -o $@ $<
