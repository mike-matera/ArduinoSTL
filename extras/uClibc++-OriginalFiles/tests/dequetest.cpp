#include <deque>
#include <iostream>
#include "testframework.h"

void test_const(const std::deque<double> d);

bool canSwapUnary(){
	std::deque<int> a, b;

	a.push_back(1);
	a.push_back(3);
	a.push_back(5);
	a.push_back(7);
	a.push_back(9);
	b.push_back(2);
	b.push_back(4);
	b.push_back(6);
	b.push_back(8);

	a.swap(b);

	for(int i = 0; i < 5; ++i){
		if(b[i] != ((2 * i) + 1) ){
			return false;
		}
	}

	for(int i = 0; i < 4; ++i){
		if(a[i] != (2 * (i + 1)) ){
			return false;
		}
	}

	return true;
}

bool canSwapBinary(){
	std::deque<int> a, b;

	a.push_back(1);
	a.push_back(3);
	a.push_back(5);
	a.push_back(7);
	a.push_back(9);
	b.push_back(2);
	b.push_back(4);
	b.push_back(6);
	b.push_back(8);

	std::swap(a, b);

	for(int i = 0; i < 5; ++i){
		if(b[i] != ((2 * i) + 1) ){
			return false;
		}
	}

	for(int i = 0; i < 4; ++i){
		if(a[i] != (2 * (i + 1)) ){
			return false;
		}
	}

	return true;
}

bool canCompareConstNonConstIter() {
	std::deque<long> d;
	d.push_back(5);
	d.push_back(6);
	d.push_back(7);
	std::deque<long>::const_iterator i = d.begin();
	std::deque<long>::iterator j = d.begin();
	std::deque<long>::iterator k = d.end();

	if (i == i && i == j && j == i && j == j) {
		// Do nothing
	} else {
		return false;
	}

	if (i != i || i != j || j != i || j != j) {
		return false;
	}

	return true;
}

int main(){
	std::deque<double> test;
	std::deque<double>::iterator i,j;
	unsigned int k;

	std::cout << "deque test start" << std::endl;

	TestFramework::init();

	i = test.begin();

	std::cout << "\nTest of push_back():\n";
	std::cout << "The following two lines should be identical.\n";

	test.push_back(12);
	test.push_back(13);
	test.push_back(14);

	std::cout << "12 13 14 " << std::endl;

	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "\nTest of subscripting:\n";
	std::cout << "The following two lines should be identical\n";
	std::cout << "12 13 14 " << std::endl;
	for(k = 0; k < test.size(); ++k){
		std::cout << test[k] << " ";
	}
	std::cout << std::endl;

	std::cout << "Pushing many elements to the front:" << std::endl;
	for(k = 1; k < 24; ++k){
		std::cout << "Pushing in: " << k;
		test.push_front(static_cast<double>(k));
		std::cout << " " << test.front() << std::endl;
	}

	std::cout << "Complete list of elements:\n";
	std::cout << "The following two lines should be identical\n";
	std::cout << "23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 \n";
	for(k = 0; k < test.size(); ++k){
		std::cout << test[k] << " ";
	}
	std::cout << std::endl;


	std::cout << "\n Testing push_back():" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 2.5\n";
	test.push_back(2.5);
	for(k = 0; k < test.size(); ++k){
		std::cout << test[k] << " ";
	}
	std::cout << std::endl;

	std::cout << "\nTesting pop_front:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 2.5\n";
	test.pop_front();
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	

	std::cout << "\nTesting pop_back:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 \n";
	test.pop_back();
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;


	std::cout << "\nCopy constructor:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 \n";
	std::deque<double> test2(test);
	i = test2.begin();
	while(i !=test2.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;


	std::cout << "\nAssignement:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 \n";
	test2.clear();
	test2 = test;
	for(i = test2.begin(); i !=test2.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "\nInsert near beginning:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 25 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 \n";
	i = test.begin();
	++i;
	i++;
	test.insert(i, 25);
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "\nInsert near end:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 25 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 27 13 14 \n";
	i=test.end();
	--i;
	i--;
	test.insert(i, 27);
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "\nErase near beginning:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 27 13 14 \n";
	i = test.begin();
	++i;
	i++;
	test.erase(i);
	for(i = test.begin(); i !=test.end(); ++i){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	std::cout << "\nErase near end:" << std::endl;
	std::cout << "The following two lines should be identical\n";
	std::cout << "22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 12 13 14 \n";
	i = test.end();
	i--;
	--i;
	i--;
	i = test.erase(i);
	for(j = test.begin(); j !=test.end(); ++j){
		std::cout << *j << " ";
	}
	std::cout << std::endl;
	std::cout << "Returned iterator points to: " << *i << " - should be 13" << std::endl;

	test.clear();
	test.push_back(12);
	test.push_back(13);
	test.push_back(14);
	test.push_back(7);
	test.push_back(25);
	test.push_back(0);
	test_const(test);
	
	TestFramework::AssertReturns<bool>(canSwapUnary, true);
	TestFramework::AssertReturns<bool>(canSwapBinary, true);
	TestFramework::AssertReturns<bool>(canCompareConstNonConstIter, true);

	TestFramework::results();

	return 0;
}

void test_const(const std::deque<double> d){
	std::cout << "Test of const_iterator" << std::endl;
	std::cout << "The following two lines should be identical:" << std::endl;
	std::deque<double>::const_iterator i = d.begin();
	while(i!=d.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;
	std::cout << "12 13 14 7 25 0 " << std::endl;
}
