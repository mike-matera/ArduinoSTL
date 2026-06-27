#pragma once
#ifdef ARDUINO_ARCH_AVR
typedef bool volatile pthread_mutex_t;
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
#define PTHREAD_MUTEX_INITIALIZER false
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER false
#else
#include_next <pthread.h>
#endif