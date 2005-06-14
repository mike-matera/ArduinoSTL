TOPDIR=../../../
include $(TOPDIR)Rules.mak

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
	$(AR) x $(shell $(CC) -print-file-name=libgcc_eh.a)
#endif
#endif

clean:
	$(RM) *.o

