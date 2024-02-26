#ifndef ARDUINO_ARCH_AVR
#include <bits/functexcept.h>
namespace std
{
	void __throw_bad_function_call() {}
	void __throw_bad_cast(void) {}
}
#endif