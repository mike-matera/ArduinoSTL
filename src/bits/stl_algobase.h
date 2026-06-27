#pragma once
// SAM也有这个文件，但是使用了被弃用的<bits/stl_iterator_base_types.h>中定义的_Iter_base，所以SAM的此文件也只能弃用
//  Core algorithmic facilities -*- C++ -*-

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

/** @file bits/stl_algobase.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{algorithm}
 */
#ifdef ARDUINO_ARCH_AVR
#include <bits/stl_pair.h>
#include <bits/cpp_type_traits.h>
#endif
#ifdef ARDUINO_ARCH_SAM
#include <debug/safe_iterator.h>
#include <bits/concept_check.h>
#if __cplusplus >= 202002L
#include <compare>
#endif
#endif
#ifdef ARDUINO_ARCH_ESP32
#include_next <bits/stl_algobase.h>
#else
#include <bits/functexcept.h>
#include <bits/stl_iterator_base_funcs.h>
#include <bits/stl_iterator.h>
#include <bits/predefined_ops.h>
#include <debug/debug.h>
#if __cplusplus >= 201402L
#include <bit> // std::__bit_width
#else
#include <ext/numeric_traits.h>
#endif
#endif
#undef min
#undef max
namespace std _GLIBCXX_VISIBILITY(default)
{
  _GLIBCXX_BEGIN_NAMESPACE_VERSION
#ifndef ARDUINO_ARCH_ESP32
  /*
   * A constexpr wrapper for __builtin_memcmp.
   * @param __num The number of elements of type _Tp (not bytes).
   */
  template <typename _Tp, typename _Up>
  _GLIBCXX14_CONSTEXPR inline int
  __memcmp(const _Tp *__first1, const _Up *__first2, size_t __num)
  {
#if __cplusplus >= 201103L
    static_assert(sizeof(_Tp) == sizeof(_Up), "can be compared with memcmp");
#endif
#ifdef __cpp_lib_is_constant_evaluated
    if (std::is_constant_evaluated())
    {
      for (; __num > 0; ++__first1, ++__first2, --__num)
        if (*__first1 != *__first2)
          return *__first1 < *__first2 ? -1 : 1;
      return 0;
    }
    else
#endif
      return __builtin_memcmp(__first1, __first2, sizeof(_Tp) * __num);
  }

  /**
   *  @brief This does what you think it does.
   *  @ingroup sorting_algorithms
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @return   The lesser of the parameters.
   *
   *  This is the simple classic generic implementation.  It will work on
   *  temporary expressions, since they are only evaluated once, unlike a
   *  preprocessor macro.
   */
  template <typename _Tp>
  _GLIBCXX_NODISCARD _GLIBCXX14_CONSTEXPR inline const _Tp &
  min(const _Tp &__a, const _Tp &__b)
  {
    // concept requirements
    __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
        // return __b < __a ? __b : __a;
        if (__b < __a) return __b;
    return __a;
  }

  /**
   *  @brief This does what you think it does.
   *  @ingroup sorting_algorithms
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @return   The greater of the parameters.
   *
   *  This is the simple classic generic implementation.  It will work on
   *  temporary expressions, since they are only evaluated once, unlike a
   *  preprocessor macro.
   */
  template <typename _Tp>
  _GLIBCXX_NODISCARD _GLIBCXX14_CONSTEXPR inline const _Tp &
  max(const _Tp &__a, const _Tp &__b)
  {
    // concept requirements
    __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
        // return  __a < __b ? __b : __a;
        if (__a < __b) return __b;
    return __a;
  }

  /**
   *  @brief This does what you think it does.
   *  @ingroup sorting_algorithms
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @param  __comp  A @link comparison_functors comparison functor@endlink.
   *  @return   The lesser of the parameters.
   *
   *  This will work on temporary expressions, since they are only evaluated
   *  once, unlike a preprocessor macro.
   */
  template <typename _Tp, typename _Compare>
  _GLIBCXX_NODISCARD _GLIBCXX14_CONSTEXPR inline const _Tp &
  min(const _Tp &__a, const _Tp &__b, _Compare __comp)
  {
    // return __comp(__b, __a) ? __b : __a;
    if (__comp(__b, __a))
      return __b;
    return __a;
  }

  /**
   *  @brief This does what you think it does.
   *  @ingroup sorting_algorithms
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @param  __comp  A @link comparison_functors comparison functor@endlink.
   *  @return   The greater of the parameters.
   *
   *  This will work on temporary expressions, since they are only evaluated
   *  once, unlike a preprocessor macro.
   */
  template <typename _Tp, typename _Compare>
  _GLIBCXX_NODISCARD _GLIBCXX14_CONSTEXPR inline const _Tp &
  max(const _Tp &__a, const _Tp &__b, _Compare __comp)
  {
    // return __comp(__a, __b) ? __b : __a;
    if (__comp(__a, __b))
      return __b;
    return __a;
  }

  // Fallback implementation of the function in bits/stl_iterator.h used to
  // remove the __normal_iterator wrapper. See copy, fill, ...
  template <typename _Iterator>
  _GLIBCXX20_CONSTEXPR inline _Iterator
  __niter_base(_Iterator __it)
      _GLIBCXX_NOEXCEPT_IF(std::is_nothrow_copy_constructible<_Iterator>::value)
  {
    return __it;
  }

#if __cplusplus < 201103L
  template <typename _Ite, typename _Seq>
  _Ite
  __niter_base(const ::__gnu_debug::_Safe_iterator<_Ite, _Seq,
                                                   std::random_access_iterator_tag> &);

  template <typename _Ite, typename _Cont, typename _Seq>
  _Ite
  __niter_base(const ::__gnu_debug::_Safe_iterator<
               ::__gnu_cxx::__normal_iterator<_Ite, _Cont>, _Seq,
               std::random_access_iterator_tag> &);
#else
  template <typename _Ite, typename _Seq>
  _GLIBCXX20_CONSTEXPR decltype(std::__niter_base(std::declval<_Ite>()))
  __niter_base(const ::__gnu_debug::_Safe_iterator<_Ite, _Seq,
                                                   std::random_access_iterator_tag> &) noexcept(std::is_nothrow_copy_constructible<_Ite>::value);
#endif

