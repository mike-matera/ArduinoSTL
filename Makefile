MAKE	=	make
CC  	=	gcc
CXX	=	g++
CFLAGS	=	-O2 -g -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -march=athlon-xp -I../include
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
LIBS	=
SUBDIRS =	include src tests
SRCS	=
EXOBJS	=
ALLOBJS	=	$(EXOBJS)
ALLBIN	=	
ALLTGT	=	

# User defines:

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir all; \
	done

objs:	$(ALLOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done


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
