#include <istream>


namespace std{

#ifdef EXPAND_ISTREAM_FOR_CHAR

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

