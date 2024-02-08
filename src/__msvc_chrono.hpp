#pragma once
#include <limits>
#include <ratio>
#include <type_traits>
_STD_BEGIN
namespace chrono
{
	_EXPORT_STD template <class _Rep>
	struct treat_as_floating_point : is_floating_point<_Rep>
	{
	}; // tests for floating-point type
#if _HAS_CXX14
	_EXPORT_STD template <class _Rep>
	_INLINE_VAR constexpr bool treat_as_floating_point_v = treat_as_floating_point<_Rep>::value;
#endif
	_EXPORT_STD template <class _Rep>
	struct duration_values
	{ // gets arithmetic properties of a type
		_NODISCARD static constexpr _Rep zero() noexcept
		{
			// get zero value
			return _Rep(0);
		}

		_NODISCARD static constexpr _Rep(min)() noexcept
		{
			// get smallest value
			return numeric_limits<_Rep>::lowest();
		}

		_NODISCARD static constexpr _Rep(max)() noexcept
		{
			// get largest value
			return (numeric_limits<_Rep>::max)();
		}
	};

#if _HAS_CXX20
	template <class _Clock, class = void>
	inline constexpr bool _Is_clock_v = false;

	template <class _Clock>
	inline constexpr bool
		_Is_clock<_Clock, void_t<typename _Clock::rep, typename _Clock::period, typename _Clock::duration,
								 typename _Clock::time_point, decltype(_Clock::is_steady), decltype(_Clock::now())>>::value =
			true; // TRANSITION, GH-602

	_EXPORT_STD template <class _Clock>
	struct is_clock : bool_constant<_Is_clock<_Clock>::value>
	{
	};
	_EXPORT_STD template <class _Clock>
	inline constexpr bool is_clock_v = _Is_clock<_Clock>::value;
#endif // _HAS_CXX20

	_EXPORT_STD template <class _Rep, class _Period = ratio<1>>
	class duration;
#if _HAS_CXX14
	template <class _Ty>
	_INLINE_VAR constexpr bool _Is_duration_v = _Is_specialization<_Ty, duration>::value;
#endif
	template <class _Ty>
	using _Is_duration = _Is_specialization<_Ty, duration>;
	_EXPORT_STD template <class _To, class _Rep, class _Period, enable_if_t<_Is_duration<_To>::value, int> = 0>
	constexpr _To duration_cast(const duration<_Rep, _Period> &) noexcept(
		is_arithmetic<_Rep>::value && is_arithmetic<typename _To::rep>::value); // strengthened

	_EXPORT_STD template <class _Rep, class _Period>
	class duration
	{ // represents a time duration
	public:
		using rep = _Rep;
		using period = typename _Period::type;

		static_assert(!_Is_duration<_Rep>::value, "duration can't have duration as first template argument");
		static_assert(_Is_ratio<_Period>::value, "period not an instance of std::ratio");
		static_assert(0 < _Period::num, "period negative or zero");

		constexpr duration() = default;

		template <class _Rep2,
				  enable_if_t<is_convertible<const _Rep2 &, _Rep>::value && (treat_as_floating_point<_Rep>::value || !treat_as_floating_point<_Rep2>::value),
							  int> = 0>
		constexpr explicit duration(const _Rep2 &_Val) noexcept(
			is_arithmetic<_Rep>::value && is_arithmetic<_Rep2>::value) // strengthened
			: _MyRep(static_cast<_Rep>(_Val))
		{
		}

		template <class _Rep2, class _Period2,
				  enable_if_t<treat_as_floating_point<_Rep>::value || (_Ratio_divide_sfinae<_Period2, _Period>::den == 1 && !treat_as_floating_point<_Rep2>::value),
							  int> = 0>
		constexpr duration(const duration<_Rep2, _Period2> &_Dur) noexcept(
			is_arithmetic<_Rep>::value && is_arithmetic<_Rep2>::value) // strengthened
			: _MyRep(_CHRONO duration_cast<duration>(_Dur).count())
		{
		}

