#include <iostream>

template <class T> void testClass(std::string tname);

int main(){
	testClass<char>("char");
	return 0;
}


template <class T> void testClass(std::string tname){
	typename std::char_traits<T>::int_type i1, i2;	
	typename std::char_traits<T>::char_type c1, c2;	
	const T* a1 = "teststring";
	// const T* a2 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789`~!@#$%^&*()_+{}|[]\\:;\"'<>?,./";
	
	//Check to make sure that EOF values are comparable and set properly
	i1 = std::char_traits<T>::eof();
	i2 = i1;

	std::char_traits<T>::assign(c1, 'a');
	std::char_traits<T>::assign(c2, 'a');

	if(std::char_traits<T>::eq(c1, c2)){
		std::cout << "eq() properly compares identical values for " << tname << std::endl;
	}else{
		std::cout << "eq() does not properly compare identical values for " << tname << std::endl;
	}

	std::char_traits<T>::assign(c1, 'a');
	std::char_traits<T>::assign(c2, 'b');

	if(std::char_traits<T>::eq(c1, c2)){
		std::cout << "eq() does not properly compares disimilar values for " << tname << std::endl;
	}else{
		std::cout << "eq() properly compares disimilar values for " << tname << std::endl;
	}

	std::char_traits<T>::assign(c1, 'a');
	std::char_traits<T>::assign(c2, 'b');

	if(std::char_traits<T>::lt(c1, c2)){
		std::cout << "lt() properly compares values for " << tname << std::endl;
	}else{
		std::cout << "lt() does not properly compares values for " << tname << std::endl;
	}

	std::char_traits<T>::assign(c1, 'b');
	std::char_traits<T>::assign(c2, 'a');

	if(std::char_traits<T>::lt(c1, c2)){
		std::cout << "lt() does not properly compare reversed values for " << tname << std::endl;
	}else{
		std::cout << "lt() properly compares reversed values for " << tname << std::endl;
	}

	std::char_traits<T>::assign(c1, 'a');
	std::char_traits<T>::assign(c2, 'a');

	if(std::char_traits<T>::lt(c1, c2)){
		std::cout << "lt() does not properly compare equal values for " << tname << std::endl;
	}else{
		std::cout << "lt() properly compares equal values for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","test", 4) == 0){
		std::cout << "compare() properly compares identical strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare identical strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","test", 3) == 0){
		std::cout << "compare() properly compares partial identical strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare partial identical strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","test", 6) == 0){
		std::cout << "compare() properly compares undersized identical strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare undersized identical strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","testing", 4) == 0){
		std::cout << "compare() properly compares different sized identical strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare different sized identical strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","testing", 5) < 0){
		std::cout << "compare() properly compares different strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare different strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","aaaa", 4) > 0){
		std::cout << "compare() properly compares different strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare different strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","testa", 4) == 0){
		std::cout << "compare() properly compares different sized identical strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare different sized identical strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::compare("test","testa", 5) < 0){
		std::cout << "compare() properly compares different sized identical strings for " << tname << std::endl;
	}else{
		std::cout << "compare() does not properly compare different sized identical strings for " << tname << std::endl;
	}

	if(std::char_traits<T>::length("test") == 4){
		std::cout << "length() properly computes length of 'test' for " << tname << std::endl;
	}else{
		std::cout << "length() does not properly computer length of 'test' " << tname << std::endl;
	}

	if(std::char_traits<T>::length("") == 0){
		std::cout << "length() properly computes length of '' for " << tname << std::endl;
	}else{
		std::cout << "length() does not properly computer length of '' " << tname << std::endl;
	}

	if(std::char_traits<T>::length("a0b1c2") == 6){
		std::cout << "length() properly computes length of 'a0b1c2' for " << tname << std::endl;
	}else{
		std::cout << "length() does not properly computer length of 'a0b1c2' " << tname << std::endl;
	}

	if(std::char_traits<T>::find(a1, sizeof(a1), 't') == a1){
		std::cout << "find() properly locates the location of 't' starting at the beginning for " << tname << std::endl;
	}else{
		std::cout << "find() does not properly locate the location of 't' starting at the beginning for " << tname << std::endl;
	}

	if(std::char_traits<T>::find(a1 + 1, sizeof(a1) - 1, 't') == (a1 + 3)){
		std::cout << "find() properly locates the location of 't' with offset 1 for " << tname << std::endl;
	}else{
		std::cout << "find() does not properly locate the location of 't' starting at the beginning for " << tname << std::endl;
	}

	if(std::char_traits<T>::find(a1 + 3, sizeof(a1) - 3, 't') == (a1 + 3)){
		std::cout << "find() properly locates the location of 't' with offset 3 for " << tname << std::endl;
	}else{
		std::cout << "find() does not properly locate the location of 't' starting at the beginning for " << tname << std::endl;
	}

	if(std::char_traits<T>::find(a1, 0, 't') == 0){
		std::cout << "find() properly returns NULL in 0-sized searches for " << tname << std::endl;
	}else{
		std::cout << "find() does not properly return NULL in 0-sized searches for " << tname << std::endl;
	}

	if(std::char_traits<T>::find(a1, sizeof(a1), 'q') == 0){
		std::cout << "find() properly returns NULL when not found for " << tname << std::endl;
	}else{
		std::cout << "find() does not properly return NULL when not found for " << tname << std::endl;
	}




	if(std::char_traits<T>::eof() == i2){
		std::cout << "eof() works properly for " << tname << std::endl;
	}else{
		std::cout << "eof() does not work properly for " << tname << std::endl;
	}
	
	i1 = std::char_traits<T>::eof();
	if(std::char_traits<T>::not_eof(i1) != i1){
		std::cout << "not_eof() works properly for " << tname << std::endl;
	}else{
		std::cout << "not_eof() does not work properly for " << tname << std::endl;
	}
}
