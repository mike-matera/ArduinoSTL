/*---------------------
 * 
 * ArduinoSTL Core Library
 *
 * This header has some glue to make STL and Streams work from a sketch.
 * 
 */

#ifndef ARDUINOSTL_M_H
#define ARDUINOSTL_M_H

#include <serstream>

// Create cout and cin.. there doesn't seem to be a way
// to control what serial device at runtime. Grr.
namespace std
{
  extern ohserialstream cout;
  extern ihserialstream cin;
}

#endif
