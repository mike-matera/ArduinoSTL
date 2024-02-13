[README.en.md](README.en.md)

因[原版ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)作者长期不更新（202203~202212），本人将此分支发布到Arduino公开库，改名为Cpp_Standard_Library以示区分。

本库试图在Arduino上实现C++11~17标准库（STL）的大部分功能。除了ArduinoSTL以外，本库部分功能实现还参考了MSVC、LLVM和boost。因为是按照STL做的接口，所以不需要另外撰写文档，你可以参考任何一个权威的STL文档。除非另有说明，否则本库的使用方法应该是一样的，如果不一样那应该就是个bug，欢迎提交Issue。

如果你需要某些标准库中应有而本库中尚未提供的功能，也欢迎提交Issue，作者将会优先为你实现。

目前支持AVR和SAM架构。暂时没有支持ESP32的计划，因为ESP32官方已经提供了标准库，同时使用两套标准库将产生很多难以处理的问题。

在包含任何C++标准头文件之前，必须先包含`Cpp_Standard_Library.h`。这是对 Arduino IDE 的提示，告诉编译器必须要将本库纳入编译流程。
# 招牌功能（不限于此）
- `<algorithm> fill_n shuffle`
- `<chrono> chrono::duration`
- `<iostream> cin cout` 使用串口作为标准输入输出流
- `<map>`
- `<memory> unique_ptr`
- `<random> mt19937, ArduinoUrng`：`mt19937`占内存较多（约5K），谨慎使用。`ArduinoUrng`是Arduino平台特定的`UniformRandomNumberGenerator`，可用于`shuffle`。
- `<ratio>`
- `<set>`
- `<type_traits>`
- `<vector>`
- `<xutility> std::begin std::end`
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
