// __msvc_chrono.hpp internal header

// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#pragma once
#include <ctime>
#include <ratio>
#include <type_traits>
_STD_BEGIN
namespace chrono
{
	// 69
	_EXPORT_STD template <class _Rep, class _Period = ratio<1>>
	class duration;
	// 72
	// 79
	_EXPORT_STD template <class _Rep, class _Period>
	class duration
	{ // represents a time duration
	};
	_EXPORT_STD template <class _Clock, class _Duration = typename _Clock::duration>
	class time_point
	{ // represents a point in time
	};
}
// 253
// 276
namespace chrono
{
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
// 634
_EXPORT_STD struct system_clock
{ // wraps GetSystemTimePreciseAsFileTime/GetSystemTimeAsFileTime
	using rep = long long;
	using period = ratio<1, 10'000'000>; // 100 nanoseconds
	using duration = _CHRONO duration<rep, period>;
	using time_point = _CHRONO time_point<system_clock>;
};
// 653
_STD_END