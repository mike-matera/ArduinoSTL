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

	template basic_string<char,char_traits<char>, allocator<char> >::basic_string(const char* s, const allocator<char>& al);

	template basic_string<char, char_traits<char>, allocator<char> >
		operator+(const basic_string<char, char_traits<char>, allocator<char> >& lhs, const char* rhs);

	template basic_string<char, char_traits<char>, allocator<char> >
		operator+(const char* lhs, const basic_string<char, char_traits<char>, allocator<char> >& rhs);

	template basic_string<char, char_traits<char>, allocator<char> >
		operator+(const basic_string<char, char_traits<char> , allocator<char> >& lhs,
			const basic_string<char, char_traits<char>, allocator<char> >& rhs);


//Functions dependent upon OSTREAM
#ifdef __UCLIBCXX_EXPAND_OSTREAM_CHAR__

template basic_ostream<char, char_traits<char> >&
	operator<<(basic_ostream<char, char_traits<char> >& os,
	const basic_string<char,char_traits<char>, std::allocator<char> >& str);

#endif


//Functions dependent upon ISTREAM
#ifdef __UCLIBCXX_EXPAND_ISTREAM_CHAR__

template basic_istream<char, char_traits<char> >& operator>>(
	basic_istream<char,char_traits<char> >& is,
	basic_string<char, char_traits<char>, allocator<char> >& str);


#endif


#endif

}