  // Reverse the __niter_base transformation to get a
  // __normal_iterator back again (this assumes that __normal_iterator
  // is only used to wrap random access iterators, like pointers).
  template <typename _From, typename _To>
  _GLIBCXX20_CONSTEXPR inline _From
  __niter_wrap(_From __from, _To __res)
  {
    return __from + (std::__niter_base(__res) - std::__niter_base(__from));
  }

  // No need to wrap, iterator already has the right type.
  template <typename _Iterator>
  _GLIBCXX20_CONSTEXPR inline _Iterator
  __niter_wrap(const _Iterator &, _Iterator __res)
  {
    return __res;
  }

  // All of these auxiliary structs serve two purposes.  (1) Replace
  // calls to copy with memmove whenever possible.  (Memmove, not memcpy,
  // because the input and output ranges are permitted to overlap.)
  // (2) If we're using random access iterators, then write the loop as
  // a for loop with an explicit count.

  template <bool _IsMove, bool _IsSimple, typename _Category>
  struct __copy_move
  {
    template <typename _II, typename _OI>
    _GLIBCXX20_CONSTEXPR static _OI
    __copy_m(_II __first, _II __last, _OI __result)
    {
      for (; __first != __last; ++__result, (void)++__first)
        *__result = *__first;
      return __result;
    }
  };

#if __cplusplus >= 201103L
  template <typename _Category>
  struct __copy_move<true, false, _Category>
  {
    template <typename _II, typename _OI>
    _GLIBCXX20_CONSTEXPR static _OI
    __copy_m(_II __first, _II __last, _OI __result)
    {
      for (; __first != __last; ++__result, (void)++__first)
        *__result = std::move(*__first);
      return __result;
    }
  };
#endif

  template <>
  struct __copy_move<false, false, random_access_iterator_tag>
  {
    template <typename _II, typename _OI>
    _GLIBCXX20_CONSTEXPR static _OI
    __copy_m(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::difference_type _Distance;
      for (_Distance __n = __last - __first; __n > 0; --__n)
      {
        *__result = *__first;
        ++__first;
        ++__result;
      }
      return __result;
    }

    template <typename _Tp, typename _Up>
    static void
    __assign_one(_Tp *__to, _Up *__from)
    {
      *__to = *__from;
    }
  };

#if __cplusplus >= 201103L
  template <>
  struct __copy_move<true, false, random_access_iterator_tag>
  {
    template <typename _II, typename _OI>
    _GLIBCXX20_CONSTEXPR static _OI
    __copy_m(_II __first, _II __last, _OI __result)
    {
      typedef typename iterator_traits<_II>::difference_type _Distance;
      for (_Distance __n = __last - __first; __n > 0; --__n)
      {
        *__result = std::move(*__first);
        ++__first;
        ++__result;
      }
      return __result;
    }

    template <typename _Tp, typename _Up>
    static void
    __assign_one(_Tp *__to, _Up *__from)
    {
      *__to = std::move(*__from);
    }
  };
#endif

  template <bool _IsMove>
  struct __copy_move<_IsMove, true, random_access_iterator_tag>
  {
    template <typename _Tp, typename _Up>
    _GLIBCXX20_CONSTEXPR static _Up *
    __copy_m(_Tp *__first, _Tp *__last, _Up *__result)
    {
      const ptrdiff_t _Num = __last - __first;
      if (__builtin_expect(_Num > 1, true))
        __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
      else if (_Num == 1)
        std::__copy_move<_IsMove, false, random_access_iterator_tag>::
            __assign_one(__result, __first);
      return __result + _Num;
    }
  };

  _GLIBCXX_BEGIN_NAMESPACE_CONTAINER

  template <typename _Tp, typename _Ref, typename _Ptr>
  struct _Deque_iterator;

  struct _Bit_iterator;

  _GLIBCXX_END_NAMESPACE_CONTAINER

#if _GLIBCXX_HOSTED
  // Helpers for streambuf iterators (either istream or ostream).
  // NB: avoid including <iosfwd>, relatively large.
  template <typename _CharT>
  struct char_traits;

  template <typename _CharT, typename _Traits>
  class istreambuf_iterator;

  template <typename _CharT, typename _Traits>
  class ostreambuf_iterator;

  template <bool _IsMove, typename _CharT>
  typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                                  ostreambuf_iterator<_CharT, char_traits<_CharT>>>::__type
  __copy_move_a2(_CharT *, _CharT *,
                 ostreambuf_iterator<_CharT, char_traits<_CharT>>);

  template <bool _IsMove, typename _CharT>
  typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                                  ostreambuf_iterator<_CharT, char_traits<_CharT>>>::__type
  __copy_move_a2(const _CharT *, const _CharT *,
                 ostreambuf_iterator<_CharT, char_traits<_CharT>>);

  template <bool _IsMove, typename _CharT>
  typename __gnu_cxx::__enable_if<__is_char<_CharT>::__value,
                                  _CharT *>::__type
  __copy_move_a2(istreambuf_iterator<_CharT, char_traits<_CharT>>,
                 istreambuf_iterator<_CharT, char_traits<_CharT>>, _CharT *);

  template <bool _IsMove, typename _CharT>
  typename __gnu_cxx::__enable_if<
      __is_char<_CharT>::__value,
      _GLIBCXX_STD_C::_Deque_iterator<_CharT, _CharT &, _CharT *>>::__type
      __copy_move_a2(
          istreambuf_iterator<_CharT, char_traits<_CharT>>,
          istreambuf_iterator<_CharT, char_traits<_CharT>>,
          _GLIBCXX_STD_C::_Deque_iterator<_CharT, _CharT &, _CharT *>);
#endif // HOSTED

  template <bool _IsMove, typename _II, typename _OI>
  _GLIBCXX20_CONSTEXPR inline _OI
  __copy_move_a2(_II __first, _II __last, _OI __result)
  {
    typedef typename iterator_traits<_II>::iterator_category _Category;
#ifdef __cpp_lib_is_constant_evaluated
    if (std::is_constant_evaluated())
      return std::__copy_move<_IsMove, false, _Category>::
          __copy_m(__first, __last, __result);
#endif
    return std::__copy_move<_IsMove, __memcpyable<_OI, _II>::__value,
                            _Category>::__copy_m(__first, __last, __result);
  }

  template <bool _IsMove,
            typename _Tp, typename _Ref, typename _Ptr, typename _OI>
  _OI
      __copy_move_a1(_GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>,
                     _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>,
                     _OI);

