#ifndef ARDUINO_ARCH_AVR
#include <bits/functexcept.h>
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
	void
	__throw_bad_function_call() {}
	// 35
}
#endif