		_NODISCARD constexpr _Rep count() const noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			return _MyRep;
		}
		template <typename T>
		using _Common_type_14 =
#if _HAS_CXX14
			common_type_t<T>
#else
			T
#endif
			;
		_NODISCARD constexpr _Common_type_14<duration> operator+() const
			noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			return _Common_type_14<duration>(*this);
		}

		_NODISCARD constexpr _Common_type_14<duration> operator-() const
			noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			return _Common_type_14<duration>(-_MyRep);
		}

		_CONSTEXPR17 duration &operator++() noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			++_MyRep;
			return *this;
		}

		_CONSTEXPR17 duration operator++(int) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			return duration(_MyRep++);
		}

		_CONSTEXPR17 duration &operator--() noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			--_MyRep;
			return *this;
		}

		_CONSTEXPR17 duration operator--(int) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			return duration(_MyRep--);
		}

		_CONSTEXPR17 duration &operator+=(const duration &_Right) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			_MyRep += _Right._MyRep;
			return *this;
		}

		_CONSTEXPR17 duration &operator-=(const duration &_Right) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			_MyRep -= _Right._MyRep;
			return *this;
		}

		_CONSTEXPR17 duration &operator*=(const _Rep &_Right) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			_MyRep *= _Right;
			return *this;
		}

		_CONSTEXPR17 duration &operator/=(const _Rep &_Right) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			_MyRep /= _Right;
			return *this;
		}

		_CONSTEXPR17 duration &operator%=(const _Rep &_Right) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			_MyRep %= _Right;
			return *this;
		}

		_CONSTEXPR17 duration &operator%=(const duration &_Right) noexcept(is_arithmetic<_Rep>::value) /* strengthened */
		{
			_MyRep %= _Right.count();
			return *this;
		}

		_NODISCARD static constexpr duration zero() noexcept
		{
			// get zero value
			return duration(duration_values<_Rep>::zero());
		}

		_NODISCARD static constexpr duration(min)() noexcept
		{
			// get minimum value
			return duration((duration_values<_Rep>::min)());
		}

		_NODISCARD static constexpr duration(max)() noexcept
		{
			// get maximum value
			return duration((duration_values<_Rep>::max)());
		}

	private:
		_Rep _MyRep; // the stored rep
	};
	// 188
	// 293
	_EXPORT_STD template <class _Rep1, class _Period1, class _Rep2,
						  enable_if_t<is_convertible<const _Rep2 &, common_type_t<_Rep1, _Rep2>>::value, int> = 0>
	_NODISCARD constexpr duration<common_type_t<_Rep1, _Rep2>, _Period1> operator*(
		const duration<_Rep1, _Period1> &_Left,
		const _Rep2 &_Right) noexcept(is_arithmetic<_Rep1>::value && is_arithmetic<_Rep2>::value) /* strengthened */
	{
		using _CR = common_type_t<_Rep1, _Rep2>;
		using _CD = duration<_CR, _Period1>;
		return _CD(_CD(_Left).count() * _Right);
	}
	// 303
	//  311
	template <class _CR, class _Period1, class _Rep2, bool = is_convertible<const _Rep2 &, _CR>::value>
	struct _Duration_div_mod1
	{ // return type for duration / rep and duration % rep
		using type = duration<_CR, _Period1>;
	};

	template <class _CR, class _Period1, class _Rep2>
	struct _Duration_div_mod1<_CR, _Period1, _Rep2, false>
	{
	}; // no return type

	template <class _CR, class _Period1, class _Rep2, bool = _Is_duration<_Rep2>::value>
	struct _Duration_div_mod
	{
	}; // no return type

	template <class _CR, class _Period1, class _Rep2>
	struct _Duration_div_mod<_CR, _Period1, _Rep2, false> : _Duration_div_mod1<_CR, _Period1, _Rep2>
	{
		// return type for duration / rep and duration % rep
	};

	_EXPORT_STD template <class _Rep1, class _Period1, class _Rep2>
	_NODISCARD constexpr typename _Duration_div_mod<common_type_t<_Rep1, _Rep2>, _Period1, _Rep2>::type operator/(
		const duration<_Rep1, _Period1> &_Left,
		const _Rep2 &_Right) noexcept(is_arithmetic<_Rep1>::value && is_arithmetic<_Rep2>::value) /* strengthened */
	{
		using _CR = common_type_t<_Rep1, _Rep2>;
		using _CD = duration<_CR, _Period1>;
		return _CD(_CD(_Left).count() / _Right);
	}

	_EXPORT_STD template <class _Rep1, class _Period1, class _Rep2, class _Period2>
	_NODISCARD constexpr common_type_t<_Rep1, _Rep2>
	operator/(const duration<_Rep1, _Period1> &_Left, const duration<_Rep2, _Period2> &_Right) noexcept(
		is_arithmetic<_Rep1>::value && is_arithmetic<_Rep2>::value) /* strengthened */
	{
		using _CD = common_type_t<duration<_Rep1, _Period1>, duration<_Rep2, _Period2>>;
		return _CD(_Left).count() / _CD(_Right).count();
	}
	// 344
	// 378
	_EXPORT_STD template <class _Rep1, class _Period1, class _Rep2, class _Period2>
	_NODISCARD constexpr bool
	operator<(const duration<_Rep1, _Period1> &_Left, const duration<_Rep2, _Period2> &_Right) noexcept(
		is_arithmetic<_Rep1>::value && is_arithmetic<_Rep2>::value) /* strengthened */
	{
		using _CT = common_type_t<duration<_Rep1, _Period1>, duration<_Rep2, _Period2>>;
		return _CT(_Left).count() < _CT(_Right).count();
	}
	// 386
