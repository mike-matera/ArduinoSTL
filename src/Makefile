#LIBS	=	-lc -lgcc_s -lm
LIBS	=	-lc -lgcc_s

TOPDIR=../
include $(TOPDIR)Rules.mak

SRCS	=\
	new.cpp \
	exception.cpp \
	abi/abi.cpp \
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
	map.cpp \
	stack.cpp \
	queue.cpp \
	algorithm.cpp \
	numeric.cpp


EXOBJS	=\
	new.o \
	exception.o \
	abi/abi.o \
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
	map.o \
	stack.o \
	queue.o \
	algorithm.o \
	numeric.o

ALLOBJS	=	$(EXOBJS)
ALLBIN	=	libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) libuClibc++.a
ALLTGT	=	libuClibc++

ifeq ($(IMPORT_LIBSUP),y)
SUPOBJS	=	$(LIBSUP_PATH)
else
SUPOBJS =
endif

# User defines:

all:	$(ALLOBJS) $(ALLTGT)

objs:	$(ALLOBJS)

libuClibc++:	$(ALLOBJS)
	ar rcs libuClibc++.a $(EXOBJS)
	gcc -shared -o libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) $(CFLAGS) $(LIBS) $(EXOBJS) $(SUPOBJS)
	ln -s -f libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION)
	ln -s -f libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION) libuClibc++.so.$(MAJOR_VERSION)
	ln -s -f libuClibc++.so.$(MAJOR_VERSION) libuClibc++.so

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin
	rm -f libuClibc++*

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
