#include <functional>
void Invoke(std::move_only_function<void() const> const& FF) {
  std::move_only_function<void()>{std::reference_wrapper<std::move_only_function<void() const> const>(FF)}();
}
void Functional() {
#ifdef ARDUINO_ARCH_SAM
  std::move_only_function<void() const> const Member{ []() {} };
#else
  std::move_only_function<void() const> const Member = []() {};  //SAM编译器的bug，不允许这样初始化
#endif
  Invoke(Member);
}