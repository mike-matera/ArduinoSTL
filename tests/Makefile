CC  	=	gcc
CXX	=	g++
CFLAGS	=	-Os -g -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -march=athlon-xp
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
INCDIRS	=	-I../include/

UFLAGS	=	-nodefaultlibs -nostdinc++ -fno-builtin -L../src
ULIBS	=	-luClibc++ -lgcc -lc -lsupc++ -lgcc_s

SRCS	=\
	newdel.cpp \
	io.cpp \
	vectortest.cpp


EXOBJS	=\
	newdel.o \
	io.o \
	vectortest.o

ALLOBJS	=	$(EXOBJS) newdel.o-old io.o-old vectortest.o-old
ALLBIN	=	newdel newdel-old io io-old vectortest vectortest-old
ALLTGT	=	newdel io vectortest

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
	$(CXX) -o hello-old hello.o-old $(CFLAGS)

newdel: $(EXOBJS)
	$(CXX) -o newdel newdel.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(LIBS) $(ULIBS)
	$(CXX) -o newdel-old newdel.o-old $(CFLAGS)

io: $(EXOBJS)
	$(CXX) -o io io.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o io-old io.o-old $(CFLAGS)

vectortest: $(EXOBJS)
	$(CXX) -o vectortest vectortest.o $(CFLAGS) $(UFLAGS) $(INCDIRS) $(ULIBS)
	$(CXX) -o vectortest-old vectortest.o-old $(CFLAGS)



.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<
	$(CXX) -c $(CXXFLAGS) -o $@-old $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCDIRS) -o $@ $<
