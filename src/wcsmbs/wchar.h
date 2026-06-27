/* Copyright (C) 1995-2025 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/*
 *      ISO C99 Standard: 7.24
 *	Extended multibyte and wide character utilities	<wchar.h>
 */

 #ifndef _WCHAR_H
 #define _WCHAR_H 1
 
 #define __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION
 #include <bits/libc-header-start.h>
 
 #define __need_size_t
 #define __need_wchar_t
 #define __need_NULL
 #include <stddef.h>
 
 #define __need___va_list
 #include <stdarg.h>
 
 #if defined __USE_XOPEN2K || defined __USE_XOPEN2K8
 # ifdef __GNUC__
 #  ifndef _VA_LIST_DEFINED
 typedef __gnuc_va_list va_list;
 #   define _VA_LIST_DEFINED
 #  endif
 # else
 #  include <stdarg.h>
 # endif
 #endif
 
 #include <bits/types/wint_t.h>
 #include <bits/types/mbstate_t.h>
 
 #if defined __USE_UNIX98 || defined __USE_XOPEN2K
 # include <bits/types/FILE.h>
 #endif
 
 /* Tell the caller that we provide correct C++ prototypes.  */
 #if defined __cplusplus && __GNUC_PREREQ (4, 4)
 # define __CORRECT_ISO_CPP_WCHAR_H_PROTO
 #endif
 
 #ifndef WCHAR_MIN
 /* These constants might also be defined in <inttypes.h>.  */
 # define WCHAR_MIN __WCHAR_MIN
 # define WCHAR_MAX __WCHAR_MAX
 #endif
 
 #ifndef WEOF
 # define WEOF (0xffffffffu)
 #endif
 
 /* All versions of XPG prior to the publication of ISO C99 required
	the bulk of <wctype.h>'s declarations to appear in this header
	(because <wctype.h> did not exist prior to C99).  In POSIX.1-2001
	those declarations were marked as XSI extensions; in -2008 they
	were additionally marked as obsolescent.  _GNU_SOURCE mode
	anticipates the removal of these declarations in the next revision
	of POSIX.  */
 #if (defined __USE_XOPEN && !defined __USE_GNU \
	  && !(defined __USE_XOPEN2K && !defined __USE_XOPEN2KXSI))
 # include <bits/wctype-wchar.h>
 #endif
 
 __BEGIN_DECLS
 
 /* This incomplete type is defined in <time.h> but needed here because
	of `wcsftime'.  */
 struct tm;
 
 
 /* Copy SRC to DEST.  */
 extern wchar_t *wcscpy (wchar_t *__restrict __dest,
			 const wchar_t *__restrict __src)
	  __THROW __nonnull ((1, 2));
 
 /* Copy no more than N wide-characters of SRC to DEST.  */
 extern wchar_t *wcsncpy (wchar_t *__restrict __dest,
			  const wchar_t *__restrict __src, size_t __n)
	  __THROW __nonnull ((1, 2));
 
 #ifdef __USE_MISC
 /* Copy at most N - 1 characters from SRC to DEST.  */
 extern size_t wcslcpy (wchar_t *__restrict __dest,
				const wchar_t *__restrict __src, size_t __n)
   __THROW __nonnull ((1, 2)) __attr_access ((__write_only__, 1, 3));
 
 /* Append SRC to DEST, possibly with truncation to keep the total size
	below N.  */
 extern size_t wcslcat (wchar_t *__restrict __dest,
				const wchar_t *__restrict __src, size_t __n)
   __THROW __nonnull ((1, 2))  __attr_access ((__read_write__, 1, 3));
 #endif
 
 /* Append SRC onto DEST.  */
 extern wchar_t *wcscat (wchar_t *__restrict __dest,
			 const wchar_t *__restrict __src)
	  __THROW __nonnull ((1, 2));
 /* Append no more than N wide-characters of SRC onto DEST.  */
 extern wchar_t *wcsncat (wchar_t *__restrict __dest,
			  const wchar_t *__restrict __src, size_t __n)
	  __THROW __nonnull ((1, 2));
 
 /* Compare S1 and S2.  */
 extern int wcscmp (const wchar_t *__s1, const wchar_t *__s2)
	  __THROW __attribute_pure__ __nonnull ((1, 2));
 /* Compare N wide-characters of S1 and S2.  */
 extern int wcsncmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
	  __THROW __attribute_pure__ __nonnull ((1, 2));
 
 #ifdef __USE_XOPEN2K8
 /* Compare S1 and S2, ignoring case.  */
 extern int wcscasecmp (const wchar_t *__s1, const wchar_t *__s2) __THROW;
 
 /* Compare no more than N chars of S1 and S2, ignoring case.  */
 extern int wcsncasecmp (const wchar_t *__s1, const wchar_t *__s2,
			 size_t __n) __THROW;
 #endif
 
 /* Compare S1 and S2, both interpreted as appropriate to the
	LC_COLLATE category of the current locale.  */
 extern int wcscoll (const wchar_t *__s1, const wchar_t *__s2) __THROW;
 /* Transform S2 into array pointed to by S1 such that if wcscmp is
	applied to two transformed strings the result is the as applying
	`wcscoll' to the original strings.  */
 extern size_t wcsxfrm (wchar_t *__restrict __s1,
				const wchar_t *__restrict __s2, size_t __n) __THROW;
 
 #ifdef __USE_XOPEN2K8
 /* Similar to the two functions above but take the information from
	the provided locale and not the global locale.  */
 
 /* Duplicate S, returning an identical malloc'd string.  */
 extern wchar_t *wcsdup (const wchar_t *__s) __THROW
   __attribute_malloc__ __attr_dealloc_free;
 #endif
 
 /* Find the first occurrence of WC in WCS.  */
 #ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
 extern "C++" wchar_t *wcschr (wchar_t *__wcs, wchar_t __wc)
	  __THROW __asm ("wcschr") __attribute_pure__;
 extern "C++" const wchar_t *wcschr (const wchar_t *__wcs, wchar_t __wc)
	  __THROW __asm ("wcschr") __attribute_pure__;
 #else
 extern wchar_t *wcschr (const wchar_t *__wcs, wchar_t __wc)
	  __THROW __attribute_pure__;
 #endif
 /* Find the last occurrence of WC in WCS.  */
 #ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
 extern "C++" wchar_t *wcsrchr (wchar_t *__wcs, wchar_t __wc)
	  __THROW __asm ("wcsrchr") __attribute_pure__;
 extern "C++" const wchar_t *wcsrchr (const wchar_t *__wcs, wchar_t __wc)
	  __THROW __asm ("wcsrchr") __attribute_pure__;
 #else
 extern wchar_t *wcsrchr (const wchar_t *__wcs, wchar_t __wc)
	  __THROW __attribute_pure__;
 #endif
 
 #ifdef __USE_GNU
 /* This function is similar to `wcschr'.  But it returns a pointer to
	the closing NUL wide character in case C is not found in S.  */
 extern wchar_t *wcschrnul (const wchar_t *__s, wchar_t __wc)
	  __THROW __attribute_pure__;
 #endif
 
 /* Return the length of the initial segmet of WCS which
	consists entirely of wide characters not in REJECT.  */
 extern size_t wcscspn (const wchar_t *__wcs, const wchar_t *__reject)
	  __THROW __attribute_pure__;
 /* Return the length of the initial segmet of WCS which
	consists entirely of wide characters in  ACCEPT.  */
 extern size_t wcsspn (const wchar_t *__wcs, const wchar_t *__accept)
	  __THROW __attribute_pure__;
 /* Find the first occurrence in WCS of any character in ACCEPT.  */
 #ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
 extern "C++" wchar_t *wcspbrk (wchar_t *__wcs, const wchar_t *__accept)
	  __THROW __asm ("wcspbrk") __attribute_pure__;
 extern "C++" const wchar_t *wcspbrk (const wchar_t *__wcs,
					  const wchar_t *__accept)
	  __THROW __asm ("wcspbrk") __attribute_pure__;
 #else
 extern wchar_t *wcspbrk (const wchar_t *__wcs, const wchar_t *__accept)
	  __THROW __attribute_pure__;
 #endif
 /* Find the first occurrence of NEEDLE in HAYSTACK.  */
 #ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
 extern "C++" wchar_t *wcsstr (wchar_t *__haystack, const wchar_t *__needle)
	  __THROW __asm ("wcsstr") __attribute_pure__;
 extern "C++" const wchar_t *wcsstr (const wchar_t *__haystack,
					 const wchar_t *__needle)
	  __THROW __asm ("wcsstr") __attribute_pure__;
 #else
 extern wchar_t *wcsstr (const wchar_t *__haystack, const wchar_t *__needle)
	  __THROW __attribute_pure__;
 #endif
 
 /* Divide WCS into tokens separated by characters in DELIM.  */
 extern wchar_t *wcstok (wchar_t *__restrict __s,
			 const wchar_t *__restrict __delim,
			 wchar_t **__restrict __ptr) __THROW;
 
 /* Return the number of wide characters in S.  */
 extern size_t wcslen (const wchar_t *__s) __THROW __attribute_pure__;
 
 #ifdef __USE_XOPEN
 /* Another name for `wcsstr' from XPG4.  */
 # ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
 extern "C++" wchar_t *wcswcs (wchar_t *__haystack, const wchar_t *__needle)
	  __THROW __asm ("wcswcs") __attribute_pure__;
 extern "C++" const wchar_t *wcswcs (const wchar_t *__haystack,
					 const wchar_t *__needle)
	  __THROW __asm ("wcswcs") __attribute_pure__;
 # else
 extern wchar_t *wcswcs (const wchar_t *__haystack, const wchar_t *__needle)
	  __THROW __attribute_pure__;
 # endif
 #endif
 
 #ifdef __USE_XOPEN2K8
 /* Return the number of wide characters in S, but at most MAXLEN.  */
 extern size_t wcsnlen (const wchar_t *__s, size_t __maxlen)
	  __THROW __attribute_pure__;
 #endif
 
 
 /* Search N wide characters of S for C.  */
 #ifdef __CORRECT_ISO_CPP_WCHAR_H_PROTO
 extern "C++" wchar_t *wmemchr (wchar_t *__s, wchar_t __c, size_t __n)
	  __THROW __asm ("wmemchr") __attribute_pure__;
 extern "C++" const wchar_t *wmemchr (const wchar_t *__s, wchar_t __c,
					  size_t __n)
	  __THROW __asm ("wmemchr") __attribute_pure__;
 #else
 extern wchar_t *wmemchr (const wchar_t *__s, wchar_t __c, size_t __n)
	  __THROW __attribute_pure__;
 #endif
 
 /* Compare N wide characters of S1 and S2.  */
 extern int wmemcmp (const wchar_t *__s1, const wchar_t *__s2, size_t __n)
	  __THROW __attribute_pure__;
 
 /* Copy N wide characters of SRC to DEST.  */
 extern wchar_t *wmemcpy (wchar_t *__restrict __s1,
			  const wchar_t *__restrict __s2, size_t __n) __THROW;
 
 /* Copy N wide characters of SRC to DEST, guaranteeing
	correct behavior for overlapping strings.  */
 extern wchar_t *wmemmove (wchar_t *__s1, const wchar_t *__s2, size_t __n)
	  __THROW;
 
 /* Set N wide characters of S to C.  */
 extern wchar_t *wmemset (wchar_t *__s, wchar_t __c, size_t __n) __THROW;
 
 #ifdef __USE_GNU
 /* Copy N wide characters of SRC to DEST and return pointer to following
	wide character.  */
 extern wchar_t *wmempcpy (wchar_t *__restrict __s1,
			   const wchar_t *__restrict __s2, size_t __n)
	  __THROW;
 #endif
 
 
 /* Determine whether C constitutes a valid (one-byte) multibyte
	character.  */
 extern wint_t btowc (int __c) __THROW;
 
 /* Determine whether C corresponds to a member of the extended
	character set whose multibyte representation is a single byte.  */
 extern int wctob (wint_t __c) __THROW;
 
 /* Determine whether PS points to an object representing the initial
	state.  */
 extern int mbsinit (const mbstate_t *__ps) __THROW __attribute_pure__;
 
 /* Write wide character representation of multibyte character pointed
	to by S to PWC.  */
 extern size_t mbrtowc (wchar_t *__restrict __pwc,
				const char *__restrict __s, size_t __n,
				mbstate_t *__restrict __p) __THROW;
 
 /* Write multibyte representation of wide character WC to S.  */
 extern size_t wcrtomb (char *__restrict __s, wchar_t __wc,
				mbstate_t *__restrict __ps) __THROW;
 
 /* Return number of bytes in multibyte character pointed to by S.  */
 extern size_t __mbrlen (const char *__restrict __s, size_t __n,
			 mbstate_t *__restrict __ps) __THROW;
 extern size_t mbrlen (const char *__restrict __s, size_t __n,
			   mbstate_t *__restrict __ps) __THROW;
 
 #ifdef __USE_EXTERN_INLINES
 /* Define inline function as optimization.  */
 
 /* We can use the BTOWC and WCTOB optimizations since we know that all
	locales must use ASCII encoding for the values in the ASCII range
	and because the wchar_t encoding is always ISO 10646.  */
 extern wint_t __btowc_alias (int __c) __asm ("btowc");
 __extern_inline wint_t
 __NTH (btowc (int __c))
 { return (__builtin_constant_p (__c) && __c >= '\0' && __c <= '\x7f'
	   ? (wint_t) __c : __btowc_alias (__c)); }
 
 extern int __wctob_alias (wint_t __c) __asm ("wctob");
 __extern_inline int
 __NTH (wctob (wint_t __wc))
 { return (__builtin_constant_p (__wc) && __wc >= L'\0' && __wc <= L'\x7f'
	   ? (int) __wc : __wctob_alias (__wc)); }
 
 __extern_inline size_t
 __NTH (mbrlen (const char *__restrict __s, size_t __n,
			mbstate_t *__restrict __ps))
 { return (__ps != NULL
	   ? mbrtowc (NULL, __s, __n, __ps) : __mbrlen (__s, __n, NULL)); }
 #endif
 
 /* Write wide character representation of multibyte character string
	SRC to DST.  */
 extern size_t mbsrtowcs (wchar_t *__restrict __dst,
			  const char **__restrict __src, size_t __len,
			  mbstate_t *__restrict __ps) __THROW;
 
 /* Write multibyte character representation of wide character string
	SRC to DST.  */
 extern size_t wcsrtombs (char *__restrict __dst,
			  const wchar_t **__restrict __src, size_t __len,
			  mbstate_t *__restrict __ps) __THROW;
 
 
 #ifdef	__USE_XOPEN2K8
 /* Write wide character representation of at most NMC bytes of the
	multibyte character string SRC to DST.  */
 extern size_t mbsnrtowcs (wchar_t *__restrict __dst,
			   const char **__restrict __src, size_t __nmc,
			   size_t __len, mbstate_t *__restrict __ps) __THROW;
 
 /* Write multibyte character representation of at most NWC characters
	from the wide character string SRC to DST.  */
 extern size_t wcsnrtombs (char *__restrict __dst,
			   const wchar_t **__restrict __src,
			   size_t __nwc, size_t __len,
			   mbstate_t *__restrict __ps) __THROW;
 #endif	/* use POSIX 2008 */
 
 
 /* The following functions are extensions found in X/Open CAE.  */
 #ifdef __USE_XOPEN
 /* Determine number of column positions required for C.  */
 extern int wcwidth (wchar_t __c) __THROW;
 
 /* Determine number of column positions required for first N wide
	characters (or fewer if S ends before this) in S.  */
 extern int wcswidth (const wchar_t *__s, size_t __n) __THROW;
 #endif	/* Use X/Open.  */
 
 
 /* Convert initial portion of the wide string NPTR to `double'
	representation.  */
 extern double wcstod (const wchar_t *__restrict __nptr,
			   wchar_t **__restrict __endptr) __THROW;
 
 #ifdef __USE_ISOC99
 /* Likewise for `float' and `long double' sizes of floating-point numbers.  */
 extern float wcstof (const wchar_t *__restrict __nptr,
			  wchar_t **__restrict __endptr) __THROW;
 extern long double wcstold (const wchar_t *__restrict __nptr,
				 wchar_t **__restrict __endptr) __THROW;
 #endif /* C99 */
 
 #if __GLIBC_USE (IEC_60559_TYPES_EXT) && __GLIBC_USE (ISOC23)
 /* Likewise for `_FloatN' and `_FloatNx' when support is enabled.  */
 
 # if __HAVE_FLOAT16
 extern _Float16 wcstof16 (const wchar_t *__restrict __nptr,
			   wchar_t **__restrict __endptr) __THROW;
 # endif
 
 # if __HAVE_FLOAT32
 extern _Float32 wcstof32 (const wchar_t *__restrict __nptr,
			   wchar_t **__restrict __endptr) __THROW;
 # endif
 
 # if __HAVE_FLOAT64
 extern _Float64 wcstof64 (const wchar_t *__restrict __nptr,
			   wchar_t **__restrict __endptr) __THROW;
 # endif
 
 # if __HAVE_FLOAT128
 extern _Float128 wcstof128 (const wchar_t *__restrict __nptr,
				 wchar_t **__restrict __endptr) __THROW;
 # endif
 
 # if __HAVE_FLOAT32X
 extern _Float32x wcstof32x (const wchar_t *__restrict __nptr,
				 wchar_t **__restrict __endptr) __THROW;
 # endif
 
 # if __HAVE_FLOAT64X
 extern _Float64x wcstof64x (const wchar_t *__restrict __nptr,
				 wchar_t **__restrict __endptr) __THROW;
 # endif
 
 # if __HAVE_FLOAT128X
 extern _Float128x wcstof128x (const wchar_t *__restrict __nptr,
				   wchar_t **__restrict __endptr) __THROW;
 # endif
 #endif /* __GLIBC_USE (IEC_60559_TYPES_EXT) && __GLIBC_USE (ISOC23) */
 
 
 /* Convert initial portion of wide string NPTR to `long int'
	representation.  */
 extern long int wcstol (const wchar_t *__restrict __nptr,
			 wchar_t **__restrict __endptr, int __base) __THROW;
 
 /* Convert initial portion of wide string NPTR to `unsigned long int'
	representation.  */
 extern unsigned long int wcstoul (const wchar_t *__restrict __nptr,
				   wchar_t **__restrict __endptr, int __base)
	  __THROW;
 
 #ifdef __USE_ISOC99
 /* Convert initial portion of wide string NPTR to `long long int'
	representation.  */
 __extension__
 extern long long int wcstoll (const wchar_t *__restrict __nptr,
				   wchar_t **__restrict __endptr, int __base)
	  __THROW;
 
 /* Convert initial portion of wide string NPTR to `unsigned long long int'
	representation.  */
 __extension__
 extern unsigned long long int wcstoull (const wchar_t *__restrict __nptr,
					 wchar_t **__restrict __endptr,
					 int __base) __THROW;
 #endif /* ISO C99.  */
 
 #ifdef __USE_GNU
 /* Convert initial portion of wide string NPTR to `long long int'
	representation.  */
 __extension__
 extern long long int wcstoq (const wchar_t *__restrict __nptr,
				  wchar_t **__restrict __endptr, int __base)
	  __THROW;
 
 /* Convert initial portion of wide string NPTR to `unsigned long long int'
	representation.  */
 __extension__
 extern unsigned long long int wcstouq (const wchar_t *__restrict __nptr,
						wchar_t **__restrict __endptr,
						int __base) __THROW;
 #endif /* Use GNU.  */
 
 /* Versions of the above functions that handle '0b' and '0B' prefixes
	in base 0 or 2.  */
 #if __GLIBC_USE (C23_STRTOL)
 # ifdef __REDIRECT
 extern long int __REDIRECT_NTH (wcstol, (const wchar_t *__restrict __nptr,
					  wchar_t **__restrict __endptr,
					  int __base), __isoc23_wcstol);
 extern unsigned long int __REDIRECT_NTH (wcstoul,
					  (const wchar_t *__restrict __nptr,
					   wchar_t **__restrict __endptr,
					   int __base), __isoc23_wcstoul);
 __extension__
 extern long long int __REDIRECT_NTH (wcstoll,
					  (const wchar_t *__restrict __nptr,
					   wchar_t **__restrict __endptr,
					   int __base), __isoc23_wcstoll);
 __extension__
 extern unsigned long long int __REDIRECT_NTH (wcstoull,
						   (const wchar_t *__restrict __nptr,
							wchar_t **__restrict __endptr,
							int __base), __isoc23_wcstoull);
 #  ifdef __USE_GNU
 __extension__
 extern long long int __REDIRECT_NTH (wcstoq, (const wchar_t *__restrict __nptr,
						   wchar_t **__restrict __endptr,
						   int __base), __isoc23_wcstoll);
 __extension__
 extern unsigned long long int __REDIRECT_NTH (wcstouq,
						   (const wchar_t *__restrict __nptr,
							wchar_t **__restrict __endptr,
							int __base), __isoc23_wcstoull);
 #  endif
 # else
 extern long int __isoc23_wcstol (const wchar_t *__restrict __nptr,
				  wchar_t **__restrict __endptr, int __base)
	  __THROW;
 extern unsigned long int __isoc23_wcstoul (const wchar_t *__restrict __nptr,
						wchar_t **__restrict __endptr,
						int __base)
	  __THROW;
 __extension__
 extern long long int __isoc23_wcstoll (const wchar_t *__restrict __nptr,
						wchar_t **__restrict __endptr,
						int __base)
	  __THROW;
 __extension__
 extern unsigned long long int __isoc23_wcstoull (const wchar_t *__restrict __nptr,
						  wchar_t **__restrict __endptr,
						  int __base)
	  __THROW;
 #  define wcstol __isoc23_wcstol
 #  define wcstoul __isoc23_wcstoul
 #  define wcstoll __isoc23_wcstoll
 #  define wcstoull __isoc23_wcstoull
 #  ifdef __USE_GNU
 #   define wcstoq __isoc23_wcstoll
 #   define wcstouq __isoc23_wcstoull
 #  endif
 # endif
 #endif
 
 
 #ifdef __USE_XOPEN2K8
 /* Copy SRC to DEST, returning the address of the terminating L'\0' in
	DEST.  */
 extern wchar_t *wcpcpy (wchar_t *__restrict __dest,
			 const wchar_t *__restrict __src) __THROW;
 
 /* Copy no more than N characters of SRC to DEST, returning the address of
	the last character written into DEST.  */
 extern wchar_t *wcpncpy (wchar_t *__restrict __dest,
			  const wchar_t *__restrict __src, size_t __n)
	  __THROW;
 #endif
 
 
 /* Wide character I/O functions.  */
 
 #if defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2)
 # ifndef __attr_dealloc_fclose
 #   if defined __has_builtin
 #     if __has_builtin (__builtin_fclose)
 /* If the attribute macro hasn't been defined yet (by <stdio.h>) and
	fclose is a built-in, use it.  */
 #      define __attr_dealloc_fclose __attr_dealloc (__builtin_fclose, 1)
 #     endif
 #   endif
 # endif
 # ifndef __attr_dealloc_fclose
 #  define __attr_dealloc_fclose /* empty */
 # endif
 #endif
 
 #if defined __USE_ISOC95 || defined __USE_UNIX98
 /* Write formatted output to stdout.
 
	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
 extern int wprintf (const wchar_t *__restrict __format, ...)
	  /* __attribute__ ((__format__ (__wprintf__, 1, 2))) */;
 /* Write formatted output of at most N characters to S.  */
 extern int swprintf (wchar_t *__restrict __s, size_t __n,
			  const wchar_t *__restrict __format, ...)
	  __THROW /* __attribute__ ((__format__ (__wprintf__, 3, 4))) */;
 /* Write formatted output to stdout from argument list ARG.
 
	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
 extern int vwprintf (const wchar_t *__restrict __format,
			  __gnuc_va_list __arg)
	  /* __attribute__ ((__format__ (__wprintf__, 1, 0))) */;
 /* Write formatted output of at most N character to S from argument
	list ARG.  */
 extern int vswprintf (wchar_t *__restrict __s, size_t __n,
			   const wchar_t *__restrict __format,
			   __gnuc_va_list __arg)
	  __THROW /* __attribute__ ((__format__ (__wprintf__, 3, 0))) */;
 /* Read formatted input from stdin.
 
	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
 extern int wscanf (const wchar_t *__restrict __format, ...)
	  /* __attribute__ ((__format__ (__wscanf__, 1, 2))) */;
 /* Read formatted input from S.  */
 extern int swscanf (const wchar_t *__restrict __s,
			 const wchar_t *__restrict __format, ...)
	  __THROW /* __attribute__ ((__format__ (__wscanf__, 2, 3))) */;
 
 #endif /* Use ISO C95, C99 and Unix98. */
 
 #ifdef __USE_ISOC99
 /* Read formatted input from stdin into argument list ARG.
 
	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
 extern int vwscanf (const wchar_t *__restrict __format,
			 __gnuc_va_list __arg)
	  /* __attribute__ ((__format__ (__wscanf__, 1, 0))) */;
 /* Read formatted input from S into argument list ARG.  */
 extern int vswscanf (const wchar_t *__restrict __s,
			  const wchar_t *__restrict __format,
			  __gnuc_va_list __arg)
	  __THROW /* __attribute__ ((__format__ (__wscanf__, 2, 0))) */;
 
 #endif /* Use ISO C99. */
 
 /* Read a character from stdin.
 
	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
 extern wint_t getwchar (void);
 
 /* Write a character to stdout.
 
	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
 extern wint_t putwchar (wchar_t __wc);
 
 
 /* Format TP into S according to FORMAT.
	Write no more than MAXSIZE wide characters and return the number
	of wide characters written, or 0 if it would exceed MAXSIZE.  */
 extern size_t wcsftime (wchar_t *__restrict __s, size_t __maxsize,
			 const wchar_t *__restrict __format,
			 const struct tm *__restrict __tp) __THROW;
 
 /* Define some macros helping to catch buffer overflows.  */
 #if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
 /* Declare all functions from bits/wchar2-decl.h first.  */
 # include <bits/wchar2-decl.h>
 #endif
 
 /* The following headers provide asm redirections.  These redirections must
	appear before the first usage of these functions, e.g. in bits/wchar.h.  */
 #if defined __LDBL_COMPAT || __LDOUBLE_REDIRECTS_TO_FLOAT128_ABI == 1
 # include <bits/wchar-ldbl.h>
 #endif
 
 #if __USE_FORTIFY_LEVEL > 0 && defined __fortify_function
 /* Now include the function definitions and redirects too.  */
 # include <bits/wchar2.h>
 #endif
 
 __END_DECLS
 
 #endif /* wchar.h  */
 