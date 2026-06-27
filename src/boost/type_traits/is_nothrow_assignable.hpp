// boost原版没有这个文件，从is_nothrow_assignable.hpp改版而来
//   (C) Copyright John Maddock 2015.
//   Use, modification and distribution are subject to the Boost Software License,
//   Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//   http://www.boost.org/LICENSE_1_0.txt).
//
//   See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_IS_ASSIGNABLE_HPP_INCLUDED
#define BOOST_TT_IS_ASSIGNABLE_HPP_INCLUDED

#include <cstddef> // size_t

namespace boost
{

	template <class T, class U = T>
	struct is_nothrow_assignable;

}

namespace boost
{
	using namespace std;
	namespace detail
	{

		struct is_nothrow_assignable_imp
		{
			template <typename T, typename U, typename = enable_if_t<noexcept(declval<T>() = declval<U>())>>
			static boost::type_traits::yes_type test(int);

			template <typename, typename>
			static boost::type_traits::no_type test(...);
		};

	}

	template <class T, class U>
	struct is_nothrow_assignable : public integral_constant<bool, sizeof(detail::is_nothrow_assignable_imp::test<T, U>(0)) == sizeof(boost::type_traits::yes_type)>
	{
		BOOST_STATIC_ASSERT_MSG(boost::is_complete<T>::value, "Arguments to is_nothrow_assignable must be complete types");
	};
	template <class T, std::size_t N, class U>
	struct is_nothrow_assignable<T[N], U> : public is_nothrow_assignable<T, U>
	{
	};
	template <class T, std::size_t N, class U>
	struct is_nothrow_assignable<T (&)[N], U> : public is_nothrow_assignable<T &, U>
	{
	};
	template <class T, class U>
	struct is_nothrow_assignable<T[], U> : public is_nothrow_assignable<T, U>
	{
	};
	template <class T, class U>
	struct is_nothrow_assignable<T (&)[], U> : public is_nothrow_assignable<T &, U>
	{
	};
	template <class U>
	struct is_nothrow_assignable<void, U> : public integral_constant<bool, false>
	{
	};
	template <class U>
	struct is_nothrow_assignable<void const, U> : public integral_constant<bool, false>
	{
	};
	template <class U>
	struct is_nothrow_assignable<void volatile, U> : public integral_constant<bool, false>
	{
	};
	template <class U>
	struct is_nothrow_assignable<void const volatile, U> : public integral_constant<bool, false>
	{
	};

} // namespace boost

#endif // BOOST_TT_IS_ASSIGNABLE_HPP_INCLUDED