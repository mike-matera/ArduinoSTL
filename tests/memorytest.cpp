#include <memory>
#include <cstdio>

std::auto_ptr<int> intMaker();

int main(){
	std::auto_ptr<int> a(new int (12));
	if(0 == a.get()){
		printf("a pointer is zero (BAD)\n");
	}else{
		printf("a pointer is non-zero (GOOD)\n");
	}
	printf("a value (should be 12): %i\n", *a);

	std::auto_ptr<int> b(a);
	if(0 == b.get()){
		printf("b pointer is zero (BAD)\n");
	}else{
		printf("b pointer is non-zero (GOOD)\n");
	}
	if(0 == a.get()){
		printf("a pointer is zero (GOOD)\n");
	}else{
		printf("a pointer is non-zero (BAD)\n");
	}
	printf("b value (should be 12): %i\n", *b);

	*b = 7;
	if(0 == b.get()){
		printf("b pointer is zero (BAD)\n");
	}else{
		printf("b pointer is non-zero (GOOD)\n");
	}
	printf("b value (should be 7): %i\n", *b);

	std::auto_ptr<int> c(intMaker());
	if(0 == c.get()){
		printf("c pointer is zero (BAD)\n");
	}else{
		printf("c pointer is non-zero (GOOD)\n");
	}
	printf("c value (should be 5): %i\n", *c);
	c.reset();
	if(0 == c.get()){
		printf("c pointer is zero (GOOD)\n");
	}else{
		printf("c pointer is non-zero (BAD)\n");
	}

	std::auto_ptr<int> x( new int(5) );
	std::auto_ptr<int> y( std::auto_ptr<int>( x ) );


	return 0;
}


std::auto_ptr<int> intMaker(){
	return std::auto_ptr<int> ( new int(5));
}
