#include <exception>
#include <stdexcept>
#include <cstdio>
#include <cstring>

int main(){
	printf("Starting exception testing\n");

	try{
		printf("Throwing out of range\n");
		throw std::out_of_range("This is text");
		printf("If you are seeing this, this is ***BAD***\n");

	}catch(std::out_of_range &e){
		if(strcmp(e.what(), "This is text") == 0){
			printf("Caught thrown exception\n");
		}else{
			printf("Caught exception with different exception text\n");
			printf("Exception text: %s\n", e.what() );
		}
	}catch(...){
		printf("Missed catching exception - this is BAD\n");
	}


	printf("Testing inheriting exception handler\n");
	try{
		printf("Throwing length_error\n");
		throw std::length_error("Length error test text");
		printf("Exception not thrown (bad)\n");
	}catch( std::out_of_range &e){
		printf("Caught out_of_range (bad)\n");
	}catch( std::logic_error &e){
		printf("Caught logic_error (good)\n");
	}catch(...){
		printf("Caught generic exception (bad)\n");
	}


	printf("Testing generic excepetion handler\n");
	try{
		printf("Throwing length_error\n");
		throw std::length_error("Length error test text");
		printf("Exception not thrown (bad)\n");
	}catch( std::out_of_range &e){
		printf("Caught out_of_range (bad)\n");
	}catch(...){
		printf("Caught generic exception (good)\n");
	}

	return 0;
}
