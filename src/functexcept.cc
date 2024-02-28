#ifdef ARDUINO_ARCH_SAM
#include <bits/functexcept.h>
namespace std
{
	// 59
	void
	__throw_bad_cast()
	{
	}
	// 63
	// 67
	void
	__throw_logic_error(const char *__s __attribute__((unused)))
	{
	}
	// 71
	//   79
	void
	__throw_length_error(const char *__s __attribute__((unused)))
	{
	}

	void
	__throw_out_of_range(const char *__s __attribute__((unused)))
	{
	}
	// 87
	// 107
	void
	__throw_runtime_error(const char *__s __attribute__((unused)))
	{
	}
	// 111
}
#endif