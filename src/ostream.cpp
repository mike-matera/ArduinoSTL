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
	
	typedef basic_ostream<char, char_traits<char> > char_ostream;

	template char_ostream::~basic_ostream();

	template char_ostream & char_ostream::operator<<(bool n);
	template char_ostream & char_ostream::operator<<(short int n);
	template char_ostream & char_ostream::operator<<(unsigned short int n);
	template char_ostream & char_ostream::operator<<(int n);
	template char_ostream & char_ostream::operator<<(unsigned int n);
	template char_ostream & char_ostream::operator<<(long n);
	template char_ostream & char_ostream::operator<<(unsigned long n);
	template char_ostream & char_ostream::operator<<(float f);
	template char_ostream & char_ostream::operator<<(double f);
	template char_ostream & char_ostream::operator<<(long double f);
	template char_ostream & char_ostream::operator<<(void* p);
	template char_ostream &	char_ostream::operator<<(basic_streambuf<char, char_traits<char> >* sb);


	template char_ostream & endl(char_ostream & os);
	template char_ostream & flush(char_ostream & os);
	template char_ostream & operator<<(char_ostream & out, char c);
	template char_ostream & operator<<(char_ostream & out, const char* c);

#endif

}
