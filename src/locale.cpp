#ifdef ARDUINO_ARCH_SAM
#include "locale"
namespace std
{
	// construct/copy/destroy:
	locale::locale()
	{
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