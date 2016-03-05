# Rules.mak
# vi: ft=make :

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

# This file and most of the menuconfiguration system have been taken wholesale from
# the uClibc package availalble at www.uclibc.org

.SUFFIXES:
.SUFFIXES: .cpp .c .S .o .so .a .s .i
PHONY := FORCE
.PHONY: $(PHONY) all clean realclean distclean install
FORCE:

ifdef CROSS
# CROSS is still supported for backward compatibily only
$(warning CROSS is deprecated, please use CROSS_COMPILE instead)
ifneq ($(CROSS_COMPILE),)
$(warning CROSS_COMPILE has precedence over CROSS, ignoring the latter)
endif
endif
CROSS_COMPILE ?= $(CROSS)
CC= $(CROSS_COMPILE)gcc
CXX= $(CROSS_COMPILE)g++
AR= $(CROSS_COMPILE)ar
LD= $(CROSS_COMPILE)ld
NM= $(CROSS_COMPILE)nm
RANLIB= $(CROSS_COMPILE)ranlib
STRIPTOOL= $(CROSS_COMPILE)strip

INSTALL = install
LN      = ln
RM      = rm -f
TAR     = tar
SED     = sed
AWK     = awk

ARFLAGS:= cr

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
SUBLEVEL:=5-git
VERSION:=$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL)
ABI_VERSION:=$(MAJOR_VERSION)
export MAJOR_VERSION MINOR_VERSION SUBLEVEL VERSION ABI_VERSION

LNAME:=uClibc++
LIBNAME:=libuClibc++
SHARED_FULLNAME:=$(LIBNAME)-$(MAJOR_VERSION).$(MINOR_VERSION).$(SUBLEVEL).so
SHARED_MAJORNAME:=$(LIBNAME).so.$(ABI_VERSION)

# Make sure DESTDIR and PREFIX can be used to install
ifdef PREFIX
# PREFIX is a uClibcism while DESTDIR is a common GNUism
$(warning PREFIX is deprecated, please use DESTDIR instead)
ifneq ($(DESTDIR),)
$(warning DESTDIR has precedence over PREFIX, ignoring the latter)
endif
endif
DESTDIR ?= $(PREFIX)

clean_targets := clean realclean distclean CLEAN_% DISTCLEAN_%
noconfig_targets := conf mconf \
	menuconfig config oldconfig silentoldconfig randconfig \
	defconfig allyesconfig allnoconfig $(clean_targets) \
	release tags TAGS help

# Pull in the user's uClibc++ configuration
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
# Prevent make from searching
-include $(abspath $(top_builddir).config)
endif

comma:=,
space:= #

# A nifty macro to make testing gcc features easier
check_gcc=$(shell \
	if $(CC) $(1) -S -o /dev/null -xc /dev/null > /dev/null 2>&1; \
	then echo "$(1)"; else echo "$(2)"; fi)
check_gxx=$(shell \
	if $(CXX) $(1) -S -o /dev/null -xc++ /dev/null > /dev/null 2>&1; \
	then echo "$(1)"; else echo "$(2)"; fi)
check_as=$(shell \
	if $(CC) -Wa,$(1) -Wa,-Z -c -o /dev/null -xassembler /dev/null > /dev/null 2>&1; \
	then echo "-Wa,$(1)"; fi)
check_ld=$(shell \
	if $(LD) $(1) -o /dev/null -b binary /dev/null > /dev/null 2>&1; \
	then echo "$(1)"; fi)

# Use variable indirection here so that we can have variable
# names with fun chars in them like equal signs
define check-tool-var
ifeq ($(filter $(clean_targets) CLEAN_%,$(MAKECMDGOALS)),)
_v = $(2)_$(3)
ifndef $$(_v)
$$(_v) := $$(call $(1),$(subst %, ,$(3)))
export $$(_v)
endif
endif
endef

