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

#include <basic_definitions>
#include <char_traits>
#include <string>
#include <string.h>
#include <ostream>

namespace std{

#ifdef __EXPAND_BASIC_STRING_FOR_CHAR
//Pure string functions
	template<> basic_string<char,char_traits<char>, allocator<char> >::
		basic_string(const char* s, const allocator<char>& al)
		: vector<char, allocator<char> >(al)
	{
		__string_helper_functions<char, char_traits<char>, allocator<char> >::constructor(*this, s);
		
	}



//Functions dependent upon OSTREAM
#ifdef __EXPAND_OSTREAM_FOR_CHAR

template<> basic_ostream<char, char_traits<char> >& 
	operator<<(basic_ostream<char, char_traits<char> >& os,
	const basic_string<char,char_traits<char>, std::allocator<char> >& str)
{
	return os.write(str.data(), str.length());
}

#endif


//Functions dependent upon ISTREAM
#ifdef __EXPAND_ISTREAM_FOR_CHAR

template<> basic_istream<char, char_traits<char> >& operator>>(
	basic_istream<char,char_traits<char> >& is,
	basic_string<char, char_traits<char>,
	allocator<char> >& str)
{
	return __string_helper_functions<char, char_traits<char>, allocator<char> >::op_right_right(is, str);
	
}


#endif


#endif

};
