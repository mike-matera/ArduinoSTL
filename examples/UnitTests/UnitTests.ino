#include <Cpp_Standard_Library.h>
//演示多个标准库的功能，无可展示的运行时效果，但应当可以编译通过

#include <chrono>
#include <algorithm>
#include <iostream>
#include <memory>
#include <dynarray>
#include <cmath>
#include <unordered_map>
#include <optional>
#include <map>
#include <queue>
#include <unordered_set>
#include <set>
#include <span>
#include <vector>
#include <functional>
std::map<uint8_t, std::move_only_function<void(std::dynarray<char> &&) const>> ListeningPorts;
std::unordered_map<uint8_t, std::move_only_function<void(std::dynarray<char> &&) const>> UListeningPorts;
std::queue<std::dynarray<char>> MessageQueue;
std::unordered_set<const std::function<void()> *> IdleTasks;
std::set<void *> PointerSet;
void Translate(std::chrono::hours H) {
  std::cout << std::chrono::duration_cast<std::chrono::seconds>(H + H).count() << std::endl;
}
std::move_only_function<void()> FF;
static volatile const float LogMin = std::log2(0);
void setup() {
  std::unique_ptr<std::chrono::hours[]> US = std::make_unique_for_overwrite<std::chrono::hours[]>(10);
  std::shared_ptr<std::chrono::hours[]> SSS;
  using namespace std::chrono_literals;
  std::fill_n(US.get(), 10, 1h);
  US[0] = std::chrono::duration_cast<std::chrono::hours>(10000us);
  std::chrono::hours H = US[5];
  FF = [H]() {
    Translate(H);
  };
  std::dynarray<int> D(std::log2(1024));
  std::unordered_map<int, std::move_only_function<void()>> UIF;
  bool A = IdleTasks.contains(nullptr);
  bool B = ListeningPorts.contains(0);
  bool C = UListeningPorts.contains(0);
  std::span<bool> SpanBool(&A, 1);
  UIF[1] = []() {};
  std::queue<std::move_only_function<void()>> QF;
  QF.emplace([]() {});
  QF.pop();
#if __cpp_exceptions
  try {
    throw 0;
  } catch (int E) {}
#endif
#ifdef __cpp_deduction_guides
  std::move_only_function DeductionTest([]() {});
#endif
  PointerSet.contains(nullptr);
  struct TestStruct {
    int A;
    int B;
    constexpr TestStruct(int A, int B)
      : A(A), B(B) {}
  };
  std::vector<TestStruct> TestVector;
  TestVector.emplace_back(1, 1);
}
void Functional();
extern std::unique_ptr<char[]> UPI;
void Span(char C);
void MapSet();
void String();
void Mutex();
void Iterator();
void Set();

void loop() {
  FF();
  Functional();
  Span(UPI[0]);
  MapSet();
  String();
  Mutex();
  Iterator();
  Set();
}
