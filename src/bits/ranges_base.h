#pragma once
#if __cplusplus < 202002L
// Core concepts and definitions for <ranges> -*- C++ -*-

// Copyright (C) 2019-2024 Free Software Foundation, Inc.
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

/** @file bits/ranges_base.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{ranges}
 */

#ifndef _GLIBCXX_RANGES_BASE_H
#define _GLIBCXX_RANGES_BASE_H 1

#ifdef _GLIBCXX_SYSHDR
#pragma GCC system_header
#endif
#ifndef ARDUINO_ARCH_AVR
#define __glibcxx_want_span
#include <concepts>
#include <bits/iterator_concepts.h>
#endif
#include <initializer_list>
#include <bits/stl_iterator.h>
#include <ext/numeric_traits.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic" // __int128

#if __glibcxx_algorithm_default_value_type // C++ >= 26
#define _GLIBCXX26_RANGE_ALGO_DEF_VAL_T(_I, _P) = projected_value_t<_I, _P>
#else
#define _GLIBCXX26_RANGE_ALGO_DEF_VAL_T(_I, _P)
#endif

namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
	namespace ranges
	{
		template <typename>
		_GLIBCXX17_INLINE constexpr bool disable_sized_range _CSL_Function17Variable(false);

		// 在<span>中有偏特化，因此不能用函数模板
		template <typename _Tp>
		_CSL_Struct17Concept(enable_borrowed_range, _GLIBCXX17_INLINE, false);

		namespace __detail
		{
			// Part of the constraints of ranges::borrowed_range
			template <typename _Tp>
			_CSL_Concept(__maybe_borrowed_range, is_lvalue_reference_v<_Tp> _CSL_Parentheses11 || enable_borrowed_range<remove_cvref_t<_Tp>> _CSL_Parentheses11);

		} // namespace __detail

		// Namespace for helpers for the <ranges> customization points.
		namespace __access
		{

			struct _Begin
			{
			private:
			};

			// Poison pill so that unqualified lookup doesn't find std::end.
			void end() = delete;

			struct _End
			{
			private:
			public:
			};

			struct _RBegin
			{
			private:
			public:
			};

			struct _REnd
			{
			private:
			public:
			};

			struct _Size
			{
			private:
			public:
			};

			struct _SSize
			{
			};

			struct _Empty
			{
			private:
			public:
			};

			struct _Data
			{
			private:
			public:
			};

		} // namespace __access

		inline namespace _Cpo
		{
			_GLIBCXX17_INLINE constexpr ranges::__access::_Begin begin{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_End end{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_RBegin rbegin{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_REnd rend{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_Size size{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_SSize ssize{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_Empty empty{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_Data data{};
		}

#define __t declval<_Tp &>()
		template <typename _Tp, typename = void>
		struct _CSL_range : false_type
		{
		};
		template <typename _Tp>
		struct _CSL_range<_Tp, void_t<decltype(ranges::begin(__t), ranges::end(__t))>> : true_type
		{
		};
		/// [range.range] The range concept.
		template <typename _Tp>
		_CSL_Concept(range, _CSL_range<_Tp>::value);

		/// [range.range] The borrowed_range concept.
		template <typename _Tp>
		_CSL_Concept(borrowed_range, range<_Tp> _CSL_Parentheses11 &&__detail::__maybe_borrowed_range<_Tp> _CSL_Parentheses11);

		template <typename _Tp>
		using iterator_t = std::__detail::__range_iter_t<_Tp>;
		// 523
		// 543
		template <typename _Range, typename = enable_if_t<range<_Range> _CSL_Parentheses11>>
		using range_reference_t = iter_reference_t<iterator_t<_Range>>;
		// 546
		// 556
		/// [range.sized] The sized_range concept.
		template <typename _Tp, typename = void>
		struct _CSL_sized_range : false_type
		{
		};
		template <typename _Tp>
		struct _CSL_sized_range<_Tp, void_t<decltype(ranges::size(__t))>>
		{
			static constexpr bool value = range<_Tp> _CSL_Parentheses11;
		};
		template <typename _Tp>
		_CSL_Concept(sized_range, _CSL_sized_range<_Tp>::value);
		// 561
		//     564
		template <typename _Derived, typename = enable_if_t<is_class_v<_Derived> _CSL_Parentheses11 && same_as<_Derived, remove_cv_t<_Derived>> _CSL_Parentheses11>>
		class view_interface; // defined in <bits/ranges_util.h>

		namespace __detail
		{
			template <typename _Tp, typename _Up, typename = enable_if_t<!same_as<_Tp, view_interface<_Up>> _CSL_Parentheses11>>
			void __is_derived_from_view_interface_fn(const _Tp &,
													 const view_interface<_Up> &); // not defined

			// Returns true iff _Tp has exactly one public base class that's a
			// specialization of view_interface.
#define __t declval<_Tp>()
			template <typename _Tp, typename = void>
			struct _CSL_is_derived_from_view_interface : false_type
			{
			};
			template <typename _Tp>
			struct _CSL_is_derived_from_view_interface<_Tp, void_t<decltype(__is_derived_from_view_interface_fn(__t, __t))>> : true_type
			{
			};
			template <typename _Tp>
			_CSL_Concept(__is_derived_from_view_interface, _CSL_is_derived_from_view_interface<_Tp>::value);
		} // namespace __detail

		/// [range.view] The ranges::view_base type.
		struct view_base
		{
		};

		//<span>中有特化，因此不能用函数模板
		/// [range.view] The ranges::enable_view boolean.
		template <typename _Tp>
		_CSL_Struct17Concept(enable_view, _GLIBCXX17_INLINE, (std::derived_from<_Tp, view_base> _CSL_Parentheses11 || __detail::__is_derived_from_view_interface<_Tp> _CSL_Parentheses11));

		/// [range.view] The ranges::view concept.
		template <typename _Tp>
		_CSL_Concept(view, range<_Tp> _CSL_Parentheses11 &&movable<_Tp> _CSL_Parentheses11 &&enable_view<_Tp> _CSL_Parentheses11);

		// [range.refinements]

		/// A range for which ranges::begin returns an output iterator.
		template <typename _Range, typename _Tp>
		_CSL_Concept(output_range, range<_Range> _CSL_Parentheses11 &&output_iterator<iterator_t<_Range>, _Tp> _CSL_Parentheses11);

		/// A range for which ranges::begin returns an input iterator.
		template <typename _Tp>
		_CSL_Concept(input_range, range<_Tp> _CSL_Parentheses11 &&input_iterator<iterator_t<_Tp>> _CSL_Parentheses11);

		/// A range for which ranges::begin returns a forward iterator.
		template <typename _Tp>
		_CSL_Concept(forward_range, input_range<_Tp> _CSL_Parentheses11 &&forward_iterator<iterator_t<_Tp>> _CSL_Parentheses11);

		/// A range for which ranges::begin returns a bidirectional iterator.
		template <typename _Tp>
		_CSL_Concept(bidirectional_range, forward_range<_Tp> _CSL_Parentheses11 &&bidirectional_iterator<iterator_t<_Tp>> _CSL_Parentheses11);

		/// A range for which ranges::begin returns a random access iterator.
		template <typename _Tp>
		_CSL_Concept(random_access_range, bidirectional_range<_Tp> _CSL_Parentheses11 &&random_access_iterator<iterator_t<_Tp>> _CSL_Parentheses11);

		/// A range for which ranges::begin returns a contiguous iterator.
#define __t declval<_Tp &>()
		template <typename _Tp, typename = add_pointer_t<range_reference_t<_Tp>>>
		struct _CSL_contiguous_range : false_type
		{
		};
		template <typename _Tp>
		struct _CSL_contiguous_range<_Tp, decltype(ranges::data(__t))>
		{
			static constexpr bool value = random_access_range<_Tp> _CSL_Parentheses11 && contiguous_iterator<iterator_t<_Tp>> _CSL_Parentheses11;
		};
		template <typename _Tp>
		_CSL_Concept(contiguous_range, _CSL_contiguous_range<_Tp>::value);
#undef __t
		namespace __access
		{
#if __glibcxx_ranges_as_const // >= C++23
			template <typename _Range>
			constexpr auto &
			__possibly_const_range(_Range &__r) noexcept
			{
				if _GLIBCXX17_CONSTEXPR (constant_range<const _Range> _CSL_Parentheses11 && !constant_range<_Range> _CSL_Parentheses11)
					return const_cast<const _Range &>(__r);
				else
					return __r;
			}
#else
			// If _To is an lvalue-reference, return const _Tp&, otherwise const _Tp&&.
			template <typename _To, typename _Tp>
			constexpr conditional_t<is_lvalue_reference_v<_To> _CSL_Parentheses11, const _Tp &, const _Tp &&>
			__as_const(_Tp &__t) noexcept
			{
				_GLIBCXX17_STATIC_ASSERT((std::is_same_v<_To &, _Tp &> _CSL_Parentheses11));

				if _GLIBCXX17_CONSTEXPR (is_lvalue_reference_v<_To> _CSL_Parentheses11)
					return const_cast<const _Tp &>(__t);
				else
					return static_cast<const _Tp &&>(__t);
			}
#endif

			struct _CBegin
			{
			};

			struct _CEnd final
			{
			};

			struct _CRBegin
			{
			};

			struct _CREnd
			{
			};

			struct _CData
			{
			};
		} // namespace __access

		inline namespace _Cpo
		{
			_GLIBCXX17_INLINE constexpr ranges::__access::_CBegin cbegin{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_CEnd cend{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_CRBegin crbegin{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_CREnd crend{};
			_GLIBCXX17_INLINE constexpr ranges::__access::_CData cdata{};
		}

		namespace __detail
		{
			template <typename _Tp>
			_CSL_Struct17Concept(__is_initializer_list, _GLIBCXX17_INLINE, false);

			template <typename _Tp>
			_CSL_Struct17Concept(__is_initializer_list, _GLIBCXX17_INLINE, true, <initializer_list<_Tp>>);
		} // namespace __detail

		// [range.iter.ops] range iterator operations

		struct __advance_fn final
		{

			void operator&() const = delete;
		};

		_GLIBCXX17_INLINE constexpr __advance_fn advance{};

		struct __distance_fn final
		{

			void operator&() const = delete;
		};

		_GLIBCXX17_INLINE constexpr __distance_fn distance{};

		struct __next_fn final
		{

			void operator&() const = delete;
		};

		_GLIBCXX17_INLINE constexpr __next_fn next{};

		struct __prev_fn final
		{

			void operator&() const = delete;
		};

		_GLIBCXX17_INLINE constexpr __prev_fn prev{};

		/// Type returned by algorithms instead of a dangling iterator or subrange.
		struct dangling
		{
			constexpr dangling() noexcept = default;
			template <typename... _Args>
			constexpr dangling(_Args &&...) noexcept {}
		};
	} // namespace ranges

#if __glibcxx_ranges_to_container // C++ >= 23
	struct from_range_t
	{
		explicit from_range_t() = default;
	};
	_GLIBCXX17_INLINE constexpr from_range_t from_range{};
#endif

	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
#pragma GCC diagnostic pop
#endif // _GLIBCXX_RANGES_BASE_H
#else
#include_next <bits/ranges_base.h>
#endif