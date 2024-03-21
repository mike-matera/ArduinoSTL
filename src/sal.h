/***
 *sal.h - markers for documenting the semantics of APIs
 *
 *       Copyright (c) Microsoft Corporation. All rights reserved.
 *
 *Purpose:
 *       sal.h provides a set of annotations to describe how a function uses its
 *       parameters - the assumptions it makes about them, and the guarantees it makes
 *       upon finishing.
 *
 *       [Public]
 *
 ****/
#pragma once

/*==========================================================================

   The comments in this file are intended to give basic understanding of
   the usage of SAL, the Microsoft Source Code Annotation Language.
   For more details, please see https://go.microsoft.com/fwlink/?LinkID=242134

   The macros are defined in 3 layers, plus the structural set:

   _In_/_Out_/_Ret_ Layer:
   ----------------------
   This layer provides the highest abstraction and its macros should be used
   in most cases. These macros typically start with:
	  _In_     : input parameter to a function, unmodified by called function
	  _Out_    : output parameter, written to by called function, pointed-to
				 location not expected to be initialized prior to call
	  _Outptr_ : like _Out_ when returned variable is a pointer type
				 (so param is pointer-to-pointer type). Called function
				 provides/allocated space.
	  _Outref_ : like _Outptr_, except param is reference-to-pointer type.
	  _Inout_  : inout parameter, read from and potentially modified by
				 called function.
	  _Ret_    : for return values
	  _Field_  : class/struct field invariants
   For common usage, this class of SAL provides the most concise annotations.
   Note that _In_/_Out_/_Inout_/_Outptr_ annotations are designed to be used
   with a parameter target. Using them with _At_ to specify non-parameter
   targets may yield unexpected results.

   This layer also includes a number of other properties that can be specified
   to extend the ability of code analysis, most notably:
	  -- Designating parameters as format strings for printf/scanf/scanf_s
	  -- Requesting stricter type checking for C enum parameters

   _Pre_/_Post_ Layer:
   ------------------
   The macros of this layer only should be used when there is no suitable macro
   in the _In_/_Out_ layer. Its macros start with _Pre_ or _Post_.
   This layer provides the most flexibility for annotations.

   Implementation Abstraction Layer:
   --------------------------------
   Macros from this layer should never be used directly. The layer only exists
   to hide the implementation of the annotation macros.

   Structural Layer:
   ----------------
   These annotations, like _At_ and _When_, are used with annotations from
   any of the other layers as modifiers, indicating exactly when and where
   the annotations apply.


   Common syntactic conventions:
   ----------------------------

   Usage:
   -----
   _In_, _Out_, _Inout_, _Pre_, _Post_, are for formal parameters.
   _Ret_, _Deref_ret_ must be used for return values.

   Nullness:
   --------
   If the parameter can be NULL as a precondition to the function, the
   annotation contains _opt. If the macro does not contain '_opt' the
   parameter cannot be NULL.

   If an out/inout parameter returns a null pointer as a postcondition, this is
   indicated by _Ret_maybenull_ or _result_maybenull_. If the macro is not
   of this form, then the result will not be NULL as a postcondition.
	 _Outptr_ - output value is not NULL
	 _Outptr_result_maybenull_ - output value might be NULL

   String Type:
   -----------
   _z: NullTerminated string
   for _In_ parameters the buffer must have the specified stringtype before the call
   for _Out_ parameters the buffer must have the specified stringtype after the call
   for _Inout_ parameters both conditions apply

   Extent Syntax:
   -------------
   Buffer sizes are expressed as element counts, unless the macro explicitly
   contains _byte_ or _bytes_. Some annotations specify two buffer sizes, in
   which case the second is used to indicate how much of the buffer is valid
   as a postcondition. This table outlines the precondition buffer allocation
   size, precondition number of valid elements, postcondition allocation size,
   and postcondition number of valid elements for representative buffer size
   annotations:
									 Pre    |  Pre    |  Post   |  Post
									 alloc  |  valid  |  alloc  |  valid
	  Annotation                     elems  |  elems  |  elems  |  elems
	  ----------                     ------------------------------------
	  _In_reads_(s)                    s    |   s     |   s     |   s
	  _Inout_updates_(s)               s    |   s     |   s     |   s
	  _Inout_updates_to_(s,c)          s    |   s     |   s     |   c
	  _Out_writes_(s)                  s    |   0     |   s     |   s
	  _Out_writes_to_(s,c)             s    |   0     |   s     |   c
	  _Outptr_result_buffer_(s)        ?    |   ?     |   s     |   s
	  _Outptr_result_buffer_to_(s,c)   ?    |   ?     |   s     |   c

   For the _Outptr_ annotations, the buffer in question is at one level of
   dereference. The called function is responsible for supplying the buffer.

   Success and failure:
   -------------------
   The SAL concept of success allows functions to define expressions that can
   be tested by the caller, which if it evaluates to non-zero, indicates the
   function succeeded, which means that its postconditions are guaranteed to
   hold.  Otherwise, if the expression evaluates to zero, the function is
   considered to have failed, and the postconditions are not guaranteed.

   The success criteria can be specified with the _Success_(expr) annotation:
	 _Success_(return != FALSE) BOOL
	 PathCanonicalizeA(_Out_writes_(MAX_PATH) LPSTR pszBuf, LPCSTR pszPath) :
		pszBuf is only guaranteed to be NULL-terminated when TRUE is returned,
		and FALSE indicates failure. In common practice, callers check for zero
		vs. non-zero returns, so it is preferable to express the success
		criteria in terms of zero/non-zero, not checked for exactly TRUE.

   Functions can specify that some postconditions will still hold, even when
   the function fails, using _On_failure_(anno-list), or postconditions that
   hold regardless of success or failure using _Always_(anno-list).

   The annotation _Return_type_success_(expr) may be used with a typedef to
   give a default _Success_ criteria to all functions returning that type.
   This is the case for common Windows API status types, including
   HRESULT and NTSTATUS.  This may be overridden on a per-function basis by
   specifying a _Success_ annotation locally.

============================================================================*/

