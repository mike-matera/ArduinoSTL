#include <vector>
#include <string>
#include <iostream>

int main(){
	std::vector<char, std::allocator<char> > ctest;
	std::string stest;
	ctest.push_back('t');

	std::vector<unsigned int> test;
	std::vector<unsigned int> test1;
	unsigned int temp;
	std::vector<unsigned int>::iterator i,j;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);

	std::cout << "Element 0: " << test[0] << std::endl;
	std::cout << "Element 1: " << test[1] << std::endl;
	std::cout << "Element 2: " << test[2] << std::endl;
	std::cout << "Element 3: " << test[3] << std::endl;
	std::cout << "Element 4: " << test[4] << std::endl;

	test.pop_back();

	std::cout << "Testing at(int)\n";
	std::cout << "Element 0: " << test.at(0) << std::endl;
	std::cout << "Element 1: " << test.at(1) << std::endl;
	std::cout << "Element 2: " << test.at(2) << std::endl;
	std::cout << "Element 3: " << test.at(3) << std::endl;
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator insert\n";
	i = test.begin();
	++i;
	++i;
	i = test.insert(i, 12);
	std::cout << "Return value points to: " << *i << ", should be 12\n";
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator multi-insert\n";
	i = test.begin();
	++i;
	temp = 23;
	test.insert(i, 3, temp);
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}


	std::cout << "Testing iterator erase\n";
	i = test.begin();
	++i;
	++i;
	test.erase(i);
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator multierase\n";
	i = test.begin();
	j = test.begin();
	++i;
	++i;
	j+=4;
	test.erase(i, j);
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}

	std::cout << "Testing iterator range insert\n";
	test1.clear();
	test1.insert(test1.begin(), test.begin(), test.end());
	std::cout << "The following should be the same as the above:\n";
	for(i=test.begin(); i!=test.end(); i++){
		std::cout << "Element: " << *i << std::endl;
	}




	return 0;
}
