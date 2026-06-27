
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_HAS_TRIVIAL_ASSIGN_HPP_INCLUDED
#define BOOST_TT_HAS_TRIVIAL_ASSIGN_HPP_INCLUDED

#include <cstddef> // size_t

namespace boost
{
	using namespace std;
	template <typename T>
	struct has_trivial_assign : public integral_constant<bool,
#ifdef BOOST_HAS_TRIVIAL_ASSIGN
														 BOOST_HAS_TRIVIAL_ASSIGN(T)
#else
														 is_pod<T>::value && !is_const<T>::value && !is_volatile<T>::value
#endif
														 >
	{
	};

	template <>
	struct has_trivial_assign<void> : public false_type
	{
	};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
	template <>
	struct has_trivial_assign<void const> : public false_type
	{
	};
	template <>
	struct has_trivial_assign<void const volatile> : public false_type
	{
	};
	template <>
	struct has_trivial_assign<void volatile> : public false_type
	{
	};
#endif
	template <class T>
	struct has_trivial_assign<T volatile> : public false_type
	{
	};
	template <class T>
	struct has_trivial_assign<T &> : public false_type
	{
	};
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
	template <class T>
	struct has_trivial_assign<T &&> : public false_type
	{
	};
#endif
	// Arrays are not explictly assignable:
	template <typename T, std::size_t N>
	struct has_trivial_assign<T[N]> : public false_type
	{
	};
	template <typename T>
	struct has_trivial_assign<T[]> : public false_type
	{
	};

} // namespace boost

#endif // BOOST_TT_HAS_TRIVIAL_ASSIGN_HPP_INCLUDED