# Usage: check-gcc-var,<flag>
# Check the C compiler to see if it supports <flag>.
# Export the variable CFLAG_<flag> if it does.
define check-gcc-var
$(call check-tool-var,check_gcc,CFLAG,$(1))
endef
# Check the C++ compiler to see if it supports <flag>.
# Export the variable CXXFLAG_<flag> if it does.
define check-gxx-var
$(call check-tool-var,check_gxx,CXXFLAG,$(1))
endef
# Usage: check-as-var,<flag>
# Check the assembler to see if it supports <flag>.  Export the
# variable ASFLAG_<flag> if it does (for invoking the assembler),
# as well CFLAG_-Wa<flag> (for invoking the compiler driver).
define check-as-var
$(call check-tool-var,check_as,ASFLAG,$(1))
_v = CFLAG_-Wa$(1)
export $$(_v) = $$(if $$(ASFLAG_$(1)),-Wa$$(comma)$$(ASFLAG_$(1)))
endef
# Usage: check-ld-var,<flag>
# Check the linker to see if it supports <flag>.  Export the
# variable LDFLAG_<flag> if it does (for invoking the linker),
# as well CFLAG_-Wl<flag> (for invoking the compiler driver).
define check-ld-var
$(call check-tool-var,check_ld,LDFLAG,$(1))
_v = CFLAG_-Wl$(1)
export $$(_v) = $$(if $$(LDFLAG_$(1)),-Wl$$(comma)$$(LDFLAG_$(1)))
endef
# Usage: cache-output-var,<variable>,<shell command>
# Execute <shell command> and cache the output in <variable>.
define cache-output-var
ifndef $(1)
$(1) := $$(shell $(2))
export $(1)
endif
endef

$(eval $(call cache-output-var,GCC_VER,$(CC) -dumpversion))
GCC_VER := $(subst ., ,$(GCC_VER))
GCC_MAJOR_VER ?= $(word 1,$(GCC_VER))
#GCC_MINOR_VER ?= $(word 2,$(GCC_VER))

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

WRAPPER = $(top_builddir)bin/g++-uc
OPTIMIZATION:=
PICFLAG:=-fPIC

# use '-Os' optimization if available, else use -O2, allow Config to override
$(eval $(call check-gcc-var,-Os))
ifneq ($(CFLAG_-Os),)
OPTIMIZATION += $(CFLAG_-Os)
else
$(eval $(call check-gcc-var,-O2))
OPTIMIZATION += $(CFLAG_-O2)
endif

$(eval $(call check-gxx-var,-fvisibility-inlines-hidden))
$(eval $(call check-gxx-var,-std=gnu++14))
$(eval $(call check-gxx-var,-Wno-sized-deallocation))

# Add a bunch of extra pedantic annoyingly strict checks
XWARNINGS=$(call qstrip,$(UCLIBCXX_WARNINGS)) -Wno-trigraphs -pedantic
CPU_CFLAGS=$(call qstrip,$(CPU_CFLAGS-y))

# Some nice CFLAGS to work with
GEN_CFLAGS:=-fno-builtin
CFLAGS:=$(XWARNINGS) $(CPU_CFLAGS)

LDFLAGS-$(LIBNAME).so:=-Wl,--warn-common -Wl,--warn-once -Wl,-z,combreloc -Wl,-z,defs

STRIP_FLAGS-src := -x -R .note -R .comment
STRIP_FLAGS-src/abi := -x -R .note -R .comment
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
GEN_CXXFLAGS+=$(if $(CXXFLAG_-fvisibility-inlines-hidden),-DGCC_HASCLASSVISIBILITY)
CXXFLAGS:=$(CFLAGS)
CFLAGS += -ansi

LIBGCC:=$(shell $(CC) -print-libgcc-file-name)
LIBGCC_DIR:=$(dir $(LIBGCC))

# Let users override these
ifndef LIBGCC_EH
$(eval $(call cache-output-var,FILE_LIBGCC_EH,$(CXX) -print-file-name=libgcc_eh.a))
LIBGCC_EH:=$(strip $(if $(IMPORT_LIBGCC_EH),$(FILE_LIBGCC_EH)))
endif
ifndef LIBSUP
$(eval $(call cache-output-var,FILE_LIBSUP,$(CXX) -print-file-name=libsupc++.a))
LIBSUP:=$(strip $(if $(IMPORT_LIBSUP),$(FILE_LIBSUP)))
endif

list-archive-members = $(if $(1),$(shell $(AR) t $(1)))
variablify = $(strip $(subst /,_,$(subst :,_,$(subst ;,_,$(subst |,_,$(subst >,_,$(subst <,_,$(1))))))))

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

