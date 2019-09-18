#include <ArduinoSTL.h>
#include <Arduino.h>

//
// ## Serial Port & In/Out Configurations
//
// If you're using an Arduino device that provides more than a single
// serial port, (such as the Mega, Uno, or any other boards listed at
// arduino.cc/reference/en/language/functions/communication/serial/),
// and your project requires use of a non-default serial port (one of
// Serial1, Serial2, or Serial3, instead of the default "Serial"), OR
// if you're using an Arduino device that statically declares a non-
// standard serial port (such as the Leonardo's "Serial1" use), then
// perform the following steps to adjust the serial port used for the
// streams implementation of this library:
//
//   1. Define ARDUINOSTL_DEFAULT_SERIAL to an available serial port
//      of your choice (one of Serial, Serial1, Serial2, or Serial3),
//      to assign the port used in this library's output and streams
//      implementation.
//
//   2. Define ARDUINOSTL_DEFAULT_CIN_COUT to "true" to initialize
//      the "cin" and "cout" behavior.
//
// E.g. To use "Serial2" as your serial port AND enable instantiation
// of serial-aware implementations of "cin" and "cout" you would use:
//
//   >  // assign the serial port used for output to "Serial2"
//   >  #define ARDUINOSTL_DEFAULT_SERIAL Serial2
//   >
//   >  // enable "cin"/"cout" behavior by defining macro to "true"
//   >  #define ARDUINOSTL_DEFAULT_CIN_COUT true
//   >
//   >  // include this library only after the above, prior config
//   >  #include <ArduinoSTL.h>
//
// ## Disabling Functionality / SoftwareSerial Usage
//
// Alternatively, if you're project requires disabling one or both
// of these features, (for example to use SoftwareSerial instead of
// the provided hardware serial pins), you can easily disable both
// items selectively by following the below steps:
//
//   1. Define ARDUINOSTL_DISABLE_SERIAL to "true" to DISABLE serial
//      output handling of printf and related functions.
//
//   2. Define ARDUINOSTL_DISABLE_CIN_COUT to "true" to DISABLE auto
//      instantiation of "cin" and "cout" for serial output use.
//
// E.g. To utalize your own SoftwareSerial object instance with this
//      library, you would use:
//
//   >  // disable setup of serial output handling by this lib
//   >  #define ARDUINOSTL_DISABLE_SERIAL true
//   >
//   >  // disable setup of "cin"/"cout" stream behavior by this lib
//   >  #define ARDUINOSTL_DISABLE_CIN_COUT true
//   >
//   >  // include this library only after the above, prior config
//   >  #include <ArduinoSTL.h>
//   >
//   >  // include the external SerialSoftware dependency
//   >  #include <SoftwareSerial.h>
//   >
//   >  // create instance of SoftwareSerial on pins P_RX and P_TX
//   >  SoftwareSerial mySoftwareSerial(P_RX, P_TX);
//   >
//   >  // setup "cin"/"cout" by instantiating with your serial obj
//   >  namespace std {
//   >    ohserialstream cout(mySoftwareSerial);
//   >    ihserialstream cin(mySoftwareSerial);
//   >  };
//   >
//   >  // setup serial streaming by instantiating with your serial obj
//   >  ArduinoSTL_serial.connect(mySoftwareSerial);
//
// NOTE: Defining ARDUINOSTL_DISABLE_CIN_COUT does not implicate the
//       state of ARDUINOSTL_DISABLE_SERIAL, BUT defining the latter
//       automatically disabled the former (as serial-based "cin" and
//       "cout" handling cannot be setup without a serial port).
//

#if defined ARDUINOSTL_DISABLE_SERIAL && ARDUINOSTL_DISABLE_SERIAL == true
    #undef ARDUINOSTL_DEFAULT_SERIAL // avoid warnings about double assigs
    #define ARDUINOSTL_DEFAULT_SERIAL NULL
#elif ! defined ARDUINOSTL_DEFAULT_SERIAL
    #define ARDUINOSTL_DEFAULT_SERIAL Serial
#endif

#if (defined ARDUINOSTL_DISABLE_SERIAL && ARDUINOSTL_DISABLE_SERIAL == true) \
 || (defined ARDUINOSTL_DISABLE_CIN_COUT && ARDUINOSTL_DISABLE_CIN_COUT == true)
    #undef ARDUINOSTL_DEFAULT_CIN_COUT
#elif ! defined ARDUINOSTL_DEFAULT_CIN_COUT
    #define ARDUINOSTL_DEFAULT_CIN_COUT true
#endif

using namespace std;

#ifdef ARDUINOSTL_DEFAULT_CIN_COUT
// Create cout and cin.. there doesn't seem to be a way
// to control what serial device at runtime. Grr.
namespace std
{
  ohserialstream cout(ARDUINOSTL_DEFAULT_SERIAL);
  ihserialstream cin(ARDUINOSTL_DEFAULT_SERIAL);
}
#endif // ARDUINOSTL_DEFAULT_CIN_COUT

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

ArduinoSTL_STDIO ArduinoSTL_Serial(ARDUINOSTL_DEFAULT_SERIAL);

// arduino_putchar(char, FILE*)
//   Output a single character to the serial port.
//   returns: 0 on success, 1 on error
//   note:
//     To maintain serial port compatibility this function
//     automatically addes a \r when it sees a \n
//
static int arduino_putchar(char c, FILE* f) {
  Stream *uart = ArduinoSTL_Serial.getUart();
  if (c == '\n') uart->write('\r');
  return uart->write(c) == 1? 0 : 1;
}

// arduino_getchar(FILE*)
//   Take a character from the serial port. This function
//   must block until a character is ready.
//   returns: The character or -1 on a read error
//
static int arduino_getchar(FILE *f) {
  Stream *uart = ArduinoSTL_Serial.getUart();
  while (! uart->available()) { /* wait */ }
  return uart->read();
}

void ArduinoSTL_STDIO::connect(Stream *u) {
  if (file != NULL)
    free (file);
  uart = u;
  file = fdevopen(arduino_putchar, arduino_getchar);
}

#else
#warning "printf() will not be functional on this platform."
#endif
