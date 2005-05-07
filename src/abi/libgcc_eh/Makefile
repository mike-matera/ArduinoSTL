TOPDIR=../../../
include $(TOPDIR)Rules.mak

SRCS	=

EXOBJS	=$(patsubst %.cpp,%.o, $(SRCS))

ALLOBJS	=       $(EXOBJS)
ALLBIN	=


GCC_VERSION = $(shell $(CXX) -dumpversion | cut -c1-3)

# User defines:

all:	libgcc_eh

objs:	$(ALLOBJS)


libgcc_eh: unwind-c.o

unwind-c.o:
#ifeq ($(GCC_VERSION),3.3)
#	echo Version 3.3
#	$(CC) -c $(CFLAGS) -o unwind-c.o GCC_3.3/unwind-c.c
#
#else
#ifeq ($(GCC_VERSION),3.4)
#	echo Version 3.4
#
#else
#	echo Binary
	$(AR) x $(shell $(CC) -print-file-name=libgcc_eh.a)
#endif
#endif

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:  cleanobjs cleanbin
	rm -rf *.o

cleanall:	cleanobjs cleanbin

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