$(eval $(call cache-output-var,LDASNEEDED,$(LD) --help 2>/dev/null | grep -q -- --as-needed && echo y))
link.asneeded = $(if $1,$(if $(LDASNEEDED),-Wl$(comma)--as-needed $(1) -Wl$(comma)--no-as-needed,$(1)))

ifneq ($(GCC_MAJOR_VER),3)
LIBS-ASNEEDED-$(LIBNAME).so = -lgcc_s
endif
ifneq ($(IMPORT_LIBGCC_EH),y)
  STATIC_LIBS += -lgcc_eh
#ifeq ($(GCC_MAJOR_VER),3)
#  LIBS += -lgcc_eh
#endif
endif

# We do not need built-in implicit rules
MAKEFLAGS += -r

ifneq ($(findstring s,$(MAKEFLAGS)),)
export MAKE_IS_SILENT := y
SECHO := -@false
DISP := sil
Q := @
else
export MAKE_IS_SILENT := n
SECHO := @echo
ifneq ($(V)$(VERBOSE),)
ifeq ($(V),1)
DISP := bri# brief, like pur but with defines
Q := @
else
SHELL_SET_X := set -x
DISP := ver
Q :=
endif
else
DISP := pur
Q := @
endif
endif

show_objs = $(subst $(top_builddir),,$(subst ../,,$@))
define show_defs
	$(filter -D%,$(call unwrapper,$(1)))
endef
define show_ldflags
	$(subst $(comma), ,$(subst -Wl$(comma),,$(filter -Wl%,$(1))))
endef

pur_disp_compile.cxx = echo "  "CXX $(show_objs)
pur_disp_compile.c   = echo "  "CC $(show_objs)
pur_disp_compile.ixx = echo "  "CPP $(show_objs)
pur_disp_compile.i   = echo "  "CPP $(show_objs)
pur_disp_compile.sxx = echo "  "CXX-S $(show_objs)
pur_disp_compile.s   = echo "  "CC-S $(show_objs)
pur_disp_compile.u   = echo "  "CC $(show_objs)
pur_disp_compile.S   = echo "  "AS $(show_objs)
pur_disp_compile.uxx = echo "  "CXX $(show_objs)
pur_disp_compile.oxx = echo "  "CXX-o $(show_objs)
pur_disp_hcompile.u  = echo "  "HOSTCC $(show_objs)
pur_disp_hcompile.o  = echo "  "HOSTCC-o $(show_objs)
pur_disp_hcompile.uxx= echo "  "HOSTCXX $(show_objs)
pur_disp_hcompile.oxx= echo "  "HOSTCXX-o $(show_objs)
pur_disp_strip       = echo "  "STRIP $(STRIP_FLAGS) $@
pur_disp_t_strip     = echo "  "STRIP $(STRIP_FLAGS-$(@D)) $@
pur_disp_ar          = echo "  "AR $(ARFLAGS) $@
pur_disp_ranlib      = echo "  "RANLIB $(RANLIBFLAGS) $@
pur_disp_ld          = echo "  "LD $(call dirify,$(1))
pur_disp_ln          = echo "  "LN $(show_objs)
pur_disp_mkdir       = echo "  "MKDIR $(show_objs)
pur_disp_gen         = echo "  "GEN $(show_objs)
pur_disp_install     = echo "  "INSTALL $(1)
pur_disp_unifdef     = echo "  "UNIFDEF $(show_objs)
pur_disp_rm          = echo "  "CLEAN $(subst CLEAN_,,$(subst DISTCLEAN_,,$@))

sil_disp_compile.cxx = true
sil_disp_compile.c   = true
sil_disp_compile.ixx = true
sil_disp_compile.i   = true
sil_disp_compile.sxx = true
sil_disp_compile.s   = true
sil_disp_compile.u   = true
sil_disp_compile.S   = true
sil_disp_compile.uxx = true
sil_disp_compile.oxx = true
sil_disp_hcompile.u  = true
sil_disp_hcompile.o  = true
sil_disp_hcompile.uxx= true
sil_disp_hcompile.oxx= true
sil_disp_strip       = true
sil_disp_t_strip     = true
sil_disp_ar          = true
sil_disp_ranlib      = true
sil_disp_ld          = true
sil_disp_ln          = true
sil_disp_mkdir       = true
sil_disp_gen         = true
sil_disp_install     = true
sil_disp_unifdef     = true
sil_disp_rm          = true