#define __ATTR_SAL

#ifndef _SAL_VERSION
#define _SAL_VERSION 20
#endif

#ifndef __SAL_H_VERSION
#define __SAL_H_VERSION 180000000
#endif

#ifdef _PREFAST_ // [

// choose attribute or __declspec implementation
#ifndef _USE_DECLSPECS_FOR_SAL // [
#define _USE_DECLSPECS_FOR_SAL 1
#endif // ]

#if _USE_DECLSPECS_FOR_SAL // [
#undef _USE_ATTRIBUTES_FOR_SAL
#define _USE_ATTRIBUTES_FOR_SAL 0
#elif !defined(_USE_ATTRIBUTES_FOR_SAL) // ][
#define _USE_ATTRIBUTES_FOR_SAL 1
#endif // ]

#if !_USE_DECLSPECS_FOR_SAL	 // [
#if !_USE_ATTRIBUTES_FOR_SAL // [
#undef _USE_ATTRIBUTES_FOR_SAL
#define _USE_ATTRIBUTES_FOR_SAL 1
#endif // ]
#endif // ]

#else

// Disable expansion of SAL macros in non-Prefast mode to
// improve compiler throughput.
#ifndef _USE_DECLSPECS_FOR_SAL // [
#define _USE_DECLSPECS_FOR_SAL 0
#endif							// ]
#ifndef _USE_ATTRIBUTES_FOR_SAL // [
#define _USE_ATTRIBUTES_FOR_SAL 0
#endif // ]

#endif // ]

// safeguard for MIDL and RC builds
#if _USE_DECLSPECS_FOR_SAL && (defined(MIDL_PASS) || defined(__midl) || defined(RC_INVOKED) || !defined(_PREFAST_)) // [
#undef _USE_DECLSPECS_FOR_SAL
#define _USE_DECLSPECS_FOR_SAL 0
#endif																													   // ]
#if _USE_ATTRIBUTES_FOR_SAL && (!defined(_MSC_EXTENSIONS) || defined(MIDL_PASS) || defined(__midl) || defined(RC_INVOKED)) // [
#undef _USE_ATTRIBUTES_FOR_SAL
#define _USE_ATTRIBUTES_FOR_SAL 0
#endif // ]
// 200
//   207
#if defined(UNDOCKED_WINDOWS_UCRT) && !_USE_ATTRIBUTES_FOR_SAL
#define _SAL1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1") _GrouP_(annotes _SAL_nop_impl_)
#define _SAL1_1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.1") _GrouP_(annotes _SAL_nop_impl_)
#define _SAL1_2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.2") _GrouP_(annotes _SAL_nop_impl_)
#define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)

#ifndef _SAL_L_Source_
// Some annotations aren't officially SAL2 yet.
#define _SAL_L_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)
#endif
#else
#define _SAL1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1") _Group_(annotes _SAL_nop_impl_)
#define _SAL1_1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.1") _Group_(annotes _SAL_nop_impl_)
#define _SAL1_2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.2") _Group_(annotes _SAL_nop_impl_)
#define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _Group_(annotes _SAL_nop_impl_)

#ifndef _SAL_L_Source_
// Some annotations aren't officially SAL2 yet.
#define _SAL_L_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _Group_(annotes _SAL_nop_impl_)
#endif
#endif
// 229
// 248
// _When_(expr, annos) specifies that the annotations listed in 'annos' only
// apply when 'expr' evaluates to non-zero.
#define _When_(expr, annos) _When_impl_(expr, annos _SAL_nop_impl_)
#define _Group_(annos) _Group_impl_(annos _SAL_nop_impl_)
#define _GrouP_(annos) _GrouP_impl_(annos _SAL_nop_impl_)
// 254
//   566
//    annotations to express value of integral or pointer parameter
#define _In_range_(lb, ub) _SAL2_Source_(_In_range_, (lb, ub), _In_range_impl_(lb, ub))
#define _Out_range_(lb, ub) _SAL2_Source_(_Out_range_, (lb, ub), _Out_range_impl_(lb, ub))
#define _Ret_range_(lb, ub) _SAL2_Source_(_Ret_range_, (lb, ub), _Ret_range_impl_(lb, ub))
#define _Deref_in_range_(lb, ub) _SAL2_Source_(_Deref_in_range_, (lb, ub), _Deref_in_range_impl_(lb, ub))
#define _Deref_out_range_(lb, ub) _SAL2_Source_(_Deref_out_range_, (lb, ub), _Deref_out_range_impl_(lb, ub))
#define _Deref_ret_range_(lb, ub) _SAL2_Source_(_Deref_ret_range_, (lb, ub), _Deref_ret_range_impl_(lb, ub))
#define _Pre_equal_to_(expr) _SAL2_Source_(_Pre_equal_to_, (expr), _In_range_(==, expr))
#define _Post_equal_to_(expr) _SAL2_Source_(_Post_equal_to_, (expr), _Out_range_(==, expr))
// 576
//1474
//============================================================================
//   Implementation Layer:
//============================================================================


// Naming conventions:
// A symbol the begins with _SA_ is for the machinery of creating any
// annotations; many of those come from sourceannotations.h in the case
// of attributes.