  template <bool _IsMove,
            typename _ITp, typename _IRef, typename _IPtr, typename _OTp>
  _GLIBCXX_STD_C::_Deque_iterator<_OTp, _OTp &, _OTp *>
      __copy_move_a1(_GLIBCXX_STD_C::_Deque_iterator<_ITp, _IRef, _IPtr>,
                     _GLIBCXX_STD_C::_Deque_iterator<_ITp, _IRef, _IPtr>,
                     _GLIBCXX_STD_C::_Deque_iterator<_OTp, _OTp &, _OTp *>);

  template <bool _IsMove, typename _II, typename _Tp>
  typename __gnu_cxx::__enable_if<
      __is_random_access_iter<_II>::__value,
      _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Tp &, _Tp *>>::__type
      __copy_move_a1(_II, _II, _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Tp &, _Tp *>);

  template <bool _IsMove, typename _II, typename _OI>
  _GLIBCXX20_CONSTEXPR inline _OI
  __copy_move_a1(_II __first, _II __last, _OI __result)
  {
    return std::__copy_move_a2<_IsMove>(__first, __last, __result);
  }

  template <bool _IsMove, typename _II, typename _OI>
  _GLIBCXX20_CONSTEXPR inline _OI
  __copy_move_a(_II __first, _II __last, _OI __result)
  {
    return std::__niter_wrap(__result,
                             std::__copy_move_a1<_IsMove>(std::__niter_base(__first),
                                                          std::__niter_base(__last),
                                                          std::__niter_base(__result)));
  }

  template <bool _IsMove,
            typename _Ite, typename _Seq, typename _Cat, typename _OI>
  _GLIBCXX20_CONSTEXPR
      _OI
      __copy_move_a(const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &,
                    const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &,
                    _OI);

  template <bool _IsMove,
            typename _II, typename _Ite, typename _Seq, typename _Cat>
  _GLIBCXX20_CONSTEXPR
      __gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat>
      __copy_move_a(_II, _II,
                    const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &);

  template <bool _IsMove,
            typename _IIte, typename _ISeq, typename _ICat,
            typename _OIte, typename _OSeq, typename _OCat>
  _GLIBCXX20_CONSTEXPR ::__gnu_debug::_Safe_iterator<_OIte, _OSeq, _OCat>
  __copy_move_a(const ::__gnu_debug::_Safe_iterator<_IIte, _ISeq, _ICat> &,
                const ::__gnu_debug::_Safe_iterator<_IIte, _ISeq, _ICat> &,
                const ::__gnu_debug::_Safe_iterator<_OIte, _OSeq, _OCat> &);

  template <typename _InputIterator, typename _Size, typename _OutputIterator>
  _GLIBCXX20_CONSTEXPR
      _OutputIterator
      __copy_n_a(_InputIterator __first, _Size __n, _OutputIterator __result,
                 bool)
  {
    if (__n > 0)
    {
      while (true)
      {
        *__result = *__first;
        ++__result;
        if (--__n > 0)
          ++__first;
        else
          break;
      }
    }
    return __result;
  }

#if _GLIBCXX_HOSTED
  template <typename _CharT, typename _Size>
  typename __gnu_cxx::__enable_if<
      __is_char<_CharT>::__value, _CharT *>::__type
  __copy_n_a(istreambuf_iterator<_CharT, char_traits<_CharT>>,
             _Size, _CharT *, bool);

  template <typename _CharT, typename _Size>
  typename __gnu_cxx::__enable_if<
      __is_char<_CharT>::__value,
      _GLIBCXX_STD_C::_Deque_iterator<_CharT, _CharT &, _CharT *>>::__type
  __copy_n_a(istreambuf_iterator<_CharT, char_traits<_CharT>>, _Size,
             _GLIBCXX_STD_C::_Deque_iterator<_CharT, _CharT &, _CharT *>,
             bool);
#endif
#endif //! ARDUINO_ARCH_ESP32
#ifdef ARDUINO_ARCH_SAM
  /**
   *  @brief Copies the range [first,last) into result.
   *  @ingroup mutating_algorithms
   *  @param  __first  An input iterator.
   *  @param  __last   An input iterator.
   *  @param  __result An output iterator.
   *  @return   result + (last - first)
   *
   *  This inline function will boil down to a call to @c memmove whenever
   *  possible.  Failing that, if random access iterators are passed, then the
   *  loop count will be known (and therefore a candidate for compiler
   *  optimizations such as unrolling).  Result may not be contained within
   *  [first,last); the copy_backward function should be used instead.
   *
   *  Note that the end of the output range is permitted to be contained
   *  within [first,last).
   */
  template <typename _II, typename _OI>
  _GLIBCXX20_CONSTEXPR inline _OI
  copy(_II __first, _II __last, _OI __result)
  {
    // concept requirements
    __glibcxx_function_requires(_InputIteratorConcept<_II>)
        __glibcxx_function_requires(_OutputIteratorConcept<_OI,
                                                           typename iterator_traits<_II>::reference>)
            __glibcxx_requires_can_increment_range(__first, __last, __result);

    return std::__copy_move_a<__is_move_iterator<_II>::__value>(std::__miter_base(__first), std::__miter_base(__last), __result);
  }
#endif // ARDUINO_ARCH_SAM
#ifndef ARDUINO_ARCH_ESP32
#if __cplusplus >= 201103L
  /**
   *  @brief Moves the range [first,last) into result.
   *  @ingroup mutating_algorithms
   *  @param  __first  An input iterator.
   *  @param  __last   An input iterator.
   *  @param  __result An output iterator.
   *  @return   result + (last - first)
   *
   *  This inline function will boil down to a call to @c memmove whenever
   *  possible.  Failing that, if random access iterators are passed, then the
   *  loop count will be known (and therefore a candidate for compiler
   *  optimizations such as unrolling).  Result may not be contained within
   *  [first,last); the move_backward function should be used instead.
   *
   *  Note that the end of the output range is permitted to be contained
   *  within [first,last).
   */
  template <typename _II, typename _OI>
  _GLIBCXX20_CONSTEXPR inline _OI
  move(_II __first, _II __last, _OI __result)
  {
    // concept requirements
    __glibcxx_function_requires(_InputIteratorConcept<_II>)
        __glibcxx_function_requires(_OutputIteratorConcept<_OI,
                                                           typename iterator_traits<_II>::value_type &&>)
            __glibcxx_requires_can_increment_range(__first, __last, __result);

    return std::__copy_move_a<true>(std::__miter_base(__first),
                                    std::__miter_base(__last), __result);
  }

#define _GLIBCXX_MOVE3(_Tp, _Up, _Vp) std::move(_Tp, _Up, _Vp)
#else
#define _GLIBCXX_MOVE3(_Tp, _Up, _Vp) std::copy(_Tp, _Up, _Vp)
#endif

