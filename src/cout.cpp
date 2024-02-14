#include "serstream"
#ifndef ARDUINO_ARCH_AVR
#include "yvals_core.h"
#include "yvals.h"
#include "iosfwd"
#include <Arduino.h>
#endif
_STD_BEGIN

__PURE_APPDOMAIN_GLOBAL static serialbuf fout(Serial);

#if defined(_M_CEE_PURE)
__PURE_APPDOMAIN_GLOBAL extern ostream cout(&fout);

#else  // ^^^ defined(_M_CEE_PURE) / !defined(_M_CEE_PURE) vvv
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2_IMPORT ostream cout(&fout);
#endif // ^^^ !defined(_M_CEE_PURE) ^^^
// 25
_STD_END