// A symbol that ends with _impl is the very lowest level macro.  It is
// not required to be a legal standalone annotation, and in the case
// of attribute annotations, usually is not.  (In the case of some declspec
// annotations, it might be, but it should not be assumed so.)  Those
// symbols will be used in the _PreN..., _PostN... and _RetN... annotations
// to build up more complete annotations.

// A symbol ending in _impl_ is reserved to the implementation as well,
// but it does form a complete annotation; usually they are used to build
// up even higher level annotations.


#if _USE_ATTRIBUTES_FOR_SAL || _USE_DECLSPECS_FOR_SAL // [
// Sharable "_impl" macros: these can be shared between the various annotation
// forms but are part of the implementation of the macros.  These are collected
// here to assure that only necessary differences in the annotations
// exist.

#define _Always_impl_(annos)            _Group_(annos _SAL_nop_impl_) _On_failure_impl_(annos _SAL_nop_impl_)
#define _Bound_impl_                    _SA_annotes0(SAL_bound)
#define _Field_range_impl_(min,max)     _Range_impl_(min,max)
#define _Literal_impl_                  _SA_annotes1(SAL_constant, __yes)
#define _Maybenull_impl_                _SA_annotes1(SAL_null, __maybe)
#define _Maybevalid_impl_               _SA_annotes1(SAL_valid, __maybe)
#define _Must_inspect_impl_ _Post_impl_ _SA_annotes0(SAL_mustInspect)
#define _Notliteral_impl_               _SA_annotes1(SAL_constant, __no)
#define _Notnull_impl_                  _SA_annotes1(SAL_null, __no)
#define _Notvalid_impl_                 _SA_annotes1(SAL_valid, __no)
#define _NullNull_terminated_impl_      _Group_(_SA_annotes1(SAL_nullTerminated, __yes) _SA_annotes1(SAL_readableTo,inexpressibleCount("NullNull terminated string")))
#define _Null_impl_                     _SA_annotes1(SAL_null, __yes)
#define _Null_terminated_impl_          _SA_annotes1(SAL_nullTerminated, __yes)
#define _Out_impl_                      _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_c_one_notref_impl) _Post_valid_impl_
#define _Out_opt_impl_                  _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_c_one_notref_impl) _Post_valid_impl_
#define _Points_to_data_impl_           _At_(*_Curr_, _SA_annotes1(SAL_mayBePointer, __no))
#define _Post_satisfies_impl_(cond)     _Post_impl_ _Satisfies_impl_(cond)
#define _Post_valid_impl_               _Post1_impl_(__valid_impl)
#define _Pre_satisfies_impl_(cond)      _Pre_impl_ _Satisfies_impl_(cond)
#define _Pre_valid_impl_                _Pre1_impl_(__valid_impl)
#define _Range_impl_(min,max)           _SA_annotes2(SAL_range, min, max)
#define _Readable_bytes_impl_(size)     _SA_annotes1(SAL_readableTo, byteCount(size))
#define _Readable_elements_impl_(size)  _SA_annotes1(SAL_readableTo, elementCount(size))
#define _Ret_valid_impl_                _Ret1_impl_(__valid_impl)
#define _Satisfies_impl_(cond)          _SA_annotes1(SAL_satisfies, cond)
#define _Valid_impl_                    _SA_annotes1(SAL_valid, __yes)
#define _Writable_bytes_impl_(size)     _SA_annotes1(SAL_writableTo, byteCount(size))
#define _Writable_elements_impl_(size)  _SA_annotes1(SAL_writableTo, elementCount(size))

#define _In_range_impl_(min,max)        _Pre_impl_ _Range_impl_(min,max)
#define _Out_range_impl_(min,max)       _Post_impl_ _Range_impl_(min,max)
#define _Ret_range_impl_(min,max)       _Post_impl_ _Range_impl_(min,max)
#define _Deref_in_range_impl_(min,max)  _Deref_pre_impl_ _Range_impl_(min,max)
#define _Deref_out_range_impl_(min,max) _Deref_post_impl_ _Range_impl_(min,max)
#define _Deref_ret_range_impl_(min,max) _Deref_post_impl_ _Range_impl_(min,max)

#define _Deref_pre_impl_                _Pre_impl_  _Notref_impl_ _Deref_impl_
#define _Deref_post_impl_               _Post_impl_ _Notref_impl_ _Deref_impl_

// The following are for the implementation machinery, and are not
// suitable for annotating general code.
// We're tying to phase this out, someday.  The parser quotes the param.
#define __AuToQuOtE                     _SA_annotes0(SAL_AuToQuOtE)

// Normally the parser does some simple type checking of annotation params,
// defer that check to the plugin.
#define __deferTypecheck                _SA_annotes0(SAL_deferTypecheck)

#define _SA_SPECSTRIZE( x ) #x
#define _SAL_nop_impl_       /* nothing */
#define __nop_impl(x)            x
#endif

#if _USE_ATTRIBUTES_FOR_SAL // [

// Using attributes for sal

#include "CodeAnalysis/sourceannotations.h"

#define _SA_annotes0(n) [SAL_annotes(Name = #n)]
#define _SA_annotes1(n, pp1) [SAL_annotes(Name = #n, p1 = _SA_SPECSTRIZE(pp1))]
#define _SA_annotes2(n, pp1, pp2) [SAL_annotes(Name = #n, p1 = _SA_SPECSTRIZE(pp1), p2 = _SA_SPECSTRIZE(pp2))]
#define _SA_annotes3(n, pp1, pp2, pp3) [SAL_annotes(Name = #n, p1 = _SA_SPECSTRIZE(pp1), p2 = _SA_SPECSTRIZE(pp2), p3 = _SA_SPECSTRIZE(pp3))]

