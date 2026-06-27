#pragma once
#ifdef ARDUINO_ARCH_AVR
#ifndef _WCHAR_H

/* Workaround PR90731 with GCC 9 when using ldbl redirects in C++.  */
# if defined __cplusplus && __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 1
#  if __GNUC_PREREQ (9, 0) && !__GNUC_PREREQ (9, 3)
#   pragma GCC system_header
#  endif
# endif

# include <wcsmbs/wchar.h>
# ifndef _ISOMAC

#include <stdbool.h>

/* Special version.  We know that all uses of mbsinit inside the libc
   have a non-NULL parameter.  And certainly we can access the
   internals of the data structure directly.  */
#  define mbsinit(state) ((state)->__count == 0)
#  define __mbsinit(state) ((state)->__count == 0)

# endif
#endif
#else
#include_next <wchar.h>
#endif