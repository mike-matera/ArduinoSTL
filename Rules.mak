# Rules.mak

# Copyright Garrett Kajmowicz, 2004-2006
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
RANLIB= $(CROSS)ranlib
STRIPTOOL= $(CROSS)strip

INSTALL= install
LN= ln -s -f
RM= rm -f
TAR= tar

ARFLAGS:= rcs

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
MINOR_VERSION:=2
SUBLEVEL:=4
VERSION:=$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL)
# Ensure consistent sort order, 'gcc -print-search-dirs' behavior, etc.
# LC_ALL:= C
# export MAJOR_VERSION MINOR_VERSION SUBLEVEL VERSION LC_ALL
export MAJOR_VERSION MINOR_VERSION SUBLEVEL VERSION 

LNAME:=uClibc++
LIBNAME:=libuClibc++
SHARED_FULLNAME:=$(LIBNAME)-$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL).so
SHARED_MAJORNAME:=$(LIBNAME).so.$(MAJOR_VERSION)

# Make sure DESTDIR and PREFIX can be used to install
# PREFIX is a uClibcism while DESTDIR is a common GNUism
PREFIX = $(DESTDIR)

# Pull in the user's uClibc++ configuration
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
-include $(TOPDIR).config
endif

# A nifty macro to make testing gcc features easier
check_gcc=$(shell if $(CC) $(1) -S -o /dev/null -xc /dev/null > /dev/null 2>&1; \
        then echo "$(1)"; else echo "$(2)"; fi)

check_gxx_visibility=$(shell if $(CXX) -fvisibility-inlines-hidden -S -o /dev/null -xc++ /dev/null > /dev/null 2>&1; \
        then echo "-DGCC_HASCLASSVISIBILITY"; fi)

check_as_needed=$(shell if $(LD) --help | grep -q 'as-needed' ; \
	then echo "-Wl,--as-needed -lgcc_s -Wl,--no-as-needed"; else echo "-lgcc_s"; fi)

# strip quotes
qstrip = $(strip $(subst ",,$(1)))
#"))

BUILD_EXTRA_LIBRARIES:=$(call qstrip,$(BUILD_EXTRA_LIBRARIES))

# Make certain these contain a final "/", but no "//"s.
UCLIBCXX_RUNTIME_PREFIX:=$(strip $(subst //,/, $(subst ,/, $(call qstrip,$(UCLIBCXX_RUNTIME_PREFIX)))))
UCLIBCXX_RUNTIME_LIBDIR:=$(strip $(subst //,/, $(subst //,/, $(subst ,/, $(call qstrip,$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR))))))
UCLIBCXX_RUNTIME_BINDIR:=$(strip $(subst //,/, $(subst //,/, $(subst ,/, $(call qstrip,$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_BIN_SUBDIR))))))
UCLIBCXX_RUNTIME_INCLUDEDIR:=$(strip $(subst //,/, $(subst //,/, $(subst ,/, $(call qstrip,$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_INCLUDE_SUBDIR))))))
export UCLIBCXX_RUNTIME_PREFIX UCLIBCXX_RUNTIME_LIBDIR UCLIBCXX_RUNTIME_BINDIR UCLIBCXX_RUNTIME_INCLUDEDIR

OPTIMIZATION:=
PICFLAG:=-fPIC

# use '-Os' optimization if available, else use -O2, allow Config to override
OPTIMIZATION+=$(call check_gcc,-Os,-O2)

# Add a bunch of extra pedantic annoyingly strict checks
XWARNINGS=$(call qstrip,$(WARNINGS)) -Wno-trigraphs -pedantic
CPU_CFLAGS=$(call qstrip,$(CPU_CFLAGS-y))

# Some nice CFLAGS to work with
GEN_CFLAGS:=-fno-builtin
CFLAGS:=$(XWARNINGS) $(CPU_CFLAGS) -ansi

LDFLAGS:=-Wl,--warn-common -Wl,--warn-once -Wl,-z,combreloc -Wl,-z,defs

ifeq ($(DODEBUG),y)
    CFLAGS += -O0 -g3 
    STRIPTOOL:= true -Since_we_are_debugging
else
    CFLAGS += $(OPTIMIZATION)
endif

ifneq ($(BUILD_ONLY_STATIC_LIB),y)
    CFLAGS += $(PICFLAG)
endif

EH_CXXFLAGS:=
ifneq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
    EH_CXXFLAGS += -fno-exceptions -fno-rtti
endif

GEN_CXXFLAGS:=-nostdinc++
GEN_CXXFLAGS+=$(call check_gxx_visibility)
CXXFLAGS:=$(CFLAGS)

LIBGCC:=$(shell $(CC) -print-libgcc-file-name)
LIBGCC_DIR:=$(dir $(LIBGCC))

#GCC_VERSION?=$(shell $(CC) -dumpversion | cut -c1-3)
GCC_MAJOR_VER?=$(shell $(CC) -dumpversion | cut -c1)
#GCC_MINOR_VER?=$(shell $(CC) -dumpversion | cut -c3)

GEN_LIBS:=
ifneq ($(LIBGCC_DIR),$(UCLIBCXX_RUNTIME_LIBDIR))
GEN_LIBS += -L$(LIBGCC_DIR)
endif
ifneq ($(IMPORT_LIBSUP),y)
  GEN_LIBS += -lsupc++
endif
GEN_LIBS += -lc -lgcc

LIBS := $(GEN_LIBS)
STATIC_LIBS := $(GEN_LIBS)
#ifeq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
ifneq ($(GCC_MAJOR_VER),3)
LIBS += $(call check_as_needed)
endif
ifneq ($(IMPORT_LIBGCC_EH),y)
  STATIC_LIBS += -lgcc_eh
ifeq ($(GCC_MAJOR_VER),3)
  LIBS += -lgcc_eh
endif
endif
#endif

.PHONY: all clean distclean install
