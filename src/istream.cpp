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

#include <istream>


namespace std{

#ifdef __EXPAND_ISTREAM_FOR_CHAR

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(short& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, short>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(unsigned short& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, unsigned short>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(int& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, int>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(unsigned int& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, unsigned int>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(long int& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, long int>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(unsigned long int& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, unsigned long int>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(float& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, float>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(double& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, double>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(long double& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, long double>::readin(*this, n);
		return *this;
	}

	template <> basic_istream<char, char_traits<char> >&
		basic_istream<char, char_traits<char> >::operator>>(void *& n)
	{
		sentry(*this);
		__istream_readin<char_traits<char>, char, void*>::readin(*this, n);
		return *this;
	}


#endif


};

