TOPDIR=../../..
include $(TOPDIR)/Rules.mak

all:	libsupc

libsupc:
#ifeq ($(GCC_VERSION),3.3)
#	echo Version 3.3
#	$(WR_CXX) -c $(CXXFLAGS) -o eh_allocQ.o GCC_3.3/eh_alloc.cc
#
#else
#ifeq ($(GCC_VERSION),3.4)
#	echo Version 3.4
#
#else
#	echo Binary
	$(AR) x $(shell CC=$(CC) $(TOPDIR)/scripts/find_libsupc.sh)
	$(RM) -f new_op*.o del_op*.o pure.o new_handler.o eh_alloc.o eh_globals.o
#
#endif
#endif

clean:
	$(RM) *.o

