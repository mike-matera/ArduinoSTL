#include <new>

struct test{
	int a;
	float b;
};


int main(){
	test * temp = new test;
	temp->a = 5;
	delete temp;
	temp = 0;

	temp = new test[25];
	delete [] temp;
	temp = 0;

	return 0;
}
