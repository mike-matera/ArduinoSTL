#pragma once
#ifdef ARDUINO_ARCH_AVR
#ifndef _LANGINFO_H

#ifndef _ISOMAC
libc_hidden_proto (nl_langinfo)

extern __typeof (nl_langinfo_l) __nl_langinfo_l;
libc_hidden_proto (__nl_langinfo_l)
#endif

#endif
#else
#include "Cpp_Standard_Library.h"
#include _CSL_OfficialC(langinfo.h)
#endif