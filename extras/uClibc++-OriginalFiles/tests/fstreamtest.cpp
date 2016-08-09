#include <fstream>
#include <iostream>

unsigned char correctValue(unsigned long int pos);
bool testIFStreamUnderflowOnUnopened();


int main()
{
	std::ofstream outFile("fstreamtest.out", std::ios::out);
	outFile <<  "output data from fstreamtest" ;
	for(unsigned char a = 0; a < 255 ; ++a){
		outFile << a;
	}
	outFile.close();
	outFile.open("fstreamtest.out", std::ios::app | std::ios::out);
	outFile.seekp(0);
	outFile << "This should be at the end";
	outFile.close();

	std::ifstream inFile;
	inFile.open("fstreamtest.out", std::ios::in | std::ios::binary );
	char a;
	unsigned char b;
	for(int i = 0 ; i < 28; ++i){
		inFile >> a;
	}
	while (!inFile.eof()){
		inFile.get(a);
		std::cout << "Read in character: " << (unsigned int)(unsigned char)a << " " << a << std::endl;
	}


	inFile.close();

	outFile.clear();
	outFile.open("fstreamtest2.out", std::ios::out);
	outFile.write("abcd", 4);
	outFile.put('e');
	outFile.write("fghi", 4);
	outFile.close();

	inFile.clear();
	inFile.open("fstreamtest2.out", std::ios::in | std::ios::binary);

	inFile >> a;
	if (a != 'a'){
		std::cout << "Error reading character a, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'b'){
		std::cout << "Error reading character b, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'c'){
		std::cout << "Error reading character c, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'd'){
		std::cout << "Error reading character d, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'e'){
		std::cout << "Error reading character e, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'f'){
		std::cout << "Error reading character f, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'g'){
		std::cout << "Error reading character g, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'h'){
		std::cout << "Error reading character h, was instead: " << a << std::endl;
	}
	inFile >> a;
	if (a != 'i'){
		std::cout << "Error reading character i, was instead: " << a << std::endl;
	}
	inFile.close();
	inFile.clear();


	std::cout << "Now reading other input file to see what wonderful goodness we can discover" << std::endl;

	inFile.open("fstreamtest.input", std::ios::in | std::ios::binary );
	if( !inFile.is_open()){
		std::cout << "Could not open fstreamtest.input" << std::endl;
		std::cout << "Are you in the correct directory?" << std::endl;
		std::cout << "This test wasn't designed to run without the uClibc++ driver behind it" << std::endl;
		return 1;
	}
	inFile.seekg(27);
	inFile.read(&a, 1);
	b = a;
	if(correctValue(27) != b){
		std::cout << "Read in invalid value.  Read in " << (int)b << ", expected " << (int)correctValue(27) << std::endl;
	}else{
		std::cout << "Character 27 read in correctly\n";
	}

	std::cout << "The following two lines should be identical\n";
	std::cout << "Current position: 28\n";
	std::cout << "Current position: " << inFile.tellg() << std::endl;

	inFile.seekg(1, std::ios::cur);
	inFile.read(&a, 1);
	b = a;
	if(correctValue(29) != b){
		std::cout << "Read in invalid value.  Read in " << (int)b << ", expected " << (int)correctValue(29) << std::endl;
	}else{
		std::cout << "Character 29 read in correctly\n";
	}

	std::cout << "The following two lines should be identical\n";
	std::cout << "Current position: 30\n";
	std::cout << "Current position: " << inFile.tellg() << std::endl;

	std::cout << "Checking input on an unopened fstream: " << std::endl;

	if( testIFStreamUnderflowOnUnopened() ){
		std::cout << "OK\n";
	}else{
		std::cout << "ERROR\n";
	}
	


	return 0;
}


unsigned char correctValue(unsigned long int pos){
	if(pos < 16){
		return 0;
	}
	return (pos - 16);

}


bool testIFStreamUnderflowOnUnopened(){
	std::ifstream test;
	if(test.get() == std::char_traits<char>::eof() ){
		return true;
	}
	return false;
}