bri_disp_compile.cxx = $(pur_disp_compile.cxx) $(call show_defs,$(cmd_compile.cxx))
bri_disp_compile.c   = $(pur_disp_compile.c) $(call show_defs,$(cmd_compile.c))
bri_disp_compile.ixx = $(pur_disp_compile.ixx) $(call show_defs,$(cmd_compile.ixx))
bri_disp_compile.i   = $(pur_disp_compile.i) $(call show_defs,$(cmd_compile.i))
bri_disp_compile.sxx = $(pur_disp_compile.sxx) $(call show_defs,$(cmd_compile.sxx))
bri_disp_compile.s   = $(pur_disp_compile.s) $(call show_defs,$(cmd_compile.s))
bri_disp_compile.u   = $(pur_disp_compile.u) $(call show_defs,$(cmd_compile.u))
bri_disp_compile.S   = $(pur_disp_compile.S) $(call show_defs,$(cmd_compile.S))
bri_disp_compile.uxx = $(pur_disp_compile.uxx) $(call show_defs,$(cmd_compile.uxx))
bri_disp_compile.oxx = $(pur_disp_compile.oxx) $(call show_defs,$(cmd_compile.oxx))
bri_disp_hcompile.u = $(pur_disp_hcompile.u) $(call show_defs,$(cmd_hcompile.u))
bri_disp_hcompile.o = $(pur_disp_hcompile.o) $(call show_defs,$(cmd_hcompile.o))
bri_disp_hcompile.uxx=$(pur_disp_hcompile.uxx) $(call show_defs,$(cmd_hcompile.uxx))
bri_disp_hcompile.oxx=$(pur_disp_hcompile.oxx) $(call show_defs,$(cmd_hcompile.oxx))
bri_disp_strip      = $(pur_disp_strip)
bri_disp_t_strip    = $(pur_disp_t_strip)
bri_disp_ar         = $(pur_disp_ar)
bri_disp_ranlib     = $(pur_disp_ranlib)
bri_disp_ld         = $(pur_disp_ld) $(call show_ldflags,$(cmd_ld))
bri_disp_ln         = $(pur_disp_ln)
bri_disp_mkdir      = $(pur_disp_mkdir)
bri_disp_gen        = $(pur_disp_gen)
bri_disp_install    = $(pur_disp_install)
bri_disp_unifdef    = $(pur_disp_unifdef)
bri_disp_rm         = $(pur_disp_rm)

esc=$(subst ','\'',$(1))
# ')
ver_disp_compile.cxx = echo '$(call esc,$(cmd_compile.cxx))'
ver_disp_compile.c   = echo '$(call esc,$(cmd_compile.c))'
ver_disp_compile.ixx = echo '$(call esc,$(cmd_compile.ixx))'
ver_disp_compile.i   = echo '$(call esc,$(cmd_compile.i))'
ver_disp_compile.sxx = echo '$(call esc,$(cmd_compile.sxx))'
ver_disp_compile.s   = echo '$(call esc,$(cmd_compile.s))'
ver_disp_compile.u   = echo '$(call esc,$(cmd_compile.u))'
ver_disp_compile.S   = echo '$(call esc,$(cmd_compile.S))'
ver_disp_compile.uxx = echo '$(call esc,$(cmd_compile.uxx))'
ver_disp_compile.oxx = echo '$(call esc,$(cmd_compile.oxx))'
ver_disp_hcompile.u  = echo '$(call esc,$(cmd_hcompile.u))'
ver_disp_hcompile.o  = echo '$(call esc,$(cmd_hcompile.o))'
ver_disp_hcompile.uxx= echo '$(call esc,$(cmd_hcompile.uxx))'
ver_disp_hcompile.oxx= echo '$(call esc,$(cmd_hcompile.oxx))'
ver_disp_strip       = echo '$(call esc,$(cmd_strip))'
ver_disp_t_strip     = echo '$(call esc,$(cmd_t_strip))'
ver_disp_ar          = echo '$(call esc,$(cmd_ar))'
ver_disp_ranlib      = echo '$(call esc,$(cmd_ranlib))'
ver_disp_ld          =
ver_disp_ln          =
ver_disp_mkdir       =
ver_disp_gen         =
ver_disp_install     =
ver_disp_unifdef     = echo '$(call esc,$(cmd_unifdef))'
ver_disp_rm          =

