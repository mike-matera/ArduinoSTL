#pragma once
	// TODO: remove this implementation once https://gcc.gnu.org/bugzilla/show_bug.cgi?id=106611 is fixed
#ifndef _LIBCPP_COMPILER_GCC

	template <class _Tp>
	struct _LIBCPP_TEMPLATE_VIS is_nothrow_move_constructible
		: public integral_constant<bool, __is_nothrow_constructible(_Tp, add_rvalue_reference_t<_Tp>)>
	{
	};

#else // _LIBCPP_COMPILER_GCC

	template <class _Tp>
	struct _LIBCPP_TEMPLATE_VIS is_nothrow_move_constructible
		: public is_nothrow_constructible<_Tp, add_rvalue_reference_t<_Tp>>
	{
	};

#endif // _LIBCPP_COMPILER_GCC

#if _LIBCPP_STD_VER > 14
	template <class _Tp>
	inline constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<_Tp>::value;
#endif