#define _Pre_impl_ [SAL_pre]
#define _Post_impl_ [SAL_post]
#define _Deref_impl_ [SAL_deref]
#define _Notref_impl_ [SAL_notref]

// Declare a function to be an annotation or primop (respectively).
// Done this way so that they don't appear in the regular compiler's
// namespace.
#define __ANNOTATION(fun) _SA_annotes0(SAL_annotation) void __SA_##fun;
#define __PRIMOP(type, fun) _SA_annotes0(SAL_primop) type __SA_##fun;
#define __QUALIFIER(fun) _SA_annotes0(SAL_qualifier) void __SA_##fun;

// Benign declspec needed here for WindowsPREfast
#define __In_impl_ [SA_Pre(Valid = SA_Yes)][SA_Pre(Deref = 1, Notref = 1, Access = SA_Read)] __declspec("SAL_pre SAL_valid")

#elif _USE_DECLSPECS_FOR_SAL // ][

// Using declspecs for sal

#define _SA_annotes0(n) __declspec(#n)
#define _SA_annotes1(n, pp1) __declspec(#n "(" _SA_SPECSTRIZE(pp1) ")")
#define _SA_annotes2(n, pp1, pp2) __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) ")")
#define _SA_annotes3(n, pp1, pp2, pp3) __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) "," _SA_SPECSTRIZE(pp3) ")")

#define _Pre_impl_ _SA_annotes0(SAL_pre)
#define _Post_impl_ _SA_annotes0(SAL_post)
#define _Deref_impl_ _SA_annotes0(SAL_deref)
#define _Notref_impl_ _SA_annotes0(SAL_notref)

// Declare a function to be an annotation or primop (respectively).
// Done this way so that they don't appear in the regular compiler's
// namespace.
#define __ANNOTATION(fun) _SA_annotes0(SAL_annotation) void __SA_##fun

#define __PRIMOP(type, fun) _SA_annotes0(SAL_primop) type __SA_##fun

#define __QUALIFIER(fun) _SA_annotes0(SAL_qualifier) void __SA_##fun;

#define __In_impl_                     \
	_Pre_impl_ _SA_annotes0(SAL_valid) \
	_Pre_impl_ _Deref_impl_ _Notref_impl_ _SA_annotes0(SAL_readonly)

#else // ][

// Using "nothing" for sal

#define _SA_annotes0(n)
#define _SA_annotes1(n, pp1)
#define _SA_annotes2(n, pp1, pp2)
#define _SA_annotes3(n, pp1, pp2, pp3)

#define __ANNOTATION(fun)
#define __PRIMOP(type, fun)
#define __QUALIFIER(type, fun)

#endif // ]
// 1624
// 1663
#if _USE_ATTRIBUTES_FOR_SAL // [

#define _Check_return_impl_ [SA_Post(MustCheck = SA_Yes)]

#define _Success_impl_(expr) [SA_Success(Condition = #expr)]
#define _On_failure_impl_(annos) [SAL_context(p1 = "SAL_failed")] _Group_(_Post_impl_ _Group_(annos _SAL_nop_impl_))

#define _Printf_format_string_impl_ [SA_FormatString(Style = "printf")]
#define _Scanf_format_string_impl_ [SA_FormatString(Style = "scanf")]
#define _Scanf_s_format_string_impl_ [SA_FormatString(Style = "scanf_s")]

#define _In_bound_impl_ [SA_PreBound(Deref = 0)]
#define _Out_bound_impl_ [SA_PostBound(Deref = 0)]
#define _Ret_bound_impl_ [SA_PostBound(Deref = 0)]
#define _Deref_in_bound_impl_ [SA_PreBound(Deref = 1)]
#define _Deref_out_bound_impl_ [SA_PostBound(Deref = 1)]
#define _Deref_ret_bound_impl_ [SA_PostBound(Deref = 1)]

#define __valid_impl Valid = SA_Yes
#define __maybevalid_impl Valid = SA_Maybe
#define __notvalid_impl Valid = SA_No

#define __null_impl Null = SA_Yes
#define __maybenull_impl Null = SA_Maybe
#define __notnull_impl Null = SA_No

#define __null_impl_notref Null = SA_Yes, Notref = 1
#define __maybenull_impl_notref Null = SA_Maybe, Notref = 1
#define __notnull_impl_notref Null = SA_No, Notref = 1

#define __zterm_impl NullTerminated = SA_Yes
#define __maybezterm_impl NullTerminated = SA_Maybe
#define __maybzterm_impl NullTerminated = SA_Maybe
#define __notzterm_impl NullTerminated = SA_No

#define __readaccess_impl Access = SA_Read
#define __writeaccess_impl Access = SA_Write
#define __allaccess_impl Access = SA_ReadWrite

#define __readaccess_impl_notref Access = SA_Read, Notref = 1
#define __writeaccess_impl_notref Access = SA_Write, Notref = 1
#define __allaccess_impl_notref Access = SA_ReadWrite, Notref = 1

// For SAL2, we need to expect general expressions.

#define __cap_impl(size) WritableElements = "\n" #size
#define __bytecap_impl(size) WritableBytes = "\n" #size
#define __bytecount_impl(size) ValidBytes = "\n" #size
#define __count_impl(size) ValidElements = "\n" #size

#define __cap_c_impl(size) WritableElementsConst = size
#define __cap_c_one_notref_impl WritableElementsConst = 1, Notref = 1
#define __cap_for_impl(param) WritableElementsLength = #param
#define __cap_x_impl(size) WritableElements = "\n@" #size

