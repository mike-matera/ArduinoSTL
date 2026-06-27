#ifdef ARDUINO_ARCH_SAM
// GCC实现
#include "bits/locale_facets.h"
#include <locale>
#include <ext/concurrence.h>
#include <cstring>
namespace
{
  const int num_facets = (
      _GLIBCXX_NUM_FACETS + _GLIBCXX_NUM_CXX11_FACETS
#ifdef _GLIBCXX_LONG_DOUBLE_ALT128_COMPAT
      + _GLIBCXX_NUM_LBDL_ALT128_FACETS
#endif
      )
#ifdef _GLIBCXX_USE_WCHAR_T
    * 2
#endif
    + _GLIBCXX_NUM_UNICODE_FACETS;

  __gnu_cxx::__mutex&
  get_locale_mutex()
  {
    static __gnu_cxx::__mutex locale_mutex;
    return locale_mutex;
  }

  using namespace std;

  typedef char fake_locale_Impl[sizeof(locale::_Impl)]
  __attribute__ ((aligned(__alignof__(locale::_Impl))));
  fake_locale_Impl c_locale_impl;

  typedef char fake_locale[sizeof(locale)]
  __attribute__ ((aligned(__alignof__(locale))));
  fake_locale c_locale;

  typedef char fake_name_vec[sizeof(char*)]
  __attribute__ ((aligned(__alignof__(char*))));
  fake_name_vec name_vec[6 + _GLIBCXX_NUM_CATEGORIES];

  typedef char fake_names[sizeof(char[2])]
  __attribute__ ((aligned(__alignof__(char[2]))));
  fake_names name_c[6 + _GLIBCXX_NUM_CATEGORIES];

  typedef char fake_facet_vec[sizeof(locale::facet*)]
  __attribute__ ((aligned(__alignof__(locale::facet*))));
  fake_facet_vec facet_vec[num_facets];

  typedef char fake_cache_vec[sizeof(locale::facet*)]
  __attribute__ ((aligned(__alignof__(locale::facet*))));
  fake_cache_vec cache_vec[num_facets];

  typedef char fake_ctype_c[sizeof(std::ctype<char>)]
  __attribute__ ((aligned(__alignof__(std::ctype<char>))));
  fake_ctype_c ctype_c;

  typedef char fake_collate_c[sizeof(std::collate<char>)]
  __attribute__ ((aligned(__alignof__(std::collate<char>))));
  fake_collate_c collate_c;

  typedef char fake_numpunct_c[sizeof(numpunct<char>)]
  __attribute__ ((aligned(__alignof__(numpunct<char>))));
  fake_numpunct_c numpunct_c;

  typedef char fake_num_get_c[sizeof(num_get<char>)]
  __attribute__ ((aligned(__alignof__(num_get<char>))));
  fake_num_get_c num_get_c;

  typedef char fake_num_put_c[sizeof(num_put<char>)]
  __attribute__ ((aligned(__alignof__(num_put<char>))));
  fake_num_put_c num_put_c;

  typedef char fake_codecvt_c[sizeof(codecvt<char, char, mbstate_t>)]
  __attribute__ ((aligned(__alignof__(codecvt<char, char, mbstate_t>))));
  fake_codecvt_c codecvt_c;

  typedef char fake_moneypunct_c[sizeof(moneypunct<char, true>)]
  __attribute__ ((aligned(__alignof__(moneypunct<char, true>))));
  fake_moneypunct_c moneypunct_ct;
  fake_moneypunct_c moneypunct_cf;

  typedef char fake_money_get_c[sizeof(money_get<char>)]
  __attribute__ ((aligned(__alignof__(money_get<char>))));
  fake_money_get_c money_get_c;

  typedef char fake_money_put_c[sizeof(money_put<char>)]
  __attribute__ ((aligned(__alignof__(money_put<char>))));
  fake_money_put_c money_put_c;

