TOPDIR=../../../
include $(TOPDIR)Rules.mak

GCC_VERSION = $(shell $(CXX) -dumpversion | cut -c1-3)

SRCS	=

EXOBJS	=$(patsubst %.cpp,%.o, $(SRCS))

ALLOBJS	=       $(EXOBJS)
ALLBIN	=
# User defines:

all:	libsupc $(ALLOBJS) $(ALLBIN)

objs:	$(ALLOBJS)

libsupc:
#ifeq ($(GCC_VERSION),3.3)
#	echo Version 3.3
#	$(CXX) -c $(CXXFLAGS) -o eh_allocQ.o GCC_3.3/eh_alloc.cc
#
#else
#ifeq ($(GCC_VERSION),3.4)
#	echo Version 3.4
#
#else
#	echo Binary
	$(AR) x $(shell $(CXX) -print-file-name=libsupc++.a)
	rm -f new_op*.o del_op*.o pure.o
#
#endif
#endif



cleanobjs:
	rm -f *.o
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin


cleanall:	cleanobjs cleanbin

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<
