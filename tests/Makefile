TOPDIR=../
include $(TOPDIR)Rules.mak

INCDIRS	=	-I../include/

UFLAGS	=	-nodefaultlibs -nostdinc++ -fno-builtin -L../src
#ULIBS	=	-luClibc++ -lgcc -lc -lsupc++ -lgcc_s
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
	dequetest.cpp \
	listtest.cpp \
	maptest.cpp \
	numerictest.cpp \
	hello.cpp 


EXOBJS	=\
	listtest.o \
	maptest.o \
	dequetest.o \
	stringtest.o \
	vectortest.o \
	io.o \
	newdel.o \
	numerictest.o \
	hello.o

ALLOBJS	=	$(EXOBJS) \
		newdel.o-old \
		io.o-old \
		vectortest.o-old \
		stringtest.o-old \
		listtest.o-old \
		dequetest.o-old \
		maptest.o-old \
		numerictest.o-old

ALLBIN	=	newdel newdel-old \
		io io-old \
		vectortest vectortest-old \
		stringtest stringtest-old \
		dequetest dequetest-old \
		maptest maptest-old \
		listtest listtest-old \
		numerictest numerictest-old

ALLTGT	=	numerictest maptest dequetest listtest stringtest vectortest io newdel

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

numerictest: $(EXOBJS)
	$(CXX) -o numerictest numerictest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o numerictest-old numerictest.o-old $(COFLAGS)


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
