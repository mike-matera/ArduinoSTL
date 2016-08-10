# ArduinoSTL
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

## Using cin an cout
When you include this header file you automatically get cin and cout based on Serial. There isn't yet a way to select you own device at runtime. Using cin and cout is 

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

## Known Issues

Printing of floats and doubles using cout ignores format specifiers. 

uClibc seems to be fairly complete. Strings and vectors both work, even with the limited amount of heap available to Arduino. The uClibc++ status page can be found here: 

https://cxx.uclibc.org/status.html

Always use the latest Arduino IDE. This library uses the Arduino IDE Library Specification rev.2.1 with features only available on Arduino 1.6.10 and higher. The specification can be found here:

https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification
