CC  	=	distcc gcc
CXX	=	distcc g++
#CFLAGS	=	-O2 -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -march=athlon-xp -I../include -nostdinc++ -fPIC -Weffc++ -ansi
CFLAGS	=	-Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -march=athlon-xp -I../include -nostdinc++ -fPIC -ansi
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
LIBS	=	-lc -lgcc_s -lsupc++ -lm
SRCS	=\
	new.cpp \
	string.cpp \
	iostream.cpp \
	ios.cpp \
	stdexcept.cpp \
	func_exception.cpp \
	locale.cpp \
	streambuf.cpp \
	istream.cpp \
	ostream.cpp \
	iterator.cpp \
	fstream.cpp \
	vector.cpp


EXOBJS	=\
	new.o \
	string.o \
	iostream.o \
	ios.o \
	stdexcept.o \
	func_exception.o \
	locale.o \
	streambuf.o \
	istream.o \
	ostream.o \
	iterator.o \
	fstream.o \
	vector.o

ALLOBJS	=	$(EXOBJS)
ALLBIN	=	libuClibc++.so libuClibc++.a
ALLTGT	=	libuClibc++

# User defines:

all:	$(ALLOBJS) $(ALLTGT)

objs:	$(ALLOBJS)

libuClibc++:	$(ALLOBJS)
#	ar rcs libuClibc++.a $(EXOBJS)
	gcc -shared -o libuClibc++.so $(CFLAGS) $(LIBS) $(EXOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

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
