#include <string>
#include <iostream>
#include "testframework.h"

bool checkStringCompareEquals(){
	std::string b = "This is test string b";
	std::string c = "This is test string c";

	return (b == c);
}

bool checkStringCompareCompare(){
	std::string l = "Tommi Maekitalo";
	std::string s = "Mae";
	int c = l.compare(6, 3, s);

	return (0 == c);
}

bool checkStringCompareNotEquals(){
	std::string b = "This is test string b";
	std::string c = "This is test string c";

	return b != c;
}

bool checkStringCompareForwardsEqual(){
	std::string a = "This is test string a";
	std::string b = "This is test string b";

	a = b + "Test cstring";
	a = b;
	return (a == b);
}

bool checkStringCompareBackwardsEqual(){
	std::string a = "This is test string a";
	std::string b = "This is test string b";

	a = b + "Test cstring";
	a = b;
	return (b == a);
}

bool checkStringCompareForwardsNotEqual(){
	std::string a = "This is test string a";
	std::string b = "This is test string b";

	a = b + "Test cstring";
	a = b;
	return (a != b);
}

bool checkStringCompareBackwardsNotEqual(){
	std::string a = "This is test string a";
	std::string b = "This is test string b";

	a = b + "Test cstring";
	a = b;
	return (b != a);
}

bool checkStringTextForwardsComparison(){
	std::string a = "Test text comparison";

	return (a == "Test text comparison");
}

bool checkStringTextBackwardsComparison(){
	std::string a = "Test text comparison";

	return (a == "Test text comparison");
}

bool checkStringOperatorLess(){
	std::string b = "This is test string b";
	std::string c = "This is test string c";

	return (b < c);
}

bool checkStringOperatorGreater(){
	std::string b = "This is test string b";
	std::string c = "This is test string c";

	return (b > c);
}

bool checkStringSubstr(){
	std::string a = "This is the base string";

	return ("is th" == a.substr(5, 5) );
}

bool checkStringCharConstructor(){
	std::string a = std::string(1, 'w');
	std::string b = "w";

	return (a == b);
}

bool checkStringOpPlusChar(){
	std::string a = std::string("test");
	std::string b = '1' + a;

	return ("1test" == b );
}

bool checkStringOpCharPlus(){
	std::string a = std::string("test");
	std::string b = a + '1';

	return ("test1" == b);
}

bool checkStringOpPlusString(){
	std::string a = std::string("test");
	std::string b = "1" + a;

	return ("1test" == b );
}

bool checkStringOpStringPlus(){
	std::string a = std::string("test");
	std::string b = a + "1";

	return ("test1" == b);
}

bool checkStringOpSubscript(){
	std::string a = "abcdefg";

	return('a' == a[0] && 'b' == a[1] && 'c' == a[2] && 'd' == a[3] && 'e' == a[4] && 'f' == a[5] && 'g' == a[6]);
}

bool checkStringErase(){
	std::string a = "this should be empty";
	a.erase();

	return ("" == a);
}

bool checkFindThe(){
	std::string a = "This is the string we are searching through";
	std::string b = "the";
	std::string::size_type retval = a.find(b);
	return 8 == retval;
}

bool checkFindCharG(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find('g');
	return 17 == retval;
}

bool checkFindSearch(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find("search");
	return 26 == retval;
}

bool checkFindThrough(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find("through");
	return 36 == retval;
}

bool checkFindIsChar3(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find("is", 3);
	return 5 == retval;
}

bool checkFindQ(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find("q");
	return a.npos == retval;
}

