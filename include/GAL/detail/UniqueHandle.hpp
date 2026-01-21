//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_UNIQUE_HANDLE_HPP
#define GAL_UNIQUE_HANDLE_HPP
#include "ResourceRegistry.hpp"
#include "GAL/config.hpp"

#include <cstdint>
#include <type_traits>

namespace gal::detail
{
	template<typename Handle, Handle Invalid, void(*Deleter)(Handle) noexcept>
	class UniqueHandle
	{
	public:
		UniqueHandle() noexcept : handle(Invalid) {}

		explicit UniqueHandle(Handle handle) noexcept : handle(handle)
		{
			if (handleValid())
				register_();
		}

		UniqueHandle(const UniqueHandle&) = delete;
		UniqueHandle& operator=(const UniqueHandle&) = delete;

		UniqueHandle(UniqueHandle&& other) noexcept : handle(other.handle)
		{
			if (other.handleValid())
			{
				resourceRegistry.unregister(toVoidPtr(other.handle));
				other.handle = Invalid;
				register_();
			}
		}

		UniqueHandle& operator=(UniqueHandle&& other) noexcept
		{
			if (this != &other)
			{
				reset();
				handle = other.handle;

				if (handleValid())
				{
					resourceRegistry.unregister(toVoidPtr(other.handle));
					other.handle = Invalid;
					register_();
				}
			}

			return *this;
		}

		~UniqueHandle() noexcept
		{
			reset();
		}

		void setHandle(Handle newHandle) noexcept
		{
			reset();
			handle = newHandle;

			if (handleValid())
				register_();
		}

		GAL_NODISCARD Handle getHandle() const noexcept { return handle; }
		GAL_NODISCARD bool handleValid() const noexcept { return handle != Invalid; }

	protected:
		void reset() noexcept
		{
			if (handleValid())
			{
				unregister();
				Deleter(handle);
				handle = Invalid;
			}
		}

		void register_() noexcept
		{
			resourceRegistry.register_(
				toVoidPtr(handle),
				static_cast<void*>(&handle),
				&deleterWrapper,
				&invalidateWrapper
			);
		}

		void unregister() const noexcept
		{
			resourceRegistry.unregister(toVoidPtr(handle));
		}

		static void deleterWrapper(void* ptr) noexcept
		{
			Deleter(fromVoidPtr(ptr));
		}

		static void invalidateWrapper(void* ownerHandlePtr) noexcept
		{
			*static_cast<Handle*>(ownerHandlePtr) = Invalid;
		}

		static void* toVoidPtr(Handle handle) noexcept
		{
			if constexpr (std::is_pointer_v<Handle>)
				return static_cast<void*>(handle);
			else
				return reinterpret_cast<void*>(static_cast<std::uintptr_t>(handle));
		}

		static Handle fromVoidPtr(void* ptr) noexcept
		{
			if constexpr (std::is_pointer_v<Handle>)
				return static_cast<Handle>(ptr);
			else
				return static_cast<Handle>(reinterpret_cast<std::uintptr_t>(ptr));
		}

		Handle handle;
	};
}

#endif //GAL_UNIQUE_HANDLE_HPP
