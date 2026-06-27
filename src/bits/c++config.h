#pragma once
#ifdef ARDUINO_ARCH_ESP32
#include_next <bits/c++config.h>
#endif
#ifdef ARDUINO_ARCH_SAM
#include <arm-none-eabi/bits/c++config.h>
#define _GLIBCXX_EXTERN_TEMPLATE 0
#undef _GTHREAD_USE_MUTEX_TIMEDLOCK
#endif
#ifndef ARDUINO_ARCH_ESP32
#include "../__config"
// 一些GCC特定版本才支持的定义
#define __unlikely__

// 78
//  Macros for deprecated attributes.
//    _GLIBCXX_USE_DEPRECATED
//    _GLIBCXX_DEPRECATED
//    _GLIBCXX_DEPRECATED_SUGGEST( string-literal )
//    _GLIBCXX11_DEPRECATED
//    _GLIBCXX11_DEPRECATED_SUGGEST( string-literal )
//    _GLIBCXX14_DEPRECATED
//    _GLIBCXX14_DEPRECATED_SUGGEST( string-literal )
//    _GLIBCXX17_DEPRECATED
//    _GLIBCXX17_DEPRECATED_SUGGEST( string-literal )
//    _GLIBCXX20_DEPRECATED
//    _GLIBCXX20_DEPRECATED_SUGGEST( string-literal )
//    _GLIBCXX23_DEPRECATED
//    _GLIBCXX23_DEPRECATED_SUGGEST( string-literal )
#ifndef _GLIBCXX_USE_DEPRECATED
#define _GLIBCXX_USE_DEPRECATED 1
#endif

#if defined(__DEPRECATED)
#define _GLIBCXX_DEPRECATED __attribute__((__deprecated__))
#define _GLIBCXX_DEPRECATED_SUGGEST(ALT) \
  __attribute__((__deprecated__("use '" ALT "' instead")))
#else
#define _GLIBCXX_DEPRECATED
#define _GLIBCXX_DEPRECATED_SUGGEST(ALT)
#endif

#if defined(__DEPRECATED) && (__cplusplus >= 201103L)
#define _GLIBCXX11_DEPRECATED _GLIBCXX_DEPRECATED
#define _GLIBCXX11_DEPRECATED_SUGGEST(ALT) _GLIBCXX_DEPRECATED_SUGGEST(ALT)
#else
#define _GLIBCXX11_DEPRECATED
#define _GLIBCXX11_DEPRECATED_SUGGEST(ALT)
#endif

#if defined(__DEPRECATED) && (__cplusplus >= 201402L)
#define _GLIBCXX14_DEPRECATED _GLIBCXX_DEPRECATED
#define _GLIBCXX14_DEPRECATED_SUGGEST(ALT) _GLIBCXX_DEPRECATED_SUGGEST(ALT)
#else
#define _GLIBCXX14_DEPRECATED
#define _GLIBCXX14_DEPRECATED_SUGGEST(ALT)
#endif

#if defined(__DEPRECATED) && (__cplusplus >= 201703L)
#define _GLIBCXX17_DEPRECATED [[__deprecated__]]
#define _GLIBCXX17_DEPRECATED_SUGGEST(ALT) _GLIBCXX_DEPRECATED_SUGGEST(ALT)
#else
#define _GLIBCXX17_DEPRECATED
#define _GLIBCXX17_DEPRECATED_SUGGEST(ALT)
#endif

#if defined(__DEPRECATED) && (__cplusplus >= 202002L)
#define _GLIBCXX20_DEPRECATED [[__deprecated__]]
#define _GLIBCXX20_DEPRECATED_SUGGEST(ALT) _GLIBCXX_DEPRECATED_SUGGEST(ALT)
#else
#define _GLIBCXX20_DEPRECATED
#define _GLIBCXX20_DEPRECATED_SUGGEST(ALT)
#endif

