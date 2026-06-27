#pragma once
#if __cplusplus < 202002L
//ESP32虽然有此头文件，但在C++20之前被条件编译选项屏蔽了，所以等于没有
#ifdef __cpp_variable_templates
#define _CSL_Return14Value
#endif
// Concepts and traits for use with iterators -*- C++ -*-

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

/** @file bits/iterator_concepts.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iterator}
 */

#ifndef _ITERATOR_CONCEPTS_H
#define _ITERATOR_CONCEPTS_H 1

#ifdef _GLIBCXX_SYSHDR
#pragma GCC system_header
#endif

#include <bits/ptr_traits.h> // to_address

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic" // __int128

namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

	/** A sentinel type that can be used to check for the end of a range.
	 *
	 * For some iterator types the past-the-end sentinel value is independent
	 * of the underlying sequence, and a default sentinel can be used with them.
	 * For example, a `std::counted_iterator` keeps a count of how many elements
	 * remain, and so checking for the past-the-end value only requires checking
	 * if that count has reached zero. A past-the-end `std::istream_iterator` is
	 * equal to the default-constructed value, which can be easily checked.
	 *
	 * Comparing iterators of these types to `std::default_sentinel` is a
	 * convenient way to check if the end has been reached.
	 *
	 * @since C++20
	 */
	struct default_sentinel_t
	{
	};

	/// A default sentinel value.
	_GLIBCXX17_INLINE constexpr default_sentinel_t default_sentinel{};

	struct input_iterator_tag;
	struct output_iterator_tag;
	struct forward_iterator_tag;
	struct bidirectional_iterator_tag;
	struct random_access_iterator_tag;
	struct contiguous_iterator_tag;

	template <typename _Iterator>
	struct iterator_traits;

	template <typename _Iterator, typename>
	struct __iterator_traits;

	namespace __detail
	{
		template <typename _Tp>
		using __with_ref = _Tp &;

		template <typename _Tp, typename = void>
		struct _CSL_can_reference : false_type
		{
		};
		template <typename _Tp>
		struct _CSL_can_reference<_Tp, void_t<__with_ref<_Tp>>> : true_type
		{
		};
		template <typename _Tp>
		_CSL_Concept(__can_reference, _CSL_can_reference<_Tp>::value);

		template <typename _Tp, typename = void>
		struct _CSL_dereferenceable : false_type
		{
		};
		template <typename _Tp>
		struct _CSL_dereferenceable<_Tp, void_t<decltype(*declval<_Tp &>())>>
		{
			static constexpr bool value = __can_reference<decltype(*declval<_Tp &>())> _CSL_Parentheses11;
		};
		template <typename _Tp>
		_CSL_Concept(__dereferenceable, _CSL_dereferenceable<_Tp>::value);
	} // namespace __detail

	template <typename _Tp, typename = enable_if_t<__detail::__dereferenceable<_Tp> _CSL_Parentheses11>>
	using iter_reference_t = decltype(*std::declval<_Tp &>());

	namespace ranges
	{
		/// @cond undocumented
		namespace __imove
		{
			void iter_move() = delete;

			struct _IterMove
			{
			private:
				template <typename _Tp>
				struct __result
				{
					using type = iter_reference_t<_Tp>;
				};

			public:
				// The result type of iter_move(std::declval<_Tp>())
				template <typename _Tp, typename = enable_if_t<std::__detail::__dereferenceable<_Tp> _CSL_Parentheses11>>
				using __type = typename __result<_Tp>::type;
			};
		} // namespace __imove
		/// @endcond

		inline namespace _Cpo
		{
			_GLIBCXX17_INLINE constexpr __imove::_IterMove iter_move{};
		}
	} // namespace ranges

	template <typename _Tp, typename = enable_if_t<__detail::__dereferenceable<_Tp> _CSL_Parentheses11 && __detail::__can_reference<ranges::__imove::_IterMove::__type<_Tp &>> _CSL_Parentheses11>>
	using iter_rvalue_reference_t = ranges::__imove::_IterMove::__type<_Tp &>;

	template <typename>
	struct incrementable_traits
	{
	};

	template <typename _Iter>
	struct incrementable_traits<const _Iter>
		: incrementable_traits<_Iter>
	{
	};

