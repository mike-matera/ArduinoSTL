#ifdef ARDUINO_ARCH_AVR
// 埃博拉酱实现
#include <stdint.h>
#include <stddef.h>
size_t _CSL_u64_dec(uint64_t u64, char *OutChar)
{
	if (u64)
	{
		char *Tail = OutChar;
		do
			*Tail++ = u64 % 10 + '0';
		while (u64 /= 10);
		const size_t Length = Tail - OutChar;
		while (OutChar < --Tail)
		{
			char Temp = *OutChar;
			*OutChar++ = *Tail;
			*Tail = Temp;
		}
		return Length;
	}
	else
	{
		*OutChar = '0';
		return 1;
	}
}
size_t _CSL_u64_oct(uint64_t u64, char *OutChar)
{
	if (u64)
	{
		char *Tail = OutChar;
		do
			*Tail++ = u64 & 07 + '0';
		while (u64 >>= 3);
		const size_t Length = Tail - OutChar;
		while (OutChar < --Tail)
		{
			char Temp = *OutChar;
			*OutChar++ = *Tail;
			*Tail = Temp;
		}
		return Length;
	}
	else
	{
		*OutChar = '0';
		return 1;
	}
}
size_t _CSL_u64_hex(uint64_t u64, char *OutChar, const char *Hex)
{
	if (u64)
	{
		char *Tail = OutChar;
		do
			*Tail++ = Hex[u64 & 0xf];
		while (u64 >>= 4);
		const size_t Length = Tail - OutChar;
		while (OutChar < --Tail)
		{
			char Temp = *OutChar;
			*OutChar++ = *Tail;
			*Tail = Temp;
		}
		return Length;
	}
	else
	{
		*OutChar = '0';
		return 1;
	}
}
#endif