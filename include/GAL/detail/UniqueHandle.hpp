//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_UNIQUE_HANDLE_HPP
#define GAL_UNIQUE_HANDLE_HPP
#include "ResourceRegistry.hpp"
#include "GAL/config.hpp"

namespace gal::detail
{
	template<typename Handle, Handle Invalid, void(*Deleter)(void*) noexcept>
	class UniqueHandle
	{
	public:
		using handle_t = Handle;

		UniqueHandle() noexcept : handle(Invalid) { }

		explicit UniqueHandle(Handle handle) noexcept : handle(handle)
		{
			register_();
		}

		// No copying.
		UniqueHandle(const UniqueHandle&) = delete;

		UniqueHandle& operator=(const UniqueHandle&) = delete;

		UniqueHandle(UniqueHandle&& other) noexcept : handle(other.handle)
		{
			if (other.handleValid())
				resourceRegistry.unregister(&other.handle);

			other.handle = Invalid;
			register_();
		}

		~UniqueHandle() noexcept
		{
			unregister();
			Deleter(&handle);
		}

		void setHandle(Handle newHandle)
		{
			if (handleValid())
				unregister();

			handle = newHandle;

			if (handleValid())
				register_();
		}

		void register_()
		{
			resourceRegistry.register_(&handle, Deleter);
		}

		void unregister()
		{
			resourceRegistry.unregister(&handle);
		}

		GAL_NODISCARD Handle getHandle() const noexcept { return handle; }
		GAL_NODISCARD bool handleValid() const noexcept { return handle != Invalid; }

	protected:
		Handle handle;
	};
}

#endif //GAL_UNIQUE_HANDLE_HPP
