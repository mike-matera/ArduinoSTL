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

namespace std{

const char_traits<char>::char_type* char_traits<char>::find(const char_type* s, int n, const char_type& a){
	for(int i=0; i < n; i++){
		if(eq(s[i], a)){
			return (s+i);
		}
	}
	return 0;
}



#ifdef __USE_WCHAR

const char_traits<wchar_t>::char_type* char_traits<wchar_t>::find(const char_type* s, int n, const char_type& a){
	for(int i=0; i < n; i++){
		if(eq(s[i], a)){
			return (s+i);
		}
	}
	return 0;
}

#endif

}
