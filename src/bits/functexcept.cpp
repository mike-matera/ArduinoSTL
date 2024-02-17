#ifdef ARDUINO_ARCH_SAM
#include <bits/functexcept.h>
namespace std
{
	void __throw_ios_failure(const char *) {}
	void __throw_bad_function_call() {}
}
#endif