  typedef char fake_timepunct_c[sizeof(__timepunct<char>)]
  __attribute__ ((aligned(__alignof__(__timepunct<char>))));
  fake_timepunct_c timepunct_c;

  typedef char fake_time_get_c[sizeof(time_get<char>)]
  __attribute__ ((aligned(__alignof__(time_get<char>))));
  fake_time_get_c time_get_c;

  typedef char fake_time_put_c[sizeof(time_put<char>)]
  __attribute__ ((aligned(__alignof__(time_put<char>))));
  fake_time_put_c time_put_c;

  typedef char fake_messages_c[sizeof(messages<char>)]
  __attribute__ ((aligned(__alignof__(messages<char>))));
  fake_messages_c messages_c;

#ifdef  _GLIBCXX_USE_WCHAR_T
  typedef char fake_wtype_w[sizeof(std::ctype<wchar_t>)]
  __attribute__ ((aligned(__alignof__(std::ctype<wchar_t>))));
  fake_wtype_w ctype_w;

  typedef char fake_wollate_w[sizeof(std::collate<wchar_t>)]
  __attribute__ ((aligned(__alignof__(std::collate<wchar_t>))));
  fake_wollate_w collate_w;

  typedef char fake_numpunct_w[sizeof(numpunct<wchar_t>)]
  __attribute__ ((aligned(__alignof__(numpunct<wchar_t>))));
  fake_numpunct_w numpunct_w;

  typedef char fake_num_get_w[sizeof(num_get<wchar_t>)]
  __attribute__ ((aligned(__alignof__(num_get<wchar_t>))));
  fake_num_get_w num_get_w;

  typedef char fake_num_put_w[sizeof(num_put<wchar_t>)]
  __attribute__ ((aligned(__alignof__(num_put<wchar_t>))));
  fake_num_put_w num_put_w;

  typedef char fake_wodecvt_w[sizeof(codecvt<wchar_t, char, mbstate_t>)]
  __attribute__ ((aligned(__alignof__(codecvt<wchar_t, char, mbstate_t>))));
  fake_wodecvt_w codecvt_w;

  typedef char fake_moneypunct_w[sizeof(moneypunct<wchar_t, true>)]
  __attribute__ ((aligned(__alignof__(moneypunct<wchar_t, true>))));
  fake_moneypunct_w moneypunct_wt;
  fake_moneypunct_w moneypunct_wf;

  typedef char fake_money_get_w[sizeof(money_get<wchar_t>)]
  __attribute__ ((aligned(__alignof__(money_get<wchar_t>))));
  fake_money_get_w money_get_w;

  typedef char fake_money_put_w[sizeof(money_put<wchar_t>)]
  __attribute__ ((aligned(__alignof__(money_put<wchar_t>))));
  fake_money_put_w money_put_w;

  typedef char fake_timepunct_w[sizeof(__timepunct<wchar_t>)]
  __attribute__ ((aligned(__alignof__(__timepunct<wchar_t>))));
  fake_timepunct_w timepunct_w;

  typedef char fake_time_get_w[sizeof(time_get<wchar_t>)]
  __attribute__ ((aligned(__alignof__(time_get<wchar_t>))));
  fake_time_get_w time_get_w;

  typedef char fake_time_put_w[sizeof(time_put<wchar_t>)]
  __attribute__ ((aligned(__alignof__(time_put<wchar_t>))));
  fake_time_put_w time_put_w;

  typedef char fake_messages_w[sizeof(messages<wchar_t>)]
  __attribute__ ((aligned(__alignof__(messages<wchar_t>))));
  fake_messages_w messages_w;
#endif

  typedef char fake_codecvt_c16[sizeof(codecvt<char16_t, char, mbstate_t>)]
  __attribute__ ((aligned(__alignof__(codecvt<char16_t, char, mbstate_t>))));
  fake_codecvt_c16 codecvt_c16;

