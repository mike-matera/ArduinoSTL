//此示例需要使用串口监视器呈现。先生成一个原始数组0123456789，然后根据用户输入的随机种子，不断产生随机排序。
#include <Cpp_Standard_Library.h>
#include <random>
#include <iostream>
#include <algorithm>
#include <utility>
template<typename T>
struct MakeArray {};
template<uint64_t... V>
struct MakeArray<std::integer_sequence<uint64_t, V...>> {
  static uint64_t value[sizeof...(V)];
};
template<uint64_t... V>
uint64_t MakeArray<std::integer_sequence<uint64_t, V...>>::value[sizeof...(V)] = { V... };
uint64_t (&Array)[10] = MakeArray<std::make_integer_sequence<uint64_t, 10>>::value;
void setup() {
  Serial.begin(9600);
  std::cout << "原始数组：";
  //很多平台并不原生支持uint64_t，但本库仍能输出
  for (uint64_t A : Array)
    std::cout << A;
  std::cout << std::endl;
}
void loop() {
  static uint32_t RandomSeed;
#ifdef ARDUINO_ARCH_AVR
  //非标准行为：ArduinoUrng是Arduino平台专用的随机生成器。你也可以使用标准库提供的mt19937，但它占用了太多内存，不建议使用。
  constexpr std::ArduinoUrng Urng;
  std::cout << "输入随机种子（非数字的输入将被忽略）：";
  std::cin >> RandomSeed;
  std::ArduinoUrng::seed(RandomSeed);
#else
  //SAM和ESP32架构额外提供真随机生成器，不需要随机种子
  constexpr std::TrueUrng Urng;
  std::cout << "输入任意字符以生成下一个乱序：";
  std::cin >> RandomSeed;
#endif

  // 清除错误标志位。必须紧贴ignore之前，因为不先清除错误状态ignore就不会生效。
  std::cin.clear();

  // 丢弃错误输入。必须在获取RandomSeed之后，否则第一次输入会被忽略
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << RandomSeed << std::endl;
  std::shuffle(std::begin(Array), std::end(Array), Urng);
  std::cout << "随机乱序：";
  for (uint64_t A : Array)
    std::cout << A;
  std::cout << std::endl;

  //此段仅用于展示异常处理，对本示例主线逻辑无意义。必须在编译选项中启用-fexceptions并禁用-fno-rtti才能使本段生效。AVR不支持异常处理。
#ifdef ARDUINO_ARCH_SAM
//SAM架构不会自动定义此宏。如果在SAM的编译选项中启用了-fexceptions，还需要手动定义__cpp_exceptions。
//#define __cpp_exceptions
#endif
#ifdef __cpp_exceptions
  try {
    throw 0;
  } catch (...) {
    std::cout << "成功捕获异常" << std::endl;
  }
#endif
}