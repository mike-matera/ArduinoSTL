#ifndef ARDUINO_ARCH_AVR
#include <bits/functexcept.h>
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
	// 86
	void
	__throw_ios_failure(const char *__s __attribute__((unused))) {}
	// 90
}
#endif