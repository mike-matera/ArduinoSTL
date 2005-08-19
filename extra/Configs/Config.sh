#
# For a description of the syntax of this configuration file,
# see extra/config/Kconfig-language.txt
#

config TARGET_ARCH
	default "sh" if CONFIG_SH2 || CONFIG_SH3 || CONFIG_SH4
	default "sh64" if CONFIG_SH5

config ARCH_SUPPORTS_LITTLE_ENDIAN
	bool
	default y

config ARCH_SUPPORTS_BIG_ENDIAN
	bool
	default y

config ARCH_CFLAGS
	string

config HAVE_DOT_HIDDEN
	bool
	default y

config UCLIBC_COMPLETELY_PIC
	bool
	default y

choice
	prompt "Target Processor Type"
	default CONFIG_SH4
	help
	  This is the processor type of your CPU. This information is used for
	  optimizing purposes, as well as to determine if your CPU has an MMU,
	  an FPU, etc.  If you pick the wrong CPU type, there is no guarantee
	  that uClibc will work at all....

	  Here are the available choices:
	  - "SH2" SuperH SH-2
	  - "SH3" SuperH SH-3
	  - "SH4" SuperH SH-4
	  - "SH5" SuperH SH-5 101, 103

config CONFIG_SH2
	bool "SH2"

config CONFIG_SH3
	bool "SH3"

config CONFIG_SH4
	bool "SH4"

config CONFIG_SH5
	bool "SH5"

endchoice


