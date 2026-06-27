#ifdef ARDUINO_ARCH_SAM
#include <locale>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <limits>
#include <cstdio>
#include "../../new"
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
	namespace
	{
		struct _Save_errno
		{
			_Save_errno() : _M_errno(errno) { errno = 0; }
			~_Save_errno()
			{
				if (errno == 0)
					errno = _M_errno;
			}
			int _M_errno;
		};

		// calls setlocale(LC_ALL, "C") and returns a string containing the old
		// locale name. Caller must delete[] the string. Returns NULL on error.
		const char *
		__set_C_locale()
		{
			char *__old = setlocale(LC_ALL, 0);
			const size_t __len = strlen(__old) + 1;
			char *__sav = new (nothrow) char[__len];
			if (__sav)
			{
				memcpy(__sav, __old, __len);
				setlocale(LC_ALL, "C");
			}
			return __sav;
		}
	}

	template <>
	void
	__convert_to_v(const char *__s, float &__v, ios_base::iostate &__err,
				   const __c_locale &) throw()
	{
		// Assumes __s formatted for "C" locale.
		const char *__sav = __set_C_locale();
		if (!__sav)
		{
			__err = ios_base::failbit;
			return;
		}
		char *__sanity;
		bool __overflow = false;

#if !__FLT_HAS_INFINITY__
		const _Save_errno __save_errno;
#endif

#ifdef _GLIBCXX_HAVE_STRTOF
		__v = strtof(__s, &__sanity);
#else
		double __d = strtod(__s, &__sanity);
		__v = static_cast<float>(__d);
#ifdef _GLIBCXX_HAVE_FINITEF
		if (!finitef(__v))
			__overflow = true;
#elif defined(_GLIBCXX_HAVE_FINITE)
		if (!finite(static_cast<double>(__v)))
			__overflow = true;
#elif defined(_GLIBCXX_HAVE_ISINF)
		if (isinf(static_cast<double>(__v)))
			__overflow = true;
#else
		if (fabs(__d) > numeric_limits<float>::max())
			__overflow = true;
#endif
#endif // _GLIBCXX_HAVE_STRTOF

		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 23. Num_get overflow result.
		if (__sanity == __s || *__sanity != '\0')
		{
			__v = 0.0f;
			__err = ios_base::failbit;
		}
		else if (__overflow
#if __FLT_HAS_INFINITY__
				 || __v == numeric_limits<float>::infinity() || __v == -numeric_limits<float>::infinity()
#else
				 || ((__v > 1.0f || __v < -1.0f) && errno == ERANGE)
#endif
		)
		{
			if (__v > 0.0f)
				__v = numeric_limits<float>::max();
			else
				__v = -numeric_limits<float>::max();
			__err = ios_base::failbit;
		}

		setlocale(LC_ALL, __sav);
		delete[] __sav;
	}

	template <>
	void
	__convert_to_v(const char *__s, double &__v, ios_base::iostate &__err,
				   const __c_locale &) throw()
	{
		// Assumes __s formatted for "C" locale.
		const char *__sav = __set_C_locale();
		if (!__sav)
		{
			__err = ios_base::failbit;
			return;
		}
		char *__sanity;

#if !__DBL_HAS_INFINITY__
		const _Save_errno __save_errno;
#endif

		__v = strtod(__s, &__sanity);

		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 23. Num_get overflow result.
		if (__sanity == __s || *__sanity != '\0')
		{
			__v = 0.0;
			__err = ios_base::failbit;
		}
		else if (
#if __DBL_HAS_INFINITY__
			__v == numeric_limits<double>::infinity() || __v == -numeric_limits<double>::infinity())
#else
			(__v > 1.0 || __v < -1.0) && errno == ERANGE)
#endif
		{
			if (__v > 0.0)
				__v = numeric_limits<double>::max();
			else
				__v = -numeric_limits<double>::max();
			__err = ios_base::failbit;
		}

		setlocale(LC_ALL, __sav);
		delete[] __sav;
	}

	template <>
	void
	__convert_to_v(const char *__s, long double &__v,
				   ios_base::iostate &__err, const __c_locale &) throw()
	{
		// Assumes __s formatted for "C" locale.
		const char *__sav = __set_C_locale();
		if (!__sav)
		{
			__err = ios_base::failbit;
			return;
		}

#if !__LDBL_HAS_INFINITY__
		const _Save_errno __save_errno;
#endif

#if defined(_GLIBCXX_HAVE_STRTOLD) && !defined(_GLIBCXX_HAVE_BROKEN_STRTOLD)
		char *__sanity;
		__v = strtold(__s, &__sanity);

		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 23. Num_get overflow result.
		if (__sanity == __s || *__sanity != '\0')
#else
		typedef char_traits<char>::int_type int_type;
		int __p = sscanf(__s, "%Lf", &__v);

		if (!__p || static_cast<int_type>(__p) == char_traits<char>::eof())
#endif
		{
			__v = 0.0l;
			__err = ios_base::failbit;
		}
		else if (
#if __LDBL_HAS_INFINITY__
			__v == numeric_limits<long double>::infinity() || __v == -numeric_limits<long double>::infinity())
#else
			(__v > 1.0l || __v < -1.0l) && errno == ERANGE)
#endif
		{
			if (__v > 0.0l)
				__v = numeric_limits<long double>::max();
			else
				__v = -numeric_limits<long double>::max();
			__err = ios_base::failbit;
		}

		setlocale(LC_ALL, __sav);
		delete[] __sav;
	}

	void
	locale::facet::_S_create_c_locale(__c_locale &__cloc, const char *__s,
									  __c_locale)
	{
		// Currently, the generic model only supports the "C" locale.
		// See http://gcc.gnu.org/ml/libstdc++/2003-02/msg00345.html
		__cloc = 0;
		if (strcmp(__s, "C"))
			__throw_runtime_error(__N("locale::facet::_S_create_c_locale "
									  "name not valid"));
	}

	void
	locale::facet::_S_destroy_c_locale(__c_locale &__cloc)
	{
		__cloc = 0;
	}
	// 253
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
#endif