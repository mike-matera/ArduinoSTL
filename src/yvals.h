#pragma once
#include "sal.h"
#include "crtdbg.h"
#include "crtdefs.h"
// 29
#if defined(MRTDLL) && defined(_CRTBLD)
// process-global is the default for code built with /clr or /clr:oldSyntax.
// appdomain-global is the default for code built with /clr:pure.
// Code in MSVCM is built with /clr, but is used by user code built with /clr:pure
// so it must conform to the expectations of /clr:pure clients.
// Use __PURE_APPDOMAIN_GLOBAL when a global needs to be appdomain-global for pure
// clients and process-global for mixed clients.
#define __PURE_APPDOMAIN_GLOBAL __declspec(appdomain)
#else
#define __PURE_APPDOMAIN_GLOBAL
#endif
// 41
//  51
#ifdef _ITERATOR_DEBUG_LEVEL // A. _ITERATOR_DEBUG_LEVEL is already defined.

// A1. Validate _ITERATOR_DEBUG_LEVEL.
#if _ITERATOR_DEBUG_LEVEL > 2 && defined(_DEBUG)
#error _ITERATOR_DEBUG_LEVEL > 2 is not supported in debug mode.
#elif _ITERATOR_DEBUG_LEVEL > 1 && !defined(_DEBUG)
#error _ITERATOR_DEBUG_LEVEL > 1 is not supported in release mode.
#endif

// A2. Inspect _HAS_ITERATOR_DEBUGGING.
#ifdef _HAS_ITERATOR_DEBUGGING // A2i. _HAS_ITERATOR_DEBUGGING is already defined, validate it.
#if _ITERATOR_DEBUG_LEVEL == 2 && _HAS_ITERATOR_DEBUGGING != 1
#error _ITERATOR_DEBUG_LEVEL == 2 must imply _HAS_ITERATOR_DEBUGGING == 1.
#elif _ITERATOR_DEBUG_LEVEL < 2 && _HAS_ITERATOR_DEBUGGING != 0
#error _ITERATOR_DEBUG_LEVEL < 2 must imply _HAS_ITERATOR_DEBUGGING == 0.
#endif
#else // A2ii. _HAS_ITERATOR_DEBUGGING is not yet defined, derive it.
#if _ITERATOR_DEBUG_LEVEL == 2
#define _HAS_ITERATOR_DEBUGGING 1
#else
#define _HAS_ITERATOR_DEBUGGING 0
#endif
#endif // _HAS_ITERATOR_DEBUGGING

// A3. Inspect _SECURE_SCL.
#ifdef _SECURE_SCL // A3i. _SECURE_SCL is already defined, validate it.
#if _ITERATOR_DEBUG_LEVEL > 0 && _SECURE_SCL != 1
#error _ITERATOR_DEBUG_LEVEL > 0 must imply _SECURE_SCL == 1.
#elif _ITERATOR_DEBUG_LEVEL == 0 && _SECURE_SCL != 0
#error _ITERATOR_DEBUG_LEVEL == 0 must imply _SECURE_SCL == 0.
#endif
#else // A3ii. _SECURE_SCL is not yet defined, derive it.
#if _ITERATOR_DEBUG_LEVEL > 0
#define _SECURE_SCL 1
#else
#define _SECURE_SCL 0
#endif
#endif // _SECURE_SCL

#else						   // B. _ITERATOR_DEBUG_LEVEL is not yet defined.

// B1. Inspect _HAS_ITERATOR_DEBUGGING.
#ifdef _HAS_ITERATOR_DEBUGGING // B1i. _HAS_ITERATOR_DEBUGGING is already defined, validate it.
#if _HAS_ITERATOR_DEBUGGING > 1
#error _HAS_ITERATOR_DEBUGGING must be either 0 or 1.
#elif _HAS_ITERATOR_DEBUGGING == 1 && !defined(_DEBUG)
#error _HAS_ITERATOR_DEBUGGING == 1 is not supported in release mode.
#endif
#else // B1ii. _HAS_ITERATOR_DEBUGGING is not yet defined, default it.
#ifdef _DEBUG
#define _HAS_ITERATOR_DEBUGGING 1
#else
#define _HAS_ITERATOR_DEBUGGING 0
#endif
#endif			   // _HAS_ITERATOR_DEBUGGING

