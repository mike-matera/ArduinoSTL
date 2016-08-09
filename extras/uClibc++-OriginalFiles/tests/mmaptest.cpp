#include <map>
#include <iostream>
#include "testframework.h"

bool test_added_elements(){
	std::multimap<std::string, double> test;
	std::multimap<std::string, double>::iterator i;
	std::pair<std::string, double> a;
	
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


	if(test.count("a") != 1){
		return false;
	}
	if(test.count("c") != 2){
		return false;
	}
	if(test.count("d") != 1){
		return false;
	}
	if(test.count("g") != 1){
		return false;
	}
	if(test.count("q") != 0){
		return false;
	}

	std::map<double, double> b;
	for(i = test.lower_bound("c"); i != test.upper_bound("c"); ++i){
		b.insert(std::pair<double, double>(i->second, (*i).second));
	}
	if(b.count(3.1) != 1){
		return false;
	}
	if(b.count(3) != 1){
		return false;
	}
	if(b.size() != 2){
		return false;
	}
	return true;
}

bool test_positioned_insert(){
	std::multimap<std::string, double> test;
	std::multimap<std::string, double>::iterator i;
	std::pair<std::string, double> a;
	
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

	a.first="c";
	a.second=3.14;
	i=test.begin();
	++i;
	++i;

	test.insert(i, a);

	if(test.count("a") != 1){
		return false;
	}
	if(test.count("c") != 3){
		return false;
	}
	if(test.count("d") != 1){
		return false;
	}
	if(test.count("g") != 1){
		return false;
	}
	if(test.count("q") != 0){
		return false;
	}

	std::map<double, double> b;
	for(i = test.lower_bound("c"); i != test.upper_bound("c"); ++i){
		b.insert(std::pair<double, double>(i->second, (*i).second));
	}
	if(b.count(3.1) != 1){
		return false;
	}
	if(b.count(3) != 1){
		return false;
	}
	if(b.count(3.14) != 1){
		return false;
	}
	if(b.size() != 3){
		return false;
	}


	return true;
}


int main(){

        TestFramework::init();

        TestFramework::AssertReturns<bool>(test_added_elements, true);
        TestFramework::AssertReturns<bool>(test_positioned_insert, true);

        TestFramework::results();



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

	std::cout << "Checking locations\n";

	i = test.find("c");
	std::cout << "Element c: " << i->first << ": " << std::endl;

	i = test.find("d");
	std::cout << "Element d: " << i->first << ": " << std::endl;


	i = test.lower_bound("c");
	std::cout << "lower bound for c: " << i->first << std::endl;

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


