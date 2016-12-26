#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include "testframework.h"


template <class T> class less_than : public std::unary_function <T, bool>{
	T arg;
public:
	explicit less_than(const T & x) : arg(x) {  }
	bool operator()(const T& x) const { return x < arg; }
};


std::vector<int> giveVec(int a, int b, int c, int d){
	std::vector<int> retval;
	retval.push_back(a);
	retval.push_back(b);
	retval.push_back(c);
	retval.push_back(d);
	return retval;
}



bool canSortList(){
	int s[6] = {12, 26, 33, 64, 85, 93};

	std::vector<int> a;
	a.push_back(12);
	a.push_back(33);
	a.push_back(85);
	a.push_back(26);
	a.push_back(64);
	a.push_back(93);

	std::sort<std::vector<int>::iterator>(a.begin(), a.end());

	for(int i = 0; i < 6; ++i){
		if(a[i] != s[i]){
			return false;
		}
	}

	if(a.size() != 6){
		return false;
	}

	return true;
}

bool canSearchList(){
	std::vector<int> a;
	a.push_back(12);
	a.push_back(33);
	a.push_back(85);
	a.push_back(26);
	a.push_back(64);
	a.push_back(93);

	std::sort<std::vector<int>::iterator>(a.begin(), a.end());


	if(1 != std::binary_search(a.begin(), a.end(), 33)){
		return false;
	}
	if(0 != std::binary_search(a.begin(), a.end(), 99)){
		return false;
	}
	if(0 != std::binary_search(a.begin(), a.end(), 1)){
		return false;
	}
	if(0 != std::binary_search(a.begin(), a.end(), 28)){
		return false;
	}
	if(0 != std::binary_search(a.begin(), a.end(), -26)){
		return false;
	}
	if(1 != std::binary_search(a.begin(), a.end(), 12)){
		return false;
	}
	return true;
}

bool canLowerBound(){
	std::vector<int> a, b;
	a.push_back(12);
	a.push_back(26);
	a.push_back(33);
	a.push_back(64);
	a.push_back(85);
	a.push_back(93);

	b.clear();
	b.push_back(2);
	b.push_back(3);
	b.push_back(3);
	b.push_back(3);
	b.push_back(4);
	b.push_back(7);
	b.push_back(8);
	b.push_back(9);

	if(33 != *(std::lower_bound(a.begin(), a.end(), 33))){
		return false;
	}
	if(3 != *(std::lower_bound(b.begin(), b.end(), 3))){
		return false;
	}
	if(2 != *(std::lower_bound(b.begin(), b.end(), 1))){
		return false;
	}

	return true;
}

bool canUpperBound(){
	std::vector<int> a, b;
	a.push_back(12);
	a.push_back(26);
	a.push_back(33);
	a.push_back(64);
	a.push_back(85);
	a.push_back(93);

	if(33 != *(std::upper_bound(a.begin(), a.end(), 27))){
		return false;
	}

	b.push_back(2);
	b.push_back(3);
	b.push_back(3);
	b.push_back(3);
	b.push_back(4);
	b.push_back(7);
	b.push_back(8);
	b.push_back(9);

	int v[4] = {4, 7, 8, 9};

	std::vector<int>::iterator i;
	i = std::upper_bound(b.begin(), b.end(), 3);
	for(int j = 0; j < 4; ++j){
		if(*i != v[j]){
			return false;
		}
		++i;
	}

	return true;
}

bool canIterateFromLowerBound(){
	std::vector<int> b;
	std::vector<int>::iterator i;

	int v[7] = {3, 3, 3, 4, 7, 8, 9};

	b.push_back(2);
	b.push_back(3);
	b.push_back(3);
	b.push_back(3);
	b.push_back(4);
	b.push_back(7);
	b.push_back(8);
	b.push_back(9);

	i = std::lower_bound(b.begin(), b.end(), 3);
	for(int j = 0; j < 7; ++j){
		if(v[j] != *i){
			return false;
		}
		++i;
	}

	if(b.end() != i){
		return false;
	}

	return true;
}

