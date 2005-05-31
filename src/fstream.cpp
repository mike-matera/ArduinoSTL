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

#define __UCLIBCXX_COMPILE_FSTREAM__ 1

#include <fstream>

namespace std{

#ifdef __UCLIBCXX_EXPAND_FSTREAM_CHAR__

#ifdef __UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template filebuf::basic_filebuf();
	template filebuf::~basic_filebuf();

#endif //__UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template filebuf::int_type filebuf::pbackfail(filebuf::int_type c);
	template filebuf * filebuf::open(const char* s, ios_base::openmode mode);
	template filebuf * filebuf::close();
	template filebuf::int_type filebuf::overflow(filebuf::int_type);
	template filebuf::int_type filebuf::underflow ();
	template streamsize filebuf::xsputn(const char* s, streamsize n);

	template basic_streambuf<char, char_traits<char> >*
		filebuf::setbuf(char * s, streamsize n);


#ifdef __UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__

	template basic_ofstream<char, char_traits<char> >::basic_ofstream();
	template basic_ofstream<char, char_traits<char> >::basic_ofstream(const char* s, ios_base::openmode mode);
	template basic_ofstream<char, char_traits<char> >::~basic_ofstream();

	template basic_ifstream<char, char_traits<char> >::basic_ifstream();
	template basic_ifstream<char, char_traits<char> >::basic_ifstream(const char* s, ios_base::openmode mode);
	template basic_ifstream<char, char_traits<char> >::~basic_ifstream();

#endif //__UCLIBCXX_EXPAND_CONSTRUCTORS_DESTRUCTORS__


#endif


}
