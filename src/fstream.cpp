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

	template basic_filebuf<char, char_traits<char> >::~basic_filebuf();

	template basic_filebuf<char, char_traits<char> >::int_type basic_filebuf<char, char_traits<char> >::
		pbackfail(basic_filebuf<char, char_traits<char> >::int_type c);

	template basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::
		open(const char* s, ios_base::openmode mode);

	template basic_ofstream<char, char_traits<char> >::~basic_ofstream();

	template basic_filebuf<char, char_traits<char> >::int_type basic_filebuf<char, char_traits<char> >::
		overflow (basic_filebuf<char, char_traits<char> >::int_type);

	template basic_filebuf<char, char_traits<char> >::int_type
		basic_filebuf<char, char_traits<char> >::underflow ();

	template basic_streambuf<char, char_traits<char> >*
		basic_filebuf<char, char_traits<char> >::
		setbuf(char * s, streamsize n);

	template streamsize basic_filebuf<char, char_traits<char> >::xsputn(const char* s, streamsize n);


#endif


}
