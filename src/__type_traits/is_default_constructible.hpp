#pragma once
#include <__type_traits/detail/yes_no_type.hpp>
#include <__type_traits/is_complete.hpp>
#include <static_assert.hpp>
namespace detail
{

	struct is_default_constructible_imp
	{
		template <typename _Tp, typename = decltype(_Tp())>
		static type_traits::yes_type test(int);

		template <typename>
		static type_traits::no_type test(...);
	};
#if BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40700)
	template <class T, bool b>
	struct is_default_constructible_abstract_filter
	{
		static const bool value = sizeof(is_default_constructible_imp::test<T>(0)) == sizeof(type_traits::yes_type);
	};
	template <class T>
	struct is_default_constructible_abstract_filter<T, true>
	{
		static const bool value = false;
	};
#endif
}

#if BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40700)
template <class T>
struct is_default_constructible : public integral_constant<bool, detail::is_default_constructible_abstract_filter<T, is_abstract<T>::value>::value>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_default_constructible must be complete types");
};
#else
template <class T>
struct is_default_constructible : public integral_constant<bool, sizeof(detail::is_default_constructible_imp::test<T>(0)) == sizeof(type_traits::yes_type)>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_default_constructible must be complete types");
};
#endif
template <class T, std::size_t N>
struct is_default_constructible<T[N]> : public is_default_constructible<T>
{
};
template <class T>
struct is_default_constructible<T[]> : public is_default_constructible<T>
{
};
template <class T>
struct is_default_constructible<T &> : public integral_constant<bool, false>
{
};
#if defined(__clang__) || (defined(__GNUC__) && (__GNUC__ <= 5)) || (defined(BOOST_MSVC) && (BOOST_MSVC == 1800))
template <class T1, class T2> struct _UCXXEXPORT pair;
template <class T, class U>
struct is_default_constructible<std::pair<T, U>> : public integral_constant<bool, is_default_constructible<T>::value && is_default_constructible<U>::value>
{
};
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template <class T>
struct is_default_constructible<T &&> : public integral_constant<bool, false>
{
};
#endif
template <>
struct is_default_constructible<void> : public integral_constant<bool, false>
{
};
template <>
struct is_default_constructible<void const> : public integral_constant<bool, false>
{
};
template <>
struct is_default_constructible<void volatile> : public integral_constant<bool, false>
{
};
template <>
struct is_default_constructible<void const volatile> : public integral_constant<bool, false>
{
};