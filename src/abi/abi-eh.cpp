/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <new>
#include <exception>
#include <basic_definitions>
#include <cstddef>
#include <cstdlib>
#include <abi/abi-eh.h>
#include <typeinfo>

namespace __cxxabiv1{

/* This function allocates the space for an exception and an
 * exception header, but returns a pointer to the space for the
 * exception, which is partway into the middle of the allocated space
 */

extern "C" void * __cxa_allocate_exception(size_t thrown_size){
	return ((char *)malloc(thrown_size + sizeof(__cxa_exception)) + sizeof(__cxa_exception));
}

//The following deallocates space allocated above

extern "C" void __cxa_free_exception(void *thrown_exception){
	free( (char*)thrown_exception - sizeof(__cxa_exception) );
}

/*extern "C" void __cxa_bad_cast(){
#ifdef __USE_EXCEPTIONS
	int i;
//	throw std::bad_cast();
#else
	abort();
#endif
}*/

/*typedef struct
{
	_Unwind_Ptr Start;
	_Unwind_Ptr LPStart;
	_Unwind_Ptr ttype_base;
	const unsigned char *TType;
	const unsigned char *action_table;
	unsigned char ttype_encoding;
	unsigned char call_site_encoding;
} lsda_header_info;
*/

/*extern "C" _Unwind_Reason_Code __gxx_personality_v0(
	int version,
	_Unwind_Action actions,
	_Unwind_Exception_Class exceptionClass,
	_Unwind_Exception *exceptionObject,
	_Unwind_Context *context)
{
	//The _Unwind_Exception is the last element in a __cxa_exception
	//so we go forward in memory one _Unwind_Exception and then convert
	//into a __cxa_exception, at which point we move back in memory,
	//getting the complete __cxa_exception

	__cxa_exception *xh = (reinterpret_cast<__cxa_exception *>(exceptionObject + 1) - 1);

	enum found_handler_type{
		found_nothing,
		found_terminate,
		found_cleanup,
		found_handler
	} found_type;

	lsda_header_info info;
	const unsigned char *language_specific_data;
	const unsigned char *action_record;
	const unsigned char *p;
	_Unwind_Ptr landing_pad, ip;
	int handler_switch_value;
	void *thrown_ptr = xh + 1;

	if (version != 1){
		return _URC_FATAL_PHASE1_ERROR;
	}

	language_specific_data = (unsigned char *)(context->lsda);
	
	//If there is no language specific data then there
	//is nothing to be done at this time
	if(language_specific_data == 0){
		return _URC_CONTINUE_UNWIND;
	}

		

	if(actions | _UA_SEARCH_PHASE){

		

	}

}*/

/*extern "C" void __cxa_throw(void *thrown_exception, void * tinfo, void (*dest) (void *)){

	//Get address of thrown exception header
	__cxa_exception *header = ((__cxa_exception *) thrown_exception - 1);

	//Save the current unexpected_handler and terminate_handler in the __cxa_exception header.
	header->unexpectedHandler = __cxxabiv1::__unexpected_handler;
	header->terminateHandler = __cxxabiv1::__terminate_handler;

	//Save the tinfo and dest arguments in the __cxa_exception header.
	header->exceptionType = static_cast<std::type_info *>(tinfo);
	header->exceptionDestructor = dest;

	//Set the exception_class field in the unwind header.
	header->unwindHeader.exception_class = __uclibcxx_exception_class;

	//Increment the uncaught_exception flag.
	__cxa_get_globals()->uncaughtExceptions++;

	//Call _Unwind_RaiseException in the system unwind library.
//	 _Unwind_RaiseException(thrown_exception);
	
}
*/


};
