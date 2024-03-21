#pragma once
// 13
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  CRT DLL Export/Import Macros
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  used to annotate symbols exported from msvcp140
#ifndef _CRTIMP2
#if defined CRTDLL2 && defined _CRTBLD
#define _CRTIMP2 __declspec(dllexport)
#else
#define _CRTIMP2
#endif
#endif
// 27
// 73
#ifndef _MRTIMP2
#if defined CRTDLL2 && defined _CRTBLD
#define _MRTIMP2 __declspec(dllexport)
#elif defined MRTDLL && defined _CRTBLD
#define _MRTIMP2 _MRTIMP
#else
#define _MRTIMP2
#endif
#endif