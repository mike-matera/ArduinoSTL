#include <deque>
#include <iostream>



int main(){
	std::deque<double> test;
	std::deque<double>::iterator i,j;
	unsigned int k;

	std::cout << "deque test start" << std::endl;

	i = test.begin();

	test.push_back(12);
	test.push_back(13);
	test.push_back(14);

	std::cout << "Deque elements:\n";
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << std::endl;
	}

	std::cout << "Deque elements by subscript:\n";
	for(k = 0; k < test.size(); ++k){
		std::cout << test[k] << std::endl;
	}


	std::cout << "Pushing many elements to the front:" << std::endl;
	for(k = 1; k < 24; ++k){
		std::cout << "Pushing in: " << k;
		test.push_front(static_cast<double>(k));
		std::cout << " " << test.front() << std::endl;
	}


	std::cout << "Deque elements:\n";
	for(k = 0; k < test.size(); ++k){
		std::cout << test[k] << std::endl;
	}

	std::cout << "Push back:" << std::endl;
	test.push_back(2.5);
	for(k = 0; k < test.size(); ++k){
		std::cout << test[k] << std::endl;
	}


	std::cout << "Pop_front:" << std::endl;
	test.pop_front();
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << std::endl;
	}
	

	std::cout << "Pop_back:" << std::endl;
	test.pop_back();
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << std::endl;
	}

	std::cout << "Copy constructor:" << std::endl;

	std::deque<double> test2(test);
	i = test2.begin();
	while(i !=test2.end()){
		std::cout << *i << std::endl;
		++i;
	}


	std::cout << "Assignement:" << std::endl;
	test2.clear();
	test2 = test;
	for(i = test2.begin(); i !=test2.end(); ++i){
		std::cout << *i << std::endl;
	}

	std::cout << "Insert near beginning:" << std::endl;
	i = test.begin();
	++i;
	i++;
	test.insert(i, 25);
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << std::endl;
	}

	std::cout << "Insert near end:" << std::endl;
	i=test.end();
	--i;
	i--;
	test.insert(i, 27);
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << std::endl;
	}

	std::cout << "Erase near begining:" << std::endl;
	i = test.begin();
	++i;
	i++;
	test.erase(i);
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << std::endl;
	}

	std::cout << "Erase near end:" << std::endl;
	i = test.end();
	i--;
	--i;
	i--;
	i = test.erase(i);
	for(j = test.begin(); j !=test.end(); ++j){
		std::cout << *j << std::endl;
	}
	std::cout << "Returned iterator points to: " << *i << std::endl;


	return 0;
}