  template <bool _IsMove, bool _IsSimple, typename _Category>
  struct __copy_move_backward
  {
    template <typename _BI1, typename _BI2>
    _GLIBCXX20_CONSTEXPR static _BI2
    __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      while (__first != __last)
        *--__result = *--__last;
      return __result;
    }
  };

#if __cplusplus >= 201103L
  template <typename _Category>
  struct __copy_move_backward<true, false, _Category>
  {
    template <typename _BI1, typename _BI2>
    _GLIBCXX20_CONSTEXPR static _BI2
    __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      while (__first != __last)
        *--__result = std::move(*--__last);
      return __result;
    }
  };
#endif

  template <>
  struct __copy_move_backward<false, false, random_access_iterator_tag>
  {
    template <typename _BI1, typename _BI2>
    _GLIBCXX20_CONSTEXPR static _BI2
    __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typename iterator_traits<_BI1>::difference_type
          __n = __last - __first;
      for (; __n > 0; --__n)
        *--__result = *--__last;
      return __result;
    }
  };

#if __cplusplus >= 201103L
  template <>
  struct __copy_move_backward<true, false, random_access_iterator_tag>
  {
    template <typename _BI1, typename _BI2>
    _GLIBCXX20_CONSTEXPR static _BI2
    __copy_move_b(_BI1 __first, _BI1 __last, _BI2 __result)
    {
      typename iterator_traits<_BI1>::difference_type
          __n = __last - __first;
      for (; __n > 0; --__n)
        *--__result = std::move(*--__last);
      return __result;
    }
  };
#endif

  template <bool _IsMove>
  struct __copy_move_backward<_IsMove, true, random_access_iterator_tag>
  {
    template <typename _Tp, typename _Up>
    _GLIBCXX20_CONSTEXPR static _Up *
    __copy_move_b(_Tp *__first, _Tp *__last, _Up *__result)
    {
      const ptrdiff_t _Num = __last - __first;
      if (__builtin_expect(_Num > 1, true))
        __builtin_memmove(__result - _Num, __first, sizeof(_Tp) * _Num);
      else if (_Num == 1)
        std::__copy_move<_IsMove, false, random_access_iterator_tag>::
            __assign_one(__result - 1, __first);
      return __result - _Num;
    }
  };

  template <bool _IsMove, typename _BI1, typename _BI2>
  _GLIBCXX20_CONSTEXPR inline _BI2
  __copy_move_backward_a2(_BI1 __first, _BI1 __last, _BI2 __result)
  {
    typedef typename iterator_traits<_BI1>::iterator_category _Category;
#ifdef __cpp_lib_is_constant_evaluated
    if (std::is_constant_evaluated())
      return std::__copy_move_backward<_IsMove, false, _Category>::
          __copy_move_b(__first, __last, __result);
#endif
    return std::__copy_move_backward<_IsMove,
                                     __memcpyable<_BI2, _BI1>::__value,
                                     _Category>::__copy_move_b(__first,
                                                               __last,
                                                               __result);
  }

  template <bool _IsMove, typename _BI1, typename _BI2>
  _GLIBCXX20_CONSTEXPR inline _BI2
  __copy_move_backward_a1(_BI1 __first, _BI1 __last, _BI2 __result)
  {
    return std::__copy_move_backward_a2<_IsMove>(__first, __last, __result);
  }

  template <bool _IsMove,
            typename _Tp, typename _Ref, typename _Ptr, typename _OI>
  _OI
      __copy_move_backward_a1(_GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>,
                              _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>,
                              _OI);

  template <bool _IsMove,
            typename _ITp, typename _IRef, typename _IPtr, typename _OTp>
  _GLIBCXX_STD_C::_Deque_iterator<_OTp, _OTp &, _OTp *>
      __copy_move_backward_a1(
          _GLIBCXX_STD_C::_Deque_iterator<_ITp, _IRef, _IPtr>,
          _GLIBCXX_STD_C::_Deque_iterator<_ITp, _IRef, _IPtr>,
          _GLIBCXX_STD_C::_Deque_iterator<_OTp, _OTp &, _OTp *>);

  template <bool _IsMove, typename _II, typename _Tp>
  typename __gnu_cxx::__enable_if<
      __is_random_access_iter<_II>::__value,
      _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Tp &, _Tp *>>::__type
      __copy_move_backward_a1(_II, _II,
                              _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Tp &, _Tp *>);

  template <bool _IsMove, typename _II, typename _OI>
  _GLIBCXX20_CONSTEXPR inline _OI
  __copy_move_backward_a(_II __first, _II __last, _OI __result)
  {
    return std::__niter_wrap(__result,
                             std::__copy_move_backward_a1<_IsMove>(std::__niter_base(__first), std::__niter_base(__last),
                                                                   std::__niter_base(__result)));
  }

  template <bool _IsMove,
            typename _Ite, typename _Seq, typename _Cat, typename _OI>
  _GLIBCXX20_CONSTEXPR
      _OI
      __copy_move_backward_a(
          const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &,
          const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &,
          _OI);

  template <bool _IsMove,
            typename _II, typename _Ite, typename _Seq, typename _Cat>
  _GLIBCXX20_CONSTEXPR
      __gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat>
      __copy_move_backward_a(_II, _II,
                             const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &);

  template <bool _IsMove,
            typename _IIte, typename _ISeq, typename _ICat,
            typename _OIte, typename _OSeq, typename _OCat>
  _GLIBCXX20_CONSTEXPR ::__gnu_debug::_Safe_iterator<_OIte, _OSeq, _OCat>
  __copy_move_backward_a(
      const ::__gnu_debug::_Safe_iterator<_IIte, _ISeq, _ICat> &,
      const ::__gnu_debug::_Safe_iterator<_IIte, _ISeq, _ICat> &,
      const ::__gnu_debug::_Safe_iterator<_OIte, _OSeq, _OCat> &);

