TOPDIR=../
include $(TOPDIR)Rules.mak

all:

clean:

distclean: clean

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)/include
	$(INSTALL) -m 644 `ls --color=never --ignore="CVS"` $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)/include

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<
