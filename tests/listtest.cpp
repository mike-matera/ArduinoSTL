#include <list>
#include <iostream>
#include <vector>
#include <string>


int main(){
	std::string test;
	std::list<double>temp(5, 12.0);
	std::list<double> a;
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


	std::cout << "Testing reverse\n";
	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	temp.reverse();

	std::cout << "The following two lines should be identical:\n";
	std::cout << "21.2 48.5 37.9 22.4 12.8\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;

	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 22.4 37.9 48.5 21.2\n";
	i = temp.end();
	while(i != temp.begin()){
		--i;
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "Testing splice" << std::endl;

	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	temp.splice(++temp.begin(), a);
	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 85.4 24.6 69.7 22.4 37.9 48.5 21.2\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;


	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	temp.splice(temp.begin(), a);
	std::cout << "The following two lines should be identical:\n";
	std::cout << "85.4 24.6 69.7 12.8 22.4 37.9 48.5 21.2\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;

	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	temp.splice(temp.end(), a);
	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 22.4 37.9 48.5 21.2 85.4 24.6 69.7\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;


	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	i = temp.begin();
	++i;
	++i;

	temp.splice(i, a, ++a.begin());
	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 22.4 24.6 37.9 48.5 21.2\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;


	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	temp.splice(temp.begin(), a, ++a.begin());
	std::cout << "The following two lines should be identical:\n";
	std::cout << "24.6 12.8 22.4 37.9 48.5 21.2\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;


	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	temp.splice(temp.end(), a, ++a.begin());
	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 22.4 37.9 48.5 21.2 24.6\n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;



	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);

	a.clear();
	a.push_back(85.4);
	a.push_back(24.6);
	a.push_back(69.7);

	i = temp.begin();
	++i;
	j = i;
	++j;
	++j;

	a.splice(++a.begin(), temp, i, j);
	std::cout << "The following two lines should be identical:\n";
	std::cout << "85.4 22.4 37.9 24.6 69.7\n";
	i = a.begin();
	while(i != a.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;



	std::cout << "Testing sorting\n";

	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);
	temp.push_back(85.4);
	temp.push_back(24.6);
	temp.push_back(69.7);

	temp.sort();
	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 21.2 22.4 24.6 37.9 48.5 69.7 85.4 \n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;



	std::cout << "Testing merging\n";

	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);

	a.clear();
	a.push_back(11.7);
	a.push_back(29.1);
	a.push_back(94.3);
	a.push_back(99.9);

	temp.merge(a);
	std::cout << "The following two lines should be identical:\n";
	std::cout << "11.7 12.8 22.4 29.1 37.9 48.5 94.3 99.9 \n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;

	


	std::cout << "Testing remove\n";

	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(11.7);
	temp.push_back(29.1);
	temp.push_back(37.9);
	temp.push_back(99.9);

	temp.remove(37.9);
	std::cout << "The following two lines should be identical:\n";
	std::cout << "12.8 22.4 48.5 11.7 29.7 99.9 \n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;



	std::cout << "Testing unique\n";

	temp.clear();
	temp.push_back(11.7);
	temp.push_back(12.8);
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(29.1);
	temp.push_back(37.9);
	temp.push_back(37.9);
	temp.push_back(37.9);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(99.9);

	temp.unique();
	std::cout << "The following two lines should be identical:\n";
	std::cout << "11.7 12.8 22.4 29.1 37.9 48.5 99.9 \n";
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;

	


	return 0;
}
