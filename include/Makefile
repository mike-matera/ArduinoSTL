MAKE	=	make
CC  	=	gcc
CXX	=	g++
CFLAGS	=	-O2 -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -march=athlon-xp -I../include
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
LIBS	=
SUBDIRS =	
SRCS	=
EXOBJS	=
ALLOBJS	=	$(EXOBJS)
ALLBIN	=	
ALLTGT	=	

# User defines:

all:

objs:	$(ALLOBJS)

cleanobjs:

cleanbin:

clean:	cleanobjs cleanbin

cleanall:	cleanobjs cleanbin

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<
