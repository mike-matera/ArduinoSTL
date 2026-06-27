/* Copyright (C) 1993-2024 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */

/* NOTE: libio is now exclusively used only by glibc since libstdc++ has its
   own implementation.  As a result, functions that were implemented for C++
   (like *sputn) may no longer have C++ semantics.  This is of course only
   relevant for internal callers of these functions since these functions are
   not intended for external use otherwise.

   FIXME: All of the C++ cruft eventually needs to go away.  */

#ifndef _LIBIOP_H
#define _LIBIOP_H 1

#include <stddef.h>

#include <errno.h>

#include <math_ldbl_opt.h>

#define _IO_seek_set 0
#define _IO_seek_cur 1
#define _IO_seek_end 2

/* THE JUMPTABLE FUNCTIONS.

 * The _IO_FILE type is used to implement the FILE type in GNU libc,
 * as well as the streambuf class in GNU iostreams for C++.
 * These are all the same, just used differently.
 * An _IO_FILE (or FILE) object is allows followed by a pointer to
 * a jump table (of pointers to functions).  The pointer is accessed
 * with the _IO_JUMPS macro.  The jump table has an eccentric format,
 * so as to be compatible with the layout of a C++ virtual function table.
 * (as implemented by g++).  When a pointer to a streambuf object is
 * coerced to an (FILE*), then _IO_JUMPS on the result just
 * happens to point to the virtual function table of the streambuf.
 * Thus the _IO_JUMPS function table used for C stdio/libio does
 * double duty as the virtual function table for C++ streambuf.
 *
 * The entries in the _IO_JUMPS function table (and hence also the
 * virtual functions of a streambuf) are described below.
 * The first parameter of each function entry is the _IO_FILE/streambuf
 * object being acted on (i.e. the 'this' parameter).
 */

/* Type of MEMBER in struct type TYPE.  */
#define _IO_MEMBER_TYPE(TYPE, MEMBER) __typeof__ (((TYPE){}).MEMBER)

/* Essentially ((TYPE *) THIS)->MEMBER, but avoiding the aliasing
   violation in case THIS has a different pointer type.  */
#define _IO_CAST_FIELD_ACCESS(THIS, TYPE, MEMBER) \
  (*(_IO_MEMBER_TYPE (TYPE, MEMBER) *)(((char *) (THIS)) \
				       + offsetof(TYPE, MEMBER)))

#define _IO_JUMPS(THIS) (THIS)->vtable
#define _IO_JUMPS_FILE_plus(THIS) \
  _IO_CAST_FIELD_ACCESS ((THIS), struct _IO_FILE_plus, vtable)
#define _IO_WIDE_JUMPS(THIS) \
  _IO_CAST_FIELD_ACCESS ((THIS), struct _IO_FILE, _wide_data)->_wide_vtable
#define _IO_CHECK_WIDE(THIS) \
  (_IO_CAST_FIELD_ACCESS ((THIS), struct _IO_FILE, _wide_data) != NULL)

#if _IO_JUMPS_OFFSET
# define _IO_JUMPS_FUNC(THIS) \
  (IO_validate_vtable                                                   \
   (*(struct _IO_jump_t **) ((void *) &_IO_JUMPS_FILE_plus (THIS)	\
			     + (THIS)->_vtable_offset)))
# define _IO_JUMPS_FUNC_UPDATE(THIS, VTABLE)				\
  (*(const struct _IO_jump_t **) ((void *) &_IO_JUMPS_FILE_plus (THIS)	\
				  + (THIS)->_vtable_offset) = (VTABLE))
# define _IO_vtable_offset(THIS) (THIS)->_vtable_offset
#else
# define _IO_JUMPS_FUNC(THIS) (IO_validate_vtable (_IO_JUMPS_FILE_plus (THIS)))
# define _IO_JUMPS_FUNC_UPDATE(THIS, VTABLE) \
  (_IO_JUMPS_FILE_plus (THIS) = (VTABLE))
# define _IO_vtable_offset(THIS) 0
#endif
#define _IO_WIDE_JUMPS_FUNC(THIS) _IO_WIDE_JUMPS(THIS)
#define JUMP_FIELD(TYPE, NAME) TYPE NAME
#define JUMP0(FUNC, THIS) (_IO_JUMPS_FUNC(THIS)->FUNC) (THIS)
#define JUMP1(FUNC, THIS, X1) (_IO_JUMPS_FUNC(THIS)->FUNC) (THIS, X1)
#define JUMP2(FUNC, THIS, X1, X2) (_IO_JUMPS_FUNC(THIS)->FUNC) (THIS, X1, X2)
#define JUMP3(FUNC, THIS, X1,X2,X3) (_IO_JUMPS_FUNC(THIS)->FUNC) (THIS, X1,X2, X3)
#define JUMP_INIT(NAME, VALUE) VALUE
#define JUMP_INIT_DUMMY JUMP_INIT(dummy, 0), JUMP_INIT (dummy2, 0)

