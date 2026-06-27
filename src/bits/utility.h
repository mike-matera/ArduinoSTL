#pragma once
// Utilities used throughout the library -*- C++ -*-

// Copyright (C) 2004-2024 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file include/bits/utility.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{utility}
 *
 *  This file contains the parts of `<utility>` needed by other headers,
 *  so they don't need to include the whole of `<utility>`.
 */

#pragma GCC system_header

#if __cplusplus >= 201103L

#ifdef ARDUINO_ARCH_ESP32
#include_next <bits/utility.h>
#else
#include <type_traits>
#include <bits/move.h>
#endif
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
#ifdef ARDUINO_ARCH_AVR
	/// Finds the size of a given tuple type.
	template <typename _Tp>
	struct tuple_size;

	// _GLIBCXX_RESOLVE_LIB_DEFECTS
	// 2313. tuple_size should always derive from integral_constant<size_t, N>
	// 2770. tuple_size<const T> specialization is not SFINAE compatible

	template <typename _Tp,
			  typename _Up = typename remove_cv<_Tp>::type,
			  typename = typename enable_if<is_same<_Tp, _Up>::value>::type,
			  size_t = tuple_size<_Tp>::value>
	using __enable_if_has_tuple_size = _Tp;

	template <typename _Tp>
	struct tuple_size<const __enable_if_has_tuple_size<_Tp>>
		: public tuple_size<_Tp>
	{
	};

	template <typename _Tp>
	struct tuple_size<volatile __enable_if_has_tuple_size<_Tp>>
		: public tuple_size<_Tp>
	{
	};

	template <typename _Tp>
	struct tuple_size<const volatile __enable_if_has_tuple_size<_Tp>>
		: public tuple_size<_Tp>
	{
	};

#if __cplusplus >= 201703L
	template <typename _Tp>
	inline constexpr size_t tuple_size_v = tuple_size<_Tp>::value;
#endif

	/// Gives the type of the ith element of a given tuple type.
	template <size_t __i, typename _Tp>
	struct tuple_element;

	// Duplicate of C++14's tuple_element_t for internal use in C++11 mode
	template <size_t __i, typename _Tp>
	using __tuple_element_t = typename tuple_element<__i, _Tp>::type;

	template <size_t __i, typename _Tp>
	struct tuple_element<__i, const _Tp>
	{
		using type = const __tuple_element_t<__i, _Tp>;
	};

	template <size_t __i, typename _Tp>
	struct tuple_element<__i, volatile _Tp>
	{
		using type = volatile __tuple_element_t<__i, _Tp>;
	};

	template <size_t __i, typename _Tp>
	struct tuple_element<__i, const volatile _Tp>
	{
		using type = const volatile __tuple_element_t<__i, _Tp>;
	};

#if __cplusplus >= 201402L

	// Return the index of _Tp in _Types, if it occurs exactly once.
	// Otherwise, return sizeof...(_Types).
	template <typename _Tp, typename... _Types>
	constexpr size_t
	__find_uniq_type_in_pack()
	{
		constexpr size_t __sz = sizeof...(_Types);
		constexpr bool __found[__sz] = {__is_same(_Tp, _Types)...};
		size_t __n = __sz;
		for (size_t __i = 0; __i < __sz; ++__i)
		{
			if (__found[__i])
			{
				if (__n < __sz) // more than one _Tp found
					return __sz;
				__n = __i;
			}
		}
		return __n;
	}
#endif // C++14

// The standard says this macro and alias template should be in <tuple> but we
// define them here, to be available in <array>, <utility> and <ranges> too.
// _GLIBCXX_RESOLVE_LIB_DEFECTS
// 3378. tuple_size_v/tuple_element_t should be available when
//       tuple_size/tuple_element are
#ifdef __glibcxx_tuple_element_t // C++ >= 14
	template <size_t __i, typename _Tp>
	using tuple_element_t = typename tuple_element<__i, _Tp>::type;
#endif
#endif // ARDUINO_ARCH_AVR
#ifndef ARDUINO_ARCH_ESP32
#ifdef __glibcxx_integer_sequence // C++ >= 14

	/// Class template integer_sequence
	template <typename _Tp, _Tp... _Idx>
	struct integer_sequence
	{
#if __cplusplus >= 202002L
		static_assert(is_integral_v<_Tp>);
#endif
		typedef _Tp value_type;
		static constexpr size_t size() noexcept { return sizeof...(_Idx); }
	};

	// LLVM实现
#include "__utility/integer_sequence.h"

	/// Alias template index_sequence
	template <size_t... _Idx>
	using index_sequence = integer_sequence<size_t, _Idx...>;

	/// Alias template make_index_sequence
	template <size_t _Num>
	using make_index_sequence = make_integer_sequence<size_t, _Num>;

	/// Alias template index_sequence_for
	template <typename... _Types>
	using index_sequence_for = make_index_sequence<sizeof...(_Types)>;
