#pragma once
#ifndef ARDUINO_ARCH_AVR
#include "../Cpp_Standard_Library.h"
#include CSL_Official(bits/codecvt.h)
namespace std _GLIBCXX_VISIBILITY(default)
{
	_GLIBCXX_BEGIN_NAMESPACE_VERSION
// 463
#if __cplusplus >= 201103L
	/** @brief  Class codecvt<char16_t, char, mbstate_t> specialization.
	 *
	 *  Converts between UTF-16 and UTF-8.
	 */
	template <>
	class codecvt<char16_t, char, mbstate_t>
		: public __codecvt_abstract_base<char16_t, char, mbstate_t>
	{
	public:
		// Types:
		typedef char16_t intern_type;
		typedef char extern_type;
		typedef mbstate_t state_type;

	public:
		static locale::id id;

		explicit codecvt(size_t __refs = 0)
			: __codecvt_abstract_base<char16_t, char, mbstate_t>(__refs) {}

	protected:
		virtual ~codecvt();

		virtual result
		do_out(state_type &__state, const intern_type *__from,
			   const intern_type *__from_end, const intern_type *&__from_next,
			   extern_type *__to, extern_type *__to_end,
			   extern_type *&__to_next) const;

		virtual result
		do_unshift(state_type &__state,
				   extern_type *__to, extern_type *__to_end,
				   extern_type *&__to_next) const;

		virtual result
		do_in(state_type &__state,
			  const extern_type *__from, const extern_type *__from_end,
			  const extern_type *&__from_next,
			  intern_type *__to, intern_type *__to_end,
			  intern_type *&__to_next) const;

		virtual int do_encoding() const throw();

		virtual bool do_always_noconv() const throw();

		virtual int do_length(state_type &, const extern_type *__from,
							  const extern_type *__end, size_t __max) const;

		virtual int
		do_max_length() const throw();
	};

	/** @brief  Class codecvt<char32_t, char, mbstate_t> specialization.
	 *
	 *  Converts between UTF-32 and UTF-8.
	 */
	template <>
	class codecvt<char32_t, char, mbstate_t>
		: public __codecvt_abstract_base<char32_t, char, mbstate_t>
	{
	public:
		// Types:
		typedef char32_t intern_type;
		typedef char extern_type;
		typedef mbstate_t state_type;

	public:
		static locale::id id;

		explicit codecvt(size_t __refs = 0)
			: __codecvt_abstract_base<char32_t, char, mbstate_t>(__refs) {}

	protected:
		virtual ~codecvt();

		virtual result
		do_out(state_type &__state, const intern_type *__from,
			   const intern_type *__from_end, const intern_type *&__from_next,
			   extern_type *__to, extern_type *__to_end,
			   extern_type *&__to_next) const;

		virtual result
		do_unshift(state_type &__state,
				   extern_type *__to, extern_type *__to_end,
				   extern_type *&__to_next) const;

		virtual result
		do_in(state_type &__state,
			  const extern_type *__from, const extern_type *__from_end,
			  const extern_type *&__from_next,
			  intern_type *__to, intern_type *__to_end,
			  intern_type *&__to_next) const;

		virtual int do_encoding() const throw();

		virtual bool do_always_noconv() const throw();

		virtual int do_length(state_type &, const extern_type *__from,
							  const extern_type *__end, size_t __max) const;

		virtual int
		do_max_length() const throw();
	};
	// 578
#endif // C++11
	// 696
	_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
#endif