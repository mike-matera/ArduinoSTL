#include <string>
#include <iostream>

int main(){
	std::cout << "Starting wchar test" << std::endl;
	std::wcout << "Test of wcout output" << std::endl;
	
	std::wstring test;
	test = L"This is a test of wstring";
	std::wcout << test << std::endl;





	return 0;
}
