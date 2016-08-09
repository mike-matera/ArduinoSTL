#include <string>
#include <iostream>
#include <locale.h>

int main(){
	setlocale(LC_ALL, "en_US.utf8");

	std::wcout.imbue( std::locale("en_US.utf8") );

	std::cout << "Starting wchar test" << std::endl;
	std::wcout << "Test of wcout output" << std::endl;
	
	std::wstring test;
	test = L"This is a test of wstring";
	std::wcout << test << std::endl;

	std::wcin >> test;
	std::wcout << test << std::endl;
	std::wcin >> test;
	std::wcout << test << std::endl;


	return 0;
}
