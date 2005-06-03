TOPDIR=../
include $(TOPDIR)Rules.mak

all:

clean:

distclean:

install:
	$(INSTALL) -d $(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_INCLUDE_SUBDIR)
	$(INSTALL) -m 644 `ls --color=never --ignore="CVS" --ignore="Makefile"` \
		$(PREFIX)$(UCLIBCXX_RUNTIME_PREFIX)$(UCLIBCXX_RUNTIME_INCLUDE_SUBDIR)

