#include <Cpp_Standard_Library.h>
#include <iostream>
#include <random>
template<typename T>
struct MakeArray {};
template<size_t... V>
struct MakeArray< std::integer_sequence<size_t, V...>> {
  static size_t value[sizeof...(V)];
};
template<size_t... V>
size_t MakeArray<std::integer_sequence<size_t, V...>>::value[sizeof...(V)] = { V... };
auto& Array = MakeArray<std::make_index_sequence<10>>::value;
void setup() {
  Serial.begin(9600);
  std::cout << "原始数组：";
  for (size_t A : Array)
    std::cout << A;
  std::cout << std::endl;
}
void loop() {
  constexpr auto BB=std::_Allow_inheriting_unwrap<unsigned int*, void>::value;
  constexpr std::ArduinoUrng AU;
  std::cout << "输入随机种子：";
  uint32_t RandomSeed;
  std::cin >> RandomSeed;
  std::ArduinoUrng::seed(RandomSeed);
  std::shuffle(std::begin(Array), std::end(Array), AU);
  std::cout << "随机乱序：";
  for (size_t A : Array)
    std::cout << A;
  std::cout << std::endl;
}