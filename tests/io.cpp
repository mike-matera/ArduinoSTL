#include <iostream>
#include <string>

int main(){
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

	std::cout << "Address of i: " << &i << std::endl;	
	std::cout << "Please enter two floats:" << std::flush;
	std::cin >> i >> j;

	std::cout << "You entered: " << i << " " << j << std::endl;

	return 0;
}