bool testStablePartition(){
	std::vector<int> b;
	std::vector<int>::iterator i, j;
	
	b.push_back(12);
	b.push_back(33);
	b.push_back(11);
	b.push_back(93);
	b.push_back(23);
	b.push_back(12);
	b.push_back(39);
	b.push_back(53);
	b.push_back(72);
	b.push_back(20);

	std::multiset<int> testValues;
	std::multiset<int>::iterator k;
	

	testValues.clear();
	testValues.insert(33);
	testValues.insert(23);
	testValues.insert(39);
	testValues.insert(53);
	testValues.insert(72);
	testValues.insert(20);
	testValues.insert(93);

	i = std::stable_partition(b.begin(), b.end(), less_than<double>(20) );
	j = i;
	while(j != b.end()){
		k = testValues.find(*j);
		if(k == testValues.end()){
			//Value in partion which shouldn't be there
			return false;
		}
		testValues.erase(k);
		++j;
	}

	//At this point, testValues should be empty
	if(0 != testValues.size()){
		return false;
	}

	testValues.insert(12);
	testValues.insert(11);
	testValues.insert(12);

	j = b.begin();
	while(j != i){
		k = testValues.find(*j);
		if(k == testValues.end()){
			//Value in partion which shouldn't be there
			return false;
		}
		testValues.erase(k);
		++j;
	}

	//At this point, testValues should be empty
	if(0 != testValues.size()){
		return false;
	}

	return true;
}

bool testPushHeap(){
	std::vector<int> a;

	a.push_back(12);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	if(1 != a.size() || a[0] != 12){
		return false;
	}

	a.clear();
	a.push_back(12);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(7);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(27);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(22);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(93);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(36);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(55);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(5);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(68);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());

	std::multiset<int> testValues;
	std::multiset<int>::iterator k;
	testValues.insert(93);
	testValues.insert(68);
	testValues.insert(55);
	testValues.insert(36);
	testValues.insert(27);
	testValues.insert(22);
	testValues.insert(12);
	testValues.insert(7);
	testValues.insert(5);

	std::vector<int>::iterator i;

	//BUG - we need to make sure that all elements are in the vector after push_heap, even though
	//they aren't guaranteed to be sorted.  Do multiset thing again?

	if(a[0] != 93){
		printf("Largest value isn't at the start of the heap\n");
		return false;
	}

	i = a.begin();
	while(i != a.end()){
		k = testValues.find(*i);
		if(k == testValues.end()){
			printf("Could not find epexted value %i\n", *i);
			return false;
		}
		testValues.erase(k);
		++i;
	}
	if(a.size() != 9){
		printf("a not 9 elements long\n");
		return false;
	}
	if(testValues.size() != 0){
		printf("Testvalues not empty\n");
		return false;
	}

	return true;
}

bool testSortHeap(){
	std::vector<int> a;
	int v[9] = {5, 7, 12, 22, 27, 36, 55, 68, 93};

	a.push_back(12);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(7);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(27);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(22);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(93);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(36);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(55);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(5);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());
	a.push_back(68);
	std::push_heap<std::vector<int>::iterator>(a.begin(), a.end());

	std::sort_heap<std::vector<int>::iterator>(a.begin(), a.end() );

	for(int j = 0; j < 9; ++j){
		if(v[j] != a[j]){
			printf("Key %i should be %i but is %i\n", j, v[j], a[j]);
			return false;
		}
	}

	return true;
}

bool testPartialSort(){
	std::vector<int> a;
	std::vector<int>::iterator i;
	int v[5] = {11, 12, 12, 20, 23};

	a.push_back(12);
	a.push_back(32);
	a.push_back(11);
	a.push_back(93);
	a.push_back(12);
	a.push_back(23);
	a.push_back(38);
	a.push_back(53);
	a.push_back(72);
	a.push_back(20);

	i = a.begin();
	i+=4;

	std::partial_sort<std::vector<int>::iterator>(a.begin(), i, a.end());

	for(int j = 0; j < 4; ++j){
		if(v[j] != a[j]){
			printf("Key %i should be %i but is %i\n", j, v[j], a[j]);
			return false;
		}
	}

	return true;
}

