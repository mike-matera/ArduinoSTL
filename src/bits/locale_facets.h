#pragma once
#ifndef ARDUINO_ARCH_AVR
#include "../Cpp_Standard_Library.h"
#include _CSL_Official(bits/locale_facets.h) //SAM不支持include_next，必须用宏
#define _GLIBCXX_USE_DUAL_ABI 0
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
// 56
//  Number of duplicated facets for cxx11 ABI
#define _GLIBCXX_NUM_CXX11_FACETS (_GLIBCXX_USE_DUAL_ABI ? 8 : 0)

// codecvt<char16_t> and codecvt<char32_t>
#ifdef _GLIBCXX_USE_CHAR8_T
#define _GLIBCXX_NUM_UNICODE_FACETS 4
#else
#define _GLIBCXX_NUM_UNICODE_FACETS 2
#endif
	// 66
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
#endif