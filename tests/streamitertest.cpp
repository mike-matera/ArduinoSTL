#include <iostream>
#include <cstdio>
#include <iterator>


int main(){
	char buffer [100];
	int i = 0;
	std::istream_iterator<char> s(std::cin);
	
	std::cin.unsetf(std::ios::skipws);

	while(*s != '\n' && i < 100){
		buffer[i++] = *s++;
	}
	buffer[i] = '\0';

	std::cout << "Read: " << buffer << std::endl;

	return 0;
}