#define __bytecap_c_impl(size) WritableBytesConst = size
#define __bytecap_x_impl(size) WritableBytes = "\n@" #size

#define __mult_impl(mult, size) __cap_impl((mult) * (size))

#define __count_c_impl(size) ValidElementsConst = size
#define __count_x_impl(size) ValidElements = "\n@" #size

#define __bytecount_c_impl(size) ValidBytesConst = size
#define __bytecount_x_impl(size) ValidBytes = "\n@" #size

#define _At_impl_(target, annos) [SAL_at(p1 = #target)] _Group_(annos)
#define _At_buffer_impl_(target, iter, bound, annos) [SAL_at_buffer(p1 = #target, p2 = #iter, p3 = #bound)] _Group_(annos)
#define _When_impl_(expr, annos) [SAL_when(p1 = #expr)] _Group_(annos)

#define _Group_impl_(annos) [SAL_begin] annos[SAL_end]
#define _GrouP_impl_(annos) [SAL_BEGIN] annos[SAL_END]

#define _Use_decl_anno_impl_ _SA_annotes0(SAL_useHeader) // this is a special case!

#define _Pre1_impl_(p1) [SA_Pre(p1)]
#define _Pre2_impl_(p1, p2) [SA_Pre(p1, p2)]
#define _Pre3_impl_(p1, p2, p3) [SA_Pre(p1, p2, p3)]

#define _Post1_impl_(p1) [SA_Post(p1)]
#define _Post2_impl_(p1, p2) [SA_Post(p1, p2)]
#define _Post3_impl_(p1, p2, p3) [SA_Post(p1, p2, p3)]

#define _Ret1_impl_(p1) [SA_Post(p1)]
#define _Ret2_impl_(p1, p2) [SA_Post(p1, p2)]
#define _Ret3_impl_(p1, p2, p3) [SA_Post(p1, p2, p3)]

#define _Deref_pre1_impl_(p1) [SA_Pre(Deref = 1, p1)]
#define _Deref_pre2_impl_(p1, p2) [SA_Pre(Deref = 1, p1, p2)]
#define _Deref_pre3_impl_(p1, p2, p3) [SA_Pre(Deref = 1, p1, p2, p3)]

#define _Deref_post1_impl_(p1) [SA_Post(Deref = 1, p1)]
#define _Deref_post2_impl_(p1, p2) [SA_Post(Deref = 1, p1, p2)]
#define _Deref_post3_impl_(p1, p2, p3) [SA_Post(Deref = 1, p1, p2, p3)]

#define _Deref_ret1_impl_(p1) [SA_Post(Deref = 1, p1)]
#define _Deref_ret2_impl_(p1, p2) [SA_Post(Deref = 1, p1, p2)]
#define _Deref_ret3_impl_(p1, p2, p3) [SA_Post(Deref = 1, p1, p2, p3)]

#define _Deref2_pre1_impl_(p1) [SA_Pre(Deref = 2, Notref = 1, p1)]
#define _Deref2_post1_impl_(p1) [SA_Post(Deref = 2, Notref = 1, p1)]
#define _Deref2_ret1_impl_(p1) [SA_Post(Deref = 2, Notref = 1, p1)]

// Obsolete -- may be needed for transition to attributes.
#define __inner_typefix(ctype) [SAL_typefix(p1 = _SA_SPECSTRIZE(ctype))]
#define __inner_exceptthat [SAL_except]

#elif _USE_DECLSPECS_FOR_SAL // ][

#define _Check_return_impl_ __post _SA_annotes0(SAL_checkReturn)

#define _Success_impl_(expr) _SA_annotes1(SAL_success, expr)
#define _On_failure_impl_(annos) _SA_annotes1(SAL_context, SAL_failed) _Group_(_Post_impl_ _Group_(_SAL_nop_impl_ annos))

#define _Printf_format_string_impl_ _SA_annotes1(SAL_IsFormatString, "printf")
#define _Scanf_format_string_impl_ _SA_annotes1(SAL_IsFormatString, "scanf")
#define _Scanf_s_format_string_impl_ _SA_annotes1(SAL_IsFormatString, "scanf_s")

#define _In_bound_impl_ _Pre_impl_ _Bound_impl_
#define _Out_bound_impl_ _Post_impl_ _Bound_impl_
#define _Ret_bound_impl_ _Post_impl_ _Bound_impl_
#define _Deref_in_bound_impl_ _Deref_pre_impl_ _Bound_impl_
#define _Deref_out_bound_impl_ _Deref_post_impl_ _Bound_impl_
#define _Deref_ret_bound_impl_ _Deref_post_impl_ _Bound_impl_

#define __null_impl _SA_annotes0(SAL_null)			 // _SA_annotes1(SAL_null, __yes)
#define __notnull_impl _SA_annotes0(SAL_notnull)	 // _SA_annotes1(SAL_null, __no)
#define __maybenull_impl _SA_annotes0(SAL_maybenull) // _SA_annotes1(SAL_null, __maybe)

#define __valid_impl _SA_annotes0(SAL_valid)		   // _SA_annotes1(SAL_valid, __yes)
#define __notvalid_impl _SA_annotes0(SAL_notvalid)	   // _SA_annotes1(SAL_valid, __no)
#define __maybevalid_impl _SA_annotes0(SAL_maybevalid) // _SA_annotes1(SAL_valid, __maybe)

#define __null_impl_notref _Notref_ _Null_impl_
#define __maybenull_impl_notref _Notref_ _Maybenull_impl_
#define __notnull_impl_notref _Notref_ _Notnull_impl_

