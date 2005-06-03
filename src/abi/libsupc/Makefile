TOPDIR=../../../
include $(TOPDIR)Rules.mak

#GCC_VERSION = $(shell $(CXX) -dumpversion | cut -c1-3)

all:	libsupc

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
	$(RM) new_op*.o del_op*.o pure.o
#
#endif
#endif

clean:
	$(RM) *.o

