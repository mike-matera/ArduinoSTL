#include <support>

extern "C" void *__cxa_allocate_exception(size_t thrown_size){
	void * retval;

	/*The amount of data needed is the size of the object *PLUS*
	the size of the header.  The header is of struct __cxa_exception
	The address needs to be adjusted because the pointer we return
	should not point to the start of the memory, but to the point
	where the object being thrown actually starts*/

	retval = malloc(thrown_size + sizeof(__cxa_exception));

//	Check to see that we actuall allocated memory
	if(retval == 0){
		std::terminate();
	}

	//Need to do a typecast to char* otherwize we are doing math with
	//a void* which makes the compiler cranky (Like me)
	return ((char *)retval + sizeof(__cxa_exception));
}

extern "C" void __cxa_free_exception(void *thrown_exception){



}

extern "C" void __cxa_throw (void *thrown_exception, std::type_info *tinfo,void (*dest) (void *) ){


}