#if defined __STRICT_ANSI__ && defined __SIZEOF_INT128__
	// __int128 is incrementable even if !integral<__int128>
	template <>
	struct incrementable_traits<__int128>
	{
		using difference_type = __int128;
	};

	template <>
	struct incrementable_traits<unsigned __int128>
	{
		using difference_type = __int128;
	};
#endif

	namespace __detail
	{
		// An iterator such that iterator_traits<_Iter> names a specialization
		// generated from the primary template.
		template <typename _Iter>
		_CSL_Concept(__primary_traits_iter, __is_base_of(__iterator_traits<_Iter, void>, iterator_traits<_Iter>));

		template <typename _Iter, typename _Tp>
		struct __iter_traits_impl
		{
			using type = iterator_traits<_Iter>;
		};

		// ITER_TRAITS
		template <typename _Iter, typename _Tp = _Iter>
		using __iter_traits = typename __iter_traits_impl<_Iter, _Tp>::type;

		template <typename _Tp>
		using __iter_diff_t = typename __iter_traits<_Tp, incrementable_traits<_Tp>>::difference_type;
	} // namespace __detail

	template <typename _Tp>
	using iter_difference_t = __detail::__iter_diff_t<remove_cvref_t<_Tp>>;

	namespace __detail
	{
		template <typename>
		struct __cond_value_type
		{
		};

	} // namespace __detail

	template <typename>
	struct indirectly_readable_traits
	{
	};

	template <typename _Tp>
	struct indirectly_readable_traits<_Tp *>
		: __detail::__cond_value_type<_Tp>
	{
	};

	template <typename _Iter>
	struct indirectly_readable_traits<const _Iter>
		: indirectly_readable_traits<_Iter>
	{
	};

	namespace __detail
	{
		template <typename _Tp>
		using __iter_value_t = typename __iter_traits<_Tp, indirectly_readable_traits<_Tp>>::value_type;
	} // namespace __detail

	template <typename _Tp>
	using iter_value_t = __detail::__iter_value_t<remove_cvref_t<_Tp>>;

	namespace __detail
	{
// _GLIBCXX_RESOLVE_LIB_DEFECTS
// 3420. cpp17-iterator should check [type] looks like an iterator first
#define __it declval<_Iter &>()
		template <typename _Iter, typename = void>
		struct _CSL_cpp17_iterator : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_cpp17_iterator<_Iter, enable_if_t<__can_reference<decltype(*__it)> _CSL_Parentheses11 && same_as<decltype(++__it), _Iter &> _CSL_Parentheses11 && __can_reference<decltype(*__it++)> _CSL_Parentheses11 && copyable<_Iter> _CSL_Parentheses11>> : true_type
		{
		};

		template <typename _Iter>
		_CSL_Concept(__cpp17_iterator, _CSL_cpp17_iterator<_Iter>::value);

		template <typename _Iter, typename = void>
		struct _CSL_cpp17_input_iterator : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_cpp17_input_iterator<_Iter, void_t<enable_if_t<__cpp17_iterator<_Iter> _CSL_Parentheses11 && equality_comparable<_Iter> _CSL_Parentheses11 && signed_integral<typename incrementable_traits<_Iter>::difference_type> _CSL_Parentheses11>, typename incrementable_traits<_Iter>::difference_type, typename indirectly_readable_traits<_Iter>::value_type, common_reference_t<iter_reference_t<_Iter> &&, typename indirectly_readable_traits<_Iter>::value_type &>, common_reference_t<decltype(*__it++) &&, typename indirectly_readable_traits<_Iter>::value_type &>>> : true_type
		{
		};
		template <typename _Iter>
		_CSL_Concept(__cpp17_input_iterator, _CSL_cpp17_input_iterator<_Iter>::value);

		template <typename _Iter, typename = void>
		struct _CSL_cpp17_fwd_iterator : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_cpp17_fwd_iterator<_Iter, enable_if_t<__cpp17_input_iterator<_Iter> _CSL_Parentheses11 && constructible_from<_Iter> _CSL_Parentheses11 && is_lvalue_reference_v<iter_reference_t<_Iter>> _CSL_Parentheses11 && same_as<remove_cvref_t<iter_reference_t<_Iter>>, typename indirectly_readable_traits<_Iter>::value_type> _CSL_Parentheses11 && convertible_to<decltype(__it++), const _Iter &> _CSL_Parentheses11 && same_as<iter_reference_t<decltype(*__it++), _Iter>> _CSL_Parentheses11>> : true_type
		{
		};
		template <typename _Iter>
		_CSL_Concept(__cpp17_fwd_iterator, _CSL_cpp17_fwd_iterator<_Iter>::value);

		template <typename _Iter, typename = void>
		struct _CSL_cpp17_bidi_iterator : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_cpp17_bidi_iterator<_Iter, enable_if_t<__cpp17_fwd_iterator<_Iter> _CSL_Parentheses11 && same_as<decltype(--__it), _Iter &> _CSL_Parentheses11 && convertible_to<decltype(__it--), const _Iter &> _CSL_Parentheses11 && same_as<decltype(*__it--), iter_reference_t<_Iter>> _CSL_Parentheses11>> : true_type
		{
		};
		template <typename _Iter>
		_CSL_Concept(__cpp17_bidi_iterator, _CSL_cpp17_bidi_iterator<_Iter>::value);

#define __n declval<incrementable_traits<_Iter>::difference_type>()
		template <typename _Iter, typename = void>
		struct _CSL_cpp17_randacc_iterator : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_cpp17_randacc_iterator<_Iter, enable_if_t<__cpp17_bidi_iterator<_Iter> _CSL_Parentheses11 && totally_ordered<_Iter> _CSL_Parentheses11 && same_as<decltype(__it += __n), _Iter &> _CSL_Parentheses11 && same_as<decltype(__it -= __n), _Iter &> _CSL_Parentheses11 && same_as<decltype(__it + __n), _Iter> _CSL_Parentheses11 && same_as<decltype(__n + __it), _Iter> _CSL_Parentheses11 && same_as<decltype(__it - __n), _Iter> _CSL_Parentheses11 && same_as<decltype(__it - __it), decltype(__n)> _CSL_Parentheses11 && convertible_to<decltype(__it[__n]), iter_reference_t<_Iter>>>> : true_type
		{
		};
		template <typename _Iter>
		_CSL_Concept(__cpp17_randacc_iterator, _CSL_cpp17_randacc_iterator<_Iter>::value);

		template <typename _Iter, typename = void>
		struct _CSL_iter_with_nested_types : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_iter_with_nested_types<_Iter, void_t<typename _Iter::iterator_category, typename _Iter::value_type, typename _Iter::difference_type, typename _Iter::reference>> : true_type
		{
		};
		template <typename _Iter>
		_CSL_Concept(__iter_with_nested_types, _CSL_iter_with_nested_types<_Iter>::value);

		template <typename _Iter>
		_CSL_Concept(__iter_without_nested_types, !__iter_with_nested_types<_Iter> _CSL_Parentheses11);

		template <typename _Iter, typename = void>
		struct _CSL_iter_without_category : true_type
		{
		};
		template <typename _Iter>
		struct _CSL_iter_without_category<_Iter, void_t<typename _Iter::iterator_category>> : false_type
		{
		};
		template <typename _Iter>
		_CSL_Concept(__iter_without_category, _CSL_iter_without_category<_Iter>::value);

	} // namespace __detail

	template <typename _Iterator>
	struct __iterator_traits<_Iterator, enable_if_t<__detail::__iter_with_nested_types<_Iterator> _CSL_Parentheses11>>
	{
	private:
		template <typename _Iter, typename = void>
		struct __ptr
		{
			using type = void;
		};

		template <typename _Iter>
		struct __ptr<_Iter, void_t<typename _Iter::pointer>>
		{
			using type = typename _Iter::pointer;
		};

	public:
		using iterator_category = typename _Iterator::iterator_category;
		using value_type = typename _Iterator::value_type;
		using difference_type = typename _Iterator::difference_type;
		using pointer = typename __ptr<_Iterator>::type;
		using reference = typename _Iterator::reference;
	};

	template <typename _Iterator>
	struct __iterator_traits<_Iterator, enable_if_t<__detail::__iter_without_nested_types<_Iterator> _CSL_Parentheses11 && __detail::__cpp17_input_iterator<_Iterator> _CSL_Parentheses11>>
	{
	private:
		template <typename _Iter, typename = void>
		struct __cat
		{
			using type = input_iterator_tag;
		};

		template <typename _Iter>
		struct __cat<_Iter, void_t<typename _Iter::iterator_category>>
		{
			using type = typename _Iter::iterator_category;
		};

		template <typename _Iter>
		struct __cat<_Iter, enable_if_t<__detail::__iter_without_category<_Iter> _CSL_Parentheses11 && __detail::__cpp17_randacc_iterator<_Iter> _CSL_Parentheses11>>
		{
			using type = random_access_iterator_tag;
		};

		template <typename _Iter>
		struct __cat<_Iter, enable_if_t<__detail::__iter_without_category<_Iter> _CSL_Parentheses11 && __detail::__cpp17_bidi_iterator<_Iter> _CSL_Parentheses11>>
		{
			using type = bidirectional_iterator_tag;
		};

		template <typename _Iter>
		struct __cat<_Iter, enable_if_t<__detail::__iter_without_category<_Iter> _CSL_Parentheses11 && __detail::__cpp17_fwd_iterator<_Iter> _CSL_Parentheses11>>
		{
			using type = forward_iterator_tag;
		};

		template <typename _Iter, typename = void>
		struct __ptr
		{
			using type = void;
		};

		template <typename _Iter>
		struct __ptr<_Iter, void_t<typename _Iter::pointer>>
		{
			using type = typename _Iter::pointer;
		};

		template <typename _Iter, typename = void>
		struct _CSL_Iter_without_pointer : true_type
		{
		};
		template <typename _Iter>
		struct _CSL_Iter_without_pointer<_Iter, void_t<typename _Iter::pointer>> : false_type
		{
		};
		template <typename _Iter>
		struct __ptr<_Iter, void_t<enable_if_t<_CSL_Iter_without_pointer<_Iter>::value>, decltype(__it.operator->())>>
		{
			using type = decltype(std::declval<_Iter &>().operator->());
		};

		template <typename _Iter, typename = void>
		struct __ref
		{
			using type = iter_reference_t<_Iter>;
		};

		template <typename _Iter>
		struct __ref<_Iter, void_t<typename _Iter::reference>>
		{
			using type = typename _Iter::reference;
		};

	public:
		using iterator_category = typename __cat<_Iterator>::type;
		using value_type = typename indirectly_readable_traits<_Iterator>::value_type;
		using difference_type = typename incrementable_traits<_Iterator>::difference_type;
		using pointer = typename __ptr<_Iterator>::type;
		using reference = typename __ref<_Iterator>::type;
	};

	template <typename _Iterator>
	struct __iterator_traits<_Iterator, enable_if_t<__detail::__iter_without_nested_types<_Iterator> _CSL_Parentheses11 && __detail::__cpp17_iterator<_Iterator> _CSL_Parentheses11>>
	{
	private:
		template <typename _Iter, typename = void>
		struct __diff
		{
			using type = void;
		};

		template <typename _Iter>
		struct __diff<_Iter, void_t<typename incrementable_traits<_Iter>::difference_type>>
		{
			using type = typename incrementable_traits<_Iter>::difference_type;
		};

	public:
		using iterator_category = output_iterator_tag;
		using value_type = void;
		using difference_type = typename __diff<_Iterator>::type;
		using pointer = void;
		using reference = void;
	};

	namespace __detail
	{
		template <typename _Iter, typename = void>
		struct _CSL_iter_traits_has_concept : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_iter_traits_has_concept<_Iter, void_t<typename __iter_traits<_Iter>::iterator_concept>> : true_type
		{
		};
		template <typename _Iter, typename = void>
		struct _CSL_iter_traits_has_category : false_type
		{
		};
		template <typename _Iter>
		struct _CSL_iter_traits_has_category<_Iter, void_t<typename __iter_traits<_Iter>::iterator_category>> : true_type
		{
		};
		// Otherwise, there is no ITER_CONCEPT(I) type.
		template <typename _Iter, typename = void>
		struct __iter_concept_impl;

		// Otherwise, random_access_tag if iterator_traits<I> is not specialized.
		template <typename _Iter>
		struct __iter_concept_impl<_Iter, enable_if_t<!_CSL_iter_traits_has_concept<_Iter>::value && !_CSL_iter_traits_has_category<_Iter>::value && __primary_traits_iter<_Iter> _CSL_Parentheses11>>
		{
			using type = random_access_iterator_tag;
		};

		// Otherwise, ITER_TRAITS(I)::iterator_category if that is valid.
		template <typename _Iter>
		struct __iter_concept_impl<_Iter, enable_if_t<!_CSL_iter_traits_has_concept<_Iter>::value && _CSL_iter_traits_has_category<_Iter>::value>>
		{
			using type = typename __iter_traits<_Iter>::iterator_category;
		};

		// ITER_CONCEPT(I) is ITER_TRAITS(I)::iterator_concept if that is valid.
		template <typename _Iter>
		struct __iter_concept_impl<_Iter, enable_if_t<_CSL_iter_traits_has_concept<_Iter>::value>>
		{
			using type = typename __iter_traits<_Iter>::iterator_concept;
		};

		// ITER_CONCEPT
		template <typename _Iter>
		using __iter_concept = typename __iter_concept_impl<_Iter>::type;
		// 535
		template <typename _In, typename = void>
		struct _CSL_indirectly_readable_impl : false_type
		{
		};
		template <typename _In>
		struct _CSL_indirectly_readable_impl<_In, void_t<iter_value_t<_In>, iter_reference_t<_In>, iter_rvalue_reference_t<_In>>>
		{
			static constexpr bool value = same_as<iter_reference_t<const _In>, iter_reference_t<_In>> _CSL_Parentheses11 && same_as<iter_rvalue_reference_t<const _In>, iter_rvalue_reference_t<_In>> _CSL_Parentheses11 && common_reference_with<iter_reference_t<_In> &&, iter_value_t<_In> &> _CSL_Parentheses11 && common_reference_with<iter_reference_t<_In> &&, iter_rvalue_reference_t<_In> &&> _CSL_Parentheses11 && common_reference_with<iter_rvalue_reference_t<_In> &&, const iter_value_t<_In> &> _CSL_Parentheses11;
		};
		template <typename _In>
		_CSL_Concept(__indirectly_readable_impl, _CSL_indirectly_readable_impl<_In>::value);

	} // namespace __detail

	/// Requirements for types that are readable by applying operator*.
	template <typename _In>
	_CSL_Concept(indirectly_readable, __detail::__indirectly_readable_impl<remove_cvref_t<_In>> _CSL_Parentheses11);
	// 559
	namespace __detail
	{
		template <typename _Tp>
		struct __indirect_value
		{
			using type = iter_value_t<_Tp> &;
		};

		// __indirect_value<projected<_Iter, _Proj>> is defined later.
	} // namespace __detail

	template <typename _Tp>
	using __indirect_value_t = typename __detail::__indirect_value<_Tp>::type;
	// 575
	/// Requirements for writing a value into an iterator's referenced object.
