#pragma once
// 此头文件用于标识本库已被包含，并提示编译器应当编译本库中的源文件。请按需包含具体的功能头文件。
#define _DEBUG 1
#define __STDCPP_DEFAULT_NEW_ALIGNMENT__ (size_t)16
#define __cpp_sized_deallocation

//Arduino不支持#include_next，只能用这种魔法实现包含官方标准库
#ifdef ARDUINO_ARCH_AVR
#define CSL_Official(Header) <Arduino.h/../../arduino/Header>
#endif
#ifdef ARDUINO_ARCH_SAM
#define CSL_Official(Header) <cxxabi.h/../../__GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__/Header>
#endif