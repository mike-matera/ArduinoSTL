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

#include <ostream>

namespace std{
	

#ifdef __EXPAND_OSTREAM_FOR_CHAR

template <> basic_ostream<char,char_traits<char> > & basic_ostream<char, char_traits<char> >::operator<<(bool n){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, bool>::printout(*this, n);
	return *this;
}

template <> basic_ostream<char, char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(short int n){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, int>::printout(*this, n);
	return *this;
}


template <> basic_ostream<char,char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(unsigned short int n){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, unsigned int>::printout(*this, n);
	return *this;
}

template <> basic_ostream<char, char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(int n){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, int>::printout(*this, n);
	return *this;
}


template <> basic_ostream<char,char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(unsigned int n){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, unsigned int>::printout(*this, n);
	return *this;
}

template <> basic_ostream<char, char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(long n){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, long int>::printout(*this, n);
	return *this;
}


template <> basic_ostream<char, char_traits<char> >&
                basic_ostream<char, char_traits<char> >::operator<<(unsigned long n)
{
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, unsigned long int>::printout(*this, n);
	return *this;
}

template <> basic_ostream<char,char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(float f){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, double>::printout(*this, f);
	return *this;
}

template <> basic_ostream<char,char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(double f){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, double>::printout(*this, f);
	return *this;
}

template <> basic_ostream<char, char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(long double f){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, long double>::printout(*this, f);
	return *this;
}

template <> basic_ostream<char, char_traits<char> >& basic_ostream<char, char_traits<char> >::operator<<(void* p){
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, void *>::printout(*this, p);
	return *this;
}

template <> basic_ostream<char, char_traits<char> >&
	basic_ostream<char, char_traits<char> >::operator<<(basic_streambuf<char, char_traits<char> >* sb)
{
	sentry s(*this);
	__ostream_printout<char_traits<char>, char, basic_streambuf<char, char_traits<char> > * >::printout(*this, sb);
	return *this;
}


template <> basic_ostream<char,char_traits<char> >&
	endl(basic_ostream<char,char_traits<char> >& os)
{
	os.put('\n');
	os.flush();
	return os;
}

template <> basic_ostream<char,char_traits<char> >&
	flush(basic_ostream<char,char_traits<char> >& os)
{
	os.flush();
	return os;
}


#endif


template<> basic_ostream<char,char_traits<char> >& operator<<(basic_ostream<char,char_traits<char> >& out, const char* c){
	basic_ostream<char, char_traits<char> >::sentry s(out);
	out.write(c, char_traits<char>::length(c));
	return out;
}


};