#if defined(__DEPRECATED) && (__cplusplus >= 202100L)
#define _GLIBCXX23_DEPRECATED [[__deprecated__]]
#define _GLIBCXX23_DEPRECATED_SUGGEST(ALT) _GLIBCXX_DEPRECATED_SUGGEST(ALT)
#else
#define _GLIBCXX23_DEPRECATED
#define _GLIBCXX23_DEPRECATED_SUGGEST(ALT)
#endif
// 145
//   150
//    Macro to warn about unused results.
#if __cplusplus >= 201703L
#define _GLIBCXX_NODISCARD [[__nodiscard__]]
#else
#define _GLIBCXX_NODISCARD
#endif
// 157
// 222
//  Macro for noexcept, to support in mixed 03/0x mode.
#if !defined _GLIBCXX_NOEXCEPT || defined ARDUINO_ARCH_SAM // SAM定义了这个，但是没定义_GLIBCXX_NOEXCEPT_IF
#if __cplusplus >= 201103L
#define _GLIBCXX_NOEXCEPT noexcept
#define _GLIBCXX_NOEXCEPT_IF(...) noexcept(__VA_ARGS__)
#define _GLIBCXX_USE_NOEXCEPT noexcept
#define _GLIBCXX_THROW(_EXC)
#else
#define _GLIBCXX_NOEXCEPT
#define _GLIBCXX_NOEXCEPT_IF(...)
#define _GLIBCXX_USE_NOEXCEPT throw()
#define _GLIBCXX_THROW(_EXC) throw(_EXC)
#endif
#endif
// 237
#endif //! ARDUINO_ARCH_ESP32
// 830
#ifdef __has_builtin
#ifdef __is_identifier
// Intel and older Clang require !__is_identifier for some built-ins:
#define _GLIBCXX_HAS_BUILTIN(B) __has_builtin(B) || !__is_identifier(B)
#else
#define _GLIBCXX_HAS_BUILTIN(B) __has_builtin(B)
#endif
#endif
// 839
//  851
//   Returns 1 if _GLIBCXX_DO_NOT_USE_BUILTIN_TRAITS is not defined and the
//   compiler has a corresponding built-in type trait, 0 otherwise.
//   _GLIBCXX_DO_NOT_USE_BUILTIN_TRAITS can be defined to disable the use of
//   built-in traits.
#ifndef _GLIBCXX_DO_NOT_USE_BUILTIN_TRAITS
#define _GLIBCXX_USE_BUILTIN_TRAIT(BT) _GLIBCXX_HAS_BUILTIN(BT)
#else
#define _GLIBCXX_USE_BUILTIN_TRAIT(BT) 0
#endif

#ifdef __cpp_variable_templates
#define _CSL_Struct14Value(StructValue, Arguments...) StructValue<Arguments>
#define _STRUCT14VALUEV(StructValue, Arguments...) StructValue##v<Arguments>
#define _CSL_Struct14Value_V(StructValue, Arguments...) StructValue##_v<Arguments>
#else
#define _GLIBCXX14_CONSTEXPR
#define _CSL_Struct14Value(StructValue, Arguments...) StructValue<Arguments>::value
#define _STRUCT14VALUEV(StructValue, Arguments...) StructValue<Arguments>::value
#define _CSL_Struct14Value_V(StructValue, Arguments...) StructValue<Arguments>::value
#endif

#if !defined _GLIBCXX17_CONSTEXPR || __cplusplus < 202002L
#if __cplusplus >= 201703L
#define _GLIBCXX17_CONSTEXPR constexpr
#define _GLIBCXX17_INLINE inline
#define _GLIBCXX17_STATIC_ASSERT(Bool_constexpr) static_assert(Bool_constexpr);
#else
#define _GLIBCXX17_CONSTEXPR
#define _GLIBCXX17_INLINE
#define _GLIBCXX17_STATIC_ASSERT(Bool_constexpr) static_assert(Bool_constexpr, #Bool_constexpr);
#endif
#endif

