#ifdef ARDUINO_ARCH_SAM
#include <HardwareSerial.h>
void HardwareSerial::begin(unsigned long) {}
void HardwareSerial::end() {}
#endif