#define WJUMP0(FUNC, THIS) (_IO_WIDE_JUMPS_FUNC(THIS)->FUNC) (THIS)
#define WJUMP1(FUNC, THIS, X1) (_IO_WIDE_JUMPS_FUNC(THIS)->FUNC) (THIS, X1)
#define WJUMP2(FUNC, THIS, X1, X2) (_IO_WIDE_JUMPS_FUNC(THIS)->FUNC) (THIS, X1, X2)
#define WJUMP3(FUNC, THIS, X1,X2,X3) (_IO_WIDE_JUMPS_FUNC(THIS)->FUNC) (THIS, X1,X2, X3)

/* The 'finish' function does any final cleaning up of an _IO_FILE object.
   It does not delete (free) it, but does everything else to finalize it.
   It matches the streambuf::~streambuf virtual destructor.  */
typedef void (*_IO_finish_t) (FILE *, int); /* finalize */
#define _IO_FINISH(FP) JUMP1 (__finish, FP, 0)
#define _IO_WFINISH(FP) WJUMP1 (__finish, FP, 0)

/* The 'overflow' hook flushes the buffer.
   The second argument is a character, or EOF.
   It matches the streambuf::overflow virtual function. */
typedef int (*_IO_overflow_t) (FILE *, int);
#define _IO_OVERFLOW(FP, CH) JUMP1 (__overflow, FP, CH)
#define _IO_WOVERFLOW(FP, CH) WJUMP1 (__overflow, FP, CH)

/* The 'underflow' hook tries to fills the get buffer.
   It returns the next character (as an unsigned char) or EOF.  The next
   character remains in the get buffer, and the get position is not changed.
   It matches the streambuf::underflow virtual function. */
typedef int (*_IO_underflow_t) (FILE *);
#define _IO_UNDERFLOW(FP) JUMP0 (__underflow, FP)
#define _IO_WUNDERFLOW(FP) WJUMP0 (__underflow, FP)

/* The 'uflow' hook returns the next character in the input stream
   (cast to unsigned char), and increments the read position;
   EOF is returned on failure.
   It matches the streambuf::uflow virtual function, which is not in the
   cfront implementation, but was added to C++ by the ANSI/ISO committee. */
#define _IO_UFLOW(FP) JUMP0 (__uflow, FP)
#define _IO_WUFLOW(FP) WJUMP0 (__uflow, FP)

/* The 'pbackfail' hook handles backing up.
   It matches the streambuf::pbackfail virtual function. */
typedef int (*_IO_pbackfail_t) (FILE *, int);
#define _IO_PBACKFAIL(FP, CH) JUMP1 (__pbackfail, FP, CH)
#define _IO_WPBACKFAIL(FP, CH) WJUMP1 (__pbackfail, FP, CH)

/* The 'xsputn' hook writes upto N characters from buffer DATA.
   Returns EOF or the number of character actually written.
   It matches the streambuf::xsputn virtual function. */
typedef size_t (*_IO_xsputn_t) (FILE *FP, const void *DATA,
				    size_t N);
#define _IO_XSPUTN(FP, DATA, N) JUMP2 (__xsputn, FP, DATA, N)
#define _IO_WXSPUTN(FP, DATA, N) WJUMP2 (__xsputn, FP, DATA, N)

/* The 'xsgetn' hook reads upto N characters into buffer DATA.
   Returns the number of character actually read.
   It matches the streambuf::xsgetn virtual function. */
typedef size_t (*_IO_xsgetn_t) (FILE *FP, void *DATA, size_t N);
#define _IO_XSGETN(FP, DATA, N) JUMP2 (__xsgetn, FP, DATA, N)
#define _IO_WXSGETN(FP, DATA, N) WJUMP2 (__xsgetn, FP, DATA, N)

/* The 'sync' hook attempts to synchronize the internal data structures
   of the file with the external state.
   It matches the streambuf::sync virtual function. */
typedef int (*_IO_sync_t) (FILE *);
#define _IO_SYNC(FP) JUMP0 (__sync, FP)
#define _IO_WSYNC(FP) WJUMP0 (__sync, FP)

/* The 'doallocate' hook is used to tell the file to allocate a buffer.
   It matches the streambuf::doallocate virtual function, which is not
   in the ANSI/ISO C++ standard, but is part traditional implementations. */
