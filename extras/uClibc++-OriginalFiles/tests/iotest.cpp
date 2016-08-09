#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <istream>

#include "testframework.h"

//using namespace std;

std::basic_istream<char, std::char_traits<char> > &
	myIstreamTestFunction(std::basic_istream<char,std::char_traits<char> >& stream)
{
	std::cout << "Number of characters most recently read in: " << stream.gcount() << std::endl;
	return stream;
}

std::basic_ios<char, std::char_traits<char> > &
	myIosTestFunction(std::basic_ios<char,std::char_traits<char> >& stream)
{
	std::cout << "Good status: " << stream.good() << std::endl;
	return stream;
}

bool canSeeIosBaseProperties() {
	std::ios_base::openmode a;
	a = std::ios_base::app;
	a = std::ios_base::in;
	a = std::ios_base::out;

	return true;
}

void testFieldWidth() {
	std::streamsize ioswidth_backup = std::cout.width();
	std::ios_base::fmtflags iosflags_backup = std::cout.flags();

	std::cout.width(10);

	std::cout.setf(std::ios_base::right);
	std::cout << 5;
	std::cout << 5.1;
	std::cout << "5.2";
	std::cout << std::endl;

	std::cout.setf(std::ios_base::left);
	std::cout << 6;
	std::cout << 6.1;
	std::cout << "6.2";
	std::cout << std::endl;

	std::cout.setf(std::ios_base::internal);
	std::cout << 7;
	std::cout << 7.1;
	std::cout << "7.2";
	std::cout << std::endl;

	std::cout.unsetf(std::ios_base::internal | std::ios_base::left | std::ios_base::right);
	std::cout << 8;
	std::cout << 8.1;
	std::cout << "8.2";
	std::cout << std::endl;

	// Restore flags from backup	
	std::cout.flags(iosflags_backup);
	std::cout.width(ioswidth_backup);
}

int main(){
//	double q;
//	std::cin >> q;

	std::basic_string<char> temp("Test string");

	std::cout << "Hello, World!\n";

	std::cout << "Test string: " << temp << std::endl;
	std::cout.setf(std::ios_base::boolalpha);
	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout << "This is the number 200:" << 200.1 << std::endl;
	std::cout << "This is the number 200:" << (short)200 << std::endl;
	std::cout << "True: " << true << std::endl;
	std::cout << "True: " << (bool)1 << std::endl;
	std::cout << "not True: " << std::noboolalpha << "true" << "(the string), " << true << std::boolalpha << std::endl;
	std::cout << "boolalpha set: " << (bool)(std::cout.flags() & std::ios_base::boolalpha) << std::endl;
	std::cout << "not True: " << 1U << std::endl;
	std::cout << "not True: " << -1L << std::endl;
	std::cout << "not True: " << (1?1:0) << std::endl;
	//std::cout << "not True: " << __builtin_constant_p(-1) << std::endl;
	std::cout << "False: " << false << std::endl;
	std::cout << "False: " << (bool)0 << std::endl;
	std::cout << "not False: " << 0 << std::endl;
	//std::cout << "not False: " << '\0' << std::endl;
	//std::cout << "not False: " << L'\0' << std::endl;
	std::cout << "not False: " << -0 << std::endl;
	std::cout << "not False: " << -0U << std::endl;
	std::cout << "not False: " << -0L << std::endl;
	
	float i = 0;
	long double j = 0;

	void * p = (void *)12345678;

	std::cout << "Pointer: " << p << std::endl;
	std::cout << "Please enter two floats:" << std::flush;
	std::cin >> i >> j;

	std::cout << "You entered: " << i << " " << j << std::endl;


	std::cout << "Checking ostream_iterator\n";
	std::ostream_iterator<double> a(std::cout, " ");

	std::cout << std::endl << "Checking length of remaining input" << std::flush << std::endl;
	std::istream::pos_type cur;
	std::istream::pos_type end;

	std::istream & s_r = std::cin;

	cur = s_r.tellg();
	std::streampos o_pos(cur);

	std::cout << "Current position in stream: " << cur << std::endl;
	s_r.seekg(0, std::ios::end);
	end = s_r.tellg();
	std::streampos n_pos(end);
	s_r.seekg(cur);
	std::cout << "Remaining bytes: " << end-cur << std::endl;

	std::cout << "fpos o_pos == n_pos ? " <<
		(o_pos == n_pos ? "true" : "false") << std::endl;
	std::cout << "fpos !(o_pos == n_pos) ? " <<
		(!(o_pos == n_pos) ? "true" : "false") << std::endl;
	std::cout << "fpos o_pos != n_pos ? " <<
		(o_pos != n_pos ? "true" : "false") << std::endl;

	std::cout << "Test of reading istream into a function: " << std::endl;
	s_r >> myIstreamTestFunction;
	std::cout << "Test of reading ios into a function: " << std::endl;
	s_r >> myIosTestFunction;

	testFieldWidth();

	TestFramework::AssertReturns<bool>(canSeeIosBaseProperties, true);

	TestFramework::results();


	return 0;
}