disp_compile.cxx = $($(DISP)_disp_compile.cxx)
disp_compile.c   = $($(DISP)_disp_compile.c)
disp_compile.ixx = $($(DISP)_disp_compile.ixx)
disp_compile.i   = $($(DISP)_disp_compile.i)
disp_compile.s   = $($(DISP)_disp_compile.s)
disp_compile.sxx = $($(DISP)_disp_compile.sxx)
disp_compile.u   = $($(DISP)_disp_compile.u)
disp_compile.S   = $($(DISP)_disp_compile.S)
disp_compile.uxx = $($(DISP)_disp_compile.uxx)
disp_compile.oxx = $($(DISP)_disp_compile.oxx)
disp_hcompile.u  = $($(DISP)_disp_hcompile.u)
disp_hcompile.o  = $($(DISP)_disp_hcompile.o)
disp_hcompile.uxx= $($(DISP)_disp_hcompile.uxx)
disp_hcompile.oxx= $($(DISP)_disp_hcompile.oxx)
disp_strip       = $($(DISP)_disp_strip)
disp_t_strip     = $($(DISP)_disp_t_strip)
disp_ar          = $($(DISP)_disp_ar)
disp_ranlib      = $($(DISP)_disp_ranlib)
disp_ld          = $($(DISP)_disp_ld)
disp_ln          = $($(DISP)_disp_ln)
disp_mkdir       = $($(DISP)_disp_mkdir)
disp_gen         = $($(DISP)_disp_gen)
disp_install     = $($(DISP)_disp_install)
disp_unifdef     = $($(DISP)_disp_unifdef)
disp_rm          = $($(DISP)_disp_rm)

any-prereq = $(filter-out $(PHONY),$?) $(filter-out $(PHONY) $(wildcard $^),$^)

# strip the top_builddir off everything to make the *string* idempotent for -C
dirify = $(subst $(top_builddir),,$(patsubst -L$(top_builddir)%,-L%,$(patsubst -I$(top_builddir)%,-I%,$(1))))
unwrapper = $(call dirify,$(subst $(call dirify,$(WRAPPER)),$(CXX) $(GEN_CFLAGS) $(GEN_CXXFLAGS) $(EH_CXXFLAGS),$(subst WRAPPER_INCLUDEDIR=,,$(subst WRAPPER_LIBDIR=,,$(1)))))
# True if not identical. Neither order nor whitespace nor identical flags
# matter.
compare_flags = \
	$(strip $(filter-out $(call unwrapper,$(cmd_$(call variablify,$(call dirify,$(1))))), \
				$(call unwrapper,$(cmd_$(call variablify,$(call dirify,$(@)))))) \
		$(filter-out $(call unwrapper,$(cmd_$(call variablify,$(call dirify,$(@))))), \
				$(call unwrapper,$(cmd_$(call variablify,$(call dirify,$(1)))))))

# Rebuild if any prerequisite, the used CC or flags changed.
# Previously used flags are stored in the corresponding .%.dep files
maybe_exec = \
		$(if $(strip $(compare_flags) $(any-prereq)), \
		@set -e; \
		$(disp_$(1)); \
		$(cmd_$(1)); \
		echo 'cmd_$(call variablify,$(call dirify,$(@))) := $(call dirify,$(cmd_$(call variablify,$(call dirify,$(1)))))' >> $(dir $@).$(notdir $@).dep)

CFLAGS_gen.dep = -MT $@ -MD -MP -MF $(dir $@).$(notdir $@).dep

cmd_compile.c = $(CC) $(CFLAGS_gen.dep) \
	$(CFLAGS-$(suffix $@)) \
	$(filter-out $(CFLAGS-OMIT-$(notdir $<)),$(CFLAGS-$(notdir $(<D)))) \
	$(CFLAGS-$(subst $(top_srcdir),,$(dir $<))) \
	$(CFLAGS-$(notdir $<)) \
	$(CFLAGS-$(notdir $@)) \
	$(CFLAGS) \
	-c $< -o $@