bool testSort() {
	struct _my_comp {
		inline bool operator()(const int &a, const int &b) const {
			return a > b;
		}
	};
	std::vector<int> a;
	std::vector<int>::iterator i;

	a.push_back(5);
	a.push_back(2);
	a.push_back(4);
	a.push_back(3);
	a.push_back(1);
	a.push_back(0);

	i = a.begin();

	std::sort<std::vector<int>::iterator>(a.begin(), a.end(), _my_comp());

	for (int j = 0; j < 6; ++j) {
		if (a[j] != 5 - j) {
			printf("Key %i should be %i but is %i\n", j, 5-j, a[j]);
			return false;
		}
	}

	return true;
}

bool testInplaceMerge(){
	std::vector<int> a;
	std::vector<int>::iterator i;

	a.push_back(11);
	a.push_back(12);
	a.push_back(33);
	a.push_back(72);

	a.push_back(12);
	a.push_back(19);
	a.push_back(23);
	a.push_back(38);
	a.push_back(53);
	a.push_back(93);

	i = a.begin();
	i = i + 4;

	std::inplace_merge<std::vector<int>::iterator>(a.begin(), i, a.end());

	int v[10] = {11, 12, 12, 19, 23, 33, 38, 53, 72, 93};

	for(int j = 0; j < 5; ++j){
		if(v[j] != a[j]){
			printf("Key %i should be %i but is %i\n", j, v[j], a[j]);
			return false;
		}
	}

	return true;
}

bool testNextPermutation(){
	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);

	std::multiset<std::vector<int> > testValues;
	std::multiset<std::vector<int> >::iterator k;
	std::vector<int> vec;


	//OK - populate the multiset with the possible permutations
	testValues.insert(giveVec(1, 2, 3, 4));
	testValues.insert(giveVec(1, 2, 4, 3));
	testValues.insert(giveVec(1, 3, 2, 4));
	testValues.insert(giveVec(1, 3, 4, 2));
	testValues.insert(giveVec(1, 4, 2, 3));
	testValues.insert(giveVec(1, 4, 3, 2));
	testValues.insert(giveVec(2, 1, 3, 4));
	testValues.insert(giveVec(2, 1, 4, 3));
	testValues.insert(giveVec(2, 3, 1, 4));
	testValues.insert(giveVec(2, 3, 4, 1));
	testValues.insert(giveVec(2, 4, 1, 3));
	testValues.insert(giveVec(2, 4, 3, 1));
	testValues.insert(giveVec(3, 1, 2, 4));
	testValues.insert(giveVec(3, 1, 4, 2));
	testValues.insert(giveVec(3, 2, 1, 4));
	testValues.insert(giveVec(3, 2, 4, 1));
	testValues.insert(giveVec(3, 4, 1, 2));
	testValues.insert(giveVec(3, 4, 2, 1));
	testValues.insert(giveVec(4, 1, 2, 3));
	testValues.insert(giveVec(4, 1, 3, 2));
	testValues.insert(giveVec(4, 2, 1, 3));
	testValues.insert(giveVec(4, 2, 3, 1));
	testValues.insert(giveVec(4, 3, 1, 2));
	testValues.insert(giveVec(4, 3, 2, 1));

	for(int x = 0; x < 24; ++x){
		std::next_permutation(a.begin(), a.end());
		vec.clear();
		vec.push_back(a[0]);
		vec.push_back(a[1]);
		vec.push_back(a[2]);
		vec.push_back(a[3]);

		k = testValues.find(vec);
		if(k == testValues.end()){
			//Value in partion which shouldn't be there
			printf("Expected to find value %i, %i, %i, %i, but didn't\n", a[0], a[1], a[2], a[3]);
			return false;
		}
		testValues.erase(k);
	}

	if( testValues.size() != 0 ){
		printf("Left over values in testValues\n");
		return false;
	}

	return true;
}

