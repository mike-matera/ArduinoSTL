#pragma once
#include <vcruntime.h>
// 461
#ifndef __has_cpp_attribute
#define _HAS_MSVC_ATTRIBUTE(x) 0
#elif defined(__CUDACC__) // TRANSITION, CUDA - warning: attribute namespace "msvc" is unrecognized
#define _HAS_MSVC_ATTRIBUTE(x) 0
#else
#define _HAS_MSVC_ATTRIBUTE(x) __has_cpp_attribute(msvc::x)
#endif

// Should we use [[msvc::known_semantics]] to tell the compiler that certain
// type trait specializations have the standard-mandated semantics?
#if _HAS_MSVC_ATTRIBUTE(known_semantics)
#define _MSVC_KNOWN_SEMANTICS [[msvc::known_semantics]]
#else
#define _MSVC_KNOWN_SEMANTICS
#endif
// 477
// 512
#if defined(__CUDACC__) && !defined(__clang__) // TRANSITION, VSO-568006
#define _NODISCARD_FRIEND friend
#else // ^^^ workaround ^^^ / vvv no workaround vvv
#define _NODISCARD_FRIEND _NODISCARD friend
#endif // TRANSITION, VSO-568006
// 518
// 553
// _HAS_NODISCARD (in vcruntime.h) controls:
// [[nodiscard]] attributes on STL functions

// TRANSITION, This should go to vcruntime.h
#ifdef __has_cpp_attribute
#if __has_cpp_attribute(nodiscard) >= 201907L
#define _NODISCARD_MSG(_Msg) [[nodiscard(_Msg)]]
#elif __has_cpp_attribute(nodiscard) >= 201603L
#define _NODISCARD_MSG(_Msg) [[nodiscard]]
#else
#define _NODISCARD_MSG(_Msg)
#endif
#else
#define _NODISCARD_MSG(_Msg)
#endif
// 567
//  611
#define _NODISCARD_EMPTY_NON_MEMBER                                                                            \
	_NODISCARD_MSG(                                                                                            \
		"This function returns a bool indicating whether the container or container-like object is empty and " \
		"has no other effects. It is not useful to call this function and discard the return value.")
// 616
// 657
//  Functions that became constexpr in C++20
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
// 678
// 722
//  Should we use [[msvc::intrinsic]] allowing the compiler to implement the
//  behavior of certain trivial functions?
#if _HAS_MSVC_ATTRIBUTE(intrinsic)
#define _MSVC_INTRINSIC [[msvc::intrinsic]]
#else
#define _MSVC_INTRINSIC
#endif
// 730
// 849
//  P2465R3 Standard Library Modules std And std.compat
#if _HAS_CXX23 && defined(_BUILD_STD_MODULE)
#define _EXPORT_STD export
#else // _HAS_CXX23 && defined(_BUILD_STD_MODULE)
#define _EXPORT_STD
#endif // _HAS_CXX23 && defined(_BUILD_STD_MODULE)
// 856
// 908
// Functions that became constexpr in C++17
#if _HAS_CXX17
#define _CONSTEXPR17 constexpr
#else // ^^^ constexpr in C++17 and later / inline (not constexpr) in C++14 vvv
#define _CONSTEXPR17 inline
#endif // ^^^ inline (not constexpr) in C++14 ^^^

// Functions that became constexpr in C++14
#if _HAS_CXX14
#define _CONSTEXPR14(Alternatve) constexpr
#else // ^^^ constexpr in C++14 and later / inline (not constexpr) in C++11 vvv
#define _CONSTEXPR14(Alternative) Alternative
#endif // ^^^ inline (not constexpr) in C++11 ^^^
// 915
//  1358
#if _HAS_CXX20
#define __cpp_lib_assume_aligned 201811L
#define __cpp_lib_atomic_flag_test 201907L
#define __cpp_lib_atomic_float 201711L
#define __cpp_lib_atomic_lock_free_type_aliases 201907L
#define __cpp_lib_atomic_ref 201806L
#define __cpp_lib_atomic_shared_ptr 201711L
#define __cpp_lib_atomic_wait 201907L
#define __cpp_lib_barrier 201907L
#define __cpp_lib_bind_front 201907L
#define __cpp_lib_bit_cast 201806L
#define __cpp_lib_bitops 201907L
#define __cpp_lib_bounded_array_traits 201902L

