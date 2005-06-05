TOPDIR=../
include $(TOPDIR)Rules.mak

WRAPPER	= g++-uc

all: $(WRAPPER)

clean:
	$(RM) $(WRAPPER)

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_BIN_SUBDIR)
	$(INSTALL) -m 755 $(WRAPPER) $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_BIN_SUBDIR)

$(WRAPPER):
	echo "#!/bin/bash" > $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo 'WRAPPER_OPTIONS=""' >> $(WRAPPER)
	echo "WRAPPER_LIBS=\"$(LIBS)\"" >> $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo 'WRAPPER_INCLIB="Y"' >> $(WRAPPER)
	echo 'while [ -n "$$1" ]' >> $(WRAPPER)
	echo 'do' >> $(WRAPPER)
	echo '	WRAPPER_OPTIONS="$$WRAPPER_OPTIONS $$1"' >> $(WRAPPER)
	echo '	if [ "$$1" == "-c" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo '		WRAPPER_INCLIB="N"' >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
ifneq ($(IMPORT_LIBGCC_EH),y)
	echo '	if [ "$$1" == "-static" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo "		WRAPPER_LIBS=\"$(STATIC_LIBS)\"" >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
endif
	echo '	shift' >> $(WRAPPER)
	echo 'done' >> $(WRAPPER)
	echo 'if [ "$$WRAPPER_INCLIB" == "Y" ]' >> $(WRAPPER)
	echo 'then' >> $(WRAPPER)
	echo '	WRAPPER_OPTIONS="$$WRAPPER_OPTIONS -l$(LNAME) $$WRAPPER_LIBS"' >> $(WRAPPER)
	echo 'fi' >> $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo -n "exec $(CXX) $(GEN_CFLAGS) $(GEN_CXXFLAGS) $(EH_CXXFLAGS)" >> $(WRAPPER)
	echo -n ' -I$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_INCLUDE_SUBDIR)' >> $(WRAPPER)
	echo -n ' -L$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)' >> $(WRAPPER)
	echo ' $$WRAPPER_OPTIONS' >> $(WRAPPER)
	chmod 755 $(WRAPPER)
