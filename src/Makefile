CC  	=	distcc gcc
CXX	=	distcc g++
#CFLAGS	=	-O2 -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -I../include -nostdinc++ -fPIC -Weffc++ -ansi
CFLAGS	=	-Os -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -I../include -nostdinc++ -fPIC -ansi
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
LIBS	=	-lc -lgcc_s -lm
SRCS	=\
	new.cpp \
	exception.cpp \
	char_traits.cpp \
	string.cpp \
	iostream.cpp \
	ios.cpp \
	utility.cpp \
	stdexcept.cpp \
	func_exception.cpp \
	locale.cpp \
	streambuf.cpp \
	istream.cpp \
	ostream.cpp \
	iterator.cpp \
	fstream.cpp \
	vector.cpp \
	deque.cpp \
	list.cpp \
	map.cpp


EXOBJS	=\
	new.o \
	exception.o \
	char_traits.o \
	string.o \
	iostream.o \
	ios.o \
	utility.o \
	stdexcept.o \
	func_exception.o \
	locale.o \
	streambuf.o \
	istream.o \
	ostream.o \
	iterator.o \
	fstream.o \
	vector.o \
	deque.o \
	list.o \
	map.o

ALLOBJS	=	$(EXOBJS)
ALLBIN	=	libuClibc++.so libuClibc++.a
ALLTGT	=	libuClibc++

SUPOBJS	=	/usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.4/libsupc++.a

# User defines:

all:	$(ALLOBJS) $(ALLTGT)

objs:	$(ALLOBJS)

libuClibc++:	$(ALLOBJS)
#	ar rcs libuClibc++.a $(EXOBJS)
	gcc -shared -o libuClibc++.so $(CFLAGS) $(LIBS) $(EXOBJS) $(SUPOBJS)

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
