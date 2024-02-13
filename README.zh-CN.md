因[原版ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)作者长期不更新（202203~202212），本人将此分支发布到Arduino公开库，改名为Cpp_Standard_Library以示区分。

本库试图在Arduino上实现C++11~17标准库（STL）的大部分功能。除了ArduinoSTL以外，本库部分功能实现还参考了MSVC、LLVM和boost。因为是按照STL做的接口，所以不需要另外撰写文档，你可以参考任何一个权威的STL文档。除非另有说明，否则本库的使用方法应该是一样的，如果不一样那应该就是个bug，欢迎提交Issue。

如果你需要某些标准库中应有而本库中尚未提供的功能，也欢迎提交Issue，作者将会优先为你实现。

目前支持AVR和SAM架构。暂时没有支持ESP32的计划，因为ESP32官方已经提供了标准库，同时使用两套标准库将产生很多难以处理的问题。

# 招牌功能（不限于此）

-   `<algorithm> fill_n shuffle`
-   `<chrono> chrono::duration`
-   `<iostream> cin cout`使用串口作为标准输入输出流
-   `<map>`
-   `<memory> unique_ptr`
-   `<random> mt19937, ArduinoUrng`：`mt19937`占内存较多（约5K），谨慎使用。`ArduinoUrng`是Arduino平台特定的`UniformRandomNumberGenerator`，可用于`shuffle`。
-   `<ratio>`
-   `<set>`
-   `<type_traits>`
-   `<vector>`
-   `<xutility> std::begin std::end`

# 原版README（仅供参考，部分内容已过时）

这是封装为 Arduino 库的 C++ 标准库的实现。该库通过将关键的 C++ 功能添加到 Arduino 环境中来支持我的 CS-11M 课程的教学。

该库是从 uClibc++ 移植的：

[HTTP://git.UC里保存.org/UC里保存++](http://git.uclibc.org/uClibc++)

使用 Andy Brown 的 Arduino 库的流实现：

<http://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/>

## 使用 printf() 和 scanf()

ArduinoSTL 头文件包含将您选择的串行端口绑定到的代码
stdio 原语。这会自动发生，但用户仍然必须调用
串行.begin()

```c++
#include <ArduinoSTL.h>

void setup() {
  Serial.begin(9600); 
  printf("Hello World\n");
}
```

## 使用`cin`一个`cout`

当您包含此头文件时，您将自动获得 cin 和 cout 基于`Serial`。请参阅下文了解如何指定您自己的设备。这是一个使用示例草图`cin`和`cout`.

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

## 更改串口

您可以更改串口`cin`,`cout`和`printf()`使用。您可以使用内置串行端口（例如`Serial1`在 Leonardo 上）或者您可以使用软件串行端口来实现`Stream`.

### 使用内置端口

在`src/ArduinoSTL.cpp`改变的值`ARDUINOSTL_DEFAULT_SERIAL`。保留其他默认值不注释。

### 使用软件串行端口。

放`ARDUINO_DEFAULT_SERAL`到`NULL`。注释掉其他默认值。

以下是使用 SofwareSerial 的示例草图：

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

## 避免实例化`cin`和`cout`

注释掉`ARDUINOSTL_DEFAULT_CIN_COUT`并且什么都不会被实例化。如果您打算选择非默认串行端口，则必须注释掉该标志。使用时没有明显的开销`printf()`所以你目前无法避免初始化它。

## 已知的问题

使用打印浮点数和双精度数`cout`忽略格式说明符。

uClibc 似乎相当完整。即使 Arduino 可用的堆数量有限，字符串和向量都可以工作。 uClibc++ 状态页面可以在这里找到：

[HTTPS://持续性.UC里保存.org/status.HTML](https://cxx.uclibc.org/status.html)

始终使用最新的 Arduino IDE。该库使用 Arduino IDE 库规范 rev.2.1，其功能仅在 Arduino 1.6.10 及更高版本上可用。该规范可以在这里找到：

[HTTPS://GitHub.com/Arduino/Arduino/wiki/Arduino-IDE-1.5:-library-specification](https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification)

## 执照

uClibc++ 库根据 LGPL 获得许可。该项目采用 LGPL 与其使用的大部分代码兼容。除非另有说明，所有代码均根据 LGPL 获得许可。有一个例外：

-   根据 Andy Brown 的意愿，src/serstream 在 BSD 许可证下获得许可：[HTTP://Andy Brown.么.UK/terms-安定-conditions/](http://andybrown.me.uk/terms-and-conditions/)
