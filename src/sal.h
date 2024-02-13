#pragma once
//2895
#ifndef _Analysis_assume_ // [
#ifdef _PREFAST_ // [
#define _Analysis_assume_(expr) __assume(expr)
#else // ][
#define _Analysis_assume_(expr)
#endif // ]
#endif // ]
//2903