// 407
#ifdef __cpp_lib_concepts
	_EXPORT_STD template <class _Rep1, class _Period1, class _Rep2, class _Period2>
		requires three_way_comparable<typename common_type_t<duration<_Rep1, _Period1>, duration<_Rep2, _Period2>>::rep>
	_NODISCARD constexpr auto
	operator<=>(const duration<_Rep1, _Period1> &_Left, const duration<_Rep2, _Period2> &_Right) noexcept(
		is_arithmetic<_Rep1>::value && is_arithmetic<_Rep2>::value) /* strengthened */
	{
		using _CT = common_type_t<duration<_Rep1, _Period1>, duration<_Rep2, _Period2>>;
		return _CT(_Left).count() <=> _CT(_Right).count();
	}
#endif // defined(__cpp_lib_concepts)

	_EXPORT_STD template <class _To, class _Rep, class _Period, enable_if_t<_Is_duration<_To>::value, int> /* = 0 */>
	_NODISCARD constexpr _To duration_cast(const duration<_Rep, _Period> &_Dur) noexcept(
		is_arithmetic<_Rep>::value && is_arithmetic<typename _To::rep>::value) /* strengthened */
	{
		// convert duration to another duration; truncate
		using _CF = ratio_divide<_Period, typename _To::period>;

		using _ToRep = typename _To::rep;
		using _CR = common_type_t<_ToRep, _Rep, intmax_t>;

		constexpr bool _Num_is_one = _CF::num == 1;
		constexpr bool _Den_is_one = _CF::den == 1;

		if _CONSTEXPR14 ()
			(_Den_is_one)
			{
				if _CONSTEXPR14 ()
					(_Num_is_one)
					{
						return static_cast<_To>(static_cast<_ToRep>(_Dur.count()));
					}
				else
				{
					return static_cast<_To>(
						static_cast<_ToRep>(static_cast<_CR>(_Dur.count()) * static_cast<_CR>(_CF::num)));
				}
			}
		else
		{
			if _CONSTEXPR14 ()
				(_Num_is_one)
				{
					return static_cast<_To>(
						static_cast<_ToRep>(static_cast<_CR>(_Dur.count()) / static_cast<_CR>(_CF::den)));
				}
			else
			{
				return static_cast<_To>(static_cast<_ToRep>(
					static_cast<_CR>(_Dur.count()) * static_cast<_CR>(_CF::num) / static_cast<_CR>(_CF::den)));
			}
		}
	}
	// 448
	// 508
	_EXPORT_STD using nanoseconds = duration<long long, nano>;
	_EXPORT_STD using microseconds = duration<long long, micro>;
	_EXPORT_STD using milliseconds = duration<long long, milli>;
	_EXPORT_STD using seconds = duration<long long>;
	_EXPORT_STD using minutes = duration<int, ratio<60>>;
	_EXPORT_STD using hours = duration<int, ratio<3600>>;
#if _HAS_CXX20
	_EXPORT_STD using days = duration<int, ratio_multiply<ratio<24>, hours::period>>;
	_EXPORT_STD using weeks = duration<int, ratio_multiply<ratio<7>, days::period>>;
	_EXPORT_STD using years = duration<int, ratio_multiply<ratio<146097, 400>, days::period>>;
	_EXPORT_STD using months = duration<int, ratio_divide<years::period, ratio<12>>>;
#endif // _HAS_CXX20
	   // 521
}
_STD_END
