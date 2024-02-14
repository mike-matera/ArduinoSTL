#include <serstream>
_STD_BEGIN

__PURE_APPDOMAIN_GLOBAL static wserialbuf wfin(Serial);
#if defined(_M_CEE_PURE)
__PURE_APPDOMAIN_GLOBAL extern wistream wcin(&wfin);
#else
__PURE_APPDOMAIN_GLOBAL extern _CRTDATA2_IMPORT wistream wcin(&wfin);
#endif
// 23
_STD_END