#include <map>
#include <iostream>


int main(){
	std::map<std::string, double> test;
	std::map<std::string, double>::iterator i, j;

	std::cout << "Start of map test" << std::endl;

	std::cout << "Adding a few elements..." << std::endl;


	std::pair<std::string, double> a;
	std::pair<std::string, double> b;
	std::pair<std::map<std::string, double>::iterator, bool> c;

	test["b"] = 2;
	test["k"] = 11;
	test["c"] = 3;
	test["a"] = 1;


	std::cout << "Elements: " << std::endl;
	std::cout << "test[\"b\"] = " << test["b"] << std::endl;
	std::cout << "test[\"a\"] = " << test["a"] << std::endl;
	std::cout << "test[\"k\"] = " << test["k"] << std::endl;


	std::cout << "Reasigning the value of a" << std::endl;
	test["a"] = 65;
	std::cout << "test[\"a\"] = " << test["a"] << std::endl;

	std::cout << "All of the contents of test:" << std::endl;

	i = test.begin();
	std::cout << "First element: " << (*i).first << ": " << (*i).second << std::endl;
	std::cout << "First element: " << i->first << ": " << i->second << std::endl;
	j = test.end();
	while(i != test.end() ){
		std::cout << i->first << ": " << i->second << std::endl;
		++i;
		--i;
		++i;
		i--;
		i++;
	}

	std::cout << "Number of elements: " << test.size() << std::endl;
	std::cout << "Container empty? " << test.empty() << std::endl;
	std::cout << "Max size: " << test.max_size() << std::endl;

	std::pair<std::string, double> q;
	q.first = "Inserted value";
	q.second = 1.0;


	std::cout << "Finding element \"c\"" << std::endl;
	j = test.find("c");
	if(j == test.end()){
		std::cout << "Not found (bad)\n";
	}else{
		std::cout << "Found value for c: " << j->second << std::endl;
	}

	std::cout << "Count of elements with key \"c\": " << test.count("c") << std::endl;


	std::cout << "Inserting element g: " << std::endl;
	a.first = "g";
	a.second = 6;
	c = test.insert(a);
	std::cout << "Value inserted? " << c.second << std::endl;
	std::cout << "Key: " << c.first->first << ", value: " << c.first->second << std::endl;

	i = test.begin();
	while(i != test.end() ){
		std::cout << i->first << ": " << i->second << std::endl;
		++i;
	}



	return 0;
}


