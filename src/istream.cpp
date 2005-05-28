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

#define __UCLIBCXX_COMPILE_ISTREAM__ 1

#include <istream>


namespace std{

#ifdef __UCLIBCXX_EXPAND_ISTREAM_CHAR__

	template <> string _readToken<char, char_traits<char> >(istream & stream)
	{
		string temp;
		char_traits<char>::int_type c;
		int exitnow = 0;
		while(exitnow == 0){
			c = stream.get();
			if(c != char_traits<char>::eof() && isspace(c) == false){
				temp.append(1, c);
			}else{
				stream.putback(c);
				exitnow = 1;
			}
		}
		return temp;
        }

	template istream::int_type istream::get();
	template istream & istream::get(char &c);


	template istream & istream::operator>>(bool &n);
	template istream & istream::operator>>(short &n);
	template istream & istream::operator>>(unsigned short &n);
	template istream & istream::operator>>(int &n);
	template istream & istream::operator>>(unsigned int &n);
	template istream & istream::operator>>(long unsigned &n);
	template istream & istream::operator>>(long int &n);
	template istream & istream::operator>>(void *& p);
	template istream & operator>>(istream & is, char & c);


#ifdef __UCLIBCXX_HAS_FLOATS__
	template istream & istream::operator>>(float &f);
	template istream & istream::operator>>(double &f);
	template istream & istream::operator>>(long double &f);
#endif



#endif


}

