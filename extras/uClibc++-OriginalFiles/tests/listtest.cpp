#include <list>
#include <iostream>
#include <vector>
#include <string>

class testClass{
public:
	virtual void write(){
		std::cout << "testClass::write()" << std::endl;
	}
};

class testSubClass : public testClass{
public:
	virtual void write(){
		std::cout << "testSubClass::write()" << std::endl;
	}
};


int main(){
	std::string test;
	std::list<double>temp(5, 12.0);
	std::list<double> a;
	std::list<double>::iterator i, j;
	std::list<testClass *> testPointer;
	std::list<testClass *>::iterator testPointerIterator;


	int array1 [] = { 1, 2};
	int array2 [] = { 3, 4};

	std::list<int> list_int_1( array1, array1 + 2);
	std::list<int> list_int_2( array2, array2 + 2);
	std::list<int>::iterator list_iter_1;
	std::list<int>::iterator list_iter_2;


	test = "Beginning of list test";

	std::cout << test << std::endl;
	for(i = temp.begin(); i!=temp.end(); i++){
		std::cout << "i: " << *i << std::endl;
	}



	std::cout << "\nList insert test\n";
	i = temp.begin();
	i++;
	++i;
	i=temp.insert(i, 52.8);
	temp.insert(i,52.4);
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}

	std::cout << "\nList multi-insert test\n";
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
	std::cout << "Second element in list: " << *i << std::endl;
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}

	std::cout << "Erasing last 3 elements\n";
	i = temp.end();
	i--;
	i--;
	i--;
	i = temp.erase(i,temp.end());
	--i;
	std::cout << "Last element in list: " << *i << std::endl;
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}

	std::cout << "Erasing first element\n";

	i = temp.begin();
	i = temp.erase(i);
	for(j = temp.begin(); j!=temp.end(); j++){
		std::cout << "j: " << *j << std::endl;
	}
	if(i == temp.begin()){
		std::cout << "Proper iterator returned\n";
	}else{
		std::cout << "Incorrect iterator returned\n";
	}

	std::cout << "\nTesting reverse\n";
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

	std::cout << "\nTesting front() and back()\n";
	std::cout << "Front (should be 21.2): " << temp.front() << std::endl;
	std::cout << "Back (should be 12.8): " << temp.back() << std::endl;


	std::cout << "\nTesting splice" << std::endl;

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


	std::cout << "The following two lines should be identical\n";
	std::cout << "1 2 3 4 \n";

	list_iter_1 = list_int_1.begin();
	while(list_iter_1 != list_int_1.end()){
		std::cout << *list_iter_1 << " ";
		++list_iter_1;
	}
	list_iter_1 = list_int_2.begin();
	while(list_iter_1 != list_int_2.end()){
		std::cout << *list_iter_1 << " ";
		++list_iter_1;
	}
	std::cout << std::endl;

	list_iter_1 = list_int_1.begin();
	list_iter_1++;


	std::cout << "The following two lines should be identical\n";
	std::cout << "1 3 4 2 \n";
	
	list_int_1.splice(list_iter_1, list_int_2, list_int_2.begin(), list_int_2.end());

	list_iter_1 = list_int_1.begin();
	while(list_iter_1 != list_int_1.end()){
		std::cout << *list_iter_1 << " ";
		++list_iter_1;
	}
	std::cout << std::endl;
	

	std::cout << "Testing operator=()\n";
	temp.clear();
	temp.push_back(12.8);
	temp.push_back(22.4);
	temp.push_back(37.9);
	temp.push_back(48.5);
	temp.push_back(21.2);
	temp.push_back(85.4);
	temp.push_back(24.6);
	temp.push_back(69.7);

	std::cout << "The following three lines should be identical\n";
	std::cout << "12.8 22.4 37.9 48.5 21.2 85.4 24.6 69.7 \n";
	a = temp;	
	i = temp.begin();
	while(i != temp.end()){
		std::cout << *i << " ";
		++i;
	}
	std::cout << std::endl;

	i = a.end();
	while(i != a.begin()){
		--i;
		std::cout << *i << " ";
	}
	std::cout << std::endl;


	std::cout << "\nTesting lists with pointer parameters" << std::endl;

	testPointer.clear();
	
	testPointer.insert(testPointer.end(), new testSubClass());

	if(testPointer.size() > 0){

		testPointerIterator = testPointer.begin();
		while(testPointerIterator != testPointer.end()){
			(*testPointerIterator)->write();
			++testPointerIterator;
		}
	}
	delete (testPointer.back());
	testPointer.pop_back();


	std::cout << "\nTesting sorting\n";

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



	std::cout << "\nTesting merging\n";

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

	


	std::cout << "\nTesting remove\n";

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

	std::cout << "\nTesting unique\n";

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

	list_int_1.clear();
	list_int_1.push_back(1);
	list_int_1.push_back(2);
	list_int_1.push_back(3);
	list_int_1.push_back(4);

	int d(3);
	int * p = &d;
	for( list_iter_1 = list_int_1.begin(); list_iter_1 != list_int_1.end(); ++list_iter_1){
		if(*list_iter_1==*p){
			std::cout << "Found 3 == 3" << std::endl;
		}
	}


	return 0;
}