typedef int (*_IO_doallocate_t) (FILE *);
#define _IO_DOALLOCATE(FP) JUMP0 (__doallocate, FP)
#define _IO_WDOALLOCATE(FP) WJUMP0 (__doallocate, FP)

/* The 'sysstat' hook is used to get information about an external file
   into a struct stat buffer.  It generalizes the Unix fstat(2) call.
   It matches the streambuf::sys_stat virtual function, which is
   specific to this implementation. */
typedef int (*_IO_stat_t) (FILE *, void *);
#define _IO_SYSSTAT(FP, BUF) JUMP1 (__stat, FP, BUF)
#define _IO_WSYSSTAT(FP, BUF) WJUMP1 (__stat, FP, BUF)

/* The 'showmany' hook can be used to get an image how much input is
   available.  In many cases the answer will be 0 which means unknown
   but some cases one can provide real information.  */
typedef int (*_IO_showmanyc_t) (FILE *);
#define _IO_SHOWMANYC(FP) JUMP0 (__showmanyc, FP)
#define _IO_WSHOWMANYC(FP) WJUMP0 (__showmanyc, FP)

/* The 'imbue' hook is used to get information about the currently
   installed locales.  */
typedef void (*_IO_imbue_t) (FILE *, void *);
#define _IO_IMBUE(FP, LOCALE) JUMP1 (__imbue, FP, LOCALE)
#define _IO_WIMBUE(FP, LOCALE) WJUMP1 (__imbue, FP, LOCALE)


#define _IO_CHAR_TYPE char /* unsigned char ? */
#define _IO_INT_TYPE int

/* We always allocate an extra word following an _IO_FILE.
   This contains a pointer to the function jump table used.
   This is for compatibility with C++ streambuf; the word can
   be used to smash to a pointer to a virtual function table. */

struct _IO_FILE_plus
{
  FILE file;
  const struct _IO_jump_t *vtable;
};

#ifdef _IO_USE_OLD_IO_FILE
/* This structure is used by the compatibility code as if it were an
   _IO_FILE_plus, but has enough space to initialize the _mode argument
   of an _IO_FILE_complete.  */
struct _IO_FILE_complete_plus
{
  struct _IO_FILE_complete file;
  const struct _IO_jump_t *vtable;
};
#endif


/* Iterator type for walking global linked list of _IO_FILE objects. */

typedef FILE *_IO_ITER;

extern int __printf_buffer_as_file_overflow (FILE *fp, int ch);
extern size_t __printf_buffer_as_file_xsputn (FILE *fp, const void *buf,
					      size_t len);
extern size_t __wprintf_buffer_as_file_xsputn (FILE *fp, const void *buf,
					       size_t len);

#ifdef SHARED
# define libio_static_fn_required(name)
#else
# define libio_static_fn_required(name) __asm (".globl " #name);
#endif

extern int _IO_do_write (FILE *, const char *, size_t);
libc_hidden_proto (_IO_do_write)
extern int _IO_new_do_write (FILE *, const char *, size_t);
extern int _IO_old_do_write (FILE *, const char *, size_t);
extern int _IO_wdo_write (FILE *, const wchar_t *, size_t);
libc_hidden_proto (_IO_wdo_write)
extern int _IO_flush_all (void);
libc_hidden_proto (_IO_flush_all)
extern void _IO_flush_all_linebuffered (void);
libc_hidden_proto (_IO_flush_all_linebuffered)


#define _IO_do_flush(_f) \
  ((_f)->_mode <= 0							      \
   ? _IO_do_write(_f, (_f)->_IO_write_base,				      \
		  (_f)->_IO_write_ptr-(_f)->_IO_write_base)		      \
   : _IO_wdo_write(_f, (_f)->_wide_data->_IO_write_base,		      \
		   ((_f)->_wide_data->_IO_write_ptr			      \
		    - (_f)->_wide_data->_IO_write_base)))
#define _IO_old_do_flush(_f) \
  _IO_old_do_write(_f, (_f)->_IO_write_base, \
		   (_f)->_IO_write_ptr-(_f)->_IO_write_base)
#define _IO_in_put_mode(_fp) ((_fp)->_flags & _IO_CURRENTLY_PUTTING)
#define _IO_mask_flags(fp, f, mask) \
       ((fp)->_flags = ((fp)->_flags & ~(mask)) | ((f) & (mask)))
#define _IO_setg(fp, eb, g, eg)  ((fp)->_IO_read_base = (eb),\
	(fp)->_IO_read_ptr = (g), (fp)->_IO_read_end = (eg))
