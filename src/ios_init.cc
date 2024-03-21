#include "istream"
#include "ostream"
#include "serstream"
#include "bits/c++config.h"
#include <Arduino.h>
#ifndef ARDUINO_ARCH_AVR
namespace __gnu_internal _GLIBCXX_VISIBILITY(hidden)
{
	using namespace __gnu_cxx;

	// Extern declarations for global objects in src/c++98/globals.cc.
	std::serialbuf serial_buf_cout_sync(Serial);
	std::serialbuf serial_buf_cin_sync(Serial);
	std::serialbuf serial_buf_cerr_sync(Serial);

#ifdef _GLIBCXX_USE_WCHAR_T
	std::wserialbuf serial_buf_wcout_sync(Serial);
	std::wserialbuf serial_buf_wcin_sync(Serial);
	std::wserialbuf serial_buf_wcerr_sync(Serial);
#endif
} // namespace __gnu_internal
#endif
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
#ifndef ARDUINO_ARCH_AVR
	using namespace __gnu_internal;
#endif
#ifdef ARDUINO_ARCH_SAM
	istream cin(&serial_buf_cin_sync);
	ostream cout(&serial_buf_cout_sync);
	ostream cerr(&serial_buf_cerr_sync);
#ifdef _GLIBCXX_USE_WCHAR_T
	wistream wcin(&serial_buf_wcin_sync);
	wostream wcout(&serial_buf_wcout_sync);
	wostream wcerr(&serial_buf_wcerr_sync);
#endif
#else
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
#endif
	ios_base::Init::Init()
	{
#ifndef ARDUINO_ARCH_AVR
		if (__gnu_cxx::__exchange_and_add_dispatch(&_S_refcount, 1) == 0)
		{
			// Standard streams default to synced with "C" operations.
			_S_synced_with_stdio = true;
#endif
#ifdef ARDUINO_ARCH_ESP32
			// The standard streams are constructed once only and never
			// destroyed.
			new (&cout) ostream(&serial_buf_cout_sync);
			new (&cin) istream(&serial_buf_cin_sync);
			new (&cerr) ostream(&serial_buf_cerr_sync);
			new (&clog) ostream(&serial_buf_cerr_sync);
#endif
			cin.tie(&cout);
#ifndef ARDUINO_ARCH_AVR
			cerr.setf(ios_base::unitbuf);
			// _GLIBCXX_RESOLVE_LIB_DEFECTS
			// 455. cerr::tie() and wcerr::tie() are overspecified.
			cerr.tie(&cout);
#endif

#ifdef _GLIBCXX_USE_WCHAR_T
#ifdef ARDUINO_ARCH_ESP32
			new (&wcout) wostream(&serial_buf_wcout_sync);
			new (&wcin) wistream(&serial_buf_wcin_sync);
			new (&wcerr) wostream(&serial_buf_wcerr_sync);
			new (&wclog) wostream(&serial_buf_wcerr_sync);
#endif
			wcin.tie(&wcout);
#ifndef ARDUINO_ARCH_AVR
			wcerr.setf(ios_base::unitbuf);
			wcerr.tie(&wcout);
#endif
#endif
#ifndef ARDUINO_ARCH_AVR
			// NB: Have to set refcount above one, so that standard
			// streams are not re-initialized with uses of ios_base::Init
			// besides <iostream> static object, ie just using <ios> with
			// ios_base::Init objects.
			__gnu_cxx::__atomic_add_dispatch(&_S_refcount, 1);
		}
#endif
	}

	ios_base::Init::~Init()
	{
#ifndef ARDUINO_ARCH_AVR
		// Be race-detector-friendly.  For more info see bits/c++config.
		_GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&_S_refcount);
		if (__gnu_cxx::__exchange_and_add_dispatch(&_S_refcount, -1) == 2)
		{
			_GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&_S_refcount);
			// Catch any exceptions thrown by basic_ostream::flush()
			__try
			{
#endif
				// Flush standard output streams as required by 27.4.2.1.6
				cout.flush();
#ifndef ARDUINO_ARCH_AVR
				cerr.flush();
#endif
#ifdef ARDUINO_ARCH_ESP32
				clog.flush();
#endif
#ifdef _GLIBCXX_USE_WCHAR_T
				wcout.flush();
#ifndef ARDUINO_ARCH_AVR
				wcerr.flush();
#endif
#ifdef ARDUINO_ARCH_ESP32
				wclog.flush();
#endif
#endif
#ifndef ARDUINO_ARCH_AVR
			}
			__catch(...)
			{
			}
		}
#endif
	}
}