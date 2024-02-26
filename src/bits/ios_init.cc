#ifndef ARDUINO_ARCH_AVR
#include "istream"
#include "ostream"
#include "serstream"
#include <Arduino.h>
namespace __gnu_internal _GLIBCXX_VISIBILITY(hidden)
{
	using namespace __gnu_cxx;

	// Extern declarations for global objects in src/c++98/globals.cc.
	std::serialbuf buf_cout_sync(Serial);
	std::serialbuf buf_cin_sync(Serial);
	std::serialbuf buf_cerr_sync(Serial);

#ifdef _GLIBCXX_USE_WCHAR_T
	std::wserialbuf buf_wcout_sync(Serial);
	std::wserialbuf buf_wcin_sync(Serial);
	std::wserialbuf buf_wcerr_sync(Serial);
#endif
} // namespace __gnu_internal

namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION

	using namespace __gnu_internal;

	extern istream cin;
	extern ostream cout;
	extern ostream cerr;
	extern ostream clog;

#ifdef _GLIBCXX_USE_WCHAR_T
	extern wistream wcin;
	extern wostream wcout;
	extern wostream wcerr;
	extern wostream wclog;
#endif

	ios_base::Init::Init()
	{
		if (__gnu_cxx::__exchange_and_add_dispatch(&_S_refcount, 1) == 0)
		{
			// Standard streams default to synced with "C" operations.
			_S_synced_with_stdio = true;

			// The standard streams are constructed once only and never
			// destroyed.
			new (&cout) ostream(&buf_cout_sync);
			new (&cin) istream(&buf_cin_sync);
			new (&cerr) ostream(&buf_cerr_sync);
			new (&clog) ostream(&buf_cerr_sync);
			cin.tie(&cout);
			cerr.setf(ios_base::unitbuf);
			// _GLIBCXX_RESOLVE_LIB_DEFECTS
			// 455. cerr::tie() and wcerr::tie() are overspecified.
			cerr.tie(&cout);

#ifdef _GLIBCXX_USE_WCHAR_T

			new (&wcout) wostream(&buf_wcout_sync);
			new (&wcin) wistream(&buf_wcin_sync);
			new (&wcerr) wostream(&buf_wcerr_sync);
			new (&wclog) wostream(&buf_wcerr_sync);
			wcin.tie(&wcout);
			wcerr.setf(ios_base::unitbuf);
			wcerr.tie(&wcout);
#endif

			// NB: Have to set refcount above one, so that standard
			// streams are not re-initialized with uses of ios_base::Init
			// besides <iostream> static object, ie just using <ios> with
			// ios_base::Init objects.
			__gnu_cxx::__atomic_add_dispatch(&_S_refcount, 1);
		}
	}

	ios_base::Init::~Init()
	{
		// Be race-detector-friendly.  For more info see bits/c++config.
		_GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_S_refcount);
		if (__gnu_cxx::__exchange_and_add_dispatch(&_S_refcount, -1) == 2)
		{
			_GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_S_refcount);
			// Catch any exceptions thrown by basic_ostream::flush()
			__try
			{
				// Flush standard output streams as required by 27.4.2.1.6
				cout.flush();
				cerr.flush();
				clog.flush();

#ifdef _GLIBCXX_USE_WCHAR_T
				wcout.flush();
				wcerr.flush();
				wclog.flush();
#endif
			}
			__catch(...)
			{
			}
		}
	}
}
#endif