#include <exception>
#include <func_exception>
#include <stdexcept>

namespace std{

void __throw_out_of_range( const char * message){
	if(message == 0){
		throw out_of_range();
	}
	throw out_of_range(message);
}

void __throw_length_error(const char * message){
	if(message == 0){
		throw length_error();
	}
	throw length_error(message);
}


};
