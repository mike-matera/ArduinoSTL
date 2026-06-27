#pragma once
// 此文件非GCC标准，而是特别独立出来，用来解决SAM旧架构循环包含问题

#ifndef ARDUINO_ARCH_ESP32
#include <bits/stl_construct.h>
#endif
#ifdef ARDUINO_ARCH_AVR
#include <bits/alloc_traits.h>
#endif
namespace std
{
#if _GLIBCXX_HOSTED
#ifndef ARDUINO_ARCH_ESP32
	/// Partial specialization for std::allocator.
	template <typename _Tp>
	struct allocator_traits<allocator<_Tp>>
	{
		/// The allocator type
		using allocator_type = allocator<_Tp>;

		/// The allocated type
		using value_type = _Tp;

		/// The allocator's pointer type.
		using pointer = _Tp *;

		/// The allocator's const pointer type.
		using const_pointer = const _Tp *;

		/// The allocator's void pointer type.
		using void_pointer = void *;

		/// The allocator's const void pointer type.
		using const_void_pointer = const void *;

		/// The allocator's difference type
		using difference_type = std::ptrdiff_t;

		/// The allocator's size type
		using size_type = std::size_t;

		/// How the allocator is propagated on copy assignment
		using propagate_on_container_copy_assignment = false_type;

		/// How the allocator is propagated on move assignment
		using propagate_on_container_move_assignment = true_type;

		/// How the allocator is propagated on swap
		using propagate_on_container_swap = false_type;

