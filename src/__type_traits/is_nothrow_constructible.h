#pragma once
#include <__config>
#if __has_builtin(__is_nothrow_constructible)

	template <
		class _Tp, class... _Args>
	struct _LIBCPP_TEMPLATE_VIS is_nothrow_constructible
		: public integral_constant<bool, __is_nothrow_constructible(_Tp, _Args...)>
	{
	};
#else

	template <bool, bool, class _Tp, class... _Args>
	struct __libcpp_is_nothrow_constructible;

	template <class _Tp, class... _Args>
	struct __libcpp_is_nothrow_constructible</*is constructible*/ true, /*is reference*/ false, _Tp, _Args...>
		: public integral_constant<bool, noexcept(_Tp(declval<_Args>()...))>
	{
	};

	template <class _Tp>
	void __implicit_conversion_to(_Tp) noexcept {}

	template <class _Tp, class _Arg>
	struct __libcpp_is_nothrow_constructible</*is constructible*/ true, /*is reference*/ true, _Tp, _Arg>
		: public integral_constant<bool, noexcept(_VSTD::__implicit_conversion_to<_Tp>(declval<_Arg>()))>
	{
	};

	template <class _Tp, bool _IsReference, class... _Args>
	struct __libcpp_is_nothrow_constructible</*is constructible*/ false, _IsReference, _Tp, _Args...>
		: public false_type
	{
	};

	template <class _Tp, class... _Args>
	struct _LIBCPP_TEMPLATE_VIS is_nothrow_constructible
		: __libcpp_is_nothrow_constructible<is_constructible<_Tp, _Args...>::value, is_reference<_Tp>::value, _Tp, _Args...>
	{
	};

	template <class _Tp, size_t _Ns>
	struct _LIBCPP_TEMPLATE_VIS is_nothrow_constructible<_Tp[_Ns]>
		: __libcpp_is_nothrow_constructible<is_constructible<_Tp>::value, is_reference<_Tp>::value, _Tp>
	{
	};

#endif // __has_builtin(__is_nothrow_constructible)

#if _LIBCPP_STD_VER > 14
	template <class _Tp, class... _Args>
	inline constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<_Tp, _Args...>::value;
#endif