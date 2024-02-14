#include "serstream"
#ifndef ARDUINO_ARCH_AVR
#include "yvals_core.h"
#include "yvals.h"
#include "iosfwd"
#include <Arduino.h>
#endif
_STD_BEGIN

__PURE_APPDOMAIN_GLOBAL static wserialbuf wfout(Serial);
#if defined(_M_CEE_PURE)
__PURE_APPDOMAIN_GLOBAL extern wostream wcout(&wfout);
#else
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2_IMPORT wostream wcout(&wfout);
#endif
// 23
_STD_END