TOPDIR=../../
include $(TOPDIR)Rules.mak

all:

clean:
	$(RM) *.test *.out

test:
ifeq ($(DODEBUG),y)
	V="$(V)" ./runtests.sh DODEBUG
else
	V="$(V)" ./runtests.sh
endif
