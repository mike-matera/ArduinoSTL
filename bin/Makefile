TOPDIR=../
include $(TOPDIR)Rules.mak

WRAPPER	= g++-uc

all: $(WRAPPER)

clean:
	$(RM) $(WRAPPER)

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_BINDIR)
	$(INSTALL) -m 755 $(WRAPPER) $(PREFIX)$(UCLIBCXX_RUNTIME_BINDIR)

$(WRAPPER): Makefile
	echo '#!/bin/sh' > $@
	echo '' >> $@
	echo 'WRAPPER_INCLUDEDIR="$${WRAPPER_INCLUDEDIR:=-I$(UCLIBCXX_RUNTIME_INCLUDEDIR)}"' >> $@
	echo 'WRAPPER_LIBDIR="$${WRAPPER_LIBDIR:=-L$(UCLIBCXX_RUNTIME_LIBDIR)}"' >> $@
	echo '' >> $@
	echo 'WRAPPER_OPTIONS=""' >> $@
	echo 'WRAPPER_LIBS="$(LIBS)"' >> $@
	echo '' >> $@
	echo 'WRAPPER_INCLIB="Y"' >> $@
	echo 'while [ -n "$$1" ]' >> $@
	echo 'do' >> $@
	echo '	WRAPPER_OPTIONS="$$WRAPPER_OPTIONS $$1"' >> $@
	echo '	if [ "$$1" = "-c" -o "$$1" = "-E" -o "$$1" = "-S" -o "$$1" = "-MF" ]' >> $@
	echo '	then' >> $@
	echo '		WRAPPER_INCLIB="N"' >> $@
	echo '	fi' >> $@
ifneq ($(strip $(LIBS)),$(strip $(STATIC_LIBS)))
	echo '	if [ "$$1" = "-static" ]' >> $@
	echo '	then' >> $@
	echo '		WRAPPER_LIBS="$(STATIC_LIBS)"' >> $@
	echo '	fi' >> $@
endif
	echo '	shift' >> $@
	echo 'done' >> $@
	echo 'if [ "$$WRAPPER_INCLIB" = "Y" ]' >> $@
	echo 'then' >> $@
	echo '	WRAPPER_OPTIONS="$$WRAPPER_OPTIONS -nodefaultlibs $$WRAPPER_LIBDIR -l$(LNAME) $$WRAPPER_LIBS"' >> $@
	echo 'fi' >> $@
	echo '' >> $@
ifeq ($(DODEBUG),y)
	echo 'echo $(CXX) $(GEN_CFLAGS) $(GEN_CXXFLAGS) $(EH_CXXFLAGS) $$WRAPPER_INCLUDEDIR $$WRAPPER_OPTIONS' >> $@
endif
	echo 'exec $(CXX) $(GEN_CFLAGS) $(GEN_CXXFLAGS) $(EH_CXXFLAGS) $$WRAPPER_INCLUDEDIR $$WRAPPER_OPTIONS' >> $@
	chmod 755 $@