#if __cplusplus >= 201103L
  /**
   *  @brief Moves the range [first,last) into result.
   *  @ingroup mutating_algorithms
   *  @param  __first  A bidirectional iterator.
   *  @param  __last   A bidirectional iterator.
   *  @param  __result A bidirectional iterator.
   *  @return   result - (last - first)
   *
   *  The function has the same effect as move, but starts at the end of the
   *  range and works its way to the start, returning the start of the result.
   *  This inline function will boil down to a call to @c memmove whenever
   *  possible.  Failing that, if random access iterators are passed, then the
   *  loop count will be known (and therefore a candidate for compiler
   *  optimizations such as unrolling).
   *
   *  Result may not be in the range (first,last].  Use move instead.  Note
   *  that the start of the output range may overlap [first,last).
   */
  template <typename _BI1, typename _BI2>
  _GLIBCXX20_CONSTEXPR inline _BI2
  move_backward(_BI1 __first, _BI1 __last, _BI2 __result)
  {
    // concept requirements
    __glibcxx_function_requires(_BidirectionalIteratorConcept<_BI1>)
        __glibcxx_function_requires(_Mutable_BidirectionalIteratorConcept<_BI2>)
            __glibcxx_function_requires(_OutputIteratorConcept<_BI2,
                                                               typename iterator_traits<_BI1>::value_type &&>)
                __glibcxx_requires_can_decrement_range(__first, __last, __result);

    return std::__copy_move_backward_a<true>(std::__miter_base(__first),
                                             std::__miter_base(__last),
                                             __result);
  }

#define _GLIBCXX_MOVE_BACKWARD3(_Tp, _Up, _Vp) std::move_backward(_Tp, _Up, _Vp)
#else
#define _GLIBCXX_MOVE_BACKWARD3(_Tp, _Up, _Vp) std::copy_backward(_Tp, _Up, _Vp)
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++17-extensions"
  template <typename _ForwardIterator, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline void
  __fill_a1(_ForwardIterator __first, _ForwardIterator __last,
            const _Tp &__value)
  {
    // We can optimize this loop by moving the load from __value outside
    // the loop, but only if we know that making that copy is trivial,
    // and the assignment in the loop is also trivial (so that the identity
    // of the operand doesn't matter).
    const bool __load_outside_loop =
#if __has_builtin(__is_trivially_constructible) && __has_builtin(__is_trivially_assignable)
        __is_trivially_constructible(_Tp, const _Tp &) && __is_trivially_assignable(__decltype(*__first), const _Tp &)
#else
        __is_trivially_copyable(_Tp) && __is_same(_Tp, __typeof__(*__first))
#endif
        && sizeof(_Tp) <= sizeof(long long);

    // When the condition is true, we use a copy of __value,
    // otherwise we just use another reference.
    typedef typename __gnu_cxx::__conditional_type<__load_outside_loop,
                                                   const _Tp,
                                                   const _Tp &>::__type _Up;
    _Up __val(__value);
    for (; __first != __last; ++__first)
      *__first = __val;
  }
#pragma GCC diagnostic pop

  // Specialization: for char types we can use memset.
  template <typename _Tp>
  _GLIBCXX20_CONSTEXPR inline typename __gnu_cxx::__enable_if<__is_byte<_Tp>::__value, void>::__type
  __fill_a1(_Tp *__first, _Tp *__last, const _Tp &__c)
  {
    const _Tp __tmp = __c;
#if __cpp_lib_is_constant_evaluated
    if (std::is_constant_evaluated())
    {
      for (; __first != __last; ++__first)
        *__first = __tmp;
      return;
    }
#endif
    if (const size_t __len = __last - __first)
      __builtin_memset(__first, static_cast<unsigned char>(__tmp), __len);
  }

  template <typename _Ite, typename _Cont, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline void
  __fill_a1(::__gnu_cxx::__normal_iterator<_Ite, _Cont> __first,
            ::__gnu_cxx::__normal_iterator<_Ite, _Cont> __last,
            const _Tp &__value)
  {
    std::__fill_a1(__first.base(), __last.base(), __value);
  }

  template <typename _Tp, typename _VTp>
  void
  __fill_a1(const _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Tp &, _Tp *> &,
            const _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Tp &, _Tp *> &,
            const _VTp &);

  _GLIBCXX20_CONSTEXPR
  void
  __fill_a1(_GLIBCXX_STD_C::_Bit_iterator, _GLIBCXX_STD_C::_Bit_iterator,
            const bool &);

  template <typename _FIte, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline void
  __fill_a(_FIte __first, _FIte __last, const _Tp &__value)
  {
    std::__fill_a1(__first, __last, __value);
  }

  template <typename _Ite, typename _Seq, typename _Cat, typename _Tp>
  _GLIBCXX20_CONSTEXPR void
  __fill_a(const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &,
           const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &,
           const _Tp &);

  // Used by fill_n, generate_n, etc. to convert _Size to an integral type:
  inline _GLIBCXX_CONSTEXPR int
  __size_to_integer(int __n) { return __n; }
  inline _GLIBCXX_CONSTEXPR unsigned
  __size_to_integer(unsigned __n) { return __n; }
  inline _GLIBCXX_CONSTEXPR long
  __size_to_integer(long __n) { return __n; }
  inline _GLIBCXX_CONSTEXPR unsigned long
  __size_to_integer(unsigned long __n) { return __n; }
  inline _GLIBCXX_CONSTEXPR long long
  __size_to_integer(long long __n) { return __n; }
  inline _GLIBCXX_CONSTEXPR unsigned long long
  __size_to_integer(unsigned long long __n) { return __n; }

#if defined(__GLIBCXX_TYPE_INT_N_0)
  __extension__ inline _GLIBCXX_CONSTEXPR __GLIBCXX_TYPE_INT_N_0
  __size_to_integer(__GLIBCXX_TYPE_INT_N_0 __n) { return __n; }
  __extension__ inline _GLIBCXX_CONSTEXPR unsigned __GLIBCXX_TYPE_INT_N_0
  __size_to_integer(unsigned __GLIBCXX_TYPE_INT_N_0 __n) { return __n; }
#endif
#if defined(__GLIBCXX_TYPE_INT_N_1)
  __extension__ inline _GLIBCXX_CONSTEXPR __GLIBCXX_TYPE_INT_N_1
  __size_to_integer(__GLIBCXX_TYPE_INT_N_1 __n) { return __n; }
  __extension__ inline _GLIBCXX_CONSTEXPR unsigned __GLIBCXX_TYPE_INT_N_1
  __size_to_integer(unsigned __GLIBCXX_TYPE_INT_N_1 __n) { return __n; }
