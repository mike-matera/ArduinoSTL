#ifndef __OBJBASE_H
#define __OBJBASE_H

#include "type_traits"

#ifdef __cplusplus
template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
class auto_bool final
{
	Enum val_;
public:
	inline constexpr auto_bool(Enum val) : val_(val) {}
	inline constexpr operator Enum() const { return val_; }
	inline constexpr explicit operator bool() const
	{
		return static_cast<std::underlying_type_t<Enum>>(val_) != 0;
	}
};

template <typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr auto_bool<Enum> operator&(Enum lhs, Enum rhs)
{
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum>(
		static_cast<T>(lhs) &
		static_cast<T>(rhs));
}

template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr Enum operator|(Enum lhs, Enum rhs) {
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum>(
		static_cast<T>(lhs) |
		static_cast<T>(rhs));
}

template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr Enum operator^(Enum lhs, Enum rhs) {
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum>(
		static_cast<T>(lhs) ^
		static_cast<T>(rhs));
}

template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr Enum& operator|=(Enum& lhs, Enum rhs) {
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum&>(
		static_cast<T&>(lhs) |
		static_cast<T>(rhs));
}

template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr Enum& operator&=(Enum& lhs, Enum rhs) {
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum&>(
		static_cast<T&>(lhs) &
		static_cast<T>(rhs));
}

template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr Enum& operator^=(Enum& lhs, Enum rhs) {
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum&>(
		static_cast<T&>(lhs) ^
		static_cast<T>(rhs));
}

template<typename Enum, typename = typename std::enable_if<std::is_enum<Enum>::value, Enum>::type>
inline constexpr Enum operator~(Enum lhs) {
	using T = typename std::underlying_type_t<Enum>;
	return static_cast<Enum>(~static_cast<T>(lhs));
}
#endif // __cplusplus

#endif // __OBJBASE_H