#define _IO_wsetg(fp, eb, g, eg)  ((fp)->_wide_data->_IO_read_base = (eb),\
	(fp)->_wide_data->_IO_read_ptr = (g), \
	(fp)->_wide_data->_IO_read_end = (eg))
#define _IO_setp(__fp, __p, __ep) \
       ((__fp)->_IO_write_base = (__fp)->_IO_write_ptr \
	= __p, (__fp)->_IO_write_end = (__ep))
#define _IO_wsetp(__fp, __p, __ep) \
       ((__fp)->_wide_data->_IO_write_base \
	= (__fp)->_wide_data->_IO_write_ptr = __p, \
	(__fp)->_wide_data->_IO_write_end = (__ep))
#define _IO_have_backup(fp) ((fp)->_IO_save_base != NULL)
#define _IO_have_wbackup(fp) ((fp)->_wide_data->_IO_save_base != NULL)
#define _IO_in_backup(fp) ((fp)->_flags & _IO_IN_BACKUP)
#define _IO_have_markers(fp) ((fp)->_markers != NULL)
#define _IO_blen(fp) ((fp)->_IO_buf_end - (fp)->_IO_buf_base)
#define _IO_wblen(fp) ((fp)->_wide_data->_IO_buf_end \
		       - (fp)->_wide_data->_IO_buf_base)

/* Internal versions of v*printf that take an additional flags
   parameter.  */
extern int __vfprintf_internal (FILE *fp, const char *format, va_list ap,
				unsigned int mode_flags)
    attribute_hidden;
extern int __vfwprintf_internal (FILE *fp, const wchar_t *format, va_list ap,
				 unsigned int mode_flags)
    attribute_hidden;

extern int __vasprintf_internal (char **result_ptr, const char *format,
				 va_list ap, unsigned int mode_flags)
    attribute_hidden;
extern int __vdprintf_internal (int d, const char *format, va_list ap,
				unsigned int mode_flags)
    attribute_hidden;

/* Note: __vsprintf_internal, unlike vsprintf, does take a maxlen argument,
   because it's called by both vsprintf and vsprintf_chk.  If maxlen is
   not set to -1, overrunning the buffer will cause a prompt crash.
   This is the behavior of ordinary (v)sprintf functions, thus they call
   __vsprintf_internal with that argument set to -1.  */
extern int __vsprintf_internal (char *string, size_t maxlen,
				const char *format, va_list ap,
				unsigned int mode_flags)
    attribute_hidden;

extern int __vsnprintf_internal (char *string, size_t maxlen,
				 const char *format, va_list ap,
				 unsigned int mode_flags)
    attribute_hidden;
extern int __vswprintf_internal (wchar_t *string, size_t maxlen,
				 const wchar_t *format, va_list ap,
				 unsigned int mode_flags)
    attribute_hidden;

/* Flags for __v*printf_internal.

   PRINTF_LDBL_IS_DBL indicates whether long double values are to be
   handled as having the same format as double, in which case the flag
   should be set to one, or as another format, otherwise.

   PRINTF_FORTIFY, when set to one, indicates that fortification checks
   are to be performed in input parameters.  This is used by the
   __*printf_chk functions, which are used when _FORTIFY_SOURCE is
   defined to 1 or 2.  Otherwise, such checks are ignored.

   PRINTF_CHK indicates, to the internal function being called, that the
   call is originated from one of the __*printf_chk functions.

   PRINTF_LDBL_USES_FLOAT128 is used on platforms where the long double
   format used to be different from the IEC 60559 double format *and*
   also different from the Quadruple 128-bits IEC 60559 format (such as
   the IBM Extended Precision format on powerpc or the 80-bits IEC 60559
   format on x86), but was later converted to the Quadruple 128-bits IEC
   60559 format, which is the same format that the _Float128 always has
   (hence the `USES_FLOAT128' suffix in the name of the flag).  When set
   to one, this macro indicates that long double values are to be
   handled as having this new format.  Otherwise, they should be handled
   as the previous format on that platform.  */
#define PRINTF_LDBL_IS_DBL		0x0001
#define PRINTF_FORTIFY			0x0002
#define PRINTF_CHK			0x0004
#define PRINTF_LDBL_USES_FLOAT128	0x0008

#if _G_HAVE_MMAP

# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/param.h>

# if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#  define MAP_ANONYMOUS MAP_ANON
# endif

# if !defined(MAP_ANONYMOUS)
#  undef _G_HAVE_MMAP
#  define _G_HAVE_MMAP 0
# endif

#endif /* _G_HAVE_MMAP */

