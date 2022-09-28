#pragma once
#include <detail/workaround.hpp>
#include <__type_traits/detail/yes_no_type.hpp>
#if !defined(BOOST_NO_CXX11_DECLTYPE) && !BOOST_WORKAROUND(BOOST_MSVC, < 1800)
namespace detail
{

	struct is_destructible_imp
	{
		template <typename T, typename = decltype(declval<T &>().~T())>
		static type_traits::yes_type test(int);
		template <typename>
		static type_traits::no_type test(...);
	};

}

template <class T>
struct is_destructible : public integral_constant<bool, sizeof(detail::is_destructible_imp::test<T>(0)) == sizeof(type_traits::yes_type)>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_destructible must be complete types");
};

#else

#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/is_class.hpp>

namespace boost
{

	// We don't know how to implement this:
	template <class T>
	struct is_destructible : public integral_constant<bool, is_pod<T>::value || is_class<T>::value>
	{
		BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_destructible must be complete types");
	};
#endif

template <>
struct is_destructible<void> : public false_type
{
};
template <>
struct is_destructible<void const> : public false_type
{
};
template <>
struct is_destructible<void volatile> : public false_type
{
};
template <>
struct is_destructible<void const volatile> : public false_type
{
};
template <class T>
struct is_destructible<T &> : public is_destructible<T>
{
};
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class T>
struct is_destructible<T &&> : public is_destructible<T>
{
};
#endif
template <class T, std::size_t N>
struct is_destructible<T[N]> : public is_destructible<T>
{
};
template <class T>
struct is_destructible<T[]> : public is_destructible<T>
{
};