#include <map>
#include <iostream>
#include "testframework.h"


struct Int {
	Int(int x = 0) : val(x) { };
	int val;
};

std::ostream& operator<<(std::ostream& s, Int x)
  { return s << x.val; }


bool canForwardIterateCorrectly(){
	std::map<int, int> a;

	a[3] = 13;
	a[5] = 15;

	std::map<int, int>::iterator i;
	int count;

	for(i = a.begin(), count=0; i != a.end() && count < 20; i++, count++){
	}

	if(2 == count){
		return true;
	}
	return false;
}

bool canCompareConstNonConstIter() {
	std::map<long, double> m;
	m[5] = 2.3;
	m[6] = 3.3;
	m[7] = 3.4;
	std::map<long, double>::const_iterator i = m.begin();
	std::map<long, double>::iterator j = m.begin();
	std::map<long, double>::iterator k = m.end();

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


bool canSwapCorrectly(){
	std::map<int, int> a, b;

	a[3] = 13;
	a[5] = 15;

	b[3] = 23;
	b[9] = 27;

	std::map<int, int>::iterator i;

	i = a.find(3);
	if (i == a.end()) {
		return false;
	}
	i = a.find(9);
	if (i != a.end()) {
		return false;
	}

	i = b.find(3);
	if (i == b.end()) {
		return false;
	}

	i = b.find(5);
	if (i != b.end()) {
		return false;
	}

	a.swap(b);

	i = a.find(3);
	if (i == a.end()) {
		return false;
	}
	i = a.find(5);
	if (i != a.end()) {
		return false;
	}
	i = a.find(9);
	if (i == a.end()) {
		return false;
	}

	i = b.find(3);
	if (i == b.end()) {
		return false;
	}
	i = b.find(5);
	if (i == b.end()) {
		return false;
	}
	i = b.find(9);
	if (i != b.end()) {
		return false;
	}

	return true;
}

class my_type {
public:
	my_type() : id(count++) { }
	void test() { }

	int id;
	static int count;
};

int my_type::count = 0;


bool canSubscriptWithoutExtraObjectCreation() {
	std::map<int, my_type> mymap;
	mymap[1].test();
	mymap[1].test();

	if (my_type::count != 1) {
		return false;
	}

	return true;
}


int main(){
	std::map<std::string, double> test;
	std::map<std::string, double>::iterator i, j;
	std::map<std::string, double>::const_iterator k;

	std::map<std::string, double>::reverse_iterator ri;

	std::cout << "Start of map test" << std::endl;

	std::cout << "Checking to make sure that map::iterator can be compared" << std::endl;
	std::cout << "to map::const_iterator: ";

	i = test.begin();
	k = test.begin();
	if( i == k ){
		std::cout << "OK" << std::endl;
	}else{
		std::cout << "FAIL" << std::endl;
	}

	std::cout << "Checking to make sure that map::iterator can be compared" << std::endl;
	std::cout << "to map::const_iterator: ";

	i = test.begin();
	k = test.begin();
	if( k == i ){
		std::cout << "OK" << std::endl;
	}else{
		std::cout << "FAIL" << std::endl;
	}


	std::cout << "Adding a few elements..." << std::endl;


	std::pair<std::string, double> a;
	std::pair<std::string, double> b;
	std::pair<std::map<std::string, double>::iterator, bool> c;

	test["b"] = 2;
	test["k"] = 11;
	test["c"] = 3;
	test["a"] = 1;


	std::cout << "Elements:" << std::endl;
	std::cout << "test[\"b\"] = " << test["b"] << " - should be 2" << std::endl;
	std::cout << "test[\"a\"] = " << test["a"] << " - should be 1" << std::endl;
	std::cout << "test[\"k\"] = " << test["k"] << " - should be 11" << std::endl;


	std::cout << "Reasigning the value of a" << std::endl;
	test["a"] = 65;
	std::cout << "test[\"a\"] = " << test["a"] << " - should be 65" << std::endl;

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

	std::cout << "Elements in reverse order:\n";
	ri = test.rbegin();
	while(ri != test.rend()){
		std::cout << (*ri).first << ": " << (*ri).second << std::endl;
		++ri;
	}



	std::cout << "Number of elements: " << test.size() << std::endl;
	std::cout << "Container empty? " << test.empty() << std::endl;

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

	std::cout << "Attempting to insert same element again: ";
	a.first="g";
	a.second = 6;
	c = test.insert(a);
	if(c.second == true){
		std::cout << "inserted  - FAILED\n";
	}else{
		std::cout << "no insert - PASSED\n";
	}

	j = test.find("g");
	std::cout << "Erasing element \"g\"" << std::endl;
	test.erase(j);

	i=test.begin();
	while(i != test.end() ){
		std::cout << i->first << ": " << i->second << std::endl;
		++i;
	}

	std::cout << "Erasing element \"c\"" << std::endl;
	test.erase("c");

	i=test.begin();
	while(i != test.end() ){
		std::cout << i->first << ": " << i->second << std::endl;
		++i;
	}

	j = test.lower_bound("b");
	std::cout << "This should read 2: " << j->second << std::endl;
	j = test.lower_bound("c");
	std::cout << "This should read 11: " << j->second << std::endl;
	j = test.lower_bound("z");
	std::cout << "This should read end: " << ((j == test.end()) ? "end" : "noend") << std::endl;

	k = test.lower_bound("b");
	std::cout << "This should read 2: " << k->second << std::endl;
	k = test.lower_bound("c");
	std::cout << "This should read 11: " << k->second << std::endl;
	k = test.lower_bound("z");
	std::cout << "This should read end: " << ((k == test.end()) ? "end" : "noend") << std::endl;

	std::cout << "This should read 11: " << test.equal_range("k").first->second << std::endl;

	std::cout << "test roman numerals" << std::endl;

	typedef std::map<char, Int, std::less<char> > maptype;

	maptype map_char_myClass;
	// Store mappings between roman numerals and decimals.

	std::cout << "Inserting values now" << std::endl;

	map_char_myClass['l'] = 50;
	map_char_myClass['x'] = 20; // Deliberate mistake.
	map_char_myClass['v'] = 5;
	map_char_myClass['i'] = 1;
	std::cout << "map_char_myClass['x'] = " << map_char_myClass['x'] << std::endl;
	map_char_myClass['x'] = 10; // Correct mistake.
	std::cout << "map_char_myClass['x'] = " << map_char_myClass['x'] << std::endl;
	std::cout << "map_char_myClass['z'] = " << map_char_myClass['z'] << std::endl; // Note default value is added.

	std::cout << "Here is the bit which is currently non-compliant:" << std::endl;
	//This needs to be fixed

	std::map<int, std::string> m;

	m.insert(std::make_pair(1, std::string("one")));
	m.insert(std::make_pair(2, std::string("two")));
	m.insert(std::make_pair(3, std::string("three")));

	std::map<int, std::string>::const_iterator m_2(m.find(2));
	std::map<int, std::string>::const_iterator m_3(m.find(3));

	std::cout << "m_2 is " << m_2->second << std::endl;
	std::cout << "m_3 is " << m_3->second << std::endl;

	m.erase(1);

	std::cout << "m_2 is now " << m_2->second << std::endl;
	std::cout << "m_3 is now " << m_3->second << std::endl;

        std::cout << "Beginning map test" << std::endl;

        TestFramework::init();
	
	TestFramework::AssertReturns<bool>(canForwardIterateCorrectly, true);
	TestFramework::AssertReturns<bool>(canCompareConstNonConstIter, true);
	TestFramework::AssertReturns<bool>(canSwapCorrectly, true);
	TestFramework::AssertReturns<bool>(canSubscriptWithoutExtraObjectCreation, true);

	TestFramework::results();

	return 0;
}


