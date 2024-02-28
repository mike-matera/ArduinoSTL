#pragma once
#ifdef ARDUINO_ARCH_AVR
// 68
#if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
#define _GLIBCXX_VISIBILITY(V) __attribute__((__visibility__(#V)))
#else
// If this is not supplied by the OS-specific or CPU-specific
// headers included below, it will be defined to an empty default.
#define _GLIBCXX_VISIBILITY(V) _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif
// 76
// 357
//  Non-zero if inline namespaces are used for versioning the entire library.
#define _GLIBCXX_INLINE_VERSION 0

#if _GLIBCXX_INLINE_VERSION
// Inline namespace for symbol versioning of (nearly) everything in std.
#define _GLIBCXX_BEGIN_NAMESPACE_VERSION \
  namespace __8                          \
  {
#define _GLIBCXX_END_NAMESPACE_VERSION }
// Unused when everything in std is versioned anyway.
#define _GLIBCXX_BEGIN_INLINE_ABI_NAMESPACE(X)
#define _GLIBCXX_END_INLINE_ABI_NAMESPACE(X)

namespace std
{
  inline _GLIBCXX_BEGIN_NAMESPACE_VERSION
#if __cplusplus >= 201402L
      inline namespace literals
  {
    inline namespace chrono_literals
    {
    }
    inline namespace complex_literals
    {
    }
    inline namespace string_literals
    {
    }
#if __cplusplus > 201402L
    inline namespace string_view_literals
    {
    }
#endif // C++17
  }
#endif // C++14
  _GLIBCXX_END_NAMESPACE_VERSION
}

namespace __gnu_cxx
{
  inline _GLIBCXX_BEGIN_NAMESPACE_VERSION
      _GLIBCXX_END_NAMESPACE_VERSION
}

#else
// Unused.
#define _GLIBCXX_BEGIN_NAMESPACE_VERSION
#define _GLIBCXX_END_NAMESPACE_VERSION
// Used to version individual components, e.g. std::_V2::error_category.
#define _GLIBCXX_BEGIN_INLINE_ABI_NAMESPACE(X) \
  inline namespace X                           \
  {
#define _GLIBCXX_END_INLINE_ABI_NAMESPACE(X) } // inline namespace X
#endif
// 399
// 683
//  If platform uses neither visibility nor psuedo-visibility,
//  specify empty default for namespace annotation macros.
#ifndef _GLIBCXX_PSEUDO_VISIBILITY
#define _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif
// 689
/* Define if code specialized for wchar_t should be used. */
#define _GLIBCXX_USE_WCHAR_T 1
#else
#include "../Cpp_Standard_Library.h"
#ifdef ARDUINO_ARCH_SAM
#include CSL_Official(arm-none-eabi/bits/c++config.h)
# define _GLIBCXX_EXTERN_TEMPLATE 0
#endif
#ifdef ARDUINO_ARCH_ESP32
#include CSL_Official(xtensa-esp32s3-elf/bits/c++config.h)
#endif
#endif