// 861
#ifdef ARDUINO_ARCH_AVR
// 40
//  Macros for various attributes.
//    _GLIBCXX_PURE
//    _GLIBCXX_CONST
//    _GLIBCXX_NORETURN
//    _GLIBCXX_NOTHROW
//    _GLIBCXX_VISIBILITY
#ifndef _GLIBCXX_PURE
#define _GLIBCXX_PURE __attribute__((__pure__))
#endif
// 50
//  56
//   See below for C++
#ifndef _GLIBCXX_NOTHROW
#ifndef __cplusplus
#define _GLIBCXX_NOTHROW __attribute__((__nothrow__))
#endif
#endif
// 63
//  68
#if _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
#define _GLIBCXX_VISIBILITY(V) __attribute__((__visibility__(#V)))
#else
// If this is not supplied by the OS-specific or CPU-specific
// headers included below, it will be defined to an empty default.
#define _GLIBCXX_VISIBILITY(V) _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif
// 76
// 155
// Macros for ABI tag attributes.
#ifndef _GLIBCXX_ABI_TAG_CXX11
#define _GLIBCXX_ABI_TAG_CXX11 __attribute((__abi_tag__("cxx11")))
#endif
// 160
//  159
#if __cplusplus

// Macro for constexpr, to support in mixed 03/0x mode.
#ifndef _GLIBCXX_CONSTEXPR
#if __cplusplus >= 201103L
#define _GLIBCXX_CONSTEXPR constexpr
#define _GLIBCXX_USE_CONSTEXPR constexpr
#else
#define _GLIBCXX_CONSTEXPR
#define _GLIBCXX_USE_CONSTEXPR const
#endif
#endif
#endif
// 172
// 237
#ifndef _GLIBCXX_NOTHROW
#define _GLIBCXX_NOTHROW _GLIBCXX_USE_NOEXCEPT
#endif
// 241
//  357
//   Non-zero if inline namespaces are used for versioning the entire library.
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
  inline _GLIBCXX_BEGIN_NAMESPACE_VERSION _GLIBCXX_END_NAMESPACE_VERSION
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
//  683
//   If platform uses neither visibility nor psuedo-visibility,
//   specify empty default for namespace annotation macros.
#ifndef _GLIBCXX_PSEUDO_VISIBILITY
#define _GLIBCXX_PSEUDO_VISIBILITY(V)
#endif
// 689

/* Define to 1 if a full hosted library is built, or 0 if freestanding. */
#define _GLIBCXX_HOSTED 1
// 748
//  This marks string literals in header files to be extracted for eventual
//  translation.  It is primarily used for messages in thrown exceptions; see
//  src/functexcept.cc.  We use __N because the more traditional _N is used
//  for something else under certain OSes (see BADNAMES).
#define __N(msgid) (msgid)

// For example, <windows.h> is known to #define min and max as macros...
#undef min
#undef max
// 758
#endif // ARDUINO_ARCH_AVR
// 159
#ifndef ARDUINO_ARCH_ESP32
#if __cplusplus

// Macro for constexpr, to support in mixed 03/0x mode.
#ifndef _GLIBCXX_CONSTEXPR
#if __cplusplus >= 201103L
#define _GLIBCXX_CONSTEXPR constexpr
#define _GLIBCXX_USE_CONSTEXPR constexpr
#else
#define _GLIBCXX_CONSTEXPR
#define _GLIBCXX_USE_CONSTEXPR const
#endif
#endif

#ifndef _GLIBCXX14_CONSTEXPR
#if __cplusplus >= 201402L
#define _GLIBCXX14_CONSTEXPR constexpr
#else
#define _GLIBCXX14_CONSTEXPR
#endif
#endif

#ifndef _GLIBCXX20_CONSTEXPR
#if __cplusplus >= 202002L
#define _GLIBCXX20_CONSTEXPR constexpr
#else
#define _GLIBCXX20_CONSTEXPR
#endif
#endif

#ifndef _GLIBCXX23_CONSTEXPR
#if __cplusplus >= 202100L
#define _GLIBCXX23_CONSTEXPR constexpr
#else
#define _GLIBCXX23_CONSTEXPR
#endif
#endif

#ifndef _GLIBCXX17_INLINE
#if __cplusplus >= 201703L
#define _GLIBCXX17_INLINE inline
#else
#define _GLIBCXX17_INLINE
#endif
#endif

// Macro for noexcept, to support in mixed 03/0x mode.
#ifndef _GLIBCXX_NOEXCEPT
#if __cplusplus >= 201103L
#define _GLIBCXX_NOEXCEPT noexcept
#define _GLIBCXX_NOEXCEPT_IF(...) noexcept(__VA_ARGS__)
#define _GLIBCXX_USE_NOEXCEPT noexcept
#define _GLIBCXX_THROW(_EXC)
#else
#define _GLIBCXX_NOEXCEPT
#define _GLIBCXX_NOEXCEPT_IF(...)
#define _GLIBCXX_USE_NOEXCEPT throw()
#define _GLIBCXX_THROW(_EXC) throw(_EXC)
#endif
#endif

