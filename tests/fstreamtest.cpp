#include <fstream>
#include <iostream>

int main()
{
	std::ofstream outFile("fstreamtest.out", std::ios::out);
	outFile <<  "output data from fstreamtest" ;
	for(unsigned char a = 0; a < 255 ; ++a){
		outFile << a;
	}
	outFile.close();

	std::ifstream inFile;
	inFile.open("fstreamtest.out", std::ios::in | std::ios::binary );
	char a;
	unsigned char b;
	for(int i = 0 ; i < 28; ++i){
		inFile >> a;
	}
	for(unsigned char c = 0; c < 255; ++c){
		inFile.get(a);
		b = a;
		if(c != b){
			std::cout << "Error reading in character #" << (int)(c);
			std::cout << ": read instead #" << (int)(b) << std::endl;
		}
	}
	inFile.close();

	outFile.open("fstreamtest2.out", std::ios::out);
	outFile.write("abcd", 4);
	outFile.put('e');
	outFile.write("fghi", 4);
	outFile.close();

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


	return 0;
}

