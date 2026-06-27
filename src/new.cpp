#ifdef ARDUINO_ARCH_AVR
#include <new>
void operator delete(void *ptr, std::size_t size) noexcept
{
	operator delete(ptr);
}
void operator delete[](void *ptr, std::size_t size) noexcept
{
	operator delete[](ptr);
}
#endif