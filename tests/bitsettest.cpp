#include <bitset>
#include <iostream>
#include <sstream>


int main(){
	std::bitset<10> a;
	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >() << std::endl;

	a.flip();
	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >() << std::endl;

	a.flip(1);
	a.flip(3);
	a.flip(4);
	a.flip(5);
	a.flip(7);
	a.flip(8);
	a.flip(9);
	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >() << std::endl;

	a.flip();
	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >() << std::endl;

	std::bitset<10> b(std::string("10110111011110"), 4);
	std::cout << b.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 0111011110" << std::endl;


	std::bitset<10> c(std::string("10110111011110"), 2, 8);
	std::cout << c.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 0011011101" << std::endl;


	a.reset();

	a[2] = true;
	a[3] = ~a[5];
	a[8].flip();
	a[5] = a[6];
	
	a.flip(6);
	a.flip();

	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 1010110011" << std::endl;

	b = a << 3;
	std::cout << b.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 0110011000" << std::endl;


	c = a >> 2;
	std::cout << c.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 0010101100" << std::endl;

	a = b & c;
	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 0010001000" << std::endl;


	a = b | c;
	std::cout << a.to_string<char, std::char_traits<char>, std::allocator<char> >();
	std::cout << " should read : 0110111100" << std::endl;

	a = b ^ c;
	std::cout << a;
	std::cout << " should read : 0100110100" << std::endl;


	std::stringstream s;
	s.str("1100100100");

	s >> a;
	std::cout << a << " should read : 1100100100" << std::endl;


	return 0;
}
