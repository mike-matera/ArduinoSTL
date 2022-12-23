#pragma once
#include <__type_traits/detail/yes_no_type.hpp>
namespace detail
{

	struct is_assignable_imp
	{
		template <typename T, typename U, typename = decltype(declval<T>() = declval<U>())>
		static type_traits::yes_type test(int);

		template <typename, typename>
		static type_traits::no_type test(...);
	};

}

template <class T, class U>
struct is_assignable : public integral_constant<bool, sizeof(detail::is_assignable_imp::test<T, U>(0)) == sizeof(type_traits::yes_type)>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_assignable must be complete types");
};
template <class T, std::size_t N, class U>
struct is_assignable<T[N], U> : public is_assignable<T, U>
{
};
template <class T, std::size_t N, class U>
struct is_assignable<T (&)[N], U> : public is_assignable<T &, U>
{
};
template <class T, class U>
struct is_assignable<T[], U> : public is_assignable<T, U>
{
};
template <class T, class U>
struct is_assignable<T (&)[], U> : public is_assignable<T &, U>
{
};
template <class U>
struct is_assignable<void, U> : public integral_constant<bool, false>
{
};
template <class U>
struct is_assignable<void const, U> : public integral_constant<bool, false>
{
};
template <class U>
struct is_assignable<void volatile, U> : public integral_constant<bool, false>
{
};
template <class U>
struct is_assignable<void const volatile, U> : public integral_constant<bool, false>
{
};