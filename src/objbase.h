#ifndef __OBJBASE_H
#define __OBJBASE_H

#include "type_traits"

#ifdef __cplusplus
template<typename Enum>
inline constexpr Enum operator|(Enum a, Enum b) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum>(static_cast<T>(a) | static_cast<T>(b));
}

template<typename Enum>
inline constexpr Enum operator&(Enum a, Enum b) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum>(static_cast<T>(a) & static_cast<T>(b));
}

template<typename Enum>
inline constexpr Enum operator^(Enum a, Enum b) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum>(static_cast<T>(a) ^ static_cast<T>(b));
}

template<typename Enum>
inline constexpr Enum& operator|=(Enum& a, Enum b) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum&>(static_cast<T&>(a) | static_cast<T>(b));
}

template<typename Enum>
inline constexpr Enum& operator&=(Enum& a, Enum b) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum&>(static_cast<T&>(a) & static_cast<T>(b));
}

template<typename Enum>
inline constexpr Enum& operator^=(Enum& a, Enum b) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum&>(static_cast<T&>(a) ^ static_cast<T>(b));
}

template<typename Enum>
inline constexpr Enum operator~(Enum a) {
	using T = std::underlying_type_t<Enum>;
	return static_cast<Enum>(~static_cast<T>(a));

}
#endif

#endif