/* Flags for __vfscanf_internal and __vfwscanf_internal.

   SCANF_LDBL_IS_DBL indicates whether long double values are to be
   handled as having the same format as double, in which case the flag
   should be set to one, or as another format, otherwise.

   SCANF_ISOC99_A, when set to one, indicates that the ISO C99 or POSIX
   behavior of the scanf functions is to be used, i.e. automatic
   allocation for input strings with %as, %aS and %a[, a GNU extension,
   is disabled. This is the behavior that the __isoc99_scanf family of
   functions use.  When the flag is set to zero, automatic allocation is
   enabled.

   SCANF_ISOC23_BIN_CST, when set to one, indicates the %i accepts
   binary constants starting 0b or 0B.

   SCANF_LDBL_USES_FLOAT128 is used on platforms where the long double
   format used to be different from the IEC 60559 double format *and*
   also different from the Quadruple 128-bits IEC 60559 format (such as
   the IBM Extended Precision format on powerpc or the 80-bits IEC 60559
   format on x86), but was later converted to the Quadruple 128-bits IEC
   60559 format, which is the same format that the _Float128 always has
   (hence the `USES_FLOAT128' suffix in the name of the flag).  When set
   to one, this macros indicates that long double values are to be
   handled as having this new format.  Otherwise, they should be handled
   as the previous format on that platform.  */
#define SCANF_LDBL_IS_DBL		0x0001
#define SCANF_ISOC99_A			0x0002
#define SCANF_ISOC23_BIN_CST		0x0004
#define SCANF_LDBL_USES_FLOAT128	0x0008

#ifdef _IO_MTSAFE_IO
/* check following! */
# ifdef _IO_USE_OLD_IO_FILE
#  define FILEBUF_LITERAL(CHAIN, FLAGS, FD, WDP) \
       { _IO_MAGIC+_IO_LINKED+_IO_IS_FILEBUF+FLAGS, \
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (FILE *) CHAIN, FD, \
	 0, _IO_pos_BAD, 0, 0, { 0 }, &_IO_stdfile_##FD##_lock }
# else
#  define FILEBUF_LITERAL(CHAIN, FLAGS, FD, WDP) \
       { _IO_MAGIC+_IO_LINKED+_IO_IS_FILEBUF+FLAGS, \
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (FILE *) CHAIN, FD, \
	 0, _IO_pos_BAD, 0, 0, { 0 }, &_IO_stdfile_##FD##_lock, _IO_pos_BAD,\
	 NULL, WDP, 0 }
# endif
#else
# ifdef _IO_USE_OLD_IO_FILE
#  define FILEBUF_LITERAL(CHAIN, FLAGS, FD, WDP) \
       { _IO_MAGIC+_IO_LINKED+_IO_IS_FILEBUF+FLAGS, \
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (FILE *) CHAIN, FD, \
	 0, _IO_pos_BAD }
# else
#  define FILEBUF_LITERAL(CHAIN, FLAGS, FD, WDP) \
       { _IO_MAGIC+_IO_LINKED+_IO_IS_FILEBUF+FLAGS, \
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (FILE *) CHAIN, FD, \
	 0, _IO_pos_BAD, 0, 0, { 0 }, 0, _IO_pos_BAD, \
	 NULL, WDP, 0 }
# endif
#endif

#ifdef IO_DEBUG
# define CHECK_FILE(FILE, RET) do {				\
    if ((FILE) == NULL						\
	|| ((FILE)->_flags & _IO_MAGIC_MASK) != _IO_MAGIC)	\
      {								\
	__set_errno (EINVAL);					\
	return RET;						\
      }								\
  } while (0)
#else
# define CHECK_FILE(FILE, RET) do { } while (0)
#endif

#if !defined _IO_MTSAFE_IO && IS_IN (libc)
# define _IO_acquire_lock(_fp)						      \
  do {
# define _IO_release_lock(_fp)						      \
  } while (0)
#endif

#ifdef SHARED
/* If equal to &_IO_vtable_check (with pointer guard protection),
   unknown vtable pointers are valid.  This function pointer is solely
   used as a flag.  */
extern void (*IO_accept_foreign_vtables) (void) attribute_hidden;

/* Assigns the passed function pointer (either NULL or
   &_IO_vtable_check) to IO_accept_foreign_vtables.  */
static inline void
IO_set_accept_foreign_vtables (void (*flag) (void))
{
  PTR_MANGLE (flag);
  atomic_store_relaxed (&IO_accept_foreign_vtables, flag);
}

#else  /* !SHARED */

/* The statically-linked version does nothing. */
static inline void
IO_set_accept_foreign_vtables (void (*flag) (void))
{
}

#endif

/* Character set conversion.  */

enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
  attribute_hidden;

#endif /* libioP.h.  */
