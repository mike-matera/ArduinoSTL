/* Declarations for internal libc locale interfaces
   Copyright (C) 1995-2024 Free Software Foundation, Inc.
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

#ifndef _LOCALEINFO_H
#define _LOCALEINFO_H 1

#include <stddef.h>
#include <langinfo.h>
#include <limits.h>
#include <stdint.h>

/* Magic number at the beginning of a locale data file for CATEGORY.  */
#define	LIMAGIC(category) \
  (category == LC_COLLATE						\
   ? ((unsigned int) (0x20051014 ^ (category)))				\
   : category == LC_CTYPE						\
   ? ((unsigned int) (0x20090720 ^ (category)))				\
   : ((unsigned int) (0x20031115 ^ (category))))

/* Two special weight constants for the collation data.  */
#define IGNORE_CHAR	2

/* We use a special value for the usage counter in `__locale_data' to
   signal that this data must never be removed anymore.  */
#define MAX_USAGE_COUNT (UINT_MAX - 1)
#define UNDELETABLE	UINT_MAX

/* Structure describing locale data in core for a category.  */
struct __locale_data
{
  const char *name;
  const char *filedata;		/* Region mapping the file data.  */
  enum				/* Flavor of storage used for those.  */
  {
    ld_malloced,		/* Both are malloc'd.  */
    ld_mapped,			/* name is malloc'd, filedata mmap'd */
    ld_archive			/* Both point into mmap'd archive regions.  */
  } alloc;

  /* This provides a slot for category-specific code to cache data
     computed about this locale.  Type of the data pointed to:

     LC_CTYPE   struct lc_ctype_data (_nl_intern_locale_data)
     LC_TIME    struct lc_time_data (_nl_init_alt_digit, _nl_init_era_entries)

     This data deallocated at the start of _nl_unload_locale.  */
  void *private;

  unsigned int usage_count;	/* Counter for users.  */

  int use_translit;		/* Nonzero if the mb*towv*() and wc*tomb()
				   functions should use transliteration.  */

  unsigned int nstrings;	/* Number of strings below.  */
  union locale_data_value
  {
    const char *string;
    unsigned int word;		/* Note endian issues vs 64-bit pointers.  */
  }
  values __flexarr;	/* Items, usually pointers into `filedata'.  */
};

/* This alignment is used for 32-bit integers in locale files, both
   those that are explicitly int32_t or uint32_t and those that are
   wchar_t, regardless of the (possibly smaller) alignment required
   for such integers on a particular host.  */
#define LOCFILE_ALIGN		sizeof (int32_t)
#define LOCFILE_ALIGN_MASK	(LOCFILE_ALIGN - 1)
#define LOCFILE_ALIGN_UP(x)	(((x) + LOCFILE_ALIGN - 1)	\
				 & ~LOCFILE_ALIGN_MASK)
#define LOCFILE_ALIGNED_P(x)	(((x) & LOCFILE_ALIGN_MASK) == 0)

/* We know three kinds of collation sorting rules.  */
enum coll_sort_rule
{
  illegal_0__,
  sort_forward,
  sort_backward,
  illegal_3__,
  sort_position,
  sort_forward_position,
  sort_backward_position,
  sort_mask
};

/* We can map the types of the entries into a few categories.  */
enum value_type
{
  none,
  string,
  stringarray,
  byte,
  bytearray,
  word,
  stringlist,
  wordarray,
  wstring,
  wstringarray,
  wstringlist
};


/* Definitions for `era' information from LC_TIME.  */
#define ERA_NAME_FORMAT_MEMBERS 4
#define ERA_M_NAME   0
#define ERA_M_FORMAT 1
#define ERA_W_NAME   2
#define ERA_W_FORMAT 3


/* Structure to access `era' information from LC_TIME.  */
struct era_entry
{
  const char *era_name;
  const char *era_format;
  const wchar_t *era_wname;
  const wchar_t *era_wformat;
  int absolute_direction;
  /* absolute direction:
     +1 indicates that year number is higher in the future. (like A.D.)
     -1 indicates that year number is higher in the past. (like B.C.)  */
};

/* Structure caching computed data about information from LC_TIME.
   The `private.time' member of `struct __locale_data' points to this.  */
struct lc_time_data
{
  struct era_entry *eras;
  size_t num_eras;
  int era_initialized;

  const char **alt_digits;
  const wchar_t **walt_digits;
  int alt_digits_initialized;
  int walt_digits_initialized;
};

/* Ancillary data for LC_CTYPE.  Co-allocated after struct
   __locale_data by _nl_intern_locale_data.  */
struct lc_ctype_data
{
  /* See get_gconv_fcts and __wcsmbs_load_conv.  */
  const struct gconv_fcts *fcts;

  /* Cached multi-byte string lengths.  This could be added to the
     locale data itself if the format is changed (which impacts
     existing statically linked binaries).  */

  /* For the outdigit decimal digits (copied from LC_CTYPE).  */
  unsigned char outdigit_bytes[10];

