# Rules.mak

# Copyright Garrett Kajmowicz, 2004
# Copyright (C) 2000 by Lineo, inc.
# Copyright (C) 2000-2002 Erik Andersen <andersen@uclibc.org>
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU Library General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option) any
# later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Library General Public License for more
# details.
#
# You should have received a copy of the GNU Library General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

# This file and most of the menuconfiguration system have been taken wholesle from
# the uClibc package availalble at www.uclibc.org

ifndef CROSS
CROSS=
endif
CC= $(CROSS)gcc
CXX= $(CROSS)g++
AR= $(CROSS)ar
LD= $(CROSS)ld
NM= $(CROSS)nm
STRIPTOOL= $(CROSS)strip

INSTALL= install
LN= ln
RM= rm -f

# Select the compiler needed to build binaries for your development system
HOSTCC=gcc
HOSTCFLAGS=-O2 -Wall
HOSTCXX=g++
HOSTCXXFLAGS=-O2 -Wall

#--------------------------------------------------------
# Nothing beyond this point should ever be touched by mere mortals.
# Unless you hang out with the gods, you should probably leave all
# this stuff alone.
MAJOR_VERSION:=0
MINOR_VERSION:=1
SUBLEVEL:=5
VERSION:=$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL)
# Ensure consistent sort order, 'gcc -print-search-dirs' behavior, etc.
# LC_ALL:= C
# export MAJOR_VERSION MINOR_VERSION SUBLEVEL VERSION LC_ALL
export MAJOR_VERSION MINOR_VERSION SUBLEVEL VERSION 

SHARED_FULLNAME:=libuClibc++-$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL).so
SHARED_MAJORNAME:=libuClibc++.so.$(MAJOR_VERSION)
LIBC:=$(TOPDIR)libc/$(LIBNAME)

# Pull in the user's uClibc++ configuration
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
-include $(TOPDIR).config
endif

# A nifty macro to make testing gcc features easier
check_gcc=$(shell if $(CC) $(1) -S -o /dev/null -xc /dev/null > /dev/null 2>&1; \
        then echo "$(1)"; else echo "$(2)"; fi)

# Make certain these contain a final "/", but no "//"s.
TARGET_ARCH:=$(strip $(subst ",, $(strip $(TARGET_ARCH))))
#RUNTIME_PREFIX:=$(strip $(subst //,/, $(subst ,/, $(subst ",, $(strip $(RUNTIME_PREFIX))))))
UCLIBCXX_RUNTIME_PREFIX:=$(strip $(subst //,/, $(subst ,/, $(subst ",, $(strip $(UCLIBCXX_RUNTIME_PREFIX))))))
export UCLIBCXX_RUNTIME_PREFIX

ARFLAGS:=r

OPTIMIZATION:=
PICFLAG:=-fPIC

# Some nice CPU specific optimizations
#ifeq ($(strip $(TARGET_ARCH)),i386)
#	OPTIMIZATION+=$(call check_gcc,-mpreferred-stack-boundary=2,)
#	OPTIMIZATION+=$(call check_gcc,-falign-jumps=0 -falign-loops=0,-malign-jumps=0 -malign-loops=0)
#	CPU_CFLAGS-$(CONFIG_386)+=-march=i386
#	CPU_CFLAGS-$(CONFIG_486)+=-march=i486
#	CPU_CFLAGS-$(CONFIG_586)+=-march=i586
#	CPU_CFLAGS-$(CONFIG_586MMX)+=$(call check_gcc,-march=pentium-mmx,-march=i586)
#	CPU_CFLAGS-$(CONFIG_686)+=-march=i686
#	CPU_CFLAGS-$(CONFIG_PENTIUMIII)+=$(call check_gcc,-march=pentium3,-march=i686)
#	CPU_CFLAGS-$(CONFIG_PENTIUM4)+=$(call check_gcc,-march=pentium4,-march=i686)
#	CPU_CFLAGS-$(CONFIG_K6)+=$(call check_gcc,-march=k6,-march=i586)
#	CPU_CFLAGS-$(CONFIG_K7)+=$(call check_gcc,-march=athlon,-malign-functions=4 -march=i686)
#	CPU_CFLAGS-$(CONFIG_CRUSOE)+=-march=i686 -malign-functions=0 -malign-jumps=0 -malign-loops=0
#	CPU_CFLAGS-$(CONFIG_WINCHIPC6)+=$(call check_gcc,-march=winchip-c6,-march=i586)
#	CPU_CFLAGS-$(CONFIG_WINCHIP2)+=$(call check_gcc,-march=winchip2,-march=i586)
#	CPU_CFLAGS-$(CONFIG_CYRIXIII)+=$(call check_gcc,-march=c3,-march=i586)
#endif


# use '-Os' optimization if available, else use -O2, allow Config to override
OPTIMIZATION+=$(call check_gcc,-Os,-O2)

# Add a bunch of extra pedantic annoyingly strict checks
XWARNINGS=$(subst ",, $(strip $(WARNINGS))) -Wno-trigraphs -W -pedantic
XARCH_CFLAGS=$(subst ",, $(strip $(ARCH_CFLAGS)))
CPU_CFLAGS=$(subst ",, $(strip $(CPU_CFLAGS-y)))


# Some nice CFLAGS to work with
CFLAGS=$(XWARNINGS) $(OPTIMIZATION) $(XARCH_CFLAGS) $(CPU_CFLAGS) \
        -fno-builtin -nostdinc++ -ansi -I$(TOPDIR)include

ifeq ($(DODEBUG),y)
    #CFLAGS += -g3
#    CFLAGS = $(XWARNINGS) -O0 -g3 $(CPU_CFLAGS) -fno-builtin -nostdinc -D_LIBC -I$(TOPDIR)include -I.
    CFLAGS += -O0 -g3 
    LDFLAGS:= $(CPU_LDFLAGS-y) -shared --warn-common --warn-once -z combreloc
    STRIPTOOL:= true -Since_we_are_debugging
else
    LDFLAGS := $(CPU_LDFLAGS-y) -shared --warn-common --warn-once -z combreloc
endif

# Sigh, some stupid versions of gcc can't seem to cope with '-iwithprefix include'
#CFLAGS+=-iwithprefix include
#CFLAGS+=$(shell $(CC) -print-search-dirs | sed -ne "s/install: *\(.*\)/-I\1include/gp")

LDSO:=$(SYSTEM_LDSO)
DYNAMIC_LINKER:=/lib/$(strip $(subst ",, $(notdir $(SYSTEM_LDSO))))


CFLAGS_NOPIC:=$(CFLAGS)
#ifeq ($(DOPIC),y)
    CFLAGS += $(PICFLAG)
#endif

CXXFLAGS=$(CFLAGS)

ifeq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)

else
    CXXFLAGS+= -fno-exceptions -fno-rtti
endif


LIBGCC_CFLAGS ?= $(CFLAGS) $(CPU_CFLAGS-y)
LIBGCC:=$(shell $(CC) $(LIBGCC_CFLAGS) -print-libgcc-file-name)
LIBGCC_DIR:=$(dir $(LIBGCC))



