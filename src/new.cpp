#include <new>
#include <cstdlib>

#ifndef _HEADER_STD_NEW
#define _HEADER_STD_NEW 1

	void* operator new(std::size_t numBytes) throw(std::bad_alloc){
		void * p = malloc(numBytes);
		if(p == 0){
			throw std::bad_alloc();
		}
		return p;
	}

        void operator delete(void* ptr) throw(){
		free(ptr);
	}

        void* operator new[](std::size_t numBytes) throw(std::bad_alloc){
		void * p = malloc(numBytes);
		if(p == 0){
			throw std::bad_alloc();
		}
		return p;
	}

        void operator delete[](void * ptr) throw(){
		free(ptr);
	}

#ifndef NO_NOTHROW
	void* operator new(std::size_t numBytes, const std::nothrow_t& ) throw(){
		return malloc(numBytes);
	}

        void operator delete(void* ptr, const std::nothrow_t& ) throw() {
		free(ptr);
	}

        void* operator new[](std::size_t numBytes, const std::nothrow_t& ) throw(){
		return malloc(numBytes);

	}
        void operator delete[](void* ptr, const std::nothrow_t& ) throw(){
		free(ptr);
	}
#endif


#endif