		/// Whether all instances of the allocator type compare equal.
		using is_always_equal = true_type;

#ifdef ARDUINO_ARCH_AVR
		template <typename _Up>
		using rebind_alloc = allocator<_Up>;
		template <typename _Up>
		using rebind_traits = allocator_traits<allocator<_Up>>;
#endif
#ifdef ARDUINO_ARCH_SAM
      template<typename _Up>
        using rebind_alloc = typename __alloctr_rebind<allocator<_Tp>, _Up>::__type;
		template <typename _Up>
		using rebind_traits = allocator_traits<rebind_alloc<_Up>>;
#endif
		/**
		 *  @brief  Allocate memory.
		 *  @param  __a  An allocator.
		 *  @param  __n  The number of objects to allocate space for.
		 *
		 *  Calls @c a.allocate(n)
		 */
		[[__nodiscard__, __gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR pointer
		allocate(allocator_type &__a, size_type __n)
		{
			return __a.allocate(__n);
		}

		/**
		 *  @brief  Allocate memory.
		 *  @param  __a  An allocator.
		 *  @param  __n  The number of objects to allocate space for.
		 *  @param  __hint Aid to locality.
		 *  @return Memory of suitable size and alignment for @a n objects
		 *          of type @c value_type
		 *
		 *  Returns <tt> a.allocate(n, hint) </tt>
		 */
		[[__nodiscard__, __gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR pointer
		allocate(allocator_type &__a, size_type __n,
				 [[maybe_unused]] const_void_pointer __hint)
		{
#if __cplusplus <= 201703L
			return __a.allocate(__n, __hint);
#else
			return __a.allocate(__n);
#endif
		}

		/**
		 *  @brief  Deallocate memory.
		 *  @param  __a  An allocator.
		 *  @param  __p  Pointer to the memory to deallocate.
		 *  @param  __n  The number of objects space was allocated for.
		 *
		 *  Calls <tt> a.deallocate(p, n) </tt>
		 */
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR void
		deallocate(allocator_type &__a, pointer __p, size_type __n)
		{
			__a.deallocate(__p, __n);
		}

		/**
		 *  @brief  Construct an object of type `_Up`
		 *  @param  __a  An allocator.
		 *  @param  __p  Pointer to memory of suitable size and alignment for
		 *	       an object of type `_Up`.
		 *  @param  __args Constructor arguments.
		 *
		 *  Calls `__a.construct(__p, std::forward<_Args>(__args)...)`
		 *  in C++11, C++14 and C++17. Changed in C++20 to call
		 *  `std::construct_at(__p, std::forward<_Args>(__args)...)` instead.
		 */
		template <typename _Up, typename... _Args>
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR void
		construct(allocator_type &__a __attribute__((__unused__)), _Up *__p,
				  _Args &&...__args) noexcept(std::is_nothrow_constructible<_Up, _Args...>::value)
		{
#if __cplusplus <= 201703L
			__a.construct(__p, std::forward<_Args>(__args)...);
#else
			std::construct_at(__p, std::forward<_Args>(__args)...);
#endif
		}

		/**
		 *  @brief  Destroy an object of type @a _Up
		 *  @param  __a  An allocator.
		 *  @param  __p  Pointer to the object to destroy
		 *
		 *  Calls @c __a.destroy(__p).
		 */
		template <typename _Up>
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR void
		destroy(allocator_type &__a __attribute__((__unused__)), _Up *__p) noexcept(is_nothrow_destructible<_Up>::value)
		{
#if __cplusplus <= 201703L
			__a.destroy(__p);
#else
			std::destroy_at(__p);
#endif
		}

		/**
		 *  @brief  The maximum supported allocation size
		 *  @param  __a  An allocator.
		 *  @return @c __a.max_size()
		 */
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR size_type
		max_size(const allocator_type &__a __attribute__((__unused__))) noexcept
		{
#if __cplusplus <= 201703L
			return __a.max_size();
#else
			return size_t(-1) / sizeof(value_type);
#endif
		}

		/**
		 *  @brief  Obtain an allocator to use when copying a container.
		 *  @param  __rhs  An allocator.
		 *  @return @c __rhs
		 */
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR allocator_type
		select_on_container_copy_construction(const allocator_type &__rhs)
		{
			return __rhs;
		}
	};

	/// Explicit specialization for std::allocator<void>.
	template <>
	struct allocator_traits<allocator<void>>
	{
		/// The allocator type
		using allocator_type = allocator<void>;

		/// The allocated type
		using value_type = void;

		/// The allocator's pointer type.
		using pointer = void *;

		/// The allocator's const pointer type.
		using const_pointer = const void *;

		/// The allocator's void pointer type.
		using void_pointer = void *;

		/// The allocator's const void pointer type.
		using const_void_pointer = const void *;

		/// The allocator's difference type
		using difference_type = std::ptrdiff_t;

		/// The allocator's size type
		using size_type = std::size_t;

		/// How the allocator is propagated on copy assignment
		using propagate_on_container_copy_assignment = false_type;

		/// How the allocator is propagated on move assignment
		using propagate_on_container_move_assignment = true_type;

		/// How the allocator is propagated on swap
		using propagate_on_container_swap = false_type;

		/// Whether all instances of the allocator type compare equal.
		using is_always_equal = true_type;

		template <typename _Up>
		using rebind_alloc = allocator<_Up>;
#ifdef ARDUINO_ARCH_AVR
		template <typename _Up>
		using rebind_traits = allocator_traits<allocator<_Up>>;
#endif
		/// allocate is ill-formed for allocator<void>
		static void *
		allocate(allocator_type &, size_type, const void * = nullptr) = delete;

		/// deallocate is ill-formed for allocator<void>
		static void
		deallocate(allocator_type &, void *, size_type) = delete;

		/**
		 *  @brief  Construct an object of type `_Up`
		 *  @param  __a  An allocator.
		 *  @param  __p  Pointer to memory of suitable size and alignment for
		 *	       an object of type `_Up`.
		 *  @param  __args Constructor arguments.
		 *
		 *  Calls `__a.construct(__p, std::forward<_Args>(__args)...)`
		 *  in C++11, C++14 and C++17. Changed in C++20 to call
		 *  `std::construct_at(__p, std::forward<_Args>(__args)...)` instead.
		 */
		template <typename _Up, typename... _Args>
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR void
		construct(allocator_type &, _Up *__p, _Args &&...__args) noexcept(std::is_nothrow_constructible<_Up, _Args...>::value)
		{
			std::_Construct(__p, std::forward<_Args>(__args)...);
		}

		/**
		 *  @brief  Destroy an object of type `_Up`
		 *  @param  __a  An allocator.
		 *  @param  __p  Pointer to the object to destroy
		 *
		 *  Invokes the destructor for `*__p`.
		 */
		template <typename _Up>
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR void
		destroy(allocator_type &, _Up *__p) noexcept(is_nothrow_destructible<_Up>::value)
		{
			std::_Destroy(__p);
		}

		/// max_size is ill-formed for allocator<void>
		static size_type
		max_size(const allocator_type &) = delete;

		/**
		 *  @brief  Obtain an allocator to use when copying a container.
		 *  @param  __rhs  An allocator.
		 *  @return `__rhs`
		 */
		[[__gnu__::__always_inline__]]
		static _GLIBCXX20_CONSTEXPR allocator_type
		select_on_container_copy_construction(const allocator_type &__rhs)
		{
			return __rhs;
		}
	};
#endif
#endif
}