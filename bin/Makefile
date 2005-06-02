TOPDIR=../
include $(TOPDIR)Rules.mak

WRAPPER	= g++-uc

INITIALOPTIONS	=
EXTRALIBS	=

ifneq ($(IMPORT_LIBSUP),y)
EXTRALIBS += -lsupc++
endif

ifneq ($(UCLIBCXX_EXCEPTION_SUPPORT),y)
INITIALOPTIONS	+= -fno-exceptions -fno-rtti
endif

# User defines:

all: $(WRAPPER)

clean:
	rm -f $(WRAPPER)

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_BIN_SUBDIR)
	$(INSTALL) -m 755 $(WRAPPER) $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_BIN_SUBDIR)

$(WRAPPER):
	echo "#!/bin/bash" > $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo "OPTIONS=\"$(INITIALOPTIONS)\"" >> $(WRAPPER)
	echo "if $(LD) --help | grep -q \"as-needed\"" >> $(WRAPPER)
	echo 'then' >> $(WRAPPER)
	echo '  LIBGCC_LIB="-Wl,--as-needed -lgcc_s -Wl,--no-as-needed"' >> $(WRAPPER)
	echo 'else' >> $(WRAPPER)
	echo '  LIBGCC_LIB="-lgcc_s"' >> $(WRAPPER)
	echo 'fi' >> $(WRAPPER)
	echo "" >> $(WRAPPER)
	echo 'INCLIB="Y"' >> $(WRAPPER)
	echo 'while [ -n "$$1" ]' >> $(WRAPPER)
	echo 'do' >> $(WRAPPER)
	echo '	OPTIONS="$$OPTIONS $$1"' >> $(WRAPPER)
	echo '	if [ "$$1" == "-c" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo '		INCLIB="N"' >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
	echo '	if [ "$$1" == "-static" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo '		LIBGCC_LIB="-lgcc"' >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
	echo '	shift' >> $(WRAPPER)
	echo 'done' >> $(WRAPPER)
	echo 'if [ "$$INCLIB" == "Y" ]' >> $(WRAPPER)
	echo 'then' >> $(WRAPPER)
	echo '	OPTIONS="$$OPTIONS -luClibc++ $(EXTRALIBS) -lc $$LIBGCC_LIB"' >> $(WRAPPER)
	echo 'fi' >> $(WRAPPER)
	echo -n "exec $(CXX) " >> $(WRAPPER)
	echo -n ' -fno-builtin -nostdinc++ -nodefaultlibs' >> $(WRAPPER)
	echo -n ' -I$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_INCLUDE_SUBDIR)' >> $(WRAPPER)
	echo -n ' -L$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_LIB_SUBDIR)' >> $(WRAPPER)
	echo ' $$OPTIONS' >> $(WRAPPER)
	chmod 755 $(WRAPPER)
