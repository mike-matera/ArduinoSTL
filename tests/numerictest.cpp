#include <vector>
#include <iostream>
#include <numeric>

int main(){

	std::vector<double> src;
	std::vector<double> dest;
	std::vector<double>::iterator i;

	src.clear();
	dest.clear();

	src.push_back(17);
	src.push_back(19);
	src.push_back(20);
	src.push_back(20);
	src.push_back(17);

	dest.push_back(0);
	dest.push_back(0);
	dest.push_back(0);
	dest.push_back(0);
	dest.push_back(0);


	std::adjacent_difference<std::vector<double>::iterator, std::vector<double>::iterator>
		(src.begin(), src.end(), dest.begin());

	std::cout << "Results from adjacent_difference\n";
	i = dest.begin();
	while(i != dest.end()){
		std::cout << "Element: " << *i << std::endl;
		++i;
	}

	src.clear();
	src.push_back(0);
	src.push_back(0);
	src.push_back(0);
	src.push_back(0);
	src.push_back(0);
	
	std::partial_sum<std::vector<double>::iterator, std::vector<double>::iterator>
		(dest.begin(), dest.end(), src.begin());

	std::cout << "Results from partial_sum\n";
	i = src.begin();
	while(i != src.end()){
		std::cout << "Element: " << *i << std::endl;
		++i;
	}



	std::cout << "End of numeric test" << std::endl;

	return 0;
}

