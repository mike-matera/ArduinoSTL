#include <list>
#include <iostream>
#include <vector>
#include <string>


int main(){
	std::string test;
	std::list<double> temp(5, 12.0);
	std::list<double>::iterator i, j;

	test = "Begining of list test";

	std::cout << test << std::endl;
	for(i = temp.begin(); i!=temp.end(); i++){
		std::cout << "i: " << *i << std::endl;
	}



	std::cout << "List insert test\n";
	i = temp.begin();
	i++;
	++i;
	i=temp.insert(i, 52.8);
	temp.insert(i,52.4);
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}


	std::cout << "List multi-insert test\n";
	i = temp.end();
	--i;
	i--;
	temp.insert(i, 3, 33.3);
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}

	std::cout << "First element in list:" << temp.front() << std::endl;


	std::cout << "Erasing 2nd element in list" << std::endl;
	i = temp.begin();
	++i;
	i = temp.erase(i);
	std::cout << "First element in list: " << *i << std::endl;
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}

	std::cout << "Erasing last 3 elements\n";
	i = temp.end();
	i--;
	i--;
	i--;
	temp.erase(i,temp.end());
	std::cout << "First element in list: " << *i << std::endl;
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}


	return 0;
}
