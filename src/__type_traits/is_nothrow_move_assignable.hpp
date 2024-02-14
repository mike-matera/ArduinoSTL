#pragma once
#include "../static_assert.hpp"
#include "is_complete.hpp"
#include "../config/detail/suffix.hpp"
#ifdef BOOST_IS_NOTHROW_MOVE_ASSIGN

template <class T>
struct is_nothrow_move_assignable : public integral_constant<bool, BOOST_IS_NOTHROW_MOVE_ASSIGN(T)>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_nothrow_move_assignable must be complete types");
};
template <class T>
struct is_nothrow_move_assignable<T const> : public false_type
{
};
template <class T>
struct is_nothrow_move_assignable<T volatile> : public false_type
{
};
template <class T>
struct is_nothrow_move_assignable<T const volatile> : public false_type
{
};
template <class T>
struct is_nothrow_move_assignable<T &> : public false_type
{
};
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template <class T>
struct is_nothrow_move_assignable<T &&> : public false_type
{
};
#endif

#elif !defined(BOOST_NO_CXX11_NOEXCEPT) && !defined(BOOST_NO_SFINAE_EXPR) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40700)

namespace detail
{

	template <class T, class Enable = void>
	struct false_or_cpp11_noexcept_move_assignable : public std::false_type
	{
	};

	template <class T>
	struct false_or_cpp11_noexcept_move_assignable<
		T,
		typename std::enable_if<sizeof(T) && BOOST_NOEXCEPT_EXPR(std::declval<T &>() = std::declval<T>())>::type> : public std::integral_constant<bool, BOOST_NOEXCEPT_EXPR(std::declval<T &>() = std::declval<T>())>
	{
	};

}

template <class T>
struct is_nothrow_move_assignable : public integral_constant<bool, detail::false_or_cpp11_noexcept_move_assignable<T>::value>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_nothrow_move_assignable must be complete types");
};

template <class T>
struct is_nothrow_move_assignable<T const> : public false_type
{
};
template <class T>
struct is_nothrow_move_assignable<T const volatile> : public false_type
{
};
template <class T>
struct is_nothrow_move_assignable<T volatile> : public false_type
{
};
template <class T>
struct is_nothrow_move_assignable<T &> : public false_type
{
};
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
template <class T>
struct is_nothrow_move_assignable<T &&> : public false_type
{
};
#endif

#else

template <class T>
struct is_nothrow_move_assignable : public integral_constant<bool,
															 (has_trivial_move_assign<T>::value || has_nothrow_assign<T>::value) && !is_array<T>::value>
{
	BOOST_STATIC_ASSERT_MSG(is_complete<T>::value, "Arguments to is_nothrow_move_assignable must be complete types");
};

#endif

template <>
struct is_nothrow_move_assignable<void> : public false_type
{
};
#ifndef BOOST_NO_CV_VOID_SPECIALIZATIONS
template <>
struct is_nothrow_move_assignable<void const> : public false_type
{
};
template <>
struct is_nothrow_move_assignable<void const volatile> : public false_type
{
};
template <>
struct is_nothrow_move_assignable<void volatile> : public false_type
{
};
#endif