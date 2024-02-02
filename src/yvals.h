#pragma once
#include <yvals_core.h>
// 51
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
// 203
#ifdef _DEBUG
#define _STL_ASSERT(cond, mesg) _STL_VERIFY(cond, mesg)
#else // ^^^ _DEBUG ^^^ // vvv !_DEBUG vvv
#define _STL_ASSERT(cond, mesg)
#endif // _DEBUG

// 209