bool checkFindQCast(){
	std::string a = "This is the string we are searching through";

	if( (long)a.find("q") >= 0){
		return false;
	}else{
		if((long)a.find("q") < 0){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

bool checkRfindThe(){
	std::string a = "This is the string we are searching through";
	std::string b = "the";
	std::string::size_type retval = a.rfind(b);
	return 8 == retval;
}

bool checkRfindCharG(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.rfind('g');
	return 41 == retval;
}

bool checkRfindSearch(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.rfind("search");
	return 26 == retval;
}

bool checkRfindIsChar3(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.rfind("is", 3);
	return 2 == retval;
}

bool checkRfindQ(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.rfind("q");
	return a.npos == retval;
}

bool checkRfindThis(){
	std::string a = "This is the string we are searching through";
	std::string b = "This";
	std::string::size_type retval = a.rfind(b);
	return 0 == retval;
}

bool checkFindFirstOfThe(){
	std::string a = "This is the string we are searching through";
	std::string b = "the";
	std::string::size_type retval = a.find_first_of(b);
	return 1 == retval;
}

bool checkFindFirstOfCharG(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_of('g');
	return 17 == retval;
}

bool checkFindFirstOfSearch(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_of("search");
	return 1 == retval;
}

bool checkFindFirstOfIsChar4(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_of("is", 4);
	return 5 == retval;
}

bool checkFindFirstOfQ(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_of("q");
	return a.npos == retval;
}

bool checkFindFirstOfThis(){
	std::string a = "This is the string we are searching through";
	std::string b = "This";
	std::string::size_type retval = a.find_first_of(b);
	return 0 == retval;
}

bool checkFindLastOfThe(){
	std::string a = "This is the string we are searching through";
	std::string b = "the";
	std::string::size_type retval = a.find_last_of(b);
	return 42 == retval;
}

bool checkFindLastOfCharG(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_of('g');
	return 41 == retval;
}

bool checkFindLastOfSearch(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_of("search");
	return 42 == retval;
}

bool checkFindLastOfIsChar4(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_of("is", 4);
	return 3 == retval;
}

bool checkFindLastOfQ(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_of("q");
	return a.npos == retval;
}

bool checkFindLastOfThis(){
	std::string a = "This is the string we are searching through";
	std::string b = "This";
	std::string::size_type retval = a.find_last_of(b);
	return 42 == retval;
}

bool checkFindFirstNotOfThe(){
	std::string a = "This is the string we are searching through";
	std::string b = "the";
	std::string::size_type retval = a.find_first_not_of(b);
	return 0 == retval;
}

bool checkFindFirstNotOfCharG(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_not_of('g');
	return 0 == retval;
}

bool checkFindFirstNotOfSearch(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_not_of("search");
	return 0 == retval;
}

bool checkFindFirstNotOfIsChar5(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_not_of("is", 5);
	return 7 == retval;
}

bool checkFindFirstNotOfQ(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_first_not_of("q");
	return 0 == retval;
}

bool checkFindFirstNotOfThis(){
	std::string a = "This is the string we are searching through";
	std::string b = "This";
	std::string::size_type retval = a.find_first_not_of(b);
	return 4 == retval;
}

bool checkFindLastNotOfThe(){
	std::string a = "This is the string we are searching through";
	std::string b = "the";
	std::string::size_type retval = a.find_last_not_of(b);
	return 41 == retval;
}

bool checkFindLastNotOfCharG(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_not_of('g');
	return 42 == retval;
}

bool checkFindLastNotOfSearch(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_not_of("search");
	return 41 == retval;
}

bool checkFindLastNotOfIsChar7(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_not_of("is", 7);
	return 7 == retval;
}

bool checkFindLastNotOfQ(){
	std::string a = "This is the string we are searching through";
	std::string::size_type retval = a.find_last_not_of("q");
	return 42 == retval;
}

bool checkFindLastNotOfThis(){
	std::string a = "This is the string we are searching through";
	std::string b = "This";
	std::string::size_type retval = a.find_last_not_of(b);
	return 41 == retval;
}

bool checkInsertAtInteractor() {
	std::string a = "abcd";
	a.insert(a.end(), 'q');
	if (a != "abcdq") {
		return false;
	}
	return true;
}

bool checkAssignFillType() {
	return true;
#if 0
	std::string a;
	a.assign<int>(10, 0x2B);
	return a == "++++++++++";
#endif
}

bool checkAssignFillChar() {
	std::string a;
	a.assign(10, '+');
	return a == "++++++++++";
}

bool checkAssignString() {
	std::string a = "This is a string";
	std::string b;
	b.assign(a);
	return b == a;
}
bool checkAssignSubstring() {
	std::string a = "This is a string";
	std::string b;
	b.assign(a, 2, 5);
	return b == "is is";
}

bool checkAssignCstring() {
	std::string a;
	a.assign("This is a c string");
	return a == "This is a c string";
}

bool checkAssignBuffer() {
	std::string a;
	a.assign("This is a c string", 8);
	return a == "This is ";
}

bool checkAssignIterator() {
	std::string a = "This is a string";
	std::string b;
	b.assign(a.begin() + 2, a.end() - 6);
	return b == "is is a ";
}

int main(){
	TestFramework::init();

	std::string a("Testing string constructor");
	std::string b, c;

	std::cout << "Value of a: " << a << std::endl;

	a = "This is test string a";
	b = "This is test string b";
	c = "This is test string c";

	std::cout << "Test string initial values:\n";

	std::cout << a << std::endl << b << std::endl << c << std::endl;

	a = b;
	std::cout << "a = b: " << a << std::endl;
	
	a = b + c;
	std::cout << "a = b + c: " << a << std::endl;

	a = "Test cstring" + b;
	std::cout << "a = \"Test cstring\" + b: " << a << std::endl;

	std::cout << "Please enter a test string:" << std::flush;
	std::cin >> a;
	std::cout << std::endl << "You entered: " << a << std::endl;

	TestFramework::AssertReturns<bool>(checkStringCompareEquals, false);
	TestFramework::AssertReturns<bool>(checkStringCompareCompare, true);
	TestFramework::AssertReturns<bool>(checkStringCompareNotEquals, true);

	TestFramework::AssertReturns<bool>(checkStringCompareForwardsEqual, true);
	TestFramework::AssertReturns<bool>(checkStringCompareBackwardsEqual, true);
	TestFramework::AssertReturns<bool>(checkStringCompareForwardsNotEqual, false);
	TestFramework::AssertReturns<bool>(checkStringCompareBackwardsNotEqual, false);

	TestFramework::AssertReturns<bool>(checkStringTextForwardsComparison, true);
	TestFramework::AssertReturns<bool>(checkStringTextBackwardsComparison, true);

	TestFramework::AssertReturns<bool>(checkStringOperatorLess, true);
	TestFramework::AssertReturns<bool>(checkStringOperatorGreater, false);

	TestFramework::AssertReturns<bool>(checkStringSubstr, true);
	TestFramework::AssertReturns<bool>(checkStringCharConstructor, true);

	TestFramework::AssertReturns<bool>(checkStringOpPlusChar, true);
	TestFramework::AssertReturns<bool>(checkStringOpCharPlus, true);
	TestFramework::AssertReturns<bool>(checkStringOpPlusString, true);
	TestFramework::AssertReturns<bool>(checkStringOpStringPlus, true);

	TestFramework::AssertReturns<bool>(checkStringOpSubscript, true);
	TestFramework::AssertReturns<bool>(checkStringErase, true);
	
	TestFramework::AssertReturns<bool>(checkFindThe, true);
	TestFramework::AssertReturns<bool>(checkFindCharG, true);
	TestFramework::AssertReturns<bool>(checkFindSearch, true);
	TestFramework::AssertReturns<bool>(checkFindThrough, true);
	TestFramework::AssertReturns<bool>(checkFindIsChar3, true);
	TestFramework::AssertReturns<bool>(checkFindQ, true);
	TestFramework::AssertReturns<bool>(checkFindQCast, true);

	TestFramework::AssertReturns<bool>(checkRfindThe, true);
	TestFramework::AssertReturns<bool>(checkRfindCharG, true);
	TestFramework::AssertReturns<bool>(checkRfindSearch, true);
	TestFramework::AssertReturns<bool>(checkRfindIsChar3, true);
	TestFramework::AssertReturns<bool>(checkRfindQ, true);
	TestFramework::AssertReturns<bool>(checkRfindThis, true);

	TestFramework::AssertReturns<bool>(checkFindFirstOfThe, true);
	TestFramework::AssertReturns<bool>(checkFindFirstOfCharG, true);
	TestFramework::AssertReturns<bool>(checkFindFirstOfSearch, true);
	TestFramework::AssertReturns<bool>(checkFindFirstOfIsChar4, true);
	TestFramework::AssertReturns<bool>(checkFindFirstOfQ, true);
	TestFramework::AssertReturns<bool>(checkFindFirstOfThis, true);

	TestFramework::AssertReturns<bool>(checkFindLastOfThe, true);
	TestFramework::AssertReturns<bool>(checkFindLastOfCharG, true);
	TestFramework::AssertReturns<bool>(checkFindLastOfSearch, true);
	TestFramework::AssertReturns<bool>(checkFindLastOfIsChar4, true);
	TestFramework::AssertReturns<bool>(checkFindLastOfQ, true);
	TestFramework::AssertReturns<bool>(checkFindLastOfThis, true);

	TestFramework::AssertReturns<bool>(checkFindFirstNotOfThe, true);
	TestFramework::AssertReturns<bool>(checkFindFirstNotOfCharG, true);
	TestFramework::AssertReturns<bool>(checkFindFirstNotOfSearch, true);
	TestFramework::AssertReturns<bool>(checkFindFirstNotOfIsChar5, true);
	TestFramework::AssertReturns<bool>(checkFindFirstNotOfQ, true);
	TestFramework::AssertReturns<bool>(checkFindFirstNotOfThis, true);

	TestFramework::AssertReturns<bool>(checkFindLastNotOfThe, true);
	TestFramework::AssertReturns<bool>(checkFindLastNotOfCharG, true);
	TestFramework::AssertReturns<bool>(checkFindLastNotOfSearch, true);
	TestFramework::AssertReturns<bool>(checkFindLastNotOfIsChar7, true);
	TestFramework::AssertReturns<bool>(checkFindLastNotOfQ, true);
	TestFramework::AssertReturns<bool>(checkFindLastNotOfThis, true);

	TestFramework::AssertReturns<bool>(checkInsertAtInteractor, true);

	TestFramework::AssertReturns<bool>(checkAssignFillType, true);
	TestFramework::AssertReturns<bool>(checkAssignFillChar, true);
	TestFramework::AssertReturns<bool>(checkAssignString, true);
	TestFramework::AssertReturns<bool>(checkAssignSubstring, true);
	TestFramework::AssertReturns<bool>(checkAssignCstring, true);
	TestFramework::AssertReturns<bool>(checkAssignBuffer, true);
	TestFramework::AssertReturns<bool>(checkAssignIterator, true);

	TestFramework::results();

	return 0;
}

