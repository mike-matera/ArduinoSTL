#include <iostream>
#include <set>

int main(){
	std::cout << "Starting set test\n";
	std::set<int> a;

	if(a.empty() == false){
		std::cout << "ERROR - set should be empty\n";
	}else{
		std::cout << "OK - set is empty\n";
	}

	a.clear();

	std::pair<std::set<int>::iterator, bool> p;

	p = a.insert(57);
	p = a.insert(75);
	p = a.insert(11);
	p = a.insert(29);
	p = a.insert(128);
	p = a.insert(103);
	p = a.insert(56);

	std::cout << *(p.first) << " should read 56\n";



	std::set<int>::iterator i;

	std::cout << "Element list" << std::endl;
	i = a.begin();
	while(i != a.end() ){
		std::cout << "Element : " << *i << std::endl;
		++i;
	}

	//Deleting element 56
	i = a.find(56);
	std::cout << *i << " should read 56\n";

	a.erase(i);


	std::cout << "Element list (56 should be deleted)\n";
	i = a.begin();
	while(i != a.end() ){
		std::cout << "Element : " << *i << std::endl;
		++i;
	}


	return 0;
}
