#pragma once
#include "is_destructible.hpp"
#include "is_default_constructible.hpp"
namespace detail
{

	struct is_constructible_imp
	{
		template <typename T, typename... TheArgs, typename = decltype(T(declval<TheArgs>()...))>
		static type_traits::yes_type test(int);
		template <typename, typename...>
		static type_traits::no_type test(...);

		template <typename T, typename Arg, typename = decltype(::new T(declval<Arg>()))>
		static type_traits::yes_type test1(int);
		template <typename, typename>
		static type_traits::no_type test1(...);

		template <typename T>
		static type_traits::yes_type ref_test(T);
		template <typename T>
		static type_traits::no_type ref_test(...);
	};

}

template <class T, class... Args>
struct is_constructible : public integral_constant<bool, sizeof(detail::is_constructible_imp::test<T, Args...>(0)) == sizeof(type_traits::yes_type)>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "The target type must be complete in order to test for constructibility");
};
template <class T, class Arg>
struct is_constructible<T, Arg> : public integral_constant<bool, is_destructible<T>::value && sizeof(detail::is_constructible_imp::test1<T, Arg>(0)) == sizeof(type_traits::yes_type)>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "The target type must be complete in order to test for constructibility");
};
template <class Ref, class Arg>
struct is_constructible<Ref &, Arg> : public integral_constant<bool, sizeof(detail::is_constructible_imp::ref_test<Ref &>(declval<Arg>())) == sizeof(type_traits::yes_type)>
{
};
template <class Ref, class Arg>
struct is_constructible<Ref &&, Arg> : public integral_constant<bool, sizeof(detail::is_constructible_imp::ref_test<Ref &&>(declval<Arg>())) == sizeof(type_traits::yes_type)>
{
};

template <>
struct is_constructible<void> : public false_type
{
};
template <>
struct is_constructible<void const> : public false_type
{
};
template <>
struct is_constructible<void const volatile> : public false_type
{
};
template <>
struct is_constructible<void volatile> : public false_type
{
};

template <class T>
struct is_constructible<T> : public is_default_constructible<T>
{
};