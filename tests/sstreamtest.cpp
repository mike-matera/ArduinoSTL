#include <iostream>
#include <sstream>

int main(){
	std::cout << "Begining sstream test\n";
	
	std::stringstream a;
	float f;
	int i;
	std::string s;
	char c;

	a << "Starting testing ";
	a << 2 ;
	a << " " << 2.0;

	std::cout << a.str() << std::endl;

	a.str("abcdefg");
	a.get(c);
	std::cout << "Character getted: " << c << std::endl;
	a.get(c);
	std::cout << "Character getted: " << c << std::endl;

	s = a.str();
	std::cout << "input buffer: " << s << std::endl;
	std::cout << "Character 0: " << s[0] << ", character 1: " << s[1] << std::endl;



	a.str("2.35 5 Test");

	a >> f >> i >> s;

	std::cout << "f (should be 2.35): " << f << std::endl;
	std::cout << "i (should be 5): " << i << std::endl;
	std::cout << "s (should be Test): " << s << std::endl;

	std::cout << "Buffer: " << a.str() << std::endl;


	return 0;
}
