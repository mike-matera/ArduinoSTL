//#include <new>
//#include <memory>
#include <string>

struct test{
	int a;
	float b;
};



int main(){
	std::exception a;
	test * temp = new test;
	temp->a = 5;
//	std::string a;
	return 0;
}
