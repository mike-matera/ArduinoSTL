#include <new>
#include <memory>
#include <cstdio>

struct test{
	int a;
	float b;
};

class base {
protected:
	int a;

public:
	base() : a(0){
		printf("Executing default base class constructor. a: %i\n", a);
	}

	virtual ~base(){
		printf("Executing base class destructor\n");
	}

	virtual void print(){
		printf("Base class print function with a=%i\n", a);
	}

};

class sub : public base{
protected:
	float f;
public:
	sub() : f(0){
		printf("Executing default sub class constructor. a: %i, f: %f\n", base::a, f);
	}
	virtual ~sub(){
		printf("Executing sub class destructor\n");
	}

	virtual void print(){
		printf("Sub class print function with a=%i and f=%f\n", a, f);
	}

};


int main(){
	test * temp = new test;
	temp->a = 5;
	delete temp;
	temp = 0;

	temp = new test[25];
	delete [] temp;
	temp = 0;

	base * b = new base;
	b->print();
	delete b;
	b=0;

	b = new base[3];
	for(int i = 0; i < 3; ++i){
		b[i].print();
	}
	delete [] b;
	b = 0;

	b = new sub;
	b->print();
	delete b;
	b = 0;

	//We can only create one because we can't step through the array properly
	b = new sub[1];
	b[0].print();
	delete [] b;
	b = 0;

	printf("Testing nothrow new\n");

	b = new(std::nothrow) base;

	printf("Checking allocator\n");
	std::allocator<base> al;
	b = al.allocate(1);
	al.construct(b, base());
	b->print();
	al.destroy(b);
	al.deallocate(b, 1);
	b = 0;

	return 0;
}
