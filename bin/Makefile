TOPDIR=../
include $(TOPDIR)Rules.mak

WRAPPERNAME	= g++-uc

# User defines:

all:	wrapper

wrapper:
	echo "#!/bin/bash" > $(WRAPPERNAME)
	echo "" >> $(WRAPPERNAME)
	echo 'OPTIONS=""' >> $(WRAPPERNAME)
	echo 'INCLIB="Y"' >> $(WRAPPERNAME)
	echo 'while [ -n "$$1" ]' >> $(WRAPPERNAME)
	echo 'do' >> $(WRAPPERNAME)
	echo '	OPTIONS="$$OPTIONS $$1"' >> $(WRAPPERNAME)
	echo '	if [ "$$1" == "-c" ]' >> $(WRAPPERNAME)
	echo '	then' >> $(WRAPPERNAME)
	echo '		INCLIB="N"' >> $(WRAPPERNAME)
	echo '	fi' >> $(WRAPPERNAME)
	echo '	shift' >> $(WRAPPERNAME)
	echo 'done' >> $(WRAPPERNAME)
	echo 'if [ "$$INCLIB" == "Y" ]' >> $(WRAPPERNAME)
	echo 'then' >> $(WRAPPERNAME)
	echo '	OPTIONS="$$OPTIONS -luClibc++"' >> $(WRAPPERNAME)
	echo 'fi' >> $(WRAPPERNAME)
	echo -n 'g++ -fno-builtin -nostdinc++ -nodefaultlibs -I' >> $(WRAPPERNAME)
	echo -n $(UCLIBCXX_RUNTIME_PREFIX) >> $(WRAPPERNAME)
	echo -n '/include/ -L' >> $(WRAPPERNAME)
	echo -n $(UCLIBCXX_RUNTIME_PREFIX) >> $(WRAPPERNAME)
	echo '/lib/ $$OPTIONS' >> $(WRAPPERNAME)
	chmod 755 $(WRAPPERNAME)
clean:
	rm -f g++-uc

