#pragma once
// Functions used by iterators -*- C++ -*-

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
 * Copyright (c) 1996-1998
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

/** @file bits/stl_iterator_base_funcs.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iterator}
 *
 *  This file contains all of the general iterator-related utility
 *  functions, such as distance() and advance().
 */
#pragma GCC system_header
#ifndef ARDUINO_ARCH_ESP32
#include <bits/stl_iterator_base_types.h> //此包含必须在<bits/stl_iterator_base_funcs.h>之前，否则SAM会出错
#endif
#ifdef ARDUINO_ARCH_AVR
#include <bits/concept_check.h>
#include <debug/assertions.h>
namespace std _GLIBCXX_VISIBILITY(default)
{
  _GLIBCXX_BEGIN_NAMESPACE_VERSION

#if __cplusplus >= 201103L

  template <typename _InputIterator>
  _GLIBCXX_NODISCARD [[__gnu__::__always_inline__]]
  inline _GLIBCXX17_CONSTEXPR _InputIterator
  next(_InputIterator __x, typename iterator_traits<_InputIterator>::difference_type __n = 1)
  {
    // concept requirements
    __glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
        std::advance(__x, __n);
    return __x;
  }

  template <typename _BidirectionalIterator>
  _GLIBCXX_NODISCARD [[__gnu__::__always_inline__]]
  inline _GLIBCXX17_CONSTEXPR _BidirectionalIterator
  prev(_BidirectionalIterator __x, typename iterator_traits<_BidirectionalIterator>::difference_type __n = 1)
  {
    // concept requirements
    __glibcxx_function_requires(_BidirectionalIteratorConcept<
                                _BidirectionalIterator>)
        std::advance(__x, -__n);
    return __x;
  }

#endif // C++11

  _GLIBCXX_END_NAMESPACE_VERSION
} // namespace
#else
#include_next <bits/stl_iterator_base_funcs.h>
#endif