#ifndef _GLIBCXX_NOTHROW
#define _GLIBCXX_NOTHROW _GLIBCXX_USE_NOEXCEPT
#endif

#ifndef _GLIBCXX_THROW_OR_ABORT
#if __cpp_exceptions
#define _GLIBCXX_THROW_OR_ABORT(_EXC) (throw(_EXC))
#else
#define _GLIBCXX_THROW_OR_ABORT(_EXC) (__builtin_abort())
#endif
#endif

#if __cpp_noexcept_function_type
#define _GLIBCXX_NOEXCEPT_PARM , bool _NE
#define _GLIBCXX_NOEXCEPT_QUAL noexcept(_NE)
#else
#define _GLIBCXX_NOEXCEPT_PARM
#define _GLIBCXX_NOEXCEPT_QUAL
#endif

/*
  Outline of libstdc++ namespaces.

  namespace std
  {
    namespace __debug { }
    namespace __parallel { }
    namespace __cxx1998 { }

    namespace __detail {
      namespace __variant { }				// C++17
    }

    namespace rel_ops { }

    namespace tr1
    {
      namespace placeholders { }
      namespace regex_constants { }
      namespace __detail { }
    }

    namespace tr2 { }

    namespace decimal { }

    namespace chrono { }				// C++11
    namespace placeholders { }				// C++11
    namespace regex_constants { }			// C++11
    namespace this_thread { }				// C++11
    inline namespace literals {				// C++14
      inline namespace chrono_literals { }		// C++14
      inline namespace complex_literals { }		// C++14
      inline namespace string_literals { }		// C++14
      inline namespace string_view_literals { }		// C++17
    }
  }

  namespace abi { }

  namespace __gnu_cxx
  {
    namespace __detail { }
  }

  For full details see:
  http://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/namespaces.html
*/
namespace std
{
  typedef __SIZE_TYPE__ size_t;
  typedef __PTRDIFF_TYPE__ ptrdiff_t;

#if __cplusplus >= 201103L
  typedef decltype(nullptr) nullptr_t;
#endif

#pragma GCC visibility push(default)
  // This allows the library to terminate without including all of <exception>
  // and without making the declaration of std::terminate visible to users.
  extern "C++" __attribute__((__noreturn__, __always_inline__)) inline void __terminate() _GLIBCXX_USE_NOEXCEPT
  {
    void terminate() _GLIBCXX_USE_NOEXCEPT __attribute__((__noreturn__, __cold__));
    terminate();
  }
#pragma GCC visibility pop
}

#if !_GLIBCXX_USE_DUAL_ABI
// Ignore any pre-defined value of _GLIBCXX_USE_CXX11_ABI
#undef _GLIBCXX_USE_CXX11_ABI
#endif

#ifndef _GLIBCXX_USE_CXX11_ABI
#define _GLIBCXX_USE_CXX11_ABI 1
#endif

