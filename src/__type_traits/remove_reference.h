#pragma once
#if __has_builtin(__remove_reference_t)
#else
	template <class _Tp>
	using __libcpp_remove_reference_t = typename remove_reference<_Tp>::type;
#endif // __has_builtin(__remove_reference_t)