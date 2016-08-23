#include <ArduinoSTL.h>
#include <Arduino.h>

using namespace std; 

// Create cout and cin.. there doesn't seem to be a way
// to control what serial device at runtime. Grr.
namespace std
{
  ohserialstream cout(Serial);
  ihserialstream cin(Serial);
}

/*
 * Implementation of printf() is highly libc dependent.
 *
 * This implementation is tested on:
 *
 *   ARDUINO_ARCH_AVR (Classic Arduinos) - Working
 *   TEENSYDUINO (ARM-based Teensy) - cin/cout work, printf doesn't
 *   ARDUINO_ARCH_* - ARMs are probably the same as above.
 */
#if defined(ARDUINO_ARCH_AVR)
//
// This is a hack to make C stdio work on "Serial" without
// having to be manually initialized. It works becuase I can
// call a constructor before setup(). 
//
class __Arduino_STDIO_hack {
public:
  __Arduino_STDIO_hack(Stream *u);
  Stream *getUart() {
    return uart;
  }
private:
  Stream *uart;
};

static __Arduino_STDIO_hack __stdio_wrapper(&Serial);

// arduino_putchar(char, FILE*) 
//   Output a single character to the serial port. 
//   returns: 0 on success, 1 on error
//   note:
//     To maintain serial port compatibility this function
//     automatically addes a \r when it sees a \n
// 
static int arduino_putchar(char c, FILE* f) {
  Stream *uart = __stdio_wrapper.getUart();
  if (c == '\n') uart->write('\r');
  return uart->write(c) == 1? 0 : 1;
}

// arduino_getchar(FILE*) 
//   Take a character from the serial port. This function
//   must block until a character is ready. 
//   returns: The character or -1 on a read error
//
static int arduino_getchar(FILE *f) {
  Stream *uart = __stdio_wrapper.getUart();
  while (! uart->available()) { /* wait */ }
  return uart->read();
}

// Initialize STDIO using a pointer to whatever Serial is. 
// Serial.begin() must be called at some point. 
//
__Arduino_STDIO_hack::__Arduino_STDIO_hack(Stream *u) {
  uart = u;
  fdevopen(arduino_putchar, arduino_getchar); 
}
#else
#warning "printf() will not be functional on this platform."
#endif