  /* If all outdigit_bytes elements are equal, this is that value,
     otherwise it is 0.  */
  unsigned char outdigit_bytes_all_equal;
};

/* LC_CTYPE specific:
   Hardwired indices for standard wide character translation mappings.  */
enum
{
  __TOW_toupper = 0,
  __TOW_tolower = 1
};


/* LC_CTYPE specific:
   Access a wide character class with a single character index.
   _ISCTYPE (c, desc) = iswctype (btowc (c), desc).
   c must be an `unsigned char'.  desc must be a nonzero wctype_t.  */
#define _ISCTYPE(c, desc) \
  (((((const uint32_t *) (desc)) - 8)[(c) >> 5] >> ((c) & 0x1f)) & 1)

/* Category name handling variables.  Concatenate all the strings in a
   single object to minimize relocations.  Individual strings can be
   accessed using _nl_category_names.  */
#define CATNAMEMF(line) CATNAMEMF1 (line)
#define CATNAMEMF1(line) str##line


/* For static linking it is desireable to avoid always linking in the code
   and data for every category when we can tell at link time that they are
   unused.  We can manage this playing some tricks with weak references.
   But with thread-local locale settings, it becomes quite ungainly unless
   we can use __thread variables.  So only in that case do we attempt this.  */
#ifndef SHARED
# define NL_CURRENT_INDIRECT	1
#endif

#ifdef NL_CURRENT_INDIRECT

/* For each category declare the thread-local variable for the current
   locale data.  This has an extra indirection so it points at the
   __locales[CATEGORY] element in either _nl_global_locale or the current
   locale object set by uselocale, which points at the actual data.  The
   reason for having these variables is so that references to particular
   categories will link in the lc-CATEGORY.c module to define this symbol,
   and we arrange that linking that module is what brings in all the code
   associated with this category.  */
#define DEFINE_CATEGORY(category, category_name, items, a) \
extern __thread struct __locale_data *const *_nl_current_##category \
  attribute_hidden attribute_tls_model_ie;
#undef	DEFINE_CATEGORY

/* Return a pointer to the current `struct __locale_data' for CATEGORY.  */
#define _NL_CURRENT_DATA(category)	(*_nl_current_##category)

/* Extract the current CATEGORY locale's string for ITEM.  */
#define _NL_CURRENT(category, item) \
  ((*_nl_current_##category)->values[_NL_ITEM_INDEX (item)].string)

/* Extract the current CATEGORY locale's string for ITEM.  */
#define _NL_CURRENT_WSTR(category, item) \
  ((wchar_t *) (*_nl_current_##category)->values[_NL_ITEM_INDEX (item)].wstr)

/* Extract the current CATEGORY locale's word for ITEM.  */
#define _NL_CURRENT_WORD(category, item) \
  ((uint32_t) (*_nl_current_##category)->values[_NL_ITEM_INDEX (item)].word)

/* This is used in lc-CATEGORY.c to define _nl_current_CATEGORY.  The symbol
   _nl_current_CATEGORY_used is set to a value unequal to zero to mark this
   category as used.  On S390 the used relocation to load the symbol address
   can only handle even addresses.  */
#define _NL_CURRENT_DEFINE(category) \
  __thread struct __locale_data *const *_nl_current_##category \
    attribute_hidden = &_nl_global_locale.__locales[category]; \
  asm (".globl " __SYMBOL_PREFIX "_nl_current_" #category "_used\n" \
       _NL_CURRENT_DEFINE_ABS (_nl_current_##category##_used, 2));
#ifdef HAVE_ASM_SET_DIRECTIVE
# define _NL_CURRENT_DEFINE_ABS(sym, val) ".set " #sym ", " #val
#else
# define _NL_CURRENT_DEFINE_ABS(sym, val) #sym " = " #val
#endif

#else

/* All categories are always loaded in the shared library, so there is no
   point in having lots of separate symbols for linking.  */

/* Return a pointer to the current `struct __locale_data' for CATEGORY.  */
# define _NL_CURRENT_DATA(category) \
  (_NL_CURRENT_LOCALE->__locales[category])

/* Extract the current CATEGORY locale's string for ITEM.  */
# define _NL_CURRENT(category, item) \
  (_NL_CURRENT_DATA (category)->values[_NL_ITEM_INDEX (item)].string)

/* Extract the current CATEGORY locale's string for ITEM.  */
# define _NL_CURRENT_WSTR(category, item) \
  ((wchar_t *) _NL_CURRENT_DATA (category)->values[_NL_ITEM_INDEX (item)].wstr)

/* Extract the current CATEGORY locale's word for ITEM.  */
# define _NL_CURRENT_WORD(category, item) \
  ((uint32_t) _NL_CURRENT_DATA (category)->values[_NL_ITEM_INDEX (item)].word)

/* This is used in lc-CATEGORY.c to define _nl_current_CATEGORY.  */
# define _NL_CURRENT_DEFINE(category) \
  /* No per-category variable here. */

#endif
#endif	/* localeinfo.h */