  typedef char fake_codecvt_c32[sizeof(codecvt<char32_t, char, mbstate_t>)]
  __attribute__ ((aligned(__alignof__(codecvt<char32_t, char, mbstate_t>))));
  fake_codecvt_c32 codecvt_c32;

#ifdef _GLIBCXX_USE_CHAR8_T
  typedef char fake_codecvt_c16_c8[sizeof(codecvt<char16_t, char8_t, mbstate_t>)]
  __attribute__ ((aligned(__alignof__(codecvt<char16_t, char8_t, mbstate_t>))));
  fake_codecvt_c16_c8 codecvt_c16_c8;

  typedef char fake_codecvt_c32_c8[sizeof(codecvt<char32_t, char8_t, mbstate_t>)]
  __attribute__ ((aligned(__alignof__(codecvt<char32_t, char8_t, mbstate_t>))));
  fake_codecvt_c32_c8 codecvt_c32_c8;
#endif

  // Storage for "C" locale caches.
  typedef char fake_num_cache_c[sizeof(std::__numpunct_cache<char>)]
  __attribute__ ((aligned(__alignof__(std::__numpunct_cache<char>))));
  fake_num_cache_c numpunct_cache_c;

  typedef char fake_money_cache_c[sizeof(std::__moneypunct_cache<char, true>)]
  __attribute__ ((aligned(__alignof__(std::__moneypunct_cache<char, true>))));
  fake_money_cache_c moneypunct_cache_ct;
  fake_money_cache_c moneypunct_cache_cf;

  typedef char fake_time_cache_c[sizeof(std::__timepunct_cache<char>)]
  __attribute__ ((aligned(__alignof__(std::__timepunct_cache<char>))));
  fake_time_cache_c timepunct_cache_c;

#ifdef _GLIBCXX_USE_WCHAR_T
  typedef char fake_num_cache_w[sizeof(std::__numpunct_cache<wchar_t>)]
  __attribute__ ((aligned(__alignof__(std::__numpunct_cache<wchar_t>))));
  fake_num_cache_w numpunct_cache_w;

  typedef char fake_money_cache_w[sizeof(std::__moneypunct_cache<wchar_t,true>)]
  __attribute__ ((aligned(__alignof__(std::__moneypunct_cache<wchar_t,true>))));
  fake_money_cache_w moneypunct_cache_wt;
  fake_money_cache_w moneypunct_cache_wf;

