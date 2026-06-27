因[原版ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)作者长期不更新（上次更新是2022年），本人将此分支发布到Arduino公开库，改名为Cpp_Standard_Library以示区分。

本库试图在Arduino上实现C++11\~17标准库（STL）的大部分功能，并尝试实现了C++20\~23的部分常用功能。除了ArduinoSTL以外，本库部分功能实现还参考了GCC（为主）和boost。因为是按照STL做的接口，所以不需要另外撰写文档，你可以参考任何一个权威的STL文档。除非另有说明，否则本库的使用方法应该是一样的，如果不一样那应该就是个bug，欢迎提交Issue。

如果你需要某些标准库中应有而本库中尚未提供的功能（即使是比C++17更新的功能也无妨），也欢迎提交Issue，作者将会优先为你实现。

支持以下架构：
- AVR，但要求C++17：需要更改`<Arduino数据目录>\packages\arduino\hardware\avr\*.*.*\platform.txt`中的`-std=gnu++11`为`-std=gnu++17`。其中<Arduino数据目录>在Windows上通常是`%LOCALAPPDATA%\Arduino15`，在Linux上通常是`~/.arduino15`
- SAM
- ESP32（by Espressif Systems, not Arduino）

对于SAM和ESP32架构，如欲使用C++标准异常处理和运行时类型识别（RTTI, typeid），还需要确保编译选项包含-fexceptions且不含-fno-rtti。AVR架构不支持异常处理，设置-fexceptions或使用try关键词将导致未定义行为。

在包含任何C++标准头文件之前，必须先`#include <Cpp_Standard_Library.h>`。这是对 Arduino IDE 的提示，告诉编译器必须要将本库纳入编译流程。
# 招牌功能（不限于此）
- `<algorithm> fill_n shuffle`
- `<chrono> chrono::duration`
- `<cmath> log2`
- `<concepts>` 注意C++20之前并不真正支持concept。此头文件允许你以 constexpr bool 变量模板（C++17）或函数模板（C++11）形式访问C++标准concepts。
- `<dynarray>` 曾经有望进入C++标准的废案。虽然最终没能进入，但作为`array`和`vector`的中间类型非常有用。
- `<functional>` 非标准行为：调用空对象时不做任何事。这是因为标准行为是应当抛出异常，但Arduino不支持异常。如果希望调用空对象时不做任何事，则可无需判断对象是否为空而直接调用。
- `<iostream> cin cout endl`使用`Serial`实现标准输入输出流。但是，使用前仍必须手动`Serial.begin`以设置波特率。不应在`setup`函数之前的全局变量初始化阶段使用`Serial`，因为在`setup`被调用之前无法保证`Serial`已完成初始化，此时使用`Serial`是未定义行为。此外测试发现，对于SAM架构，串口刚完成初始化后可能会发送一些随机字节，这似乎是硬件设计缺陷使然，软件层面无法解决，接收端必须要考虑到这个问题。字符写入串口依赖中断，禁用中断的上下文中所有字符将被缓存，待启用中断上下文后才会实际写出到串口。支持使用F宏的Flash字符串。
- `<map>` `map::contains` `map::erase`
- `<memory> unique_ptr make_unique shared_ptr make_unique_for_overwrite`
- `<mutex>` 注意Arduino并不真正支持多线程，因此只能检查互斥锁是否被占用，如果被占就必须放弃，而不能等待
- `<optional>`
- `<random>` `ArduinoUrng`是Arduino平台特定的`UniformRandomNumberGenerator`，可用于`shuffle`，属于软件伪随机生成器，需要设置随机种子。ESP32和SAM架构还额外支持`TrueUrng`，是硬件真随机生成器，不支持设置种子。
- `<ratio>`
- `<set>` `set::contains` `set::erase` `set::merge`
- `<span>`
- `<string>` `string::resize_and_overwrite`
- `<tuple>`
- `<type_traits>`
- `<unordered_map>` `unordered_map::contains` `unordered_map::erase`
- `<unordered_set>` `unordered_set::contains` `unordered_set::erase`
- `<vector>`
- `std::begin std::end`
- `<string>` `string::resize_and_overwrite`
- 如果编译器随附了某些重名的标准库功能，将优先使用随附的版本。编译器可能还随附了本库未提供的其它标准库功能，那些功能也不会与本库冲突。
- （AVR不支持）C++标准异常处理和RTTI。要使用此功能，请确保编译选项（在platform.txt中设置）包含-fexceptions且不含-fno-rtti。异常处理代码依赖RTTI，因此不能在关闭RTTI的情况下使用异常处理。

安装后记得查看示例项目！