#define __o std::declval<_Out &&>()
#define __t std::declval<_Tp &&>()
	template <typename _Out, typename _Tp, typename = void>
	struct _CSL_indirectly_writable : false_type
	{
	};
	template <typename _Out, typename _Tp>
	struct _CSL_indirectly_writable<_Out, _Tp, void_t<decltype(*__o = std::forward<_Tp>(__t), *std::forward<_Out>(__o) = std::forward<_Tp>(__t), const_cast<const iter_reference_t<_Out> &&>(*__o) = std::forward<_Tp>(__t), const_cast<const iter_reference_t<_Out> &&>(*std::forward<_Out>(__o)) = std::forward<_Tp>(__t))>> : true_type
	{
	};
	template <typename _Out, typename _Tp>
	_CSL_Concept(indirectly_writable, _CSL_indirectly_writable<_Out, _Tp>::value);
	// 587
	namespace ranges
	{
		namespace __detail
		{
			class __max_diff_type;
			class __max_size_type;

			__extension__ template <typename _Tp>
			constexpr bool __is_signed_int128
#if __SIZEOF_INT128__
			_CSL_Function17Variable(same_as<_Tp, __int128> _CSL_Parentheses11);
#else
				_CSL_Function17Variable(false);
#endif

			__extension__ template <typename _Tp>
			constexpr bool __is_unsigned_int128
#if __SIZEOF_INT128__
			_CSL_Function17Variable(same_as<_Tp, unsigned __int128> _CSL_Parentheses11);
#else
				_CSL_Function17Variable(false);
#endif

			template <typename _Tp>
			_CSL_Concept(__cv_bool, same_as<const volatile _Tp, const volatile bool> _CSL_Parentheses11);

			template <typename _Tp>
			_CSL_Concept(__integral_nonbool, integral<_Tp> _CSL_Parentheses11 && !__cv_bool<_Tp> _CSL_Parentheses11);

			template <typename _Tp>
			_CSL_Concept(__is_int128, __is_signed_int128<_Tp> _CSL_Parentheses11 || __is_unsigned_int128<_Tp> _CSL_Parentheses11);

			template <typename _Tp>
			_CSL_Concept(__is_integer_like, __integral_nonbool<_Tp> _CSL_Parentheses11 || __is_int128<_Tp> _CSL_Parentheses11 || same_as<_Tp, __max_diff_type> _CSL_Parentheses11 || same_as<_Tp, __max_size_type> _CSL_Parentheses11);

			template <typename _Tp>
			_CSL_Concept(__is_signed_integer_like, signed_integral<_Tp> _CSL_Parentheses11 || __is_signed_int128<_Tp> _CSL_Parentheses11 || same_as<_Tp, __max_diff_type> _CSL_Parentheses11);

		}
	} // namespace ranges::__detail

	namespace __detail
	{
		using ranges::__detail::__is_signed_integer_like;
	}
	// 633
	/// Requirements on types that can be incremented with ++.
#define __i declval<_Iter &>() // GCC原文中是requires(_Iter)，但是requires如同创建了_Iter变量所以可以自增，但declval不创建变量不能自增，所以必须加引用
	template <typename _Iter, typename = void, typename = _Iter &>
	struct _CSL_weakly_incrementable : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_weakly_incrementable<_Iter, void_t<iter_difference_t<_Iter>>, decltype(__i++, ++__i)>
	{
		static constexpr bool value = movable<_Iter> _CSL_Parentheses11 && __detail::__is_signed_integer_like<iter_difference_t<_Iter>> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(weakly_incrementable, _CSL_weakly_incrementable<_Iter>::value);

	template <typename _Iter, typename = _Iter>
	struct _CSL_incrementable : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_incrementable<_Iter, decltype(__i++)>
	{
		static constexpr bool value = regular<_Iter> _CSL_Parentheses11 && weakly_incrementable<_Iter> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(incrementable, _CSL_incrementable<_Iter>::value);

	template <typename _Iter, typename = void>
	struct _CSL_input_or_output_iterator : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_input_or_output_iterator<_Iter, void_t<decltype(*std::declval<_Iter>())>>
	{
		static constexpr bool value = __detail::__can_reference<decltype(*std::declval<_Iter>())> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(input_or_output_iterator, _CSL_input_or_output_iterator<_Iter>::value);

	template <typename _Sent, typename _Iter>
	_CSL_Concept(sentinel_for, semiregular<_Sent> _CSL_Parentheses11 &&input_or_output_iterator<_Iter> _CSL_Parentheses11 &&__detail::__weakly_eq_cmp_with<_Sent, _Iter> _CSL_Parentheses11);

	template <typename _Sent, typename _Iter>
	_GLIBCXX17_INLINE _CSL_Concept(disable_sized_sentinel_for, false);

#define __i declval<const _Iter &>()
#define __s declval<const _Sent &>()
	template <typename _Sent, typename _Iter, typename = iter_difference_t<_Iter>, typename = iter_difference_t<_Iter>>
	struct _CSL_sized_sentinel_for : false_type
	{
	};
	template <typename _Sent, typename _Iter>
	struct _CSL_sized_sentinel_for<_Sent, _Iter, decltype(__i - __s), decltype(__s - __i)>
	{
		static constexpr bool value = sentinel_for<_Sent, _Iter> _CSL_Parentheses11 && !disable_sized_sentinel_for<remove_cv_t<_Sent>, remove_cv_t<_Iter>> _CSL_Parentheses11;
	};
	template <typename _Sent, typename _Iter>
	_CSL_Concept(sized_sentinel_for, _CSL_sized_sentinel_for<_Sent, _Iter>::value);

	template <typename _Iter, typename = void>
	struct _CSL_input_iterator : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_input_iterator<_Iter, void_t<__detail::__iter_concept<_Iter>>>
	{
		static constexpr bool value = input_or_output_iterator<_Iter> _CSL_Parentheses11 && indirectly_readable<_Iter> _CSL_Parentheses11 && derived_from<__detail::__iter_concept<_Iter>, input_iterator_tag> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(input_iterator, _CSL_input_iterator<_Iter>::value);

#define __t declval<_Tp>()
	template <typename _Iter, typename _Tp, typename = void>
	struct _CSL_output_iterator : false_type
	{
	};
	template <typename _Iter, typename _Tp>
	struct _CSL_output_iterator<_Iter, _Tp, void_t<decltype(*__i++ = std::forward<_Tp>(__t))>>
	{
		static constexpr bool value = input_or_output_iterator<_Iter> _CSL_Parentheses11 && indirectly_writable<_Iter, _Tp> _CSL_Parentheses11;
	};
	template <typename _Iter, typename _Tp>
	_CSL_Concept(output_iterator, _CSL_output_iterator<_Iter, _Tp>::value);

	template <typename _Iter>
	_CSL_Concept(forward_iterator, input_iterator<_Iter> _CSL_Parentheses11 &&derived_from<__detail::__iter_concept<_Iter>, forward_iterator_tag> _CSL_Parentheses11 &&incrementable<_Iter> _CSL_Parentheses11 &&sentinel_for<_Iter, _Iter> _CSL_Parentheses11);

#define __i declval<_Iter &>()
	template <typename _Iter, typename = _Iter &, typename = _Iter>
	struct _CSL_bidirectional_iterator : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_bidirectional_iterator<_Iter, decltype(--__i), decltype(__i--)>
	{
		static constexpr bool value = forward_iterator<_Iter> _CSL_Parentheses11 && derived_from<__detail::__iter_concept<_Iter>, bidirectional_iterator_tag> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(bidirectional_iterator, _CSL_bidirectional_iterator<_Iter>::value);

#define __j declval<const _Iter>()
#define __n declval<iter_difference_t<_Iter>>()
	template <typename _Iter, typename = _Iter &, typename = _Iter, typename = _Iter, typename = _Iter &, typename = _Iter, typename = iter_reference_t<_Iter>>
	struct _CSL_random_access_iterator : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_random_access_iterator<_Iter, decltype(__i += __n), decltype(__j + __n), decltype(__n + __j), decltype(__i -= __n), decltype(__j - __n), decltype(__j[__n])>
	{
		static constexpr bool value = bidirectional_iterator<_Iter> _CSL_Parentheses11 && derived_from<__detail::__iter_concept<_Iter>, random_access_iterator_tag> _CSL_Parentheses11 && totally_ordered<_Iter> _CSL_Parentheses11 && sized_sentinel_for<_Iter, _Iter> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(random_access_iterator, _CSL_random_access_iterator<_Iter>::value);

	template <typename _Iter, typename = iter_value_t<_Iter>, typename = add_pointer_t<iter_reference_t<_Iter>>>
	struct _CSL_contiguous_iterator : false_type
	{
	};
	template <typename _Iter>
	struct _CSL_contiguous_iterator<_Iter, remove_cvref_t<iter_reference_t<_Iter>>, decltype(std::to_address(std::declval<const _Iter &>()))>
	{
		static constexpr bool value = random_access_iterator<_Iter> _CSL_Parentheses11 && derived_from<__detail::__iter_concept<_Iter>, contiguous_iterator_tag> _CSL_Parentheses11 && is_lvalue_reference_v<iter_reference_t<_Iter>> _CSL_Parentheses11;
	};
	template <typename _Iter>
	_CSL_Concept(contiguous_iterator, _CSL_contiguous_iterator<_Iter>::value);
	// 723
	// 1000
	// This is the namespace for [range.access] CPOs.
	namespace ranges
	{
		namespace __access
		{
			using std::__detail::__class_or_enum;

#undef __t
			struct _Decay_copy final
			{
				template <typename _Tp>
				constexpr decay_t<_Tp>
				operator()(_Tp &&__t) const
					noexcept(is_nothrow_convertible_v<_Tp, decay_t<_Tp>> _CSL_Parentheses11)
				{
					return std::forward<_Tp>(__t);
				}
			} _GLIBCXX17_INLINE constexpr __decay_copy{};

#define __t std::declval<_Tp &>()
			template <typename _Tp>
			_CSL_Concept(__member_begin, input_or_output_iterator<decltype(__decay_copy(__t.begin()))> _CSL_Parentheses11);
#if __cplusplus > 201103L
			// Poison pill so that unqualified lookup doesn't find std::begin.
			void begin() = delete;
#endif
			template <typename _Tp>
			_CSL_Concept(__adl_begin, __class_or_enum<remove_reference_t<_Tp>> _CSL_Parentheses11 &&input_or_output_iterator<decltype(__decay_copy(begin(__t)))> _CSL_Parentheses11);

#undef __t
			// Simplified version of std::ranges::begin that only supports lvalues,
			// for use by __range_iter_t below.
			template <typename _Tp, typename = enable_if_t<is_array_v<_Tp> _CSL_Parentheses11 || __member_begin<_Tp &> _CSL_Parentheses11 || __adl_begin<_Tp &> _CSL_Parentheses11>>
			auto
			__begin(_Tp &__t)->decltype(is_array_v<_Tp> _CSL_Parentheses11?__t + 0:__member_begin<_Tp &> _CSL_Parentheses11?__t.begin():begin(__t))
			{
				if _GLIBCXX17_CONSTEXPR (is_array_v<_Tp> _CSL_Parentheses11)
					return __t + 0;
				else if _GLIBCXX17_CONSTEXPR (__member_begin<_Tp &> _CSL_Parentheses11)
					return __t.begin();
				else
					return begin(__t);
			}
		}
	} // namespace ranges::__access

	namespace __detail
	{
		// Implementation of std::ranges::iterator_t, without using ranges::begin.
		template <typename _Tp>
		using __range_iter_t = decltype(ranges::__access::__begin(std::declval<_Tp &>()));

	} // namespace __detail
#undef __i
#undef __it
#undef __j
#undef __n
#undef __o
#undef __s
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
#pragma GCC diagnostic pop
#endif // _ITERATOR_CONCEPTS_H
#else
#include_next <bits/iterator_concepts.h>
#endif