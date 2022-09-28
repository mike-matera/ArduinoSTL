#pragma once
#include <vcruntime.h>
//657
// Functions that became constexpr in C++20
#if _HAS_CXX20
#define _CONSTEXPR20 constexpr
#else // ^^^ constexpr in C++20 and later / inline (not constexpr) in C++17 and earlier vvv
#define _CONSTEXPR20 inline
#endif // ^^^ inline (not constexpr) in C++17 and earlier ^^^

// Functions that became constexpr in C++23
#if _HAS_CXX23
#define _CONSTEXPR23 constexpr
#else // ^^^ constexpr in C++23 and later / inline (not constexpr) in C++20 and earlier vvv
#define _CONSTEXPR23 inline
#endif // ^^^ inline (not constexpr) in C++20 and earlier ^^^

// P0607R0 Inline Variables For The STL
#if _HAS_CXX17
#define _INLINE_VAR inline
#else // _HAS_CXX17
#define _INLINE_VAR
#endif // _HAS_CXX17
//678
//1557
#define _STD_BEGIN namespace std {
#define _STD_END   }
#define _STD       ::std::
#define _CHRONO    ::std::chrono::
#define _RANGES    ::std::ranges::
//1563