cmd_compile.i = $(cmd_compile.c:-c=-E -dD) $(UCLIBC_EXTRA_CPPFLAGS)
cmd_compile.s = $(cmd_compile.c:-c=-S)
cmd_compile.cxx = $(WR_CXX) $(CFLAGS_gen.dep) \
	$(CXXFLAGS-$(suffix $@)) \
	$(filter-out $(CXXFLAGS-OMIT-$(notdir $<)),$(CXXFLAGS-$(notdir $(<D)))) \
	$(CXXFLAGS-$(subst $(top_srcdir),,$(dir $<))) \
	$(CXXFLAGS-$(notdir $<)) \
	$(CXXFLAGS-$(notdir $@)) \
	$(CXXFLAGS) \
	-c $< -o $@
cmd_compile.ixx = $(cmd_compile.cxx:-c=-E -dD) $(CXXCPPFLAGS)
cmd_compile.sxx = $(cmd_compile.cxx:-c=-S)
cmd_compile.oxx = $(WR_CXX) $(CFLAGS_gen.dep) \
	$(CXXFLAGS-$(suffix $@)) \
	$(filter-out $(CXXFLAGS-OMIT-$(notdir $<)),$(CXXFLAGS-$(notdir $(<D)))) \
	$(CXXFLAGS-$(subst $(top_srcdir),,$(dir $<))) \
	$(CXXFLAGS-$(notdir $<)) \
	$(CXXFLAGS-$(notdir $@)) \
	$(CXXFLAGS) \
	-c $< -o $@
cmd_compile.uxx = $(WR_CXX) $(CFLAGS_gen.dep) \
	$(filter-out $(CXXFLAGS-OMIT-$(notdir $<)),$(CXXFLAGS-$(notdir $(<D)))) \
	$(CXXFLAGS-$(subst $(top_srcdir),,$(dir $<))) \
	$(CXXFLAGS-$(notdir $<)) \
	$(CXXFLAGS-$(notdir $@)) \
	$(CXXFLAGS) \
	$^ $(LDFLAGS) $(DEPS-$(notdir $@)) -o $@
cmd_compile.u = $(CC) $(CFLAGS_gen.dep) $(CFLAGS) $(CFLAGS-$(notdir $(^D))) $(CFLAGS-$(notdir $@)) $^ $(DEPS-$(notdir $@)) -o $@
cmd_compile.S = $(filter-out -std=gnu99, $(cmd_compile.c)) -D__ASSEMBLER__ $(ASFLAGS) $(ARCH_ASFLAGS) $(ASFLAGS-$(suffix $@)) $(ASFLAGS-$(notdir $<)) $(ASFLAGS-$(notdir $@))
cmd_hcompile.uxx = $(HOSTCXX) $(CFLAGS_gen.dep) $(HOSTCXXFLAGS) $(CXXFLAGS-$(notdir $(^D))) $(CXXFLAGS-$(notdir $@)) $^ $(HOSTLDFLAGS) $(DEPS-$(notdir $@)) -o $@
cmd_hcompile.oxx = $(HOSTCXX) $(CFLAGS_gen.dep) $(HOSTCXXFLAGS) $(HOSTCXXFLAGS-$(notdir $(^D))) $(HOSTCXXFLAGS-$(notdir $@)) -c $< -o $@
cmd_strip     = $(STRIPTOOL) $(STRIP_FLAGS) $^
cmd_t_strip   = $(STRIPTOOL) $(STRIP_FLAGS) $@
cmd_ar        = $(AR) $(ARFLAGS) $@ $^
cmd_ranlib    = $(RANLIB) $(RANLIBFLAGS) $@

define do_ln
	@$(disp_ln)
	$(Q)$(LN) -f -s
endef

define do_mkdir
	@$(disp_mkdir)
	$(Q)$(INSTALL) -d $@
endef

define do_rm
	@$(disp_rm)
	$(Q)$(RM)
endef

define do_awk
	@$(disp_gen)
	$(Q)$(AWK) -f
endef

define do_sed
	@$(disp_gen)
	$(Q)$(SED)
endef

