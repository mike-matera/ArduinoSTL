/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "ios_base.h"
#include "../serstream"
#include "iostream"
#include <Arduino.h>
namespace std
{
#ifdef __UCLIBCXX_SUPPORT_CDIR__
#ifdef ARDUINO_ARCH_AVR
	_UCXXLOCAL int ios_base::Init::init_cnt = 0; // Needed to ensure the static value is created
#define CSL_IOS_Count init_cnt
#else
#ifdef ARDUINO_ARCH_SAM
	_Atomic_word ios_base::Init::_S_refcount = 0;
#endif
#define CSL_IOS_Count _S_refcount
#endif
// Create buffers first
#ifdef __UCLIBCXX_SUPPORT_COUT__
	_UCXXEXPORT serialbuf _cout_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
	_UCXXEXPORT serialbuf _cin_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
	_UCXXEXPORT filebuf _cerr_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_CLOG__
	_UCXXEXPORT filebuf _clog_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_WCOUT__
	_UCXXEXPORT wserialbuf _wcout_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCIN__
	_UCXXEXPORT wserialbuf _wcin_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCERR__
	_UCXXEXPORT wfilebuf _wcerr_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_WCLOG__
	_UCXXEXPORT wfilebuf _wclog_filebuf;
#endif
#ifndef ARDUINO_ARCH_ESP32
// Then create streams
#ifdef __UCLIBCXX_SUPPORT_COUT__
	_UCXXEXPORT ostream cout(&_cout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
	_UCXXEXPORT istream cin(&_cin_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
	_UCXXEXPORT ostream cerr(&_cerr_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CLOG__
	_UCXXEXPORT ostream clog(&_clog_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCOUT__
	_UCXXEXPORT wostream wcout(&_wcout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCIN__
	_UCXXEXPORT wistream wcin(&_wcin_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCERR__
	_UCXXEXPORT wostream wcerr(&_wcerr_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCLOG__
	_UCXXEXPORT wostream wclog(&_wclog_filebuf);
#endif
#endif
	_UCXXEXPORT ios_base::Init::Init()
	{
#ifdef ARDUINO_ARCH_SAM
		static const locale L;
		cout.imbue(L);
		cin.imbue(L);
		wcout.imbue(L);
		wcin.imbue(L);
#endif
#ifdef ARDUINO_ARCH_ESP32
		if (CSL_IOS_Count == 0)
		{ // Need to construct cout et al
#ifdef __UCLIBCXX_SUPPORT_COUT__
			cout.~basic_ostream();
			new (&cout) ostream(&_cout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
			_cerr_filebuf.fp = stderr;
			_cerr_filebuf.openedFor = ios_base::out;
			cerr.mformat |= ios_base::unitbuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_CLOG__
			_clog_filebuf.fp = stderr;
			_clog_filebuf.openedFor = ios_base::out;
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
			cin.~basic_istream();
			new (&cin) istream(&_cin_filebuf);

#ifdef __UCLIBCXX_SUPPORT_COUT__
			cin.tie(&cout);
#endif

#endif
#ifdef __UCLIBCXX_SUPPORT_WCOUT__
			wcout.~basic_ostream();
			new (&wcout) wostream(&_wcout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCERR__
			_wcerr_filebuf.fp = stderr;
			_wcerr_filebuf.openedFor = ios_base::out;
			wcerr.mformat |= ios_base::unitbuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_WCLOG__
			_wclog_filebuf.fp = stderr;
			_wclog_filebuf.openedFor = ios_base::out;
#endif
#ifdef __UCLIBCXX_SUPPORT_WCIN__
			wcin.~basic_istream();
			new (&wcin) wistream(&_wcin_filebuf);

#ifdef __UCLIBCXX_SUPPORT_WCOUT__
			wcin.tie(&wcout);
#endif
#endif
		}
#endif
		CSL_IOS_Count++;
	}
	_UCXXEXPORT ios_base::Init::~Init()
	{
		--CSL_IOS_Count;
	}
#endif
#ifdef ARDUINO_ARCH_AVR
#ifdef __UCLIBCXX_EXPAND_IOS_CHAR__

	template _UCXXEXPORT void basic_ios<char, char_traits<char>>::clear(iostate state);
	template _UCXXEXPORT void basic_ios<char, char_traits<char>>::setstate(iostate state);

#endif

	_UCXXEXPORT ios_base::fmtflags ios_base::flags(fmtflags fmtfl)
	{
		fmtflags temp = mformat;
		mformat = fmtfl;
		return temp;
	}

	_UCXXEXPORT ios_base::fmtflags ios_base::setf(fmtflags fmtfl)
	{
		return flags(flags() | fmtfl);
	}

	_UCXXEXPORT ios_base::fmtflags ios_base::setf(fmtflags fmtfl, fmtflags mask)
	{
		return flags((flags() & ~mask) | (fmtfl & mask));
	}

	_UCXXEXPORT streamsize ios_base::precision(streamsize prec)
	{
		streamsize temp = mprecision;
		mprecision = prec;
		return temp;
	}

	_UCXXEXPORT streamsize ios_base::width(streamsize wide)
	{
		streamsize temp = mwidth;
		mwidth = wide;
		return temp;
	}

	_UCXXEXPORT locale ios_base::imbue(const locale &loc)
	{
		locale retval = mLocale;
		mLocale = loc;
		return retval;
	}
#endif
#ifdef ARDUINO_ARCH_SAM
	ios_base::~ios_base() {}
	ios_base::ios_base() {}
	locale ios_base::imbue(const locale &loc)
	{
		locale retval = _M_ios_locale;
		_M_ios_locale = loc;
		return _M_ios_locale;
	}
	void ios_base::_M_init() throw() {}
#endif
}