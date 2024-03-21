#include "new"
#if __cplusplus < 201402L
void operator delete(void *ptr, std::size_t size) noexcept
{
	operator delete(ptr);
}
void operator delete[](void *ptr, std::size_t size) noexcept
{
	operator delete[](ptr);
}
#endif // __cplusplus >= 201402L