#define __zterm_impl _SA_annotes1(SAL_nullTerminated, __yes)
#define __maybezterm_impl _SA_annotes1(SAL_nullTerminated, __maybe)
#define __maybzterm_impl _SA_annotes1(SAL_nullTerminated, __maybe)
#define __notzterm_impl _SA_annotes1(SAL_nullTerminated, __no)

#define __readaccess_impl _SA_annotes1(SAL_access, 0x1)
#define __writeaccess_impl _SA_annotes1(SAL_access, 0x2)
#define __allaccess_impl _SA_annotes1(SAL_access, 0x3)

#define __readaccess_impl_notref _Notref_ _SA_annotes1(SAL_access, 0x1)
#define __writeaccess_impl_notref _Notref_ _SA_annotes1(SAL_access, 0x2)
#define __allaccess_impl_notref _Notref_ _SA_annotes1(SAL_access, 0x3)

#define __cap_impl(size) _SA_annotes1(SAL_writableTo, elementCount(size))
#define __cap_c_impl(size) _SA_annotes1(SAL_writableTo, elementCount(size))
#define __cap_c_one_notref_impl _Notref_ _SA_annotes1(SAL_writableTo, elementCount(1))
#define __cap_for_impl(param) _SA_annotes1(SAL_writableTo, inexpressibleCount(sizeof(param)))
#define __cap_x_impl(size) _SA_annotes1(SAL_writableTo, inexpressibleCount(#size))

#define __bytecap_impl(size) _SA_annotes1(SAL_writableTo, byteCount(size))
#define __bytecap_c_impl(size) _SA_annotes1(SAL_writableTo, byteCount(size))
#define __bytecap_x_impl(size) _SA_annotes1(SAL_writableTo, inexpressibleCount(#size))

#define __mult_impl(mult, size) _SA_annotes1(SAL_writableTo, (mult) * (size))

#define __count_impl(size) _SA_annotes1(SAL_readableTo, elementCount(size))
#define __count_c_impl(size) _SA_annotes1(SAL_readableTo, elementCount(size))
#define __count_x_impl(size) _SA_annotes1(SAL_readableTo, inexpressibleCount(#size))

#define __bytecount_impl(size) _SA_annotes1(SAL_readableTo, byteCount(size))
#define __bytecount_c_impl(size) _SA_annotes1(SAL_readableTo, byteCount(size))
#define __bytecount_x_impl(size) _SA_annotes1(SAL_readableTo, inexpressibleCount(#size))

#define _At_impl_(target, annos) _SA_annotes0(SAL_at(target)) _Group_(annos)
#define _At_buffer_impl_(target, iter, bound, annos) _SA_annotes3(SAL_at_buffer, target, iter, bound) _Group_(annos)
#define _Group_impl_(annos) _SA_annotes0(SAL_begin) annos _SA_annotes0(SAL_end)
#define _GrouP_impl_(annos) _SA_annotes0(SAL_BEGIN) annos _SA_annotes0(SAL_END)
#define _When_impl_(expr, annos) _SA_annotes0(SAL_when(expr)) _Group_(annos)

#define _Use_decl_anno_impl_ __declspec("SAL_useHeader()") // this is a special case!

#define _Pre1_impl_(p1) _Pre_impl_ p1
#define _Pre2_impl_(p1, p2) _Pre_impl_ p1 _Pre_impl_ p2
#define _Pre3_impl_(p1, p2, p3) _Pre_impl_ p1 _Pre_impl_ p2 _Pre_impl_ p3

#define _Post1_impl_(p1) _Post_impl_ p1
#define _Post2_impl_(p1, p2) _Post_impl_ p1 _Post_impl_ p2
#define _Post3_impl_(p1, p2, p3) _Post_impl_ p1 _Post_impl_ p2 _Post_impl_ p3

#define _Ret1_impl_(p1) _Post_impl_ p1
#define _Ret2_impl_(p1, p2) _Post_impl_ p1 _Post_impl_ p2
#define _Ret3_impl_(p1, p2, p3) _Post_impl_ p1 _Post_impl_ p2 _Post_impl_ p3

#define _Deref_pre1_impl_(p1) _Deref_pre_impl_ p1
#define _Deref_pre2_impl_(p1, p2) _Deref_pre_impl_ p1 _Deref_pre_impl_ p2
#define _Deref_pre3_impl_(p1, p2, p3) _Deref_pre_impl_ p1 _Deref_pre_impl_ p2 _Deref_pre_impl_ p3

#define _Deref_post1_impl_(p1) _Deref_post_impl_ p1
#define _Deref_post2_impl_(p1, p2) _Deref_post_impl_ p1 _Deref_post_impl_ p2
#define _Deref_post3_impl_(p1, p2, p3) _Deref_post_impl_ p1 _Deref_post_impl_ p2 _Deref_post_impl_ p3

#define _Deref_ret1_impl_(p1) _Deref_post_impl_ p1
#define _Deref_ret2_impl_(p1, p2) _Deref_post_impl_ p1 _Deref_post_impl_ p2
#define _Deref_ret3_impl_(p1, p2, p3) _Deref_post_impl_ p1 _Deref_post_impl_ p2 _Deref_post_impl_ p3

#define _Deref2_pre1_impl_(p1) _Deref_pre_impl_ _Notref_impl_ _Deref_impl_ p1
#define _Deref2_post1_impl_(p1) _Deref_post_impl_ _Notref_impl_ _Deref_impl_ p1
#define _Deref2_ret1_impl_(p1) _Deref_post_impl_ _Notref_impl_ _Deref_impl_ p1

#define __inner_typefix(ctype) _SA_annotes1(SAL_typefix, ctype)
#define __inner_exceptthat _SA_annotes0(SAL_except)

