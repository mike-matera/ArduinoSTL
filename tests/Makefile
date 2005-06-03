TOPDIR=../
include $(TOPDIR)Rules.mak

ULIBS := -L$(TOPDIR)/src -l$(LNAME)

CXXOFLAGS := -O0 -g3 -ansi $(EH_CXXFLAGS)

SRCS	:= $(wildcard *.cpp)

ifneq ($(UCLIBCXX_HAS_WCHAR),y)
SRCS	:= $(filter-out wchartest.cpp,$(SRCS))
endif

ifneq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
SRCS    := $(filter-out excepttest.cpp,$(SRCS))
endif

EXOBJS	:= $(patsubst %.cpp,%.o, $(SRCS))

OLDOBJS	:= $(patsubst %.cpp,%.o-old, $(SRCS))

ALLBIN	:= $(patsubst %.cpp,%, $(SRCS))

OLDBIN	:= $(patsubst %.cpp,%-old, $(SRCS))

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
	$(CXX) $(LDFLAGS) -o $@ $@.o $(ULIBS) $(LIBS)

$(OLDBIN): $(OLDOBJS)
	$(HOSTCXX) $(LDFLAGS) -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.cpp.o-old:
	$(HOSTCXX) $(CXXOFLAGS) -o $@ -c $<

