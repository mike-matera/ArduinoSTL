MAKE    = make
SUBDIRS = include src tests bin

# User defines:

noconfig_targets := menuconfig config oldconfig randconfig \
	defconfig allyesconfig allnoconfig clean distclean \
	release tags TAGS

TOPDIR=./
include Rules.mak

all: headers
	$(MAKE) -C include all
	$(MAKE) -C src all
	$(MAKE) -C bin all


tests: all
	$(MAKE) -C tests all

check test: all tests
	$(MAKE) -C tests test


clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(MAKE) -C extra/locale clean

distclean: clean
	$(MAKE) -C extra clean
	rm -f .config
	rm -f .config.cmd
	rm -f .config.old
	rm -f include/system_configuration.h


#Menu configuration system

extra/config/conf:
	make -C extra/config conf

extra/config/mconf:
	make -C extra/config ncurses mconf

menuconfig: extra/config/mconf
	@./extra/config/mconf extra/Configs/Config.in

config: extra/config/conf
	@./extra/config/conf extra/Configs/Config.in

oldconfig: extra/config/conf
	@./extra/config/conf -o extra/Configs/Config.in

randconfig: extra/config/conf
	@./extra/config/conf -r extra/Configs/Config.in

allyesconfig: extra/config/conf
	@./extra/config/conf -y extra/Configs/Config.in

allnoconfig: extra/config/conf
	@./extra/config/conf -n extra/Configs/Config.in

defconfig: extra/config/conf
	@./extra/config/conf -d extra/Configs/Config.in

include/system_configuration.h: .config
	@if [ ! -x ./extra/config/conf ] ; then \
		make -C extra/config conf; \
	fi;
	@./extra/config/conf -o extra/Configs/Config.in

headers: include/system_configuration.h

install:
	$(MAKE) -C include install
	$(MAKE) -C src install
	$(MAKE) -C bin install


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