#endif
#if defined(__GLIBCXX_TYPE_INT_N_2)
  __extension__ inline _GLIBCXX_CONSTEXPR __GLIBCXX_TYPE_INT_N_2
  __size_to_integer(__GLIBCXX_TYPE_INT_N_2 __n) { return __n; }
  __extension__ inline _GLIBCXX_CONSTEXPR unsigned __GLIBCXX_TYPE_INT_N_2
  __size_to_integer(unsigned __GLIBCXX_TYPE_INT_N_2 __n) { return __n; }
#endif
#if defined(__GLIBCXX_TYPE_INT_N_3)
  __extension__ inline _GLIBCXX_CONSTEXPR unsigned __GLIBCXX_TYPE_INT_N_3
  __size_to_integer(__GLIBCXX_TYPE_INT_N_3 __n) { return __n; }
  __extension__ inline _GLIBCXX_CONSTEXPR __GLIBCXX_TYPE_INT_N_3
  __size_to_integer(unsigned __GLIBCXX_TYPE_INT_N_3 __n) { return __n; }
#endif

  inline _GLIBCXX_CONSTEXPR long long
  __size_to_integer(float __n) { return (long long)__n; }
  inline _GLIBCXX_CONSTEXPR long long
  __size_to_integer(double __n) { return (long long)__n; }
  inline _GLIBCXX_CONSTEXPR long long
  __size_to_integer(long double __n) { return (long long)__n; }
#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_FLOAT128)
  __extension__ inline _GLIBCXX_CONSTEXPR long long
  __size_to_integer(__float128 __n) { return (long long)__n; }
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++17-extensions"
  template <typename _OutputIterator, typename _Size, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline _OutputIterator
  __fill_n_a1(_OutputIterator __first, _Size __n, const _Tp &__value)
  {
    // See std::__fill_a1 for explanation of this condition.
    const bool __load_outside_loop =
#if __has_builtin(__is_trivially_constructible) && __has_builtin(__is_trivially_assignable)
        __is_trivially_constructible(_Tp, const _Tp &) && __is_trivially_assignable(__decltype(*__first), const _Tp &)
#else
        __is_trivially_copyable(_Tp) && __is_same(_Tp, __typeof__(*__first))
#endif
        && sizeof(_Tp) <= sizeof(long long);

    // When the condition is true, we use a copy of __value,
    // otherwise we just use another reference.
    typedef typename __gnu_cxx::__conditional_type<__load_outside_loop,
                                                   const _Tp,
                                                   const _Tp &>::__type _Up;
    _Up __val(__value);
    for (; __n > 0; --__n, (void)++__first)
      *__first = __val;
    return __first;
  }
