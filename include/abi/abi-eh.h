#include <typeinfo>
#include <support>
#include <exception>


#ifndef __UNWIND_ABI_EH
#define __UNWIND_ABI_EH

namespace __cxxabiv1{

	extern "C" _Unwind_Reason_Code __gxx_personality_v0(
		int version, 
		_Unwind_Action actions,
		_Unwind_Exception_Class exceptionClass,
		struct _Unwind_Exception *exceptionObject,
		struct _Unwind_Context *context
	);

};	//namespace __cxxabiv1





#endif

