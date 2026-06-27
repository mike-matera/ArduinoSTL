#pragma once
#include "../detail/workaround.hpp"
//
// We will undef this if the trait isn't fully functional:
//
#define BOOST_TT_HAS_WORKING_IS_COMPLETE

#if !defined(BOOST_NO_SFINAE_EXPR) && !BOOST_WORKAROUND(BOOST_MSVC, <= 1900) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40600)

namespace detail
{

	template <std::size_t N>
	struct ok_tag
	{
		double d;
		char c[N];
	};

	template <class T>
	ok_tag<sizeof(T)> check_is_complete(int);
	template <class T>
	char check_is_complete(...);
}

template <class T>
struct is_complete
	: public integral_constant<bool, is_function<typename remove_reference<T>::type>::value || (sizeof(detail::check_is_complete<T>(0)) != sizeof(char))>
{
};

#elif !defined(BOOST_NO_SFINAE) && !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS) && !BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40500)

namespace detail
{

	template <class T>
	struct is_complete_imp
	{
		template <class U, class = decltype(sizeof(declval<U>()))>
		static type_traits::yes_type check(U *);

		template <class U>
		static type_traits::no_type check(...);

		static const bool value = sizeof(check<T>(0)) == sizeof(type_traits::yes_type);
	};

} // namespace detail

template <class T>
struct is_complete : integral_constant<bool, is_function<typename remove_reference<T>::type>::value || detail::is_complete_imp<T>::value>
{
};
template <class T>
struct is_complete<T &> : is_complete<T>
{
};

#else

template <class T>
struct is_complete
	: public integral_constant<bool, true>
{
};

#undef BOOST_TT_HAS_WORKING_IS_COMPLETE

#endif