#elif defined(_MSC_EXTENSIONS) && !defined(MIDL_PASS) && !defined(__midl) && !defined(RC_INVOKED) && defined(_PFT_VER) // ][

// minimum attribute expansion for foreground build

#pragma push_macro("SA")
#pragma push_macro("REPEATABLE")

#ifdef __cplusplus // [
#define SA(id) id
#define REPEATABLE [repeatable]
#else // !__cplusplus // ][
#define SA(id) SA_##id
#define REPEATABLE
#endif			   // !__cplusplus // ]

REPEATABLE
[source_annotation_attribute(SA(Parameter))] struct __P_impl
{
#ifdef __cplusplus // [
	__P_impl();
#endif			   // ]
	int __d_;
};
typedef struct __P_impl __P_impl;

REPEATABLE
[source_annotation_attribute(SA(ReturnValue))] struct __R_impl
{
#ifdef __cplusplus // [
	__R_impl();
#endif			   // ]
	int __d_;
};
typedef struct __R_impl __R_impl;

[source_annotation_attribute(SA(Method))] struct __M_
{
#ifdef __cplusplus // [
	__M_();
#endif			   // ]
	int __d_;
};
typedef struct __M_ __M_;

[source_annotation_attribute(SA(All))] struct __A_
{
#ifdef __cplusplus // [
	__A_();
#endif			   // ]
	int __d_;
};
typedef struct __A_ __A_;

[source_annotation_attribute(SA(Field))] struct __F_
{
#ifdef __cplusplus // [
	__F_();
#endif			   // ]
	int __d_;
};
typedef struct __F_ __F_;

#pragma pop_macro("REPEATABLE")
#pragma pop_macro("SA")

#define _SAL_nop_impl_

#define _At_impl_(target, annos) [__A_(__d_ = 0)]
#define _At_buffer_impl_(target, iter, bound, annos) [__A_(__d_ = 0)]
#define _When_impl_(expr, annos) annos
#define _Group_impl_(annos) annos
#define _GrouP_impl_(annos) annos
#define _Use_decl_anno_impl_ [__M_(__d_ = 0)]

#define _Points_to_data_impl_ [__P_impl(__d_ = 0)]
#define _Literal_impl_ [__P_impl(__d_ = 0)]
#define _Notliteral_impl_ [__P_impl(__d_ = 0)]

#define _Pre_valid_impl_ [__P_impl(__d_ = 0)]
#define _Post_valid_impl_ [__P_impl(__d_ = 0)]
#define _Ret_valid_impl_ [__R_impl(__d_ = 0)]

#define _Check_return_impl_ [__R_impl(__d_ = 0)]
#define _Must_inspect_impl_ [__R_impl(__d_ = 0)]

#define _Success_impl_(expr) [__M_(__d_ = 0)]
#define _On_failure_impl_(expr) [__M_(__d_ = 0)]
#define _Always_impl_(expr) [__M_(__d_ = 0)]

#define _Printf_format_string_impl_ [__P_impl(__d_ = 0)]
#define _Scanf_format_string_impl_ [__P_impl(__d_ = 0)]
#define _Scanf_s_format_string_impl_ [__P_impl(__d_ = 0)]

#define _Raises_SEH_exception_impl_ [__M_(__d_ = 0)]
#define _Maybe_raises_SEH_exception_impl_ [__M_(__d_ = 0)]

#define _In_bound_impl_ [__P_impl(__d_ = 0)]
#define _Out_bound_impl_ [__P_impl(__d_ = 0)]
#define _Ret_bound_impl_ [__R_impl(__d_ = 0)]
#define _Deref_in_bound_impl_ [__P_impl(__d_ = 0)]
#define _Deref_out_bound_impl_ [__P_impl(__d_ = 0)]
#define _Deref_ret_bound_impl_ [__R_impl(__d_ = 0)]

#define _Range_impl_(min, max) [__P_impl(__d_ = 0)]
#define _In_range_impl_(min, max) [__P_impl(__d_ = 0)]
#define _Out_range_impl_(min, max) [__P_impl(__d_ = 0)]
#define _Ret_range_impl_(min, max) [__R_impl(__d_ = 0)]
#define _Deref_in_range_impl_(min, max) [__P_impl(__d_ = 0)]
#define _Deref_out_range_impl_(min, max) [__P_impl(__d_ = 0)]
#define _Deref_ret_range_impl_(min, max) [__R_impl(__d_ = 0)]

#define _Field_range_impl_(min, max) [__F_(__d_ = 0)]

#define _Pre_satisfies_impl_(cond) [__A_(__d_ = 0)]
#define _Post_satisfies_impl_(cond) [__A_(__d_ = 0)]
#define _Satisfies_impl_(cond) [__A_(__d_ = 0)]

#define _Null_impl_ [__A_(__d_ = 0)]
#define _Notnull_impl_ [__A_(__d_ = 0)]
#define _Maybenull_impl_ [__A_(__d_ = 0)]

#define _Valid_impl_ [__A_(__d_ = 0)]
#define _Notvalid_impl_ [__A_(__d_ = 0)]
#define _Maybevalid_impl_ [__A_(__d_ = 0)]

#define _Readable_bytes_impl_(size) [__A_(__d_ = 0)]
#define _Readable_elements_impl_(size) [__A_(__d_ = 0)]
#define _Writable_bytes_impl_(size) [__A_(__d_ = 0)]
#define _Writable_elements_impl_(size) [__A_(__d_ = 0)]

#define _Null_terminated_impl_ [__A_(__d_ = 0)]
#define _NullNull_terminated_impl_ [__A_(__d_ = 0)]