#pragma GCC diagnostic pop

  template <typename _Ite, typename _Seq, typename _Cat, typename _Size,
            typename _Tp>
  _GLIBCXX20_CONSTEXPR ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat>
  __fill_n_a(const ::__gnu_debug::_Safe_iterator<_Ite, _Seq, _Cat> &__first,
             _Size __n, const _Tp &__value,
             std::input_iterator_tag);

  template <typename _OutputIterator, typename _Size, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline _OutputIterator
  __fill_n_a(_OutputIterator __first, _Size __n, const _Tp &__value,
             std::output_iterator_tag)
  {
#if __cplusplus >= 201103L
    static_assert(is_integral<_Size>{}, "fill_n must pass integral size");
#endif
    return __fill_n_a1(__first, __n, __value);
  }

  template <typename _OutputIterator, typename _Size, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline _OutputIterator
  __fill_n_a(_OutputIterator __first, _Size __n, const _Tp &__value,
             std::input_iterator_tag)
  {
#if __cplusplus >= 201103L
    static_assert(is_integral<_Size>{}, "fill_n must pass integral size");
#endif
    return __fill_n_a1(__first, __n, __value);
  }

  template <typename _OutputIterator, typename _Size, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline _OutputIterator
  __fill_n_a(_OutputIterator __first, _Size __n, const _Tp &__value,
             std::random_access_iterator_tag)
  {
#if __cplusplus >= 201103L
    static_assert(is_integral<_Size>{}, "fill_n must pass integral size");
#endif
    if (__n <= 0)
      return __first;

    __glibcxx_requires_can_increment(__first, __n);

    std::__fill_a(__first, __first + __n, __value);
    return __first + __n;
  }

  /**
   *  @brief Fills the range [first,first+n) with copies of value.
   *  @ingroup mutating_algorithms
   *  @param  __first  An output iterator.
   *  @param  __n      The count of copies to perform.
   *  @param  __value  A reference-to-const of arbitrary type.
   *  @return   The iterator at first+n.
   *
   *  This function fills a range with copies of the same value.  For char
   *  types filling contiguous areas of memory, this becomes an inline call
   *  to @c memset or @c wmemset.
   *
   *  If @p __n is negative, the function does nothing.
   */
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // DR 865. More algorithms that throw away information
  // DR 426. search_n(), fill_n(), and generate_n() with negative n
  template <typename _OI, typename _Size, typename _Tp>
  _GLIBCXX20_CONSTEXPR inline _OI
  fill_n(_OI __first, _Size __n, const _Tp &__value)
  {
    // concept requirements
    __glibcxx_function_requires(_OutputIteratorConcept<_OI, const _Tp &>)

        return std::__fill_n_a(__first, std::__size_to_integer(__n), __value,
                               std::__iterator_category(__first));
  }

  template <bool _BoolType>
  struct __equal
  {
    template <typename _II1, typename _II2>
    _GLIBCXX20_CONSTEXPR static bool
    equal(_II1 __first1, _II1 __last1, _II2 __first2)
    {
      for (; __first1 != __last1; ++__first1, (void)++__first2)
        if (!(*__first1 == *__first2))
          return false;
      return true;
    }
  };

  template <>
  struct __equal<true>
  {
    template <typename _Tp>
    _GLIBCXX20_CONSTEXPR static bool
    equal(const _Tp *__first1, const _Tp *__last1, const _Tp *__first2)
    {
      if (const size_t __len = (__last1 - __first1))
        return !std::__memcmp(__first1, __first2, __len);
      return true;
    }
  };

  template <typename _Tp, typename _Ref, typename _Ptr, typename _II>
  typename __gnu_cxx::__enable_if<
      __is_random_access_iter<_II>::__value, bool>::__type
      __equal_aux1(_GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>,
                   _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>,
                   _II);

  template <typename _Tp1, typename _Ref1, typename _Ptr1,
            typename _Tp2, typename _Ref2, typename _Ptr2>
  bool
      __equal_aux1(_GLIBCXX_STD_C::_Deque_iterator<_Tp1, _Ref1, _Ptr1>,
                   _GLIBCXX_STD_C::_Deque_iterator<_Tp1, _Ref1, _Ptr1>,
                   _GLIBCXX_STD_C::_Deque_iterator<_Tp2, _Ref2, _Ptr2>);

  template <typename _II, typename _Tp, typename _Ref, typename _Ptr>
  typename __gnu_cxx::__enable_if<
      __is_random_access_iter<_II>::__value, bool>::__type
      __equal_aux1(_II, _II,
                   _GLIBCXX_STD_C::_Deque_iterator<_Tp, _Ref, _Ptr>);

  template <typename _II1, typename _II2>
  _GLIBCXX20_CONSTEXPR inline bool
  __equal_aux1(_II1 __first1, _II1 __last1, _II2 __first2)
  {
    typedef typename iterator_traits<_II1>::value_type _ValueType1;
    const bool __simple = ((__is_integer<_ValueType1>::__value
#if _GLIBCXX_USE_BUILTIN_TRAIT(__is_pointer)
                            || __is_pointer(_ValueType1)
#endif
#if __glibcxx_byte && __glibcxx_type_trait_variable_templates
                            // bits/cpp_type_traits.h declares std::byte
                            || is_same_v<_ValueType1, byte>
#endif
                            ) &&
                           __memcmpable<_II1, _II2>::__value);
    return std::__equal<__simple>::equal(__first1, __last1, __first2);
  }

  template <typename _II1, typename _II2>
  _GLIBCXX20_CONSTEXPR inline bool
  __equal_aux(_II1 __first1, _II1 __last1, _II2 __first2)
  {
    return std::__equal_aux1(std::__niter_base(__first1),
                             std::__niter_base(__last1),
                             std::__niter_base(__first2));
  }

  template <typename _II1, typename _Seq1, typename _Cat1, typename _II2>
  _GLIBCXX20_CONSTEXPR bool
  __equal_aux(const ::__gnu_debug::_Safe_iterator<_II1, _Seq1, _Cat1> &,
              const ::__gnu_debug::_Safe_iterator<_II1, _Seq1, _Cat1> &,
              _II2);

  template <typename _II1, typename _II2, typename _Seq2, typename _Cat2>
  _GLIBCXX20_CONSTEXPR bool
  __equal_aux(_II1, _II1,
              const ::__gnu_debug::_Safe_iterator<_II2, _Seq2, _Cat2> &);

  template <typename _II1, typename _Seq1, typename _Cat1,
            typename _II2, typename _Seq2, typename _Cat2>
  _GLIBCXX20_CONSTEXPR bool
  __equal_aux(const ::__gnu_debug::_Safe_iterator<_II1, _Seq1, _Cat1> &,
              const ::__gnu_debug::_Safe_iterator<_II1, _Seq1, _Cat1> &,
              const ::__gnu_debug::_Safe_iterator<_II2, _Seq2, _Cat2> &);

  template <typename, typename>
  struct __lc_rai
  {
    template <typename _II1, typename _II2>
    _GLIBCXX20_CONSTEXPR static _II1
    __newlast1(_II1, _II1 __last1, _II2, _II2)
    {
      return __last1;
    }

    template <typename _II>
    _GLIBCXX20_CONSTEXPR static bool
    __cnd2(_II __first, _II __last)
    {
      return __first != __last;
    }
  };

  template <>
  struct __lc_rai<random_access_iterator_tag, random_access_iterator_tag>
  {
    template <typename _RAI1, typename _RAI2>
    _GLIBCXX20_CONSTEXPR static _RAI1
    __newlast1(_RAI1 __first1, _RAI1 __last1,
               _RAI2 __first2, _RAI2 __last2)
    {
      const typename iterator_traits<_RAI1>::difference_type
          __diff1 = __last1 - __first1;
      const typename iterator_traits<_RAI2>::difference_type
          __diff2 = __last2 - __first2;
      return __diff2 < __diff1 ? __first1 + __diff2 : __last1;
    }

    template <typename _RAI>
    static _GLIBCXX20_CONSTEXPR bool
    __cnd2(_RAI, _RAI)
    {
      return true;
    }
  };

  template <typename _II1, typename _II2, typename _Compare>
  _GLIBCXX20_CONSTEXPR bool
  __lexicographical_compare_impl(_II1 __first1, _II1 __last1,
                                 _II2 __first2, _II2 __last2,
                                 _Compare __comp)
  {
    typedef typename iterator_traits<_II1>::iterator_category _Category1;
    typedef typename iterator_traits<_II2>::iterator_category _Category2;
    typedef std::__lc_rai<_Category1, _Category2> __rai_type;

    __last1 = __rai_type::__newlast1(__first1, __last1, __first2, __last2);
    for (; __first1 != __last1 && __rai_type::__cnd2(__first2, __last2);
         ++__first1, (void)++__first2)
    {
      if (__comp(__first1, __first2))
        return true;
      if (__comp(__first2, __first1))
        return false;
    }
    return __first1 == __last1 && __first2 != __last2;
  }

  template <bool _BoolType>
  struct __lexicographical_compare
  {
    template <typename _II1, typename _II2>
    _GLIBCXX20_CONSTEXPR static bool
    __lc(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
    {
      using __gnu_cxx::__ops::__iter_less_iter;
      return std::__lexicographical_compare_impl(__first1, __last1,
                                                 __first2, __last2,
                                                 __iter_less_iter());
    }

    template <typename _II1, typename _II2>
    _GLIBCXX20_CONSTEXPR static int
    __3way(_II1 __first1, _II1 __last1, _II2 __first2, _II2 __last2)
    {
      while (__first1 != __last1)
      {
        if (__first2 == __last2)
          return +1;
        if (*__first1 < *__first2)
          return -1;
        if (*__first2 < *__first1)
          return +1;
        ++__first1;
        ++__first2;
      }
      return int(__first2 == __last2) - 1;
    }
  };

  template <>
  struct __lexicographical_compare<true>
  {
    template <typename _Tp, typename _Up>
    _GLIBCXX20_CONSTEXPR static bool
    __lc(const _Tp *__first1, const _Tp *__last1,
         const _Up *__first2, const _Up *__last2)
    {
      return __3way(__first1, __last1, __first2, __last2) < 0;
    }

    template <typename _Tp, typename _Up>
    _GLIBCXX20_CONSTEXPR static ptrdiff_t
    __3way(const _Tp *__first1, const _Tp *__last1,
           const _Up *__first2, const _Up *__last2)
    {
      const size_t __len1 = __last1 - __first1;
      const size_t __len2 = __last2 - __first2;
      if (const size_t __len = std::min(__len1, __len2))
        if (int __result = std::__memcmp(__first1, __first2, __len))
          return __result;
      return ptrdiff_t(__len1 - __len2);
    }
  };
  // 1574
  /// This is a helper function for the sort routines and for random.tcc.
  //  Precondition: __n > 0.
  template <typename _Tp>
  inline _GLIBCXX_CONSTEXPR _Tp
  __lg(_Tp __n)
  {
#if __cplusplus >= 201402L
    return std::__bit_width(make_unsigned_t<_Tp>(__n)) - 1;
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlong-long"
    // Use +__n so it promotes to at least int.
    return (sizeof(+__n) * __CHAR_BIT__ - 1) - (sizeof(+__n) == sizeof(long long)
                                                    ? __builtin_clzll(+__n)
                                                    : (sizeof(+__n) == sizeof(long)
                                                           ? __builtin_clzl(+__n)
                                                           : __builtin_clz(+__n)));
#pragma GCC diagnostic pop
#endif
  }
  // 1596
  //  Implementation of std::find_if, also used in std::remove_if and others.
  template <typename _Iterator, typename _Predicate>
  _GLIBCXX20_CONSTEXPR inline _Iterator
  __find_if(_Iterator __first, _Iterator __last, _Predicate __pred)
  {
    while (__first != __last && !__pred(__first))
      ++__first;
    return __first;
  }

  template <typename _InputIterator, typename _Predicate>
  _GLIBCXX20_CONSTEXPR
      typename iterator_traits<_InputIterator>::difference_type
      __count_if(_InputIterator __first, _InputIterator __last, _Predicate __pred)
  {
    typename iterator_traits<_InputIterator>::difference_type __n = 0;
    for (; __first != __last; ++__first)
      if (__pred(__first))
        ++__n;
    return __n;
  }

  template <typename _ForwardIterator, typename _Predicate>
  _GLIBCXX20_CONSTEXPR
      _ForwardIterator
      __remove_if(_ForwardIterator __first, _ForwardIterator __last,
                  _Predicate __pred)
  {
    __first = std::__find_if(__first, __last, __pred);
    if (__first == __last)
      return __first;
    _ForwardIterator __result = __first;
    ++__first;
    for (; __first != __last; ++__first)
      if (!__pred(__first))
      {
        *__result = _GLIBCXX_MOVE(*__first);
        ++__result;
      }
    return __result;
  }
#endif //! ARDUINO_ARCH_ESP32
#ifdef ARDUINO_ARCH_AVR
#if __cplusplus >= 201103L
  template <typename _ForwardIterator1, typename _ForwardIterator2,
            typename _BinaryPredicate>
  _GLIBCXX20_CONSTEXPR bool
  __is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                   _ForwardIterator2 __first2, _BinaryPredicate __pred)
  {
    // Efficiently compare identical prefixes:  O(N) if sequences
    // have the same elements in the same order.
    for (; __first1 != __last1; ++__first1, (void)++__first2)
      if (!__pred(__first1, __first2))
        break;

    if (__first1 == __last1)
      return true;

    // Establish __last2 assuming equal ranges by iterating over the
    // rest of the list.
    _ForwardIterator2 __last2 = __first2;
    std::advance(__last2, std::distance(__first1, __last1));
    for (_ForwardIterator1 __scan = __first1; __scan != __last1; ++__scan)
    {
      if (__scan != std::__find_if(__first1, __scan,
                                   __gnu_cxx::__ops::__iter_comp_iter(__pred, __scan)))
        continue; // We've seen this one before.

      auto __matches = std::__count_if(__first2, __last2,
                                       __gnu_cxx::__ops::__iter_comp_iter(__pred, __scan));
      if (0 == __matches ||
          std::__count_if(__scan, __last1,
                          __gnu_cxx::__ops::__iter_comp_iter(__pred, __scan)) != __matches)
        return false;
    }
    return true;
  }

  /**
   *  @brief  Checks whether a permutation of the second sequence is equal
   *          to the first sequence.
   *  @ingroup non_mutating_algorithms
   *  @param  __first1  Start of first range.
   *  @param  __last1   End of first range.
   *  @param  __first2  Start of second range.
   *  @return true if there exists a permutation of the elements in the range
   *          [__first2, __first2 + (__last1 - __first1)), beginning with
   *          ForwardIterator2 begin, such that equal(__first1, __last1, begin)
   *          returns true; otherwise, returns false.
   */
  template <typename _ForwardIterator1, typename _ForwardIterator2>
  _GLIBCXX20_CONSTEXPR inline bool
  is_permutation(_ForwardIterator1 __first1, _ForwardIterator1 __last1,
                 _ForwardIterator2 __first2)
  {
    // concept requirements
    __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator1>)
        __glibcxx_function_requires(_ForwardIteratorConcept<_ForwardIterator2>)
            __glibcxx_function_requires(_EqualOpConcept<
                                        typename iterator_traits<_ForwardIterator1>::value_type,
                                        typename iterator_traits<_ForwardIterator2>::value_type>)
                __glibcxx_requires_valid_range(__first1, __last1);

    return std::__is_permutation(__first1, __last1, __first2,
                                 __gnu_cxx::__ops::__iter_equal_to_iter());
  }
#endif // C++11
#endif
  _GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
#ifdef ARDUINO_ARCH_SAM
#include <debug/safe_iterator.tcc> //此文件依赖本文件，所以不能由<safe_iterator.h>包含
#endif
#ifndef ARDUINO_ARCH_ESP32
// NB: This file is included within many other C++ includes, as a way
// of getting the base algorithms. So, make sure that parallel bits
// come in too if requested.
#ifdef _GLIBCXX_PARALLEL
#include <parallel/algobase.h>
#endif
#endif