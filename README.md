[README.en.md](README.en.md)

因[原版ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)作者长期不更新（202203~202212），本人将此分支发布到Arduino公开库，改名为Cpp_Standard_Library以示区分。

本库试图在Arduino上实现C++11~17标准库（STL）的大部分功能。除了ArduinoSTL以外，本库部分功能实现还参考了MSVC、LLVM、boost和GCC。因为是按照STL做的接口，所以不需要另外撰写文档，你可以参考任何一个权威的STL文档。除非另有说明，否则本库的使用方法应该是一样的，如果不一样那应该就是个bug，欢迎提交Issue。

如果你需要某些标准库中应有而本库中尚未提供的功能，也欢迎提交Issue，作者将会优先为你实现。

支持以下架构，但需要额外配置：
- AVR，要求C++17。需要更改`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\avr\*.*.*\platform.txt`中的`-std=gnu++11`为`-std=gnu++17`
- SAM，要求C++11。需要在`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\sam\*.*.*\platform.txt`中的`compiler.cpp.flags`中添加`-fpermissive`旗帜
- ESP32，要求C++17。需要更改`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\esp32\*.*.*\platform.txt`中的所有`-std=gnu++11`为`-std=gnu++17`，并在`compiler.cpp.flags`中添加`-fpermissive`旗帜

在包含任何C++标准头文件之前，必须先包含`Cpp_Standard_Library.h`。这是对 Arduino IDE 的提示，告诉编译器必须要将本库纳入编译流程。
# 招牌功能（不限于此）
- `<algorithm> fill_n shuffle`
- `<chrono> chrono::duration`
- `<functional> std::function` 非标准行为：调用空对象时不做任何事。这是因为标准行为是应当抛出异常，但Arduino不支持异常。如果希望调用空对象时不做任何事，则可无需判断对象是否为空而直接调用。
- `<iostream> cin cout endl` 使用`Serial`实现标准输入输出流。但是，使用前仍必须手动`Serial.begin`。不应在`setup`函数之前的全局变量初始化阶段使用`Serial`，因为在`setup`被调用之前无法保证`Serial`已完成初始化，此时使用`Serial`是未定义行为。此外测试发现，对于SAM架构，串口刚完成初始化后可能会发送一些随机字节，这似乎是硬件设计缺陷使然，软件层面无法解决，接收端必须要考虑到这个问题。
- `<map>`
- `<memory> unique_ptr make_unique`
- `<random>`，`mt19937`占内存较多（约5K），谨慎使用。`ArduinoUrng`是Arduino平台特定的`UniformRandomNumberGenerator`，可用于`shuffle`，属于软件伪随机生成器，需要设置随机种子。ESP32架构还额外支持`EspUrng`，是硬件真随机生成器，不支持设置种子。
- `<ratio>`
- `<set>`
- `<type_traits>`
- `<vector>`
- `std::begin std::end`
- 如果编译器随附了某些重名的标准库功能，将优先使用随附的版本。编译器可能还随附了本库未提供的其它标准库功能，那些功能也不会与本库冲突。

安装后记得查看示例项目！
# 原版README（仅供参考，部分内容已过时）

This is an implementation of a C++ standard library packaged as an Arduino library. The library supports teaching my CS-11M class by adding key C++ features into the Arduino environment. 

The library is ported from uClibc++:

http://git.uclibc.org/uClibc++

With a streams implementation from Andy Brown's Arduino Library: 

http://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/


## Using printf() and scanf()
The ArduinoSTL header file contains code to bind a serial port of your choice to
the stdio primitives. This happens automatically but the user must still call
Serial.begin()

```c++
#include <ArduinoSTL.h>

void setup() {
  Serial.begin(9600); 
  printf("Hello World\n");
}
```

## Using ```cin``` an ```cout```
When you include this header file you automatically get cin and cout based on ```Serial```. See below for how to specify your own device. Here's an example sketch using ```cin``` and ```cout``` .

```c++
#include <ArduinoSTL.h>

using namespace std;

void setup() {
  Serial.begin(9600);
  cout << "Feed me an integers." << endl;
}

void loop() {
  int foo;
  if (cin >> foo) { 
    cout << "You fed me " << foo << endl;
  }else{
    cin.clear();
    cin.ignore();
  }
}
```
## Changing the Serial Port 
You can change what serial port that ```cin```, ```cout``` and ```printf()``` use. You can use built-in serial ports (e.g. ```Serial1``` on Leonardo) or you can use software serial ports that implement ```Stream```. 

### Using a Built-in Port 
In ```src/ArduinoSTL.cpp``` change the value of ```ARDUINOSTL_DEFAULT_SERIAL```. Leave the other defaults uncommented. 

### Using a SoftwareSerial port. 
Set ```ARDUINO_DEFAULT_SERAL``` to ```NULL```. Comment out the other defaults. 

Here's an example sketch that uses SofwareSerial:

```c++
#include <ArduinoSTL.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1);

namespace std { 
  ohserialstream cout(mySerial);
  ihserialstream cin(mySerial);
}

void setup() {
  mySerial.begin(9600);
  ArduinoSTL_Serial.connect(mySerial);
}
```

## Avoiding Instantiation of ```cin``` and ```cout```
Comment out ```ARDUINOSTL_DEFAULT_CIN_COUT``` and nothing will be instantiated. You must comment out this flag if you intend to select a non-default serial port. There's no appreciable overhead for using ```printf()``` so you cannot currently avoid initializaing it.

## Known Issues

Printing of floats and doubles using ```cout``` ignores format specifiers. 

uClibc seems to be fairly complete. Strings and vectors both work, even with the limited amount of heap available to Arduino. The uClibc++ status page can be found here: 

https://cxx.uclibc.org/status.html

Always use the latest Arduino IDE. This library uses the Arduino IDE Library Specification rev.2.1 with features only available on Arduino 1.6.10 and higher. The specification can be found here:

https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification

## License

The uClibc++ library is licensed under the LGPL. This project adopts the LGPL to be compatible with the bulk of the code that it uses. Unless otherwise noted all code is licensed under the LGPL. There's one exception: 

  - src/serstream is licensed under the BSD license according to Andy Brown's wishes here: http://andybrown.me.uk/terms-and-conditions/
