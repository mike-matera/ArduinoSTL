TOPDIR=../
include $(TOPDIR)Rules.mak

LDFLAGS += -shared -Wl,-soname,$(SHARED_MAJORNAME)
ifneq ($(DODEBUG),y)
LDFLAGS += -Wl,-s
endif

SRCS =	$(wildcard *.cpp)
SRCS += abi/abi.cpp
SRCS := $(filter-out support.cpp,$(SRCS))
SRCS := $(filter-out typeinfo.cpp,$(SRCS))

EXOBJS	:= $(patsubst %.cpp,%.o, $(SRCS))

ALLBIN :=
ifeq ($(BUILD_STATIC_LIB),y)
ALLBIN	+=	$(LIBNAME).a
endif
ifneq ($(BUILD_ONLY_STATIC_LIB),y)
ALLBIN	+=	$(SHARED_FULLNAME)
endif

all:	libgcc_eh libsupc $(EXOBJS) $(ALLBIN)

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
ifneq ($(BUILD_ONLY_STATIC_LIB),y)
	$(INSTALL) -m 755 $(SHARED_FULLNAME) \
		$(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
	cp -fa $(SHARED_MAJORNAME) $(LIBNAME).so $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
endif
ifeq ($(BUILD_STATIC_LIB),y)
	$(INSTALL) -m 644 $(LIBNAME).a $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)
endif

libgcc_eh:
ifeq ($(BUILD_STATIC_LIB),y)
	$(MAKE) -C abi/libgcc_eh all
GCCOBJS := $(wildcard abi/libgcc_eh/*.o)
endif

libsupc:
ifeq ($(IMPORT_LIBSUP),y)
	$(MAKE) -C abi/libsupc all
SUPOBJS = $(wildcard abi/libsupc/*.o)
else
SUPOBJS =
endif

$(LIBNAME).a: libgcc_eh libsupc
	$(AR) $(ARFLAGS) $@ $(EXOBJS) $(GCCOBJS) $(SUPOBJS)
	$(RANLIB) $@

$(SHARED_FULLNAME): libsupc
	$(CC) $(LDFLAGS) -o $@ $(EXOBJS) $(SUPOBJS) $(LIBS)
	$(LN) $@ $(SHARED_MAJORNAME)
	$(LN) $(SHARED_MAJORNAME) $(LIBNAME).so

clean:
	$(MAKE) -C abi/libgcc_eh clean
	$(MAKE) -C abi/libsupc clean
	$(RM) *.o abi/*.o libuClibc++* core

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $<
	$(STRIPTOOL) -x -R .note -R .comment $@