#ifdef ARDUINO_ARCH_AVR
	// Stores a tuple of indices.  Also used by bind() to extract the elements
	// in a tuple.
	template <std::size_t... _Indexes>
	struct _Index_tuple
	{
		typedef _Index_tuple<_Indexes..., sizeof...(_Indexes)> __next;
	};

	// Builds an _Index_tuple<0, 1, 2, ..., _Num-1>.
	template <std::size_t _Num>
	struct _Build_index_tuple
	{
		typedef typename _Build_index_tuple<_Num - 1>::__type::__next __type;
	};

	template <>
	struct _Build_index_tuple<0>
	{
		typedef _Index_tuple<> __type;
	};
#endif // ARDUINO_ARCH_AVR
#endif // __glibcxx_integer_sequence

	struct in_place_t
	{
		explicit in_place_t() = default;
	};

	_GLIBCXX17_INLINE constexpr in_place_t in_place{};

	template <typename _Tp>
	struct in_place_type_t
	{
		explicit in_place_type_t() = default;
#if __cplusplus < 201402L
		static constexpr in_place_type_t value{};
#endif
	};
#if __cplusplus >= 201402L
	template <typename _Tp>
	inline constexpr in_place_type_t<_Tp> in_place_type{};
#endif
	template <size_t _Idx>
	struct in_place_index_t
	{
		explicit in_place_index_t() = default;
#if __cplusplus < 201402L
		static constexpr in_place_index_t value{};
#endif
	};
#if __cplusplus < 201402L
	template <typename>
	struct __is_in_place_type : bool_constant<false>
	{
	};

	template <typename _Tp>
	struct __is_in_place_type<in_place_type_t<_Tp>> : bool_constant<true>
	{
	};

	template <typename>
	struct __is_in_place_index : bool_constant<false>
	{
	};

	template <size_t _Nm>
	struct __is_in_place_index<in_place_index_t<_Nm>> : bool_constant<true>
	{
	};
#else
	template <size_t _Idx>
	inline constexpr in_place_index_t<_Idx> in_place_index{};

	template <typename>
	inline constexpr bool __is_in_place_type_v = false;

	template <typename _Tp>
	inline constexpr bool __is_in_place_type_v<in_place_type_t<_Tp>> = true;

	template <typename _Tp>
	using __is_in_place_type = bool_constant<__is_in_place_type_v<_Tp>>;

	template <typename>
	inline constexpr bool __is_in_place_index_v = false;

	template <size_t _Nm>
	inline constexpr bool __is_in_place_index_v<in_place_index_t<_Nm>> = true;
#endif
#endif //! defined ARDUINO_ARCH_ESP32
#ifdef ARDUINO_ARCH_AVR
#if _GLIBCXX_USE_BUILTIN_TRAIT(__type_pack_element)
	template <size_t _Np, typename... _Types>
	struct _Nth_type
	{
		using type = __type_pack_element<_Np, _Types...>;
	};
#else
	template <size_t _Np, typename... _Types>
	struct _Nth_type
	{
	};

	template <typename _Tp0, typename... _Rest>
	struct _Nth_type<0, _Tp0, _Rest...>
	{
		using type = _Tp0;
	};

	template <typename _Tp0, typename _Tp1, typename... _Rest>
	struct _Nth_type<1, _Tp0, _Tp1, _Rest...>
	{
		using type = _Tp1;
	};

	template <typename _Tp0, typename _Tp1, typename _Tp2, typename... _Rest>
	struct _Nth_type<2, _Tp0, _Tp1, _Tp2, _Rest...>
	{
		using type = _Tp2;
	};

	template <size_t _Np, typename _Tp0, typename _Tp1, typename _Tp2,
			  typename... _Rest>
#if __cpp_concepts
		requires(_Np >= 3)
#endif
	struct _Nth_type<_Np, _Tp0, _Tp1, _Tp2, _Rest...>
		: _Nth_type<_Np - 3, _Rest...>
	{
	};

#if !__cpp_concepts // Need additional specializations to avoid ambiguities.
	template <typename _Tp0, typename _Tp1, typename _Tp2, typename... _Rest>
	struct _Nth_type<0, _Tp0, _Tp1, _Tp2, _Rest...>
	{
		using type = _Tp0;
	};

	template <typename _Tp0, typename _Tp1, typename _Tp2, typename... _Rest>
	struct _Nth_type<1, _Tp0, _Tp1, _Tp2, _Rest...>
	{
		using type = _Tp1;
	};
#endif
#endif

#if __glibcxx_ranges
	namespace ranges::__detail
	{
		template <typename _Range>
		inline constexpr bool __is_subrange = false;
	} // namespace __detail
#endif
#endif // ARDUINO_ARCH_AVR
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

#endif // C++11