  typedef char fake_time_cache_w[sizeof(std::__timepunct_cache<wchar_t>)]
  __attribute__ ((aligned(__alignof__(std::__timepunct_cache<wchar_t>))));
  fake_time_cache_w timepunct_cache_w;
#endif
} // anonymous namespace

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

	locale::locale() throw() : _M_impl(0)
	{
		_S_initialize();

		// Checked locking to optimize the common case where _S_global
		// still points to _S_classic (locale::_S_initialize_once()):
		// - If they are the same, just increment the reference count and
		//   we are done.  This effectively constructs a C locale object
		//   identical to the static c_locale.
		// - Otherwise, _S_global can and may be destroyed due to
		//   locale::global() call on another thread, in which case we
		//   fall back to lock protected access to both _S_global and
		//   its reference count.
		_M_impl = _S_global;
		if (_M_impl != _S_classic)
		{
			__gnu_cxx::__scoped_lock sentry(get_locale_mutex());
			_S_global->_M_add_reference();
			_M_impl = _S_global;
		}
	}

	locale
	locale::global(const locale &__other)
	{
		_S_initialize();
		_Impl *__old;
		{
			__gnu_cxx::__scoped_lock sentry(get_locale_mutex());
			__old = _S_global;
			if (__other._M_impl != _S_classic)
				__other._M_impl->_M_add_reference();
			_S_global = __other._M_impl;
			const string __other_name = __other.name();
			if (__other_name != "*")
				setlocale(LC_ALL, __other_name.c_str());
		}

		// Reference count sanity check: one reference removed for the
		// subsition of __other locale, one added by return-by-value. Net
		// difference: zero. When the returned locale object's destructor
		// is called, then the reference count is decremented and possibly
		// destroyed.
		return locale(__old);
	}
	// 314
	// 321
	void
	locale::_S_initialize_once() throw()
	{
		// Need to check this because we could get called once from _S_initialize()
		// when the program is single-threaded, and then again (via __gthread_once)
		// when it's multi-threaded.
		if (_S_classic)
			return;

		// 2 references.
		// One reference for _S_classic, one for _S_global
		_S_classic = new (&c_locale_impl) _Impl(2);
		_S_global = _S_classic;
		new (&c_locale) locale(_S_classic);
	}

	void
	locale::_S_initialize()
	{
#ifdef __GTHREADS
		if (!__gnu_cxx::__is_single_threaded())
			__gthread_once(&_S_once, _S_initialize_once);
#endif
		if (__builtin_expect(!_S_classic, 0))
			_S_initialize_once();
	}
	// 348
	// 488
	//  Construct "C" _Impl.
	locale::_Impl::
		_Impl(size_t __refs) throw()
		: _M_refcount(__refs), _M_facets(0), _M_facets_size(num_facets),
		  _M_caches(0), _M_names(0)
	{
		_M_facets = new (&facet_vec) const facet *[_M_facets_size]();
		_M_caches = new (&cache_vec) const facet *[_M_facets_size]();

		// Name the categories.
		_M_names = new (&name_vec) char *[_S_categories_size]();
		_M_names[0] = new (&name_c[0]) char[2];
		std::memcpy(_M_names[0], locale::facet::_S_get_c_name(), 2);

		// This is needed as presently the C++ version of "C" locales
		// != data in the underlying locale model for __timepunct,
		// numpunct, and moneypunct. Also, the "C" locales must be
		// constructed in a way such that they are pre-allocated.
		// NB: Set locale::facets(ref) count to one so that each individual
		// facet is not destroyed when the locale (and thus locale::_Impl) is
		// destroyed.
		_M_init_facet(new (&ctype_c) std::ctype<char>((const ctype_base::mask*)0, false, 1));
		_M_init_facet(new (&codecvt_c) codecvt<char, char, mbstate_t>(1));

		typedef __numpunct_cache<char> num_cache_c;
		num_cache_c *__npc = new (&numpunct_cache_c) num_cache_c(2);
		_M_init_facet(new (&numpunct_c) numpunct<char>(__npc, 1));

		_M_init_facet(new (&num_get_c) num_get<char>(1));
		_M_init_facet(new (&num_put_c) num_put<char>(1));
		_M_init_facet(new (&collate_c) std::collate<char>(1));

		typedef __moneypunct_cache<char, false> money_cache_cf;
		typedef __moneypunct_cache<char, true> money_cache_ct;
		money_cache_cf *__mpcf = new (&moneypunct_cache_cf) money_cache_cf(2);
		_M_init_facet(new (&moneypunct_cf) moneypunct<char, false>(__mpcf, 1));
		money_cache_ct *__mpct = new (&moneypunct_cache_ct) money_cache_ct(2);
		_M_init_facet(new (&moneypunct_ct) moneypunct<char, true>(__mpct, 1));

		_M_init_facet(new (&money_get_c) money_get<char>(1));
		_M_init_facet(new (&money_put_c) money_put<char>(1));

		typedef __timepunct_cache<char> time_cache_c;
		time_cache_c *__tpc = new (&timepunct_cache_c) time_cache_c(2);
		_M_init_facet(new (&timepunct_c) __timepunct<char>(__tpc, 1));

		_M_init_facet(new (&time_get_c) time_get<char>(1));
		_M_init_facet(new (&time_put_c) time_put<char>(1));
		_M_init_facet(new (&messages_c) std::messages<char>(1));

#ifdef _GLIBCXX_USE_WCHAR_T
		_M_init_facet(new (&ctype_w) std::ctype<wchar_t>(1));
		_M_init_facet(new (&codecvt_w) codecvt<wchar_t, char, mbstate_t>(1));

		typedef __numpunct_cache<wchar_t> num_cache_w;
		num_cache_w *__npw = new (&numpunct_cache_w) num_cache_w(2);
		_M_init_facet(new (&numpunct_w) numpunct<wchar_t>(__npw, 1));

		_M_init_facet(new (&num_get_w) num_get<wchar_t>(1));
		_M_init_facet(new (&num_put_w) num_put<wchar_t>(1));
		_M_init_facet(new (&collate_w) std::collate<wchar_t>(1));

		typedef __moneypunct_cache<wchar_t, false> money_cache_wf;
		typedef __moneypunct_cache<wchar_t, true> money_cache_wt;
		money_cache_wf *__mpwf = new (&moneypunct_cache_wf) money_cache_wf(2);
		_M_init_facet(new (&moneypunct_wf) moneypunct<wchar_t, false>(__mpwf, 1));
		money_cache_wt *__mpwt = new (&moneypunct_cache_wt) money_cache_wt(2);
		_M_init_facet(new (&moneypunct_wt) moneypunct<wchar_t, true>(__mpwt, 1));

		_M_init_facet(new (&money_get_w) money_get<wchar_t>(1));
		_M_init_facet(new (&money_put_w) money_put<wchar_t>(1));

		typedef __timepunct_cache<wchar_t> time_cache_w;
		time_cache_w *__tpw = new (&timepunct_cache_w) time_cache_w(2);
		_M_init_facet(new (&timepunct_w) __timepunct<wchar_t>(__tpw, 1));

		_M_init_facet(new (&time_get_w) time_get<wchar_t>(1));
		_M_init_facet(new (&time_put_w) time_put<wchar_t>(1));
		_M_init_facet(new (&messages_w) std::messages<wchar_t>(1));
#endif

#if _GLIBCXX_NUM_UNICODE_FACETS != 0
		_M_init_facet(new (&codecvt_c16) codecvt<char16_t, char, mbstate_t>(1));
		_M_init_facet(new (&codecvt_c32) codecvt<char32_t, char, mbstate_t>(1));

#ifdef _GLIBCXX_USE_CHAR8_T
		_M_init_facet(new (&codecvt_c16_c8) codecvt<char16_t, char8_t, mbstate_t>(1));
		_M_init_facet(new (&codecvt_c32_c8) codecvt<char32_t, char8_t, mbstate_t>(1));
#endif

#endif

#ifdef _GLIBCXX_LONG_DOUBLE_ALT128_COMPAT
		_M_init_extra_ldbl128(true);
#endif

#if _GLIBCXX_USE_DUAL_ABI
		facet *extra[] = {__npc, __mpcf, __mpct
#ifdef _GLIBCXX_USE_WCHAR_T
						  ,
						  __npw, __mpwf, __mpwt
#endif
		};

		// This call must be after creating all facets, as it sets caches.
		_M_init_extra(extra);
#endif

		// This locale is safe to pre-cache, after all the facets have
		// been created and installed.
		_M_caches[numpunct<char>::id._M_id()] = __npc;
		_M_caches[moneypunct<char, false>::id._M_id()] = __mpcf;
		_M_caches[moneypunct<char, true>::id._M_id()] = __mpct;
		_M_caches[__timepunct<char>::id._M_id()] = __tpc;
#ifdef _GLIBCXX_USE_WCHAR_T
		_M_caches[numpunct<wchar_t>::id._M_id()] = __npw;
		_M_caches[moneypunct<wchar_t, false>::id._M_id()] = __mpwf;
		_M_caches[moneypunct<wchar_t, true>::id._M_id()] = __mpwt;
		_M_caches[__timepunct<wchar_t>::id._M_id()] = __tpw;
#endif
	}

	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace
#endif