#include <exception>
#include <stdexcept>

namespace std{

	logic_error::logic_error() throw() : mstring(){

	}

	logic_error::logic_error(const string& what_arg) : mstring(what_arg){

	}

	logic_error::~logic_error() throw(){

	}

	const char * logic_error::what(){
		return mstring.c_str();
	}


	runtime_error::runtime_error() : mstring(){

	}

};