#define _Pre_impl_ [__P_impl(__d_ = 0)]
#define _Pre1_impl_(p1) [__P_impl(__d_ = 0)]
#define _Pre2_impl_(p1, p2) [__P_impl(__d_ = 0)]
#define _Pre3_impl_(p1, p2, p3) [__P_impl(__d_ = 0)]

#define _Post_impl_ [__P_impl(__d_ = 0)]
#define _Post1_impl_(p1) [__P_impl(__d_ = 0)]
#define _Post2_impl_(p1, p2) [__P_impl(__d_ = 0)]
#define _Post3_impl_(p1, p2, p3) [__P_impl(__d_ = 0)]

#define _Ret1_impl_(p1) [__R_impl(__d_ = 0)]
#define _Ret2_impl_(p1, p2) [__R_impl(__d_ = 0)]
#define _Ret3_impl_(p1, p2, p3) [__R_impl(__d_ = 0)]

#define _Deref_pre1_impl_(p1) [__P_impl(__d_ = 0)]
#define _Deref_pre2_impl_(p1, p2) [__P_impl(__d_ = 0)]
#define _Deref_pre3_impl_(p1, p2, p3) [__P_impl(__d_ = 0)]

#define _Deref_post1_impl_(p1) [__P_impl(__d_ = 0)]
#define _Deref_post2_impl_(p1, p2) [__P_impl(__d_ = 0)]
#define _Deref_post3_impl_(p1, p2, p3) [__P_impl(__d_ = 0)]

#define _Deref_ret1_impl_(p1) [__R_impl(__d_ = 0)]
#define _Deref_ret2_impl_(p1, p2) [__R_impl(__d_ = 0)]
#define _Deref_ret3_impl_(p1, p2, p3) [__R_impl(__d_ = 0)]

#define _Deref2_pre1_impl_(p1)	//[__P_impl(__d_=0)]
#define _Deref2_post1_impl_(p1) //[__P_impl(__d_=0)]
#define _Deref2_ret1_impl_(p1)	//[__P_impl(__d_=0)]

#else // ][

#define _SAL_nop_impl_ X

#define _At_impl_(target, annos)
#define _When_impl_(expr, annos)
#define _Group_impl_(annos)
#define _GrouP_impl_(annos)
#define _At_buffer_impl_(target, iter, bound, annos)
#define _Use_decl_anno_impl_
#define _Points_to_data_impl_
#define _Literal_impl_
#define _Notliteral_impl_
#define _Notref_impl_

#define _Pre_valid_impl_
#define _Post_valid_impl_
#define _Ret_valid_impl_

#define _Check_return_impl_
#define _Must_inspect_impl_

#define _Success_impl_(expr)
#define _On_failure_impl_(annos)
#define _Always_impl_(annos)

#define _Printf_format_string_impl_
#define _Scanf_format_string_impl_
#define _Scanf_s_format_string_impl_

#define _In_bound_impl_
#define _Out_bound_impl_
#define _Ret_bound_impl_
#define _Deref_in_bound_impl_
#define _Deref_out_bound_impl_
#define _Deref_ret_bound_impl_

#define _Range_impl_(min, max)
#define _In_range_impl_(min, max)
#define _Out_range_impl_(min, max)
#define _Ret_range_impl_(min, max)
#define _Deref_in_range_impl_(min, max)
#define _Deref_out_range_impl_(min, max)
#define _Deref_ret_range_impl_(min, max)

#define _Satisfies_impl_(expr)
#define _Pre_satisfies_impl_(expr)
#define _Post_satisfies_impl_(expr)

#define _Null_impl_
#define _Notnull_impl_
#define _Maybenull_impl_

#define _Valid_impl_
#define _Notvalid_impl_
#define _Maybevalid_impl_

#define _Field_range_impl_(min, max)

#define _Pre_impl_
#define _Pre1_impl_(p1)
#define _Pre2_impl_(p1, p2)
#define _Pre3_impl_(p1, p2, p3)

#define _Post_impl_
#define _Post1_impl_(p1)
#define _Post2_impl_(p1, p2)
#define _Post3_impl_(p1, p2, p3)

#define _Ret1_impl_(p1)
#define _Ret2_impl_(p1, p2)
#define _Ret3_impl_(p1, p2, p3)

#define _Deref_pre1_impl_(p1)
#define _Deref_pre2_impl_(p1, p2)
#define _Deref_pre3_impl_(p1, p2, p3)

#define _Deref_post1_impl_(p1)
#define _Deref_post2_impl_(p1, p2)
#define _Deref_post3_impl_(p1, p2, p3)

#define _Deref_ret1_impl_(p1)
#define _Deref_ret2_impl_(p1, p2)
#define _Deref_ret3_impl_(p1, p2, p3)

#define _Deref2_pre1_impl_(p1)
#define _Deref2_post1_impl_(p1)
#define _Deref2_ret1_impl_(p1)

#define _Readable_bytes_impl_(size)
#define _Readable_elements_impl_(size)
#define _Writable_bytes_impl_(size)
#define _Writable_elements_impl_(size)

#define _Null_terminated_impl_
#define _NullNull_terminated_impl_

// Obsolete -- may be needed for transition to attributes.
#define __inner_typefix(ctype)
#define __inner_exceptthat

#endif // ]
// 2149
//   2895
#ifndef _Analysis_assume_ // [
#ifdef _PREFAST_		  // [
#define _Analysis_assume_(expr) __assume(expr)
#else // ][
#define _Analysis_assume_(expr)
#endif // ]
#endif // ]
	   // 2903