#pragma once
//Arduino平台不适用的调用规约
#define __thiscall
#define __cdecl
// 139
//  Definitions of calling conventions used code sometimes compiled as managed
#if defined _M_CEE_PURE || defined MRTDLL
#define __CLRCALL_OR_CDECL __clrcall
#define __CLR_OR_THIS_CALL __clrcall
#else
#define __CLRCALL_OR_CDECL __cdecl
#define __CLR_OR_THIS_CALL
#endif

#ifdef _M_CEE_PURE
#define __CLRCALL_PURE_OR_CDECL __clrcall
#elif defined(__cdecl)
#define __CLRCALL_PURE_OR_CDECL __cdecl
#else
#define __CLRCALL_PURE_OR_CDECL
#endif
// 154
// 264
#ifdef __cplusplus
#if defined(_MSVC_LANG) && _MSVC_LANG > __cplusplus
#define _STL_LANG _MSVC_LANG
#else // ^^^ language mode is _MSVC_LANG / language mode is __cplusplus vvv
#define _STL_LANG __cplusplus
#endif // ^^^ language mode is larger of _MSVC_LANG and __cplusplus ^^^
#else  // ^^^ determine compiler's C++ mode / no C++ support vvv
#define _STL_LANG 0L
#endif // ^^^ no C++ support ^^^

#ifndef _HAS_CXX14
#if _STL_LANG > 201103L
#define _HAS_CXX14 1
#else
#define _HAS_CXX14 0
#endif
#endif // _HAS_CXX14

#ifndef _HAS_CXX17
#if _STL_LANG > 201402L
#define _HAS_CXX17 1
#else
#define _HAS_CXX17 0
#endif
#endif // _HAS_CXX17

#ifndef _HAS_CXX20
#if _HAS_CXX17 && _STL_LANG > 201703L
#define _HAS_CXX20 1
#else
#define _HAS_CXX20 0
#endif
#endif // _HAS_CXX20

#ifndef _HAS_CXX23
#if _HAS_CXX20 && _STL_LANG > 202002L
#define _HAS_CXX23 1
#else
#define _HAS_CXX23 0
#endif
#endif // _HAS_CXX23

#undef _STL_LANG
// 300
// 319
#if _HAS_NODISCARD
#define _NODISCARD [[nodiscard]]
#else // ^^^ CAN HAZ [[nodiscard]] / NO CAN HAZ [[nodiscard]] vvv
#define _NODISCARD
#endif // _HAS_NODISCARD
       // 325