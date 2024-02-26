#ifdef ARDUINO_ARCH_SAM
#include "locale"
#include "yvals.h"
_MRTIMP2_PURE std::locale::_Impl *__CLRCALL_PURE_OR_CDECL _Init(bool _Do_incref, std::locale::_Impl *&global_locale)
{ // setup global and "C" locales
	using namespace std;
	locale::_Impl *ptr = nullptr;

	_BEGIN_LOCK(_LOCK_LOCALE) // prevent double initialization

	ptr = _Getgloballocale();

	if (ptr == nullptr)
	{ // create new locales
		_Setgloballocale(ptr = locale::_Impl::_New_Impl());
		ptr->_Catmask = all; // set current locale to "C"
		ptr->_Name = "C";

		// set classic to match
		ptr->_Incref();
		::new (&classic_locale) locale{ptr};
#if defined(_M_CEE_PURE)
		locale::_Impl::_Clocptr = ptr;
#else // ^^^ defined(_M_CEE_PURE) / !defined(_M_CEE_PURE) vvv
		const auto mem = reinterpret_cast<volatile intptr_t *>(&locale::_Impl::_Clocptr);
		const auto as_bytes = reinterpret_cast<intptr_t>(ptr);
		_Compiler_or_memory_barrier();
#ifdef _WIN64
		__iso_volatile_store64(mem, as_bytes);
#else  // ^^^ 64-bit / 32-bit vvv
		__iso_volatile_store32(mem, as_bytes);
#endif // ^^^ 32-bit ^^^
#endif // ^^^ !defined(_M_CEE_PURE) ^^^
	}

	if (_Do_incref)
	{
		ptr->_Incref();
	}

	_END_LOCK()

	return ptr;
}
namespace std
{
	// construct/copy/destroy:
	locale::locale() : _M_impl(_Init(true, _S_global)) {}
	locale::locale(const locale &other)
	{
		_M_impl = other._M_impl;
		return;
	}
	locale::~locale()
	{
		return;
	}
	size_t locale::id::_M_id() const throw()
	{
		return _M_index;
	}
	void __throw_bad_cast(void) {}
	locale::id ctype<char>::id;
	locale::id ctype<wchar_t>::id;
	void ctype<char>::_M_widen_init() const {}
}
#endif