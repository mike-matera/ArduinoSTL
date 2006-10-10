TOPDIR=../../..
include $(TOPDIR)/Rules.mak

all:	libgcc_eh

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
	$(AR) x $(shell CC=$(CC) $(TOPDIR)/scripts/find_libgcc_eh.sh)
#endif
#endif

clean:
	$(RM) *.o

