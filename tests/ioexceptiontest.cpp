#include <sstream>
#include <iostream>
#include <exception>
#include <cstring>
#include "testframework.h"

bool found_no_exception(){
	std::stringstream s("http://myurl.com");
	char buffer[10];

	s.get(buffer, 8);

	if(0 == strncmp("http://", buffer, 8)){
		return true;
	}

	return false;
}

void no_found_throws(){
	std::stringstream s("http");
	char buffer[10];

	s.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);

	s.get(buffer, 8);

	return;
}

int main(){
	std::cout << "Begining ioexception test" << std::endl;

	TestFramework::init();

	TestFramework::AssertReturns<bool>(found_no_exception, true);
	TestFramework::AssertThrows<std::ios_base::failure>(no_found_throws);

	TestFramework::results();

	return 0;
}
