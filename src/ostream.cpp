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

#define __UCLIBCXX_COMPILE_OSTREAM__ 1

#include <ostream>

namespace std{
	

#ifdef __UCLIBCXX_EXPAND_OSTREAM_CHAR__
	
	template ostream::~basic_ostream();

	template ostream & ostream::flush();

	template ostream & ostream::operator<<(bool n);
	template ostream & ostream::operator<<(short int n);
	template ostream & ostream::operator<<(unsigned short int n);
	template ostream & ostream::operator<<(int n);
	template ostream & ostream::operator<<(unsigned int n);
	template ostream & ostream::operator<<(long n);
	template ostream & ostream::operator<<(unsigned long n);
	template ostream & ostream::operator<<(float f);
	template ostream & ostream::operator<<(double f);
	template ostream & ostream::operator<<(long double f);
	template ostream & ostream::operator<<(void* p);
	template ostream & ostream::operator<<(basic_streambuf<char, char_traits<char> >* sb);

//	template ostream::sentry::sentry(ostream & os);
//	template ostream::sentry::~sentry();

	template ostream & endl(ostream & os);
	template ostream & flush(ostream & os);
	template ostream & operator<<(ostream & out, char c);
	template ostream & operator<<(ostream & out, const char* c);
	template ostream & operator<<(ostream & out, unsigned char c);
	template ostream & operator<<(ostream & out, const unsigned char* c);

#endif


}
