#pragma once
// 此头文件用于标识本库已被包含，并提示编译器应当编译本库中的源文件。请按需包含具体的功能头文件。

//Arduino for Linux 对此宏的支持存在问题。如出现相关错误需一律改用#include_next。此宏仅用于处理SAM架构上@include_next<new>失败的问题。
#ifdef ARDUINO_ARCH_AVR
#define _CSL_Official(Header) <Arduino.h/../../arduino/Header>
#define _CSL_OfficialC(Header) <alloca.h/../../include/Header>
#else
#define _CSL_Official(Header) <c++/__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__/Header>
#define _CSL_OfficialC(Header) <_ansi.h/../../include/Header>
#endif
#define __GLIBC__ 2
#define __GLIBC_MINOR__ 39