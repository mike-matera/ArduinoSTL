/*
 * The purpose of theses tests is to test strange combinations of code which doesn't
 * properly belong in a unit test.  For example, does pushing an object into a vector
 * contained in a map work properly?  That doesn't really belong in either the map
 * or the vector tests.  So we put it here until we find some place better to put things.
 */


#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "testframework.h"

bool canInsertIntoVectorInMap() {
	std::map<std::string, std::vector<void *> > test;

	std::vector<void *> tempvec;

	tempvec.clear();
	tempvec.push_back((void *)1);
	tempvec.push_back((void *)2);
	test["2e"] = tempvec;

	tempvec.clear();
	tempvec.push_back((void *)1);
	test["1e"] = tempvec;

	tempvec.clear();
	test["0e"] = tempvec;

	if( test["0e"].size() != 0 ){
		return false;
	}
	if( test["1e"].size() != 1 ){
		return false;
	}
	if( test["2e"].size() != 2 ){
		return false;
	}

	test["2e"].push_back((void *)7);
	if( test["2e"].size() != 3 ){
		return false;
	}


	return true;
}


int main() {

	std::cout << "Begining combo tests" << std::endl;

        TestFramework::init();

        TestFramework::AssertReturns<bool>(canInsertIntoVectorInMap, true);

        TestFramework::results();

}
