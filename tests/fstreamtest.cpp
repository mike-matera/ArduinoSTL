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
	return 0;
}