#if !defined(__EDG__) || defined(__INTELLISENSE__) // TRANSITION, EDG concepts support
#define __cpp_lib_concepts 202002L
#endif // !defined(__EDG__) || defined(__INTELLISENSE__)

#define __cpp_lib_constexpr_algorithms 201806L
#define __cpp_lib_constexpr_complex 201711L
#define __cpp_lib_constexpr_dynamic_alloc 201907L
#define __cpp_lib_constexpr_functional 201907L
#define __cpp_lib_constexpr_iterator 201811L
#define __cpp_lib_constexpr_numeric 201911L
#define __cpp_lib_constexpr_string 201907L
#define __cpp_lib_constexpr_string_view 201811L
#define __cpp_lib_constexpr_tuple 201811L
#define __cpp_lib_constexpr_utility 201811L
#define __cpp_lib_constexpr_vector 201907L
#define __cpp_lib_destroying_delete 201806L
#define __cpp_lib_endian 201907L
#define __cpp_lib_erase_if 202002L

#if defined(__cpp_lib_concepts) // TRANSITION, GH-395
#define __cpp_lib_format 202110L
#endif // defined(__cpp_lib_concepts)

#define __cpp_lib_generic_unordered_lookup 201811L
#define __cpp_lib_int_pow2 202002L
#define __cpp_lib_integer_comparison_functions 202002L
#define __cpp_lib_interpolate 201902L
#define __cpp_lib_is_constant_evaluated 201811L

#ifndef __EDG__	  // TRANSITION, VSO-1268984
#ifndef __clang__ // TRANSITION, LLVM-48860
#define __cpp_lib_is_layout_compatible 201907L
#endif // __clang__
#endif // __EDG__

#define __cpp_lib_is_nothrow_convertible 201806L

#ifndef __EDG__	  // TRANSITION, VSO-1268984
#ifndef __clang__ // TRANSITION, LLVM-48860
#define __cpp_lib_is_pointer_interconvertible 201907L
#endif // __clang__
#endif // __EDG__

#define __cpp_lib_jthread 201911L
#define __cpp_lib_latch 201907L
#define __cpp_lib_list_remove_return_type 201806L
#define __cpp_lib_math_constants 201907L
#define __cpp_lib_polymorphic_allocator 201902L

#if defined(__cpp_lib_concepts) // TRANSITION, GH-395
#define __cpp_lib_ranges 202110L
#endif // defined(__cpp_lib_concepts)

#define __cpp_lib_remove_cvref 201711L
#define __cpp_lib_semaphore 201907L
#define __cpp_lib_smart_ptr_for_overwrite 202002L

#ifdef __cpp_consteval
#define __cpp_lib_source_location 201907L
#endif // __cpp_consteval

#define __cpp_lib_span 202002L
#define __cpp_lib_ssize 201902L
#define __cpp_lib_starts_ends_with 201711L
#define __cpp_lib_syncbuf 201803L

#ifdef __cpp_lib_concepts // TRANSITION, GH-395
#define __cpp_lib_three_way_comparison 201907L
#endif // __cpp_lib_concepts

#define __cpp_lib_to_address 201711L
#define __cpp_lib_to_array 201907L
#define __cpp_lib_type_identity 201806L
#define __cpp_lib_unwrap_ref 201811L
#endif // _HAS_CXX20
// 1448
// 1557
#define _STD_BEGIN \
	namespace std  \
	{
#define _STD_END }
#define _STD ::std::
#define _CHRONO ::std::chrono::
#define _RANGES ::std::ranges::
// 1563