compile.cxx = @$(call maybe_exec,compile.cxx)
compile.c   = @$(call maybe_exec,compile.c)
compile.ixx =  $(call maybe_exec,compile.ixx)
compile.i   =  $(call maybe_exec,compile.i)
compile.sxx =  $(call maybe_exec,compile.sxx)
compile.s   =  $(call maybe_exec,compile.s)
compile.S   = @$(call maybe_exec,compile.S)
compile.uxx = @$(call maybe_exec,compile.uxx)
compile.oxx = @$(call maybe_exec,compile.oxx)
do_strip    = @$(disp_strip)     ; $(cmd_strip)
do_t_strip  = @$(disp_t_strip)   ; $(cmd_t_strip)
do_unifdef  = @$(disp_unifdef)   ; $(cmd_unifdef)
hcompile.u  = @$(disp_hcompile.u); $(cmd_hcompile.u)
hcompile.o  = @$(disp_hcompile.o); $(cmd_hcompile.o)
hcompile.uxx= @$(call maybe_exec,hcompile.uxx)
hcompile.oxx= @$(call maybe_exec,hcompile.oxx)

define do_ar
	@$(disp_ar) ; $(cmd_ar)
	@$(disp_ranlib) ; $(cmd_ranlib)
endef
define compile.u
	@$(disp_compile.u) ; $(cmd_compile.u)
	@$(disp_t_strip)
endef
cmd_hcompile.u = $(HOSTCC) $(filter-out $(PHONY),$^) $(DEPS-$(notdir $@)) -o $@ $(HOSTLDFLAGS) $(HOSTLDFLAGS-$(notdir $(^D))) $(HOSTLDFLAGS-$(notdir $@)) $(HOSTCFLAGS) $(HOSTCFLAGS-$(notdir $(^D))) $(HOSTCFLAGS-$(notdir $@))
cmd_hcompile.o = $(HOSTCC) $(filter-out $(PHONY),$<) $(DEPS-$(notdir $@)) -c -o $@ $(HOSTCFLAGS) $(HOSTCFLAGS-$(notdir $(^D))) $(HOSTCFLAGS-$(notdir $@))

define link.so
	$(Q)$(RM) $@ $@.$(2) $(1)
	@$(disp_ld)
	$(Q)$(CXX) $(LDFLAGS-$(@F)) $(LDFLAGS-y-$(@F)) \
		-Wl,-soname=$(@F).$(2) \
		-o $(1) $^ \
		$(START_FILE-$(@F)) \
		$(LIBS-$(@F)) $(call link.asneeded,$(LIBS-ASNEEDED-$(@F))) \
		$(END_FILE-$(@F))
	$(Q)$(LN) -sf $(notdir $(1)) $@.$(2)
	$(Q)$(LN) -sf $(@F).$(2) $@
endef

$(top_builddir)%.o:  $(top_srcdir)%.cpp FORCE ; $(compile.cxx)
$(top_builddir)%.o:  $(top_srcdir)%.c FORCE ; $(compile.c)
$(top_builddir)%.o:  $(top_srcdir)%.S FORCE ; $(compile.S)
$(top_builddir)%.o:  $(top_srcdir)%.s FORCE ; $(compile.S)
$(top_builddir)%.i:  $(top_srcdir)%.cpp FORCE ; $(compile.ixx)
$(top_builddir)%.i:  $(top_srcdir)%.c FORCE ; $(compile.i)
$(top_builddir)%.i:  $(top_srcdir)%.S FORCE ; $(compile.i)
$(top_builddir)%.s:  $(top_srcdir)%.cpp FORCE ; $(compile.sxx)
$(top_builddir)%.s:  $(top_srcdir)%.c FORCE ; $(compile.s)
$(top_builddir)%.s:  $(top_srcdir)%.S FORCE ; $(compile.s)
#$(top_builddir)tests/%.o:  $(top_srcdir)tests/%.cpp FORCE ; $(hcompile.oxx)
#$(top_builddir)tests/%:    $(top_builddir)tests/%.o FORCE ; $(hcompile.uxx)
$(top_builddir)%.dep:
FORCE: ;

ifeq ($(HAVE_DOT_CONFIG),y)
$(DESTDIR)$(UCLIBCXX_RUNTIME_LIBDIR) $(DESTDIR)$(UCLIBCXX_RUNTIME_BINDIR) $(DESTDIR)$(UCLIBCXX_RUNTIME_INCLUDEDIR):
	$(do_mkdir)
endif
