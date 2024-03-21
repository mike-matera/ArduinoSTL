#pragma once
#ifndef ARDUINO_ARCH_AVR
#include "../Cpp_Standard_Library.h"
#include CSL_Official(ext/atomicity.h)
#endif
#ifdef ARDUINO_ARCH_ESP32
namespace __gnu_cxx _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

	__attribute__((__always_inline__)) inline bool
	__is_single_threaded() _GLIBCXX_NOTHROW
	{
#ifndef __GTHREADS
		return true;
#elif __has_include(<sys/single_threaded.h>)
		return ::__libc_single_threaded;
#else
		return !__gthread_active_p();
#endif
	}
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
#endif