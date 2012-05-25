TOPDIR=../
include $(TOPDIR)Rules.mak

WR_CXX := WRAPPER_INCLUDEDIR=-I$(TOPDIR)include WRAPPER_LIBDIR=-L$(TOPDIR)src $(TOPDIR)bin/g++-uc

CXXOFLAGS := -Wall -pedantic -Os -g3 -ansi $(EH_CXXFLAGS)

TEST_SRCS	:= $(wildcard *test.cpp)
UTILITY_SRCS	:= testframework.cpp

ifneq ($(UCLIBCXX_HAS_WCHAR),y)
TEST_SRCS	:= $(filter-out wchartest.cpp,$(TEST_SRCS))
endif

ifneq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
TEST_SRCS	:= $(filter-out excepttest.cpp,$(TEST_SRCS))
endif

UTILITY_OBJS	:= $(patsubst %.cpp,%.o, $(UTILITY_SRCS))
OLDUTILITY_OBJS	:= $(patsubst %.cpp,%-old.o, $(UTILITY_SRCS))

EXOBJS		:= $(patsubst %.cpp,%.o, $(TEST_SRCS))
OLDOBJS		:= $(patsubst %.cpp,%-old.o, $(TEST_SRCS))

ALLBIN	:= $(patsubst %.cpp,%, $(TEST_SRCS))

OLDBIN	:= $(patsubst %.cpp,%-old, $(TEST_SRCS))

LDFLAGS-valarraytest := -lm

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

$(ALLBIN): $(EXOBJS) $(UTILITY_OBJS)
	$(WR_CXX) $(LDFLAGS) $(UTILITY_OBJS) -o $@ $@.o $(LDFLAGS-$(notdir $(@)))

$(OLDBIN): $(OLDOBJS) $(OLDUTILITY_OBJS)
	$(HOSTCXX) $(LDFLAGS) $(UTILITY_OBJS) -o $@ $@.o $(LDFLAGS-$(notdir $(@)))

$(EXOBJS): %.o : %.cpp
	$(WR_CXX) $(CXXFLAGS) $(CXXFLAGS-$(notdir $(*))) -o $@ -c $<

$(OLDOBJS): %-old.o : %.cpp
	$(HOSTCXX) $(CXXFLAGS) $(CXXFLAGS-$(notdir $(*))) -o $@ -c $<

$(UTILITY_OBJS): %.o : %.cpp
	$(WR_CXX) $(CXXFLAGS) -o $@ -c $<

$(OLDUTILITY_OBJS): %-old.o : %.cpp
	$(HOSTCXX) $(CXXFLAGS) -o $@ -c $<

