TOPDIR=../
include $(TOPDIR)Rules.mak

CXXOFLAGS = -O0 -g3 -ansi -fPIC

ifeq ($(IMPORT_LIBSUP),y)
ULIBS = -luClibc++ -lc
else
ULIBS = -luClibc++ -lc -lsupc++
endif

UCXX	= $(CXX) -nodefaultlibs -nostdinc++ -fno-builtin -I$(TOPDIR)/include -L$(TOPDIR)/src

UFLAGS	=	-L$(TOPDIR)/src

SRCS	= $(wildcard *.cpp)

ifneq ($(UCLIBCXX_HAS_WCHAR),y)
SRCS	:= $(filter-out wchartest.cpp,$(SRCS))
endif

ifneq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
SRCS    := $(filter-out excepttest.cpp,$(SRCS))
endif


EXOBJS  =$(patsubst %.cpp,%.o, $(SRCS))

ALLOBJS	=	$(EXOBJS) $(patsubst %.cpp,%.o-old, $(SRCS))

ALLBIN	=	$(patsubst %.cpp,%, $(SRCS)) $(patsubst %.cpp,%-old, $(SRCS))

ALLTGT	=	$(patsubst %.cpp,%, $(SRCS))


# User defines:

all:	$(ALLTGT)

objs:	$(ALLOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin
	$(MAKE) -C testoutput clean
	rm -f fstreamtest.out
	rm -f fstreamtest2.out

test:	all
	$(MAKE) -C testoutput test


$(ALLTGT): $(EXOBJS)
	$(UCXX) -o $@ $@.o $(CXXFLAGS) $(UFLAGS) $(ULIBS)
	$(CXX) -o $@-old $@.o-old $(COFLAGS)

.cpp.o:
	$(UCXX) -c $(CXXFLAGS) -o $@ $<
	$(CXX) -c $(CXXOFLAGS) -o $@-old $<
