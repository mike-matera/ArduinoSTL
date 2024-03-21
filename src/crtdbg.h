#pragma once
// 24
#define _CRT_WARN 0
#define _CRT_ERROR 1
#define _CRT_ASSERT 2
#define _CRT_ERRCNT 3
// 29
// 693
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//  Assertions and Error Reporting Macros
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#ifndef _DEBUG

#define _CrtDbgBreak() ((void)0)

#ifndef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, msg) ((void)0)
#endif

#ifndef _ASSERT
#define _ASSERT(expr) ((void)0)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr) ((void)0)
#endif

#define _RPT0(rptno, msg)
#define _RPTN(rptno, msg, ...)

#define _RPTW0(rptno, msg)
#define _RPTWN(rptno, msg, ...)

#define _RPTF0(rptno, msg)
#define _RPTFN(rptno, msg, ...)

#define _RPTFW0(rptno, msg)
#define _RPTFWN(rptno, msg, ...)

#else // ^^^ !_DEBUG ^^^ // vvv _DEBUG vvv //

#define _CrtDbgBreak() //Arduino不支持 __debugbreak()

// !! is used to ensure that any overloaded operators used to evaluate expr
// do not end up at &&.
#ifndef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, msg) /*Arduino不支持                                                  \
	 (void)((!!(expr)) ||                                                                           \
			(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, L"%ls", msg)) || \
			(_CrtDbgBreak(), 0))*/
#endif

#ifndef _ASSERT
#define _ASSERT(expr) _ASSERT_EXPR((expr), NULL)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr) _ASSERT_EXPR((expr), _CRT_WIDE(#expr))
#endif

#define _RPT_BASE(...) /*Arduino不支持                          \
	(void)((1 != _CrtDbgReport(__VA_ARGS__)) || \
		   (_CrtDbgBreak(), 0))*/

#define _RPT_BASE_W(...) /*Arduino不支持                         \
	(void)((1 != _CrtDbgReportW(__VA_ARGS__)) || \
		   (_CrtDbgBreak(), 0))*/

#define _RPT0(rptno, msg) _RPT_BASE(rptno, NULL, 0, NULL, "%s", msg)
#define _RPTN(rptno, msg, ...) _RPT_BASE(rptno, NULL, 0, NULL, msg, __VA_ARGS__)

#define _RPTW0(rptno, msg) _RPT_BASE_W(rptno, NULL, 0, NULL, L"%ls", msg)
#define _RPTWN(rptno, msg, ...) _RPT_BASE_W(rptno, NULL, 0, NULL, msg, __VA_ARGS__)

#define _RPTF0(rptno, msg) _RPT_BASE(rptno, __FILE__, __LINE__, NULL, "%s", msg)
#define _RPTFN(rptno, msg, ...) _RPT_BASE(rptno, __FILE__, __LINE__, NULL, msg, __VA_ARGS__)

#define _RPTFW0(rptno, msg) _RPT_BASE_W(rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, L"%ls", msg)
#define _RPTFWN(rptno, msg, ...) _RPT_BASE_W(rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, __VA_ARGS__)

#endif // _DEBUG
	   // 771