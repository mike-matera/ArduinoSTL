/*	Copyright (C) 2004 Garrett A. Kajmowicz
	This file is part of the uClibc++ Library.
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __BASIC_DEFINITIONS
#define __BASIC_DEFINITIONS 1

#include "system_configuration.h"

#pragma GCC visibility push(default)

//The following is used to support GCC symbol visibility patch

#ifdef GCC_HASCLASSVISIBILITY
	#define _UCXXEXPORT __attribute__ ((visibility("default")))
	#define _UCXXLOCAL __attribute__ ((visibility("hidden")))
#else
	#define _UCXXEXPORT
	#define _UCXXLOCAL

#endif

#ifdef __GCC__
#define __UCLIBCXX_NORETURN __attribute__ ((__noreturn__))
#else
#define __UCLIBCXX_NORETURN
#endif

#ifdef __GCC__
# ifndef _UCXX_NOTHROW
#  ifndef __cplusplus
#   define _UCXX_NOTHROW __attribute__((__nothrow__))
#  endif
# endif
#endif
#ifdef __cplusplus
# if __cplusplus >= 201103L
#  define _UCXX_NOEXCEPT noexcept
#  define _UCXX_USE_NOEXCEPT noexcept
#  define _UCXX_THROW(_EXCEPTION)
# else
#  define _UCXX_NOEXCEPT
#  define _UCXX_USE_NOEXCEPT throw()
#  define _UCXX_THROW(_EXCEPTION) throw(_EXCEPTION)
# endif
# ifndef _UCXX_NOTHROW
#  define _UCXX_NOTHROW _UCXX_USE_NOEXCEPT
# endif
#endif

#ifdef __UCLIBCXX_HAS_TLS__
	#define __UCLIBCXX_TLS __thread
#else
	#define __UCLIBCXX_TLS
#endif



//Testing purposes
#define __STRING_MAX_UNITS 65535

namespace std{
	typedef signed long int streamsize;
}

#pragma GCC visibility pop

# ifdef __DODEBUG__
	#define UCLIBCXX_DEBUG 1
# else
	#define UCLIBCXX_DEBUG 0
# endif
#endif
