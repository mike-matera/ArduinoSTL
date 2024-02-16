#pragma once
#include "../locale"
#ifdef ARDUINO_ARCH_SAM
#include <bits/postypes.h>
#endif
namespace std
{
	class _UCXXEXPORT ios_base
	{
	public:
		class failure;
#ifdef __UCLIBCXX_EXCEPTION_SUPPORT__
		class failure : public exception
		{
		public:
			explicit failure(const std::string &) {}
			explicit failure() {}
			virtual const char *what() const _UCXX_USE_NOEXCEPT
			{
				return "std::ios_base failure exception";
			}
		};
#endif
#ifdef __UCLIBCXX_SUPPORT_CDIR__
		class _UCXXLOCAL Init
		{
		public:
			_UCXXEXPORT Init();
			_UCXXEXPORT ~Init();

		private:
			static int init_cnt;
		};
#endif

	public:
		typedef unsigned short int fmtflags;

		static const fmtflags skipws = 0x0001;

		static const fmtflags left = 0x0002;
		static const fmtflags right = 0x0004;
		static const fmtflags internal = 0x0008;

		static const fmtflags boolalpha = 0x0010;

		static const fmtflags dec = 0x0020;
		static const fmtflags oct = 0x0040;
		static const fmtflags hex = 0x0080;

		static const fmtflags scientific = 0x0100;
		static const fmtflags fixed = 0x0200;

		static const fmtflags showbase = 0x0400;
		static const fmtflags showpoint = 0x0800;
		static const fmtflags showpos = 0x1000;
		static const fmtflags uppercase = 0x2000;

		static const fmtflags adjustfield = left | right | internal;
		static const fmtflags basefield = dec | oct | hex;
		static const fmtflags floatfield = fixed | scientific;

		static const fmtflags unitbuf = 0x4000;

		typedef unsigned char iostate;
		static const iostate goodbit = 0x00;
		static const iostate badbit = 0x01;
		static const iostate eofbit = 0x02;
		static const iostate failbit = 0x04;

		typedef unsigned char openmode;
		static const openmode app = 0x01;
		static const openmode ate = 0x02;
		static const openmode binary = 0x04;
		static const openmode in = 0x08;
		static const openmode out = 0x10;
		static const openmode trunc = 0x20;

		typedef unsigned char seekdir;
		static const seekdir beg = 0x01;
		static const seekdir cur = 0x02;
		static const seekdir end = 0x04;

		_UCXXEXPORT fmtflags flags() const
		{
			return mformat;
		}
		_UCXXEXPORT fmtflags flags(fmtflags fmtfl);

		fmtflags setf(fmtflags fmtfl);
		fmtflags setf(fmtflags fmtfl, fmtflags mask);

		_UCXXEXPORT void unsetf(fmtflags mask)
		{
			mformat &= ~mask;
		}

		_UCXXEXPORT streamsize precision() const
		{
			return mprecision;
		}

		_UCXXEXPORT streamsize precision(streamsize prec);

		_UCXXEXPORT streamsize width() const
		{
			return mwidth;
		}

		_UCXXEXPORT streamsize width(streamsize wide);

		_UCXXEXPORT locale imbue(const locale &loc);

		_UCXXEXPORT locale getloc() const
		{
			return mLocale;
		}

		//		FIXME - These need to be implemented
		//		static int xalloc();
		//		long&  iword(int index);
		//		void*& pword(int index);

		enum event
		{
			erase_event,
			imbue_event,
			copyfmt_event
		};

		typedef void (*event_callback)(event, ios_base &, int index);
		//		void register_callback(event_call_back fn, int index);

		virtual _UCXXEXPORT ~ios_base()
		{
			/* would run erase_event callbacks here */
		}

		// We are going to wrap stdio so we don't need implementation of the following:
		inline static bool sync_with_stdio(bool = true) { return true; }

	protected:
		_UCXXEXPORT ios_base() : mLocale(), mformat(dec | skipws), mstate(goodbit),
								 mmode(), mdir(), mprecision(6), mwidth(0)
#ifdef __UCLIBCXX_SUPPORT_CDIR__
								 ,
								 mInit()
#endif
		{
		}
		locale mLocale;
		fmtflags mformat;
		iostate mstate;
		openmode mmode;
		seekdir mdir;
		streamsize mprecision;
		streamsize mwidth;
#ifdef __UCLIBCXX_SUPPORT_CDIR__
		Init mInit;
#endif
	};
}