#if _GLIBCXX_USE_CXX11_ABI
namespace std
{
  inline namespace __cxx11 __attribute__((__abi_tag__("cxx11"))) {
  }
}
namespace __gnu_cxx
{
  inline namespace __cxx11 __attribute__((__abi_tag__("cxx11"))) {
  }
}
#define _GLIBCXX_NAMESPACE_CXX11 __cxx11::
#define _GLIBCXX_BEGIN_NAMESPACE_CXX11 \
  namespace __cxx11                    \
  {
#define _GLIBCXX_END_NAMESPACE_CXX11 }
#define _GLIBCXX_DEFAULT_ABI_TAG _GLIBCXX_ABI_TAG_CXX11
#else
#define _GLIBCXX_NAMESPACE_CXX11
#define _GLIBCXX_BEGIN_NAMESPACE_CXX11
#define _GLIBCXX_END_NAMESPACE_CXX11
#define _GLIBCXX_DEFAULT_ABI_TAG
#endif

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
  inline _GLIBCXX_BEGIN_NAMESPACE_VERSION _GLIBCXX_END_NAMESPACE_VERSION
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

// In the case that we don't have a hosted environment, we can't provide the
// debugging mode.  Instead, we do our best and downgrade to assertions.
#if defined(_GLIBCXX_DEBUG) && !__STDC_HOSTED__
#undef _GLIBCXX_DEBUG
#define _GLIBCXX_ASSERTIONS 1
#endif

// Inline namespaces for special modes: debug, parallel.
#if defined(_GLIBCXX_DEBUG) || defined(_GLIBCXX_PARALLEL)
namespace std
{
  _GLIBCXX_BEGIN_NAMESPACE_VERSION

  // Non-inline namespace for components replaced by alternates in active mode.
  namespace __cxx1998
  {
#if _GLIBCXX_USE_CXX11_ABI
    inline namespace __cxx11 __attribute__((__abi_tag__("cxx11"))) {
    }
#endif
  }

  _GLIBCXX_END_NAMESPACE_VERSION

  // Inline namespace for debug mode.
#ifdef _GLIBCXX_DEBUG
  inline namespace __debug
  {
  }
#endif

  // Inline namespaces for parallel mode.
#ifdef _GLIBCXX_PARALLEL
  inline namespace __parallel
  {
  }
#endif
}

// Check for invalid usage and unsupported mixed-mode use.
#if defined(_GLIBCXX_DEBUG) && defined(_GLIBCXX_PARALLEL)
#error illegal use of multiple inlined namespaces
#endif

// Check for invalid use due to lack for weak symbols.
#if __NO_INLINE__ && !__GXX_WEAK__
#warning currently using inlined namespace mode which may fail \
   without inlining due to lack of weak symbols
#endif
#endif

// Macros for namespace scope. Either namespace std:: or the name
// of some nested namespace within it corresponding to the active mode.
// _GLIBCXX_STD_A
// _GLIBCXX_STD_C
//
// Macros for opening/closing conditional namespaces.
// _GLIBCXX_BEGIN_NAMESPACE_ALGO
// _GLIBCXX_END_NAMESPACE_ALGO
// _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
// _GLIBCXX_END_NAMESPACE_CONTAINER
#if defined(_GLIBCXX_DEBUG)
#define _GLIBCXX_STD_C __cxx1998
#define _GLIBCXX_BEGIN_NAMESPACE_CONTAINER \
  namespace _GLIBCXX_STD_C                 \
  {
#define _GLIBCXX_END_NAMESPACE_CONTAINER }
#else
#define _GLIBCXX_STD_C std
#define _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
#define _GLIBCXX_END_NAMESPACE_CONTAINER
#endif

#ifdef _GLIBCXX_PARALLEL
#define _GLIBCXX_STD_A __cxx1998
#define _GLIBCXX_BEGIN_NAMESPACE_ALGO \
  namespace _GLIBCXX_STD_A            \
  {
#define _GLIBCXX_END_NAMESPACE_ALGO }
#else
#define _GLIBCXX_STD_A std
#define _GLIBCXX_BEGIN_NAMESPACE_ALGO
#define _GLIBCXX_END_NAMESPACE_ALGO
#endif

// GLIBCXX_ABI Deprecated
// Define if compatibility should be provided for -mlong-double-64.
#undef _GLIBCXX_LONG_DOUBLE_COMPAT

// Define if compatibility should be provided for alternative 128-bit long
// double formats. Not possible for Clang until __ibm128 is supported.
#ifndef __clang__
#undef _GLIBCXX_LONG_DOUBLE_ALT128_COMPAT
#endif

// Inline namespaces for long double 128 modes.
#if defined _GLIBCXX_LONG_DOUBLE_ALT128_COMPAT && defined __LONG_DOUBLE_IEEE128__
namespace std
{
  // Namespaces for 128-bit IEEE long double format on 64-bit POWER LE.
  inline namespace __gnu_cxx_ieee128
  {
  }
  inline namespace __gnu_cxx11_ieee128
  {
  }
}
#define _GLIBCXX_NAMESPACE_LDBL __gnu_cxx_ieee128::
#define _GLIBCXX_BEGIN_NAMESPACE_LDBL \
  namespace __gnu_cxx_ieee128         \
  {
#define _GLIBCXX_END_NAMESPACE_LDBL }
#define _GLIBCXX_NAMESPACE_LDBL_OR_CXX11 __gnu_cxx11_ieee128::
#define _GLIBCXX_BEGIN_NAMESPACE_LDBL_OR_CXX11 \
  namespace __gnu_cxx11_ieee128                \
  {
#define _GLIBCXX_END_NAMESPACE_LDBL_OR_CXX11 }

#else // _GLIBCXX_LONG_DOUBLE_ALT128_COMPAT && IEEE128

#if defined _GLIBCXX_LONG_DOUBLE_COMPAT && defined __LONG_DOUBLE_128__
namespace std
{
  inline namespace __gnu_cxx_ldbl128
  {
  }
}
#define _GLIBCXX_NAMESPACE_LDBL __gnu_cxx_ldbl128::
#define _GLIBCXX_BEGIN_NAMESPACE_LDBL \
  namespace __gnu_cxx_ldbl128         \
  {
#define _GLIBCXX_END_NAMESPACE_LDBL }
#else
#define _GLIBCXX_NAMESPACE_LDBL
#define _GLIBCXX_BEGIN_NAMESPACE_LDBL
#define _GLIBCXX_END_NAMESPACE_LDBL
#endif

#if _GLIBCXX_USE_CXX11_ABI
#define _GLIBCXX_NAMESPACE_LDBL_OR_CXX11 _GLIBCXX_NAMESPACE_CXX11
#define _GLIBCXX_BEGIN_NAMESPACE_LDBL_OR_CXX11 _GLIBCXX_BEGIN_NAMESPACE_CXX11
#define _GLIBCXX_END_NAMESPACE_LDBL_OR_CXX11 _GLIBCXX_END_NAMESPACE_CXX11
#else
#define _GLIBCXX_NAMESPACE_LDBL_OR_CXX11 _GLIBCXX_NAMESPACE_LDBL
#define _GLIBCXX_BEGIN_NAMESPACE_LDBL_OR_CXX11 _GLIBCXX_BEGIN_NAMESPACE_LDBL
#define _GLIBCXX_END_NAMESPACE_LDBL_OR_CXX11 _GLIBCXX_END_NAMESPACE_LDBL
#endif

#endif // _GLIBCXX_LONG_DOUBLE_ALT128_COMPAT && IEEE128

namespace std
{
#pragma GCC visibility push(default)
  // Internal version of std::is_constant_evaluated().
  // This can be used without checking if the compiler supports the feature.
  // The macro _GLIBCXX_HAVE_IS_CONSTANT_EVALUATED can be used to check if
  // the compiler support is present to make this function work as expected.
  __attribute__((__always_inline__))
  _GLIBCXX_CONSTEXPR inline bool
  __is_constant_evaluated() _GLIBCXX_NOEXCEPT
  {
#if __cpp_if_consteval >= 202106L
#define _GLIBCXX_HAVE_IS_CONSTANT_EVALUATED 1
    if consteval
    {
      return true;
    }
    else
    {
      return false;
    }
#elif __cplusplus >= 201103L && __has_builtin(__builtin_is_constant_evaluated)
#define _GLIBCXX_HAVE_IS_CONSTANT_EVALUATED 1
    return __builtin_is_constant_evaluated();
#else
    return false;
#endif
  }
#pragma GCC visibility pop
}

// Debug Mode implies checking assertions.
#if defined(_GLIBCXX_DEBUG) && !defined(_GLIBCXX_ASSERTIONS)
#define _GLIBCXX_ASSERTIONS 1
#endif

// Disable std::string explicit instantiation declarations in order to assert.
#ifdef _GLIBCXX_ASSERTIONS
#undef _GLIBCXX_EXTERN_TEMPLATE
#define _GLIBCXX_EXTERN_TEMPLATE -1
#endif

#undef _GLIBCXX_VERBOSE_ASSERT

// Assert.
#ifdef _GLIBCXX_VERBOSE_ASSERT
namespace std
{
#pragma GCC visibility push(default)
  // Don't use <cassert> because this should be unaffected by NDEBUG.
  extern "C++" _GLIBCXX_NORETURN void
      __glibcxx_assert_fail /* Called when a precondition violation is detected. */
      (const char *__file, int __line, const char *__function,
       const char *__condition)
          _GLIBCXX_NOEXCEPT;
#pragma GCC visibility pop
}
#define _GLIBCXX_ASSERT_FAIL(_Condition)                              \
  std::__glibcxx_assert_fail(__FILE__, __LINE__, __PRETTY_FUNCTION__, \
                             #_Condition)
#else // ! VERBOSE_ASSERT
#define _GLIBCXX_ASSERT_FAIL(_Condition) __builtin_abort()
#endif

#if defined(_GLIBCXX_ASSERTIONS)
// Enable runtime assertion checks, and also check in constant expressions.
#define __glibcxx_assert(cond)                \
  do                                          \
  {                                           \
    if (__builtin_expect(!bool(cond), false)) \
      _GLIBCXX_ASSERT_FAIL(cond);             \
  } while (false)
#elif _GLIBCXX_HAVE_IS_CONSTANT_EVALUATED
// Only check assertions during constant evaluation.
namespace std
{
  __attribute__((__always_inline__, __visibility__("default"))) inline void
  __glibcxx_assert_fail()
  {
  }
}
#define __glibcxx_assert(cond)                  \
  do                                            \
  {                                             \
    if (std::__is_constant_evaluated())         \
      if (__builtin_expect(!bool(cond), false)) \
        std::__glibcxx_assert_fail();           \
  } while (false)
#else
// Don't check any assertions.
#define __glibcxx_assert(cond)
#endif

// Macro indicating that TSAN is in use.
#if __SANITIZE_THREAD__
#define _GLIBCXX_TSAN 1
#elif defined __has_feature
#if __has_feature(thread_sanitizer)
#define _GLIBCXX_TSAN 1
#endif
#endif

// Macros for race detectors.
// _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A) and
// _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A) should be used to explain
// atomic (lock-free) synchronization to race detectors:
// the race detector will infer a happens-before arc from the former to the
// latter when they share the same argument pointer.
//
// The most frequent use case for these macros (and the only case in the
// current implementation of the library) is atomic reference counting:
//   void _M_remove_reference()
//   {
//     _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&this->_M_refcount);
//     if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount, -1) <= 0)
//       {
//         _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&this->_M_refcount);
//         _M_destroy(__a);
//       }
//   }
// The annotations in this example tell the race detector that all memory
// accesses occurred when the refcount was positive do not race with
// memory accesses which occurred after the refcount became zero.
#ifndef _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A)
#endif
#ifndef _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A)
#endif

// Macros for C linkage: define extern "C" linkage only when using C++.
#define _GLIBCXX_BEGIN_EXTERN_C \
  extern "C"                    \
  {
#define _GLIBCXX_END_EXTERN_C }

#ifdef __SIZEOF_INT128__
#if !defined __GLIBCXX_TYPE_INT_N_0 && !defined __STRICT_ANSI__
// If __int128 is supported, we expect __GLIBCXX_TYPE_INT_N_0 to be defined
// unless the compiler is in strict mode. If it's not defined and the strict
// macro is not defined, something is wrong.
#warning "__STRICT_ANSI__ seems to have been undefined; this is not supported"
#endif
#endif

#else // !__cplusplus
#define _GLIBCXX_BEGIN_EXTERN_C
#define _GLIBCXX_END_EXTERN_C
#endif
// 675
//  704
//  Conditionally enable annotations for the Transactional Memory TS on C++11.
//  Most of the following conditions are due to limitations in the current
//  implementation.
#if __cplusplus >= 201103L && _GLIBCXX_USE_CXX11_ABI && _GLIBCXX_USE_DUAL_ABI && __cpp_transactional_memory >= 201500L && !_GLIBCXX_FULLY_DYNAMIC_STRING && _GLIBCXX_USE_WEAK_REF && _GLIBCXX_USE_ALLOCATOR_NEW
#define _GLIBCXX_TXN_SAFE transaction_safe
#define _GLIBCXX_TXN_SAFE_DYN transaction_safe_dynamic
#else
#define _GLIBCXX_TXN_SAFE
#define _GLIBCXX_TXN_SAFE_DYN
#endif
// 718
#ifndef __has_cpp_attribute
#define __has_cpp_attribute(A) 0
#endif
#define __constinit
#endif