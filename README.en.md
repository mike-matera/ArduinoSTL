[README.en.md](README.en.md)

because[Original ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)The author has not updated it for a long time (202203~202212). I released this branch to the Arduino public library and renamed it Cpp_Standard_Library to distinguish it.

本库试图在Arduino上实现C++11~17标准库（STL）的大部分功能。除了ArduinoSTL以外，本库部分功能实现还参考了MSVC、LLVM和boost。因为是按照STL做的接口，所以不需要另外撰写文档，你可以参考任何一个权威的STL文档。除非另有说明，否则本库的使用方法应该是一样的，如果不一样那应该就是个bug，欢迎提交Issue。

If you need some functions that are included in the standard library but are not provided in this library, you are welcome to submit an Issue, and the author will implement it for you first.

Currently supported architecture:

-   AVR, requires C++17. need to change`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\avr\*.*.*\platform.txt`neutral`-std=gnu++11`for`-std=gnu++17`
-   SAM, requires C++11
-   ESP32, requires C++17. need to change`%LOCALAPPDATA%\Arduino15\packages\arduino\hardware\esp32\*.*.*\platform.txt`all in`-std=gnu++11`for`-std=gnu++17`

Before including any C++ standard header file, you must first include`Cpp_Standard_Library.h`. This is a prompt to the Arduino IDE, telling the compiler that this library must be included in the compilation process.

# Signature functions (not limited to this)

-   `<algorithm> fill_n shuffle`
-   `<chrono> chrono::duration`
-   `<functional> std::function`
-   `<iostream> cin cout endl`Use the serial port as the standard input and output stream. However, users still need to manually call`Serial.begin`, considering that the serial port may not be connected or the baud rate is not 9600.
-   `<map>`
-   `<memory> unique_ptr make_unique`
-   `<random>`，`mt19937`It takes up a lot of memory (about 5K), so use it with caution.`ArduinoUrng`is Arduino platform specific`UniformRandomNumberGenerator`,Can be used as`shuffle`, which is a software pseudo-random generator and needs to set a random seed. The ESP32 architecture also additionally supports`EspUrng`, is a hardware true random generator and does not support setting seeds.
-   `<ratio>`
-   `<set>`
-   `<type_traits>`
-   `<vector>`
-   `std::begin std::end`
-   If the compiler comes with some standard library function with the same name, the version that comes with it will take precedence. The compiler may ship with other standard library features that are not provided by this library, and those features do not conflict with this library.

Remember to check out the sample project after installation!

# Original README (for reference only, some contents are outdated)

This is an implementation of a C++ standard library packaged as an Arduino library. The library supports teaching my CS-11M class by adding key C++ features into the Arduino environment.

The library is ported from uClibc++:

<http://git.uclibc.org/uClibc++>

With a streams implementation from Andy Brown's Arduino Library:

<http://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/>

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

## Using`cin`an`cout`

When you include this header file you automatically get cin and cout based on`Serial`. See below for how to specify your own device. Here's an example sketch using`cin`and`cout`.

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

You can change what serial port that`cin`,`cout`and`printf()`use. You can use built-in serial ports (e.g.`Serial1`on Leonardo) or you can use software serial ports that implement`Stream`.

### Using a Built-in Port

In`src/ArduinoSTL.cpp`change the value of`ARDUINOSTL_DEFAULT_SERIAL`. Leave the other defaults uncommented.

### Using a SoftwareSerial port.

Set`ARDUINO_DEFAULT_SERAL`to`NULL`. Comment out the other defaults.

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

## Avoiding Instantiation of `cin`and`cout`

Comment out`ARDUINOSTL_DEFAULT_CIN_COUT`and nothing will be instantiated. You must comment out this flag if you intend to select a non-default serial port. There's no appreciable overhead for using`printf()`so you cannot currently avoid initializing it.

## Known Issues

Printing of floats and doubles using`cout`ignores format specifiers.

uClibc seems to be fairly complete. Strings and vectors both work, even with the limited amount of heap available to Arduino. The uClibc++ status page can be found here:

<https://cxx.uclibc.org/status.html>

Always use the latest Arduino IDE. This library uses the Arduino IDE Library Specification rev.2.1 with features only available on Arduino 1.6.10 and higher. The specification can be found here:

<https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification>

## License

The uClibc++ library is licensed under the LGPL. This project adopts the LGPL to be compatible with the bulk of the code that it uses. Unless otherwise noted all code is licensed under the LGPL. There's one exception:

-   src/serstream is licensed under the BSD license according to Andy Brown's wishes here:<http://andybrown.me.uk/terms-and-conditions/>
