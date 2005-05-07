LIBS	=	-lc -lgcc_s
ifneq ($(IMPORT_LIBSUP),y)
LIBS	+= -lsupc++
endif

TOPDIR=../
include $(TOPDIR)Rules.mak

SRCS	=\
	new_op.cpp \
	new_opv.cpp \
	new_opnt.cpp \
	new_opvnt.cpp \
	del_op.cpp \
	del_opv.cpp \
	del_opnt.cpp \
	del_opvnt.cpp \
	exception.cpp \
	abi/abi.cpp \
	char_traits.cpp \
	string.cpp \
	fstream.cpp \
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
	iomanip.cpp \
	vector.cpp \
	deque.cpp \
	list.cpp \
	map.cpp \
	set.cpp \
	stack.cpp \
	queue.cpp \
	algorithm.cpp \
	numeric.cpp \
	sstream.cpp \
	bitset.cpp \
	valarray.cpp \
	complex.cpp


EXOBJS	=$(patsubst %.cpp,%.o, $(SRCS))

ALLOBJS	=	$(EXOBJS)
ALLBIN	=	
ifeq ($(BUILD_STATIC_LIB),y)
ALLBIN	+=	libuClibc++.a
endif
ifneq ($(BUILD_ONLY_STATIC_LIB),y)
ALLBIN	+=	libuClibc++.so
endif

# User defines:

all:	libgcc_eh libsupc $(ALLOBJS) $(ALLBIN)

objs:	$(ALLOBJS)

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
ifneq ($(BUILD_ONLY_STATIC_LIB),y)
	$(INSTALL) -m 644 lib*.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) \
		$(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
	cp -fa *.so $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
	cp -fa *.so.$(MAJOR_VERSION) $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
	cp -fa *.so.$(MAJOR_VERSION).$(MINOR_VERSION) $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
endif
ifeq ($(BUILD_STATIC_LIB),y)
	$(INSTALL) -m 644 libuClibc++.a $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
endif


libgcc_eh:
	$(MAKE) -C abi/libgcc_eh all
GCCOBJS = $(wildcard abi/libgcc_eh/*.o)

libsupc:
ifeq ($(IMPORT_LIBSUP),y)
	$(MAKE) -C abi/libsupc all
SUPOBJS = $(wildcard abi/libsupc/*.o)
else
SUPOBJS =
endif


libuClibc++.a: libgcc_eh libsupc
	$(AR) rcs libuClibc++.a $(EXOBJS) $(GCCOBJS) $(SUPOBJS)

libuClibc++.so: libsupc
	$(CC) -shared -Wl,-z,defs $(CFLAGS) $(EXOBJS) $(SUPOBJS) \
		-o libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) \
		-Wl,-soname,libuClibc++.so.$(MAJOR_VERSION) $(LIBS)
	ln -s -f libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION)
	ln -s -f libuClibc++.so.$(MAJOR_VERSION).$(MINOR_VERSION) libuClibc++.so.$(MAJOR_VERSION)
	ln -s -f libuClibc++.so.$(MAJOR_VERSION) libuClibc++.so

cleanobjs:
	$(MAKE) -C abi/libgcc_eh clean
	$(MAKE) -C abi/libsupc clean
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin
	rm -f libuClibc++*
	rm -rf libsupc libgcc_eh
	

cleanall:	cleanobjs cleanbin

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
