//此示例需要使用串口监视器呈现。先生成一个原始数组0123456789，然后根据用户输入的随机种子，不断产生随机排序。
#include <Cpp_Standard_Library.h>
#include <iostream>
#include <random>
#include <algorithm>
template<typename T>
struct MakeArray {};
template<size_t... V>
struct MakeArray< std::integer_sequence<size_t, V...>> {
  static size_t value[sizeof...(V)];
};
template<size_t... V>
size_t MakeArray<std::integer_sequence<size_t, V...>>::value[sizeof...(V)] = { V... };
size_t (&Array)[10] = MakeArray<std::make_index_sequence<10>>::value;
void setup() {
  Serial.begin(9600);
  std::cout << "原始数组：";
  for (size_t A : Array)
    std::cout << A;
  std::cout << std::endl;
}
void loop() {
#ifdef ARDUINO_ARCH_ESP32
  //ESP32架构推荐使用硬件随机生成器，不需要设置种子即可得到真随机数
  constexpr std::EspUrng Urng;
#else
  //非标准行为：ArduinoUrng是Arduino平台专用的随机生成器。你也可以使用标准库提供的mt19937，但它占用了太多内存，不建议使用。
  constexpr std::ArduinoUrng Urng;
  std::cout << "输入随机种子：";
  uint32_t RandomSeed;
  std::cin >> RandomSeed;
  std::cout << RandomSeed << std::endl;
  std::ArduinoUrng::seed(RandomSeed);
#endif
  std::shuffle(std::begin(Array), std::end(Array), Urng);
  std::cout << "随机乱序：";
  for (size_t A : Array)
    std::cout << A;
  std::cout << std::endl;
}