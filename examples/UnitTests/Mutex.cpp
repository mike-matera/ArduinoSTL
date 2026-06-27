#include <mutex>
void Mutex() {
  static std::mutex Mutex;
  if (Mutex.try_lock()) {
    //此处代码将只会被单线程执行（这并不意味着它不会被中断，只是不会被多个线程同时访问）
  }
}