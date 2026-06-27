#ifdef ARDUINO_ARCH_AVR
#include <cerrno>
#include <pthread.h>
#include <Arduino.h>
struct InterruptGuard
{
	InterruptGuard() : HasInterrupt(
#ifdef ARDUINO_ARCH_AVR
						   SREG & (1 << SREG_I)
#endif
#ifdef ARDUINO_ARCH_SAM
									  !__get_PRIMASK()
#endif
					   )
	{
		noInterrupts();
	}
	~InterruptGuard()
	{
		if (HasInterrupt)
			interrupts();
	}

protected:
	bool const HasInterrupt;
};
int pthread_mutex_lock(pthread_mutex_t *mutex)
{
	InterruptGuard const Guard;
	if (*mutex)
		return EDEADLK;
	else
	{
		*mutex = true;
		return 0;
	}
}
int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	InterruptGuard const Guard;
	if (*mutex)
	{
		*mutex = false;
		return 0;
	}
	else
		return EPERM;
}
int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
	return pthread_mutex_lock(mutex);
}
#endif