// B2. Inspect _SECURE_SCL.
#ifdef _SECURE_SCL // B2i. _SECURE_SCL is already defined, validate it.
#if _SECURE_SCL > 1
#error _SECURE_SCL must be either 0 or 1.
#endif
#else // B2ii. _SECURE_SCL is not yet defined, default it.
#if _HAS_ITERATOR_DEBUGGING == 1
#define _SECURE_SCL 1
#else
#define _SECURE_SCL 0
#endif
#endif // _SECURE_SCL

// B3. Derive _ITERATOR_DEBUG_LEVEL.
#if _HAS_ITERATOR_DEBUGGING
#define _ITERATOR_DEBUG_LEVEL 2
#elif _SECURE_SCL
#define _ITERATOR_DEBUG_LEVEL 1
#else
#define _ITERATOR_DEBUG_LEVEL 0
#endif

#endif // _ITERATOR_DEBUG_LEVEL
// 131
// 171
#ifndef _STL_CRT_SECURE_INVALID_PARAMETER
#ifdef _STL_CALL_ABORT_INSTEAD_OF_INVALID_PARAMETER
#define _STL_CRT_SECURE_INVALID_PARAMETER(expr) _CSTD abort()
#elif defined(_DEBUG)							// avoid emitting unused long strings for function names; see GH-1956
#define _STL_CRT_SECURE_INVALID_PARAMETER(expr) // Arduino不支持 ::_invalid_parameter(_CRT_WIDE(#expr), L"", __FILEW__, __LINE__, 0)
#else											// ^^^ defined(_DEBUG) / !defined(_DEBUG) vvv
#define _STL_CRT_SECURE_INVALID_PARAMETER(expr) _CRT_SECURE_INVALID_PARAMETER(expr)
#endif // ^^^ !defined(_DEBUG) ^^^
#endif // _STL_CRT_SECURE_INVALID_PARAMETER

#define _STL_REPORT_ERROR(mesg)                  \
	do                                           \
	{                                            \
		_RPTF0(_CRT_ASSERT, mesg);               \
		_STL_CRT_SECURE_INVALID_PARAMETER(mesg); \
	} while (false)

#ifdef __clang__
#define _STL_VERIFY(cond, mesg)                                                          \
	_Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wassume\"") do \
	{                                                                                    \
		if (cond)                                                                        \
		{ /* contextually convertible to bool paranoia */                                \
		}                                                                                \
		else                                                                             \
		{                                                                                \
			_STL_REPORT_ERROR(mesg);                                                     \
		}                                                                                \
                                                                                         \
		_Analysis_assume_(cond);                                                         \
	}                                                                                    \
	while (false)                                                                        \
	_Pragma("clang diagnostic pop")
#else // ^^^ Clang / MSVC vvv
#define _STL_VERIFY(cond, mesg)                           \
	do                                                    \
	{                                                     \
		if (cond)                                         \
		{ /* contextually convertible to bool paranoia */ \
		}                                                 \
		else                                              \
		{                                                 \
			_STL_REPORT_ERROR(mesg);                      \
		}                                                 \
                                                          \
		_Analysis_assume_(cond);                          \
	} while (false)
#endif // ^^^ MSVC ^^^

#ifdef _DEBUG
#define _STL_ASSERT(cond, mesg) _STL_VERIFY(cond, mesg)
#else // ^^^ defined(_DEBUG) / !defined(_DEBUG) vvv
#define _STL_ASSERT(cond, mesg) _Analysis_assume_(cond)
#endif // ^^^ !defined(_DEBUG) ^^^
// 217
// 269
#ifndef _CRTIMP2_PURE
#ifdef _M_CEE_PURE
#define _CRTIMP2_PURE
#else
#define _CRTIMP2_PURE _CRTIMP2
#endif
#endif // _CRTIMP2_PURE
// 277
//   285
#ifndef _CRTIMP2_IMPORT
#if defined(CRTDLL2) && defined(_CRTBLD)
#define _CRTIMP2_IMPORT __declspec(dllexport)
#elif defined(_DLL) && !defined(_STATIC_CPPLIB)
#define _CRTIMP2_IMPORT __declspec(dllimport)
#else
#define _CRTIMP2_IMPORT
#endif
#endif // _CRTIMP2_IMPORT
// 295
// 311
#ifndef _CRTDATA2_IMPORT
#if defined(MRTDLL) && defined(_CRTBLD)
#define _CRTDATA2_IMPORT
#else
#define _CRTDATA2_IMPORT _CRTIMP2_IMPORT
#endif
#endif // _CRTDATA2_IMPORT
	   // 319