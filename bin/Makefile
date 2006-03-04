TOPDIR=../
include $(TOPDIR)Rules.mak

WRAPPER	= g++-uc

all: $(WRAPPER)

clean:
	$(RM) $(WRAPPER)

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_BINDIR)
	$(INSTALL) -m 755 $(WRAPPER) $(PREFIX)$(UCLIBCXX_RUNTIME_BINDIR)

$(WRAPPER):
	echo "#!/bin/bash" > $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo 'WRAPPER_INCLUDEDIR="$${WRAPPER_INCLUDEDIR:=-I$(UCLIBCXX_RUNTIME_INCLUDEDIR)}"' >> $(WRAPPER)
	echo 'WRAPPER_LIBDIR="$${WRAPPER_LIBDIR:=-L$(UCLIBCXX_RUNTIME_LIBDIR)}"' >> $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo 'WRAPPER_OPTIONS=""' >> $(WRAPPER)
	echo "WRAPPER_LIBS=\"$(LIBS)\"" >> $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo 'WRAPPER_INCLIB="Y"' >> $(WRAPPER)
	echo 'while [ -n "$$1" ]' >> $(WRAPPER)
	echo 'do' >> $(WRAPPER)
	echo '	WRAPPER_OPTIONS="$$WRAPPER_OPTIONS $$1"' >> $(WRAPPER)
	echo '	if [ "$$1" = "-c" -o "$$1" = "-E" -o "$$1" = "-S" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo '		WRAPPER_INCLIB="N"' >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
ifneq ($(strip $(LIBS)),$(strip $(STATIC_LIBS)))
	echo '	if [ "$$1" == "-static" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo "		WRAPPER_LIBS=\"$(STATIC_LIBS)\"" >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
endif
	echo '	shift' >> $(WRAPPER)
	echo 'done' >> $(WRAPPER)
	echo 'if [ "$$WRAPPER_INCLIB" == "Y" ]' >> $(WRAPPER)
	echo 'then' >> $(WRAPPER)
	echo '	WRAPPER_OPTIONS="$$WRAPPER_OPTIONS -nodefaultlibs $$WRAPPER_LIBDIR -l$(LNAME) $$WRAPPER_LIBS"' >> $(WRAPPER)
	echo 'fi' >> $(WRAPPER)
	echo "" >> $(WRAPPER)
ifeq ($(DODEBUG),y)
	echo 'echo $(CXX) $(GEN_CFLAGS) $(GEN_CXXFLAGS) $(EH_CXXFLAGS) $$WRAPPER_INCLUDEDIR $$WRAPPER_OPTIONS' >> $(WRAPPER)
endif
	echo 'exec $(CXX) $(GEN_CFLAGS) $(GEN_CXXFLAGS) $(EH_CXXFLAGS) $$WRAPPER_INCLUDEDIR $$WRAPPER_OPTIONS' >> $(WRAPPER)
	chmod 755 $(WRAPPER)
