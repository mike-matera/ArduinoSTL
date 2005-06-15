TOPDIR=../../
include $(TOPDIR)Rules.mak

all:

clean:
	$(RM) *.test *.out

test:
ifeq ($(DODEBUG),y)
	./runtests.sh DODEBUG
else
	./runtests.sh
endif
