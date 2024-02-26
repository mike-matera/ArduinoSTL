#ifndef ARDUINO_ARCH_AVR
#include <locale>
#include <ext/concurrence.h>
namespace std
{
	// 69
	//  These are no longer exported.
	locale::_Impl *locale::_S_classic;
	locale::_Impl *locale::_S_global;
	// 73
	// 84
	// This is used to initialize global and classic locales, and
	// assumes that the _Impl objects are constructed correctly.
	// The lack of a reference increment is intentional.
	locale::locale(_Impl *__ip) throw() : _M_impl(__ip)
	{
	}

	locale::~locale() throw()
	{
		if (_M_impl != _S_classic)
			_M_impl->_M_remove_reference();
	}
	// 96
	// 231
	locale::facet::
		~facet() {}

	// locale::_Impl
	locale::_Impl::
		~_Impl() throw()
	{
		if (_M_facets)
			for (size_t __i = 0; __i < _M_facets_size; ++__i)
				if (_M_facets[__i])
					_M_facets[__i]->_M_remove_reference();
		delete[] _M_facets;

		if (_M_caches)
			for (size_t __i = 0; __i < _M_facets_size; ++__i)
				if (_M_caches[__i])
					_M_caches[__i]->_M_remove_reference();
		delete[] _M_caches;

		if (_M_names)
			for (size_t __i = 0; __i < _S_categories_size; ++__i)
				delete[] _M_names[__i];
		delete[] _M_names;
	}
	// 256
	// 472
	// locale::id
	// Definitions for static const data members of locale::id
	_Atomic_word locale::id::_S_refcount; // init'd to 0 by linker
										  // 476
	//   501
	size_t
	locale::id::_M_id() const throw()
	{
		if (!_M_index)
		{
			// XXX GLIBCXX_ABI Deprecated
#ifdef _GLIBCXX_LONG_DOUBLE_COMPAT
			if (locale::id *f = find_ldbl_sync_facet(this))
			{
				const size_t sync_id = f->_M_id();
				_M_index = 1 + sync_id;
				return sync_id;
			}
#endif

#ifdef __GTHREADS
			if (!__gnu_cxx::__is_single_threaded())
			{
				if (__atomic_always_lock_free(sizeof(_M_index), &_M_index))
				{
					const _Atomic_word next = 1 + __gnu_cxx::__exchange_and_add(&_S_refcount, 1);
					size_t expected = 0;
					__atomic_compare_exchange_n(&_M_index, &expected, next,
												/* weak = */ false,
												/* success = */ __ATOMIC_ACQ_REL,
												/* failure = */ __ATOMIC_ACQUIRE);
				}
				else
				{
					static __gnu_cxx::__mutex m;
					__gnu_cxx::__scoped_lock l(m);
					if (!_M_index)
						_M_index = ++_S_refcount;
				}
			}
			else
#endif
				_M_index = ++_S_refcount; // single-threaded case
		}
		return _M_index - 1;
	}
	// 544
}
#endif