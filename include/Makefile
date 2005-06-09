TOPDIR=../
include $(TOPDIR)Rules.mak

all:

clean:

distclean:

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_INCLUDEDIR)
	$(INSTALL) -m 644 `ls --color=never --ignore="CVS" --ignore="Makefile"` \
		$(PREFIX)$(UCLIBCXX_RUNTIME_INCLUDEDIR)

