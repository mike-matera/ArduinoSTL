#include <string>
#include <iostream>



int main(){
	std::string a("Testing string constructor");
	std::string b, c;

	std::cout << "Value of a: " << a << std::endl;

	a = "This is test string a";
	b = "This is test string b";
	c = "This is test string c";

	std::cout << "Test string initial values:\n";

	std::cout << a << std::endl << b << std::endl << c << std::endl;

	a = b;
	std::cout << "a = b: " << a << std::endl;
	
	a = b + c;
	std::cout << "a = b + c: " << a << std::endl;

	a = "Test cstring" + b;
	std::cout << "a = \"Test cstring\" + b: " << a << std::endl;


	a = c + "Test cstring";
	std::cout << "a = c + \"Test cstring\": " << a << std::endl;

	if(b == c){
		std::cout << "b == c (bad)" << std::endl;
	}else{
		std::cout << "b !===c (good)" << std::endl;
	}

	if(b != c){
		std::cout << "b != c (good)" << std::endl;
	}else{
		std::cout << "b !!=c (bad)" << std::endl;
	}

	a = b;

	if(b == a){
		std::cout << "b == a (good)" << std::endl;
	}else{
		std::cout << "b !== a (bad)" << std::endl;
	}

	if(a == b){
		std::cout << "a == b (good)" << std::endl;
	}else{
		std::cout << "a !== b (bad)" << std::endl;
	}

	if(b != a){
		std::cout << "b != a (bad)" << std::endl;
	}else{
		std::cout << "b !!= a (good)" << std::endl;
	}

	if(a != b){
		std::cout << "a != b (bad)" << std::endl;
	}else{
		std::cout << "a !!= b (good)" << std::endl;
	}

	a = "Test text comparison";

	if( a == "Test text comparison"){
		std::cout << "a == \"Test text comparison\" (good)" << std::endl;
	}else{
		std::cout << "a !== \"Test text comparison\" (bad)" << std::endl;
	}

	if( "Test text comparison" == a){
		std::cout << "\"Test text comparison\" == a (good)" << std::endl;
	}else{
		std::cout << "\"Test text comparison\" !== a (bad)" << std::endl;
	}


	if(b < c){
		std::cout << "b < c (good)" << std::endl;
	}else{
		std::cout << "b !< c (bad)" << std::endl;
	}

	if(b > c){
		std::cout << "b > c (bad)" << std::endl;
	}else{
		std::cout << "b !> c (good)" << std::endl;
	}


	std::cout << "Please enter a test string:" << std::flush;
	std::cin >> a;
	std::cout << std::endl << "You entered: " << a << std::endl;

	std::cout << "Checking advanced string functions:\n";
	std::cout << "Checking substr.  The following two lines should be identical:\n";
	a="This is the base string";
	std::cout << "\"is th\"" << std::endl;
	std::cout << "\"" << a.substr(5, 5) << "\""  << std::endl;


	std::cout << "\nChecking char constructor\n";
	a = std::string(1, 'w');
	b = "w";
	std::cout << "The following two lines should be identical:\n";
	std::cout << a << std::endl << b << std::endl;

	std::cout << "\nChecking + operators\n";
	a = std::string("test");
	b = '1' + a;
	std::cout << "The following two lines should be identical\n";
	std::cout << "1test" << std::endl;
	std::cout << b << std::endl;

	a = std::string("test");
	b = a + '1';
	std::cout << "The following two lines should be identical\n";
	std::cout << "test1" << std::endl;
	std::cout << b << std::endl;

	a = std::string("test");
	b = "1" + a;
	std::cout << "The following two lines should be identical\n";
	std::cout << "1test" << std::endl;
	std::cout << b << std::endl;

	a = std::string("test");
	b = a + "1";
	std::cout << "The following two lines should be identical\n";
	std::cout << "test1" << std::endl;
	std::cout << b << std::endl;


	std::cout << "\nChecking operator[]()\n";
	std::cout << "The following two lines should be identical\n";
	a = "abcdefg";
	std::cout << "abcdefg\n";
	std::cout << a[0] << a[1] << a[2] << a[3] << a[4] << a[5] << a[6] << std::endl;


	std::cout << "\nChecking erase()\n";
	std::cout << "The following two lines should ber identical\n";
	a = "this should be empty";
	a.erase();
	std::cout << "String value: '" << a << "'" << std::endl;
	std::cout << "String value: ''" << std::endl;


	std::cout << "\nChecking find on string \"" ;
	a = "This is the string we are searching through";
	std::cout << a << "\"\n";

	std::cout << "Position of \"the\": ";
	b = "the";
	std::cout << a.find(b) << " - should be 8\n";

	std::cout << "Position of \'g\': ";
	std::cout << a.find('g') << " - should be 17\n";

	std::cout << "Position of \"search\": ";
	std::cout << a.find("search") << " - should be 26\n";

	std::cout << "Position of \"through\": ";
	std::cout << a.find("through") << " - should be 36\n";


	std::cout << "Position of \"is\" starting at character 3: ";
	std::cout << a.find("is", 3) << " - should be 5\n";

	std::cout << "Position of \"q\": ";
	std::cout << a.find("q") << " - should be " << a.npos << std::endl;
	std::cout << "Making sure return value can be casted - ";
	if( (long)a.find("q") >= 0){
		std::cout << "error\n";
	}else{
		if((long)a.find("q") < 0){
			std::cout << "OK\n";
		}else{
			std::cout << "error\n";
		}
	}
	std::cout << std::endl;


	std::cout << "\nChecking rfind on string \"";
	a = "This is the string we are searching through";
	std::cout << a << "\"\n";

	std::cout << "Position of \"the\": ";
	b = "the";
	std::cout << a.rfind(b) << " = should be 8\n";

	std::cout << "Position of \'g\': ";
	std::cout << a.rfind('g') << " - should be 41\n";

	std::cout << "Position of \"search\": ";
	std::cout << a.rfind("search") << " - should be 26\n";

	std::cout << "Position of \"is\" starting at character 3: ";
	std::cout << a.rfind("is", 3) << " - should be 2\n";

	std::cout << "Position of \"q\": ";
	std::cout << a.rfind("q") << " - should be " << a.npos << std::endl;

	std::cout << "Position of \"This\": ";
	std::cout << a.rfind("This") << " - should be 0\n";


	std::cout << "\nChecking find_first_of on string \"";
	a = "This is the string we are searching through";
	std::cout << a << "\"\n";

	std::cout << "Position of \"the\": ";
	b = "the";
	std::cout << a.find_first_of(b) << " = should be 1\n";

	std::cout << "Position of \'g\': ";
	std::cout << a.find_first_of('g') << " - should be 17\n";

	std::cout << "Position of \"search\": ";
	std::cout << a.find_first_of("search") << " - should be 1\n";

	std::cout << "Position of \"is\" starting at character 4: ";
	std::cout << a.find_first_of("is", 5) << " - should be 5\n";

	std::cout << "Position of \"q\": ";
	std::cout << a.find_first_of("q") << " - should be " << a.npos << std::endl;

	std::cout << "Position of \"This\": ";
	std::cout << a.find_first_of("This") << " - should be 0\n";



	std::cout << "\nChecking find_last_of on string \"";
	a = "This is the string we are searching through";
	std::cout << a << "\"\n";

	std::cout << "Position of \"the\": ";
	b = "the";
	std::cout << a.find_last_of(b) << " = should be 42\n";

	std::cout << "Position of \'g\': ";
	std::cout << a.find_last_of('g') << " - should be 41\n";

	std::cout << "Position of \"search\": ";
	std::cout << a.find_last_of("search") << " - should be 42\n";

	std::cout << "Position of \"is\" starting at character 4: ";
	std::cout << a.find_last_of("is", 4) << " - should be 3\n";

	std::cout << "Position of \"q\": ";
	std::cout << a.find_last_of("q") << " - should be " << a.npos << std::endl;

	std::cout << "Position of \"This\": ";
	std::cout << a.find_last_of("This") << " - should be 42\n";


	std::cout << "\nChecking find_first_not_of on string \"";
	a = "This is the string we are searching through";
	std::cout << a << "\"\n";

	std::cout << "Position of \"the\": ";
	b = "the";
	std::cout << a.find_first_not_of(b) << " = should be 0\n";

	std::cout << "Position of \'g\': ";
	std::cout << a.find_first_not_of('g') << " - should be 0\n";

	std::cout << "Position of \"search\": ";
	std::cout << a.find_first_not_of("search") << " - should be 0\n";

	std::cout << "Position of \"is\" starting at character 5: ";
	std::cout << a.find_first_not_of("is", 7) << " - should be 7\n";

	std::cout << "Position of \"q\": ";
	std::cout << a.find_first_not_of("q") << " - should be 0" << std::endl;

	std::cout << "Position of \"This\": ";
	std::cout << a.find_first_not_of("This") << " - should be 4\n";

	return 0;
}

