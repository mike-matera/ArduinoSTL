#include <ostream>

namespace std{
	

#ifdef EXPAND_OSTREAM_FOR_CHAR

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

#endif


template<> basic_ostream<char,char_traits<char> >& operator<<(basic_ostream<char,char_traits<char> >& out, const char* c){
	basic_ostream<char, char_traits<char> >::sentry s(out);
	out.write(c, char_traits<char>::length(c));
	return out;
}


};
