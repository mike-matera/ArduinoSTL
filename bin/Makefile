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
	echo 'INCLIB="Y"' >> $(WRAPPER)
	echo 'while [ -n "$$1" ]' >> $(WRAPPER)
	echo 'do' >> $(WRAPPER)
	echo '	OPTIONS="$$OPTIONS $$1"' >> $(WRAPPER)
	echo '	if [ "$$1" == "-c" ]' >> $(WRAPPER)
	echo '	then' >> $(WRAPPER)
	echo '		INCLIB="N"' >> $(WRAPPER)
	echo '	fi' >> $(WRAPPER)
	echo '	shift' >> $(WRAPPER)
	echo 'done' >> $(WRAPPER)
	echo 'if [ "$$INCLIB" == "Y" ]' >> $(WRAPPER)
	echo 'then' >> $(WRAPPER)
	echo '	OPTIONS="$$OPTIONS -luClibc++ -lc $(EXTRALIBS)"' >> $(WRAPPER)
	echo 'fi' >> $(WRAPPER)
	echo -n "$(CXX) " >> $(WRAPPER)
	echo -n ' -fno-builtin -nostdinc++ -nodefaultlibs -I' >> $(WRAPPER)
	echo -n $(UCLIBCXX_RUNTIME_PREFIX) >> $(WRAPPER)
	echo -n '/include/ -L' >> $(WRAPPER)
	echo -n $(UCLIBCXX_RUNTIME_PREFIX) >> $(WRAPPER)
	echo '/lib/ $$OPTIONS' >> $(WRAPPER)
	chmod 755 $(WRAPPER)
