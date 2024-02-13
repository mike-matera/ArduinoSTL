because[Original ArduinoSTL](https://github.com/mike-matera/ArduinoSTL)The author has not updated it for a long time (202203~202212). I released this branch to the Arduino public library and renamed it Cpp_Standard_Library to distinguish it.

This library attempts to implement most of the functions of the C++11~17 Standard Library (STL) on Arduino. In addition to ArduinoSTL, some functions of this library also refer to MSVC, LLVM and boost. Because the interface is based on STL, there is no need to write additional documents. You can refer to any authoritative STL document. Unless otherwise stated, the usage of this library should be the same. If it is different, it should be a bug. You are welcome to submit an issue.

If you need some functions that are in the standard library but are not provided in this library, you are also welcome to submit an Issue, and the author will implement it for you first.

Currently supports AVR and SAM architectures. There are currently no plans to support ESP32, because ESP32 has officially provided a standard library, and using two sets of standard libraries at the same time will cause many problems that are difficult to deal with.

Before including any C++ standard header file, you must first include`Cpp_Standard_Library.h`. This is a prompt to the Arduino IDE, telling the compiler that this library must be included in the compilation process.

# Signature functions (not limited to this)

-   `<algorithm> fill_n shuffle`
-   `<chrono> chrono::duration`
-   `<iostream> cin cout`Use the serial port as the standard input and output stream
-   `<map>`
-   `<memory> unique_ptr`
-   `<random> mt19937, ArduinoUrng`：`mt19937`It takes up a lot of memory (about 5K), so use it with caution.`ArduinoUrng`is Arduino platform specific`UniformRandomNumberGenerator`,Can be used as`shuffle`。
-   `<ratio>`
-   `<set>`
-   `<type_traits>`
-   `<vector>`
-   `<xutility> std::begin std::end`

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

You can change what serial port that`cin`, `cout` and `printf()`use. You can use built-in serial ports (e.g.`Serial1`on Leonardo) or you can use software serial ports that implement`Stream`.

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

## Avoiding Instantiation of`cin`and`cout`

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
