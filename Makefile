MAKE	=	make
CC  	=	gcc
CXX	=	g++
CFLAGS	=	-O2 -g -Wall -Wpointer-arith -Wstrict-prototypes -W -pedantic -march=athlon-xp -I../include
C_FLAGS	=	$(CFLAGS)
CXXFLAGS=	$(CFLAGS)
LIBS	=
SUBDIRS =	include src tests
SRCS	=
EXOBJS	=
ALLOBJS	=	$(EXOBJS)
ALLBIN	=	
ALLTGT	=	

# User defines:

noconfig_targets := menuconfig config oldconfig randconfig \
	defconfig allyesconfig allnoconfig clean distclean \
	release tags TAGS

TOPDIR=./
include Rules.mak

all:	headers
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir all; \
	done

objs:	$(ALLOBJS)

cleanobjs:
	rm -f $(ALLOBJS)

cleanbin:
	rm -f $(ALLBIN)

clean:	cleanobjs cleanbin
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(MAKE) -C extra/locale clean

cleanall:	cleanobjs cleanbin


distclean: clean
	$(MAKE) -C extra clean
	rm -f .config
	rm -f .config.cmd
	rm -f .config.old


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
	echo "headers"

install:
	$(INSTALL) -d $(PREFIX)$(RUNTIME_PREFIX)lib
	$(INSTALL) -m 644 src/lib*.so.$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL) \
		$(PREFIX)$(RUNTIME_PREFIX)lib
	cp -fa lib/*.so* $(PREFIX)$(RUNTIME_PREFIX)lib
	$(INSTALL) -d $(PREFIX)$(RUNTIME_PREFIX)include
	$(INSTALL) -m 644 include/* \
		$(PREFIX)$(RUNTIME_PREFIX)include
	

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
