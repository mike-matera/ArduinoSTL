#ifndef ARDUINO_ARCH_AVR
#include <locale>
// GCC实现
namespace std
{
	// 44
	//  Definitions for locale::id of standard facets that are specialized.
	locale::id ctype<char>::id;

#ifdef _GLIBCXX_USE_WCHAR_T
	locale::id ctype<wchar_t>::id;
#endif
	// 51
	// 86
	void
	ctype<char>::
		_M_widen_init() const
	{
		char __tmp[sizeof(_M_widen)];
		for (size_t __i = 0; __i < sizeof(_M_widen); ++__i)
			__tmp[__i] = __i;
		do_widen(__tmp, __tmp + sizeof(__tmp), _M_widen);

		_M_widen_ok = 1;
		// Set _M_widen_ok to 2 if memcpy can't be used.
		if (__builtin_memcmp(__tmp, _M_widen, sizeof(_M_widen)))
			_M_widen_ok = 2;
	}
	// 101
}
#endif