#include <fstream>

int main()
{
	std::ofstream outFile("newout.txt", std::ios::out);
	outFile <<  "output data from fstreamtest" ;
}

