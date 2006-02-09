#include <map>
#include <iostream>


int main(){
	std::multimap<std::string, double> test;
	std::multimap<std::string, double>::iterator i, j;
	std::multimap<std::string, double>::const_iterator k;

	std::cout << "Start of multimap test" << std::endl;

	std::cout << "Adding a few elements..." << std::endl;


	std::pair<std::string, double> a;
	std::pair<std::string, double> b;
	std::pair<std::map<std::string, double>::iterator, bool> c;

	a.first="a";
	a.second=1;
	test.insert(a);

	a.first="c";
	a.second=3;
	test.insert(a);

	a.first="c";
	a.second=3.1;
	test.insert(a);

	a.first="d";
	a.second=4;
	test.insert(a);

	a.first="g";
	a.second=7;
	test.insert(a);

	i = test.begin();
	while(i != test.end()){
		std::cout << "Element " << i->first << ": " << i->second << std::endl;
		++i;
	}

	std::cout << "Checking locations\n";

	i = test.find("c");
	std::cout << "Element c: " << i->first << ": " << i->second << std::endl;

	i = test.find("d");
	std::cout << "Element d: " << i->first << ": " << i->second << std::endl;


	a.first="c";
	a.second=3.14;
	i=test.begin();
	++i;
	++i;

	test.insert(i, a);

	std::cout << "Testing positioned inserting\n";

	i = test.begin();
	while(i != test.end()){
		std::cout << "Element " << i->first << ": " << i->second << std::endl;
		++i;
	}

	std::cout << "Count of \"c\" elements: " << test.count("c") << std::endl;
	std::cout << "Count of \"d\" elements: " << test.count("d") << std::endl;
	std::cout << "Count of \"q\" elements: " << test.count("q") << std::endl;


	i = test.lower_bound("c");
	std::cout << "lower bound for c: " << i->first << ": " << i->second << std::endl;

	std::cout << "Erasing all \"c\" elements\n";
	test.erase("c");

	i = test.begin();
	while(i != test.end()){
		std::cout << "Element " << i->first << ": " << i->second << std::endl;
		++i;
	}

	std::cout << "Inserting \"c\": 3.7\n";

	a.first = "c";
	a.second=3.7;
	test.insert(a);

	i = test.begin();
	while(i != test.end()){
		std::cout << "Element " << i->first << ": " << i->second << std::endl;
		++i;
	}


	
	return 0;
}


