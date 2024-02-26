#ifndef ARDUINO_ARCH_AVR
#include "ios_base.h"
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

	// Called only by basic_ios<>::init.
	void
	ios_base::_M_init() throw()
	{
		// NB: May be called more than once
		_M_precision = 6;
		_M_width = 0;
		_M_flags = skipws | dec;
		_M_ios_locale = locale();
	}

	// 27.4.2.3  ios_base locale functions
	locale
	ios_base::imbue(const locale &__loc) throw()
	{
		locale __old = _M_ios_locale;
		_M_ios_locale = __loc;
		_M_call_callbacks(imbue_event);
		return __old;
	}
}
#endif