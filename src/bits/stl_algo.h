#pragma once
#ifdef ARDUINO_ARCH_AVR
// Algorithm implementation -*- C++ -*-

// Copyright (C) 2001-2024 Free Software Foundation, Inc.
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

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/** @file bits/stl_algo.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{algorithm}
 */

#ifndef _STL_ALGO_H
#define _STL_ALGO_H 1

#include <bits/stl_algobase.h>
#include <algorithm>

#if __cplusplus >= 201103L
#include <bits/uniform_int_dist.h>
#endif

#if _GLIBCXX_HOSTED
#if (__cplusplus <= 201103L || _GLIBCXX_USE_DEPRECATED)
#include <cstdlib> // for rand
#endif
#endif

// See concept_check.h for the __glibcxx_*_requires macros.

namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

#if __cplusplus >= 201103L

  /**
   *  @brief Generate two uniformly distributed integers using a
   *         single distribution invocation.
   *  @param  __b0    The upper bound for the first integer.
   *  @param  __b1    The upper bound for the second integer.
   *  @param  __g     A UniformRandomBitGenerator.
   *  @return  A pair (i, j) with i and j uniformly distributed
   *           over [0, __b0) and [0, __b1), respectively.
   *
   *  Requires: __b0 * __b1 <= __g.max() - __g.min().
   *
   *  Using uniform_int_distribution with a range that is very
   *  small relative to the range of the generator ends up wasting
   *  potentially expensively generated randomness, since
   *  uniform_int_distribution does not store leftover randomness
   *  between invocations.
   *
   *  If we know we want two integers in ranges that are sufficiently
   *  small, we can compose the ranges, use a single distribution
   *  invocation, and significantly reduce the waste.
  */
  template<typename _IntType, typename _UniformRandomBitGenerator>
    pair<_IntType, _IntType>
    __gen_two_uniform_ints(_IntType __b0, _IntType __b1,
			   _UniformRandomBitGenerator&& __g)
    {
      _IntType __x
	= uniform_int_distribution<_IntType>{0, (__b0 * __b1) - 1}(__g);
      return std::make_pair(__x / __b1, __x % __b1);
    }

	/**
	 *  @brief Shuffle the elements of a sequence using a uniform random
	 *         number generator.
	 *  @ingroup mutating_algorithms
	 *  @param  __first   A forward iterator.
	 *  @param  __last    A forward iterator.
	 *  @param  __g       A UniformRandomNumberGenerator (26.5.1.3).
	 *  @return  Nothing.
	 *
	 *  Reorders the elements in the range @p [__first,__last) using @p __g to
	 *  provide random numbers.
	 */
	template <typename _RandomAccessIterator,
			  typename _UniformRandomNumberGenerator>
	void
	shuffle(_RandomAccessIterator __first, _RandomAccessIterator __last,
			_UniformRandomNumberGenerator &&__g)
	{
		// concept requirements
		__glibcxx_function_requires(_Mutable_RandomAccessIteratorConcept<
									_RandomAccessIterator>)
			__glibcxx_requires_valid_range(__first, __last);

		if (__first == __last)
			return;

		typedef typename iterator_traits<_RandomAccessIterator>::difference_type
			_DistanceType;

		typedef typename std::make_unsigned<_DistanceType>::type __ud_type;
		typedef typename std::uniform_int_distribution<__ud_type> __distr_type;
		typedef typename __distr_type::param_type __p_type;

		typedef typename remove_reference<_UniformRandomNumberGenerator>::type
			_Gen;
		typedef typename common_type<typename _Gen::result_type, __ud_type>::type
			__uc_type;

		const __uc_type __urngrange = __g.max() - __g.min();
		const __uc_type __urange = __uc_type(__last - __first);

		if (__urngrange / __urange >= __urange)
		// I.e. (__urngrange >= __urange * __urange) but without wrap issues.
		{
			_RandomAccessIterator __i = __first + 1;

			// Since we know the range isn't empty, an even number of elements
			// means an uneven number of elements /to swap/, in which case we
			// do the first one up front:

			if ((__urange % 2) == 0)
			{
				__distr_type __d{0, 1};
				std::iter_swap(__i++, __first + __d(__g));
			}

			// Now we know that __last - __i is even, so we do the rest in pairs,
			// using a single distribution invocation to produce swap positions
			// for two successive elements at a time:

			while (__i != __last)
			{
				const __uc_type __swap_range = __uc_type(__i - __first) + 1;

				const pair<__uc_type, __uc_type> __pospos =
					__gen_two_uniform_ints(__swap_range, __swap_range + 1, __g);

				std::iter_swap(__i++, __first + __pospos.first);
				std::iter_swap(__i++, __first + __pospos.second);
			}

			return;
		}

		__distr_type __d;

		for (_RandomAccessIterator __i = __first + 1; __i != __last; ++__i)
			std::iter_swap(__i, __first + __d(__g, __p_type(0, __i - __first)));
	}
#endif // C++11
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif /* _STL_ALGO_H */
#else
#include_next <bits/stl_algo.h>
#endif