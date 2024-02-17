#ifdef ARDUINO_ARCH_AVR
#include "functional"
namespace std
{
	extern "C++" [[noreturn]] _CRTIMP2_PURE void __CLRCALL_PURE_OR_CDECL _Xbad_function_call() {}
}
#endif