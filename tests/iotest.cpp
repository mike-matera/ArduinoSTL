#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <istream>

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
	std::cout << "Current position in stream: " << cur << std::endl;
	s_r.seekg(0, std::ios::end);
	end = s_r.tellg();
	s_r.seekg(cur);
	std::cout << "Remaining bytes: " << end-cur << std::endl;

	std::cout << "Test of reading istream into a function: " << std::endl;
	s_r >> myIstreamTestFunction;
	std::cout << "Test of reading ios into a function: " << std::endl;
	s_r >> myIosTestFunction;

	return 0;
}
