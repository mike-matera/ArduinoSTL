TOPDIR=../
include $(TOPDIR)Rules.mak

WR_CXX := WRAPPER_INCLUDEDIR=-I$(TOPDIR)include WRAPPER_LIBDIR=-L$(TOPDIR)src $(TOPDIR)bin/g++-uc

CXXOFLAGS := -Wall -pedantic -O0 -g3 -ansi $(EH_CXXFLAGS)

TEST_SRCS	:= $(wildcard *test.cpp)

ifneq ($(UCLIBCXX_HAS_WCHAR),y)
TEST_SRCS	:= $(filter-out wchartest.cpp,$(TEST_SRCS))
endif

ifneq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
TEST_SRCS    := $(filter-out excepttest.cpp,$(TEST_SRCS))
endif

EXOBJS	:= $(patsubst %.cpp,%.o, $(TEST_SRCS))

OLDOBJS	:= $(patsubst %.cpp,%-old.o, $(TEST_SRCS))

ALLBIN	:= $(patsubst %.cpp,%, $(TEST_SRCS))

OLDBIN	:= $(patsubst %.cpp,%-old, $(TEST_SRCS))

ifeq ($(DODEBUG),y)
all:	$(ALLBIN) $(OLDBIN)
else
all:	$(ALLBIN)
endif

clean:
	$(RM) $(ALLBIN) $(OLDBIN)
	$(RM) *.o *.o-old core
	$(MAKE) -C testoutput clean

test:	all
	$(MAKE) -C testoutput test

$(ALLBIN): $(EXOBJS)
	$(WR_CXX) $(LDFLAGS) -o $@ $@.o

$(OLDBIN): $(OLDOBJS)
	$(HOSTCXX) $(LDFLAGS) -o $@ $@.o

$(EXOBJS): %.o : %.cpp
	$(WR_CXX) $(CXXFLAGS) -o $@ -c $<

$(OLDOBJS): %-old.o : %.cpp
	$(HOSTCXX) $(CXXOFLAGS) -o $@ -c $<

