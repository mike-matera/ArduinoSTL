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

#define __UCLIBCXX_COMPILE_STRING__ 1

#include <basic_definitions>
#include <char_traits>
#include <string>
#include <string_iostream>
#include <string.h>
#include <ostream>

namespace std{

#ifdef __UCLIBCXX_EXPAND_STRING_CHAR__

	typedef basic_string<char, char_traits<char> , allocator<char> > char_string;

	template char_string::basic_string(const char* s, const allocator<char>& al);
	template char_string::basic_string(const basic_string& str, size_type pos, size_type n, const allocator<char>& al);
	template char_string& char_string::operator=(const char_string & str);
	template char_string char_string::substr(size_type pos, size_type n) const;
	template char_string::size_type char_string::find(const char_string & str, size_type pos) const;
	template char_string operator+(const char_string & lhs, const char* rhs);
	template char_string operator+(const char* lhs, const char_string & rhs);
	template char_string operator+(const char_string & lhs,	const char_string & rhs);


//Functions dependent upon OSTREAM
#ifdef __UCLIBCXX_EXPAND_OSTREAM_CHAR__

template basic_ostream<char, char_traits<char> >&
	operator<<(basic_ostream<char, char_traits<char> >& os,	const char_string & str);

#endif


//Functions dependent upon ISTREAM
#ifdef __UCLIBCXX_EXPAND_ISTREAM_CHAR__

template basic_istream<char, char_traits<char> >& operator>>(
	basic_istream<char,char_traits<char> >& is, char_string & str);


#endif


#endif

}
