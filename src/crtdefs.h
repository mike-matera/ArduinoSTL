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