bool testPrevPermutation(){
	std::vector<int> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);

	std::multiset<std::vector<int> > testValues;
	std::multiset<std::vector<int> >::iterator k;
	std::vector<int> vec;


	//OK - populate the multiset with the possible permutations
	testValues.insert(giveVec(1, 2, 3, 4));
	testValues.insert(giveVec(1, 2, 4, 3));
	testValues.insert(giveVec(1, 3, 2, 4));
	testValues.insert(giveVec(1, 3, 4, 2));
	testValues.insert(giveVec(1, 4, 2, 3));
	testValues.insert(giveVec(1, 4, 3, 2));
	testValues.insert(giveVec(2, 1, 3, 4));
	testValues.insert(giveVec(2, 1, 4, 3));
	testValues.insert(giveVec(2, 3, 1, 4));
	testValues.insert(giveVec(2, 3, 4, 1));
	testValues.insert(giveVec(2, 4, 1, 3));
	testValues.insert(giveVec(2, 4, 3, 1));
	testValues.insert(giveVec(3, 1, 2, 4));
	testValues.insert(giveVec(3, 1, 4, 2));
	testValues.insert(giveVec(3, 2, 1, 4));
	testValues.insert(giveVec(3, 2, 4, 1));
	testValues.insert(giveVec(3, 4, 1, 2));
	testValues.insert(giveVec(3, 4, 2, 1));
	testValues.insert(giveVec(4, 1, 2, 3));
	testValues.insert(giveVec(4, 1, 3, 2));
	testValues.insert(giveVec(4, 2, 1, 3));
	testValues.insert(giveVec(4, 2, 3, 1));
	testValues.insert(giveVec(4, 3, 1, 2));
	testValues.insert(giveVec(4, 3, 2, 1));

	for(int x = 0; x < 24; ++x){
		std::prev_permutation(a.begin(), a.end());
		vec.clear();
		vec.push_back(a[0]);
		vec.push_back(a[1]);
		vec.push_back(a[2]);
		vec.push_back(a[3]);

		k = testValues.find(vec);
		if(k == testValues.end()){
			//Value in partion which shouldn't be there
			printf("Expected to find value %i, %i, %i, %i, but didn't\n", a[0], a[1], a[2], a[3]);
			return false;
		}
		testValues.erase(k);
	}

	if( testValues.size() != 0 ){
		printf("Left over values in testValues\n");
		return false;
	}

	return true;
}

bool checkMinDefault(){
	return std::min(3, 5) == 3;
}

bool checkMinLess(){
	return std::min(3, 5, std::less<int>()) == 3;
}

int main(){
	std::cout << "Beginning algorithm test" << std::endl;

        TestFramework::init();

        TestFramework::AssertReturns<bool>(canSortList, true);
        TestFramework::AssertReturns<bool>(canSearchList, true);
        TestFramework::AssertReturns<bool>(canUpperBound, true);
        TestFramework::AssertReturns<bool>(canLowerBound, true);
        TestFramework::AssertReturns<bool>(canIterateFromLowerBound, true);
        TestFramework::AssertReturns<bool>(testStablePartition, true);
        TestFramework::AssertReturns<bool>(testPushHeap, true);
        TestFramework::AssertReturns<bool>(testSortHeap, true);
        TestFramework::AssertReturns<bool>(testPartialSort, true);
        TestFramework::AssertReturns<bool>(testSort, true);
        TestFramework::AssertReturns<bool>(testInplaceMerge, true);
        TestFramework::AssertReturns<bool>(testNextPermutation, true);
        TestFramework::AssertReturns<bool>(testPrevPermutation, true);
	TestFramework::AssertReturns<bool>(checkMinDefault, true);
	TestFramework::AssertReturns<bool>(checkMinLess, true);

        TestFramework::results();

	return 0;
}
