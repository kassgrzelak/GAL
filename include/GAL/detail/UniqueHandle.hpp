//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_UNIQUE_HANDLE_HPP
#define GAL_UNIQUE_HANDLE_HPP
#include "ResourceRegistry.hpp"
#include "GAL/config.hpp"

namespace gal::detail
{
	/// @brief Class to keep track of an allocated resource, register/unregister it from the RR, and destroy it when it
	/// goes out of scope like RAII.
	/// @tparam Handle_t Type of the resource's handle (e.g., GLFWwindow*, GLuint).
	/// @tparam Invalid The value that indicates an invalidated handle (i.e., deleted or not yet set).
	/// @tparam Deleter Function pointer that takes the handle and deletes the allocated resource (e.g., glfwDestroyWindow()).
	/// @note "Handle," in the context of this class, refers to a value that wholly identifies an allocated resource
	/// and can be used to delete it (GLFWwindow* for windows, GLuint IDs for OpenGL objects, etc.).
	template<typename Handle_t, Handle_t Invalid, void(*Deleter)(Handle_t) noexcept>
	class UniqueHandle
	{
	public:
		UniqueHandle() noexcept : handle(Invalid) { }

		explicit UniqueHandle(Handle_t handle) noexcept : handle(handle)
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
				resourceRegistry.unregister(static_cast<void*>(&other.handle));
				other.handle = Invalid;
				register_();
			}
		}

		~UniqueHandle() noexcept
		{
			reset();
		}

		UniqueHandle& operator=(UniqueHandle&& other) noexcept
		{
			if (this != &other)
			{
				reset();
				handle = other.handle;

				if (handleValid())
				{
					resourceRegistry.unregister(ResourceRegistry::handleToVoidPtr(other.handle));
					other.handle = Invalid;
					register_();
				}
			}

			return *this;
		}

		/// @brief Set and register a new handle, deleting any previously set one.
		/// @param newHandle The new handle to set.
		void setHandle(Handle_t newHandle) noexcept
		{
			reset();
			handle = newHandle;

			if (handleValid())
				register_();
		}

		/// @brief Get the currently registered handle.
		GAL_NODISCARD Handle_t getHandle() const noexcept { return handle; }
		/// @brief Get a pointer to the currently registered handle.
		GAL_NODISCARD Handle_t* getHandlePtr() noexcept { return &handle; }
		/// @brief Check if the current handle is valid (i.e., not equal to Invalid).
		GAL_NODISCARD bool handleValid() const noexcept { return handle != Invalid; }

	private:
		/// @brief If the current handle is valid, unregister it, delete the associated resource, and invalidate the handle.
		void reset() noexcept
		{
			if (handleValid())
			{
				unregister();
				Deleter(handle);
				handle = Invalid;
			}
		}

		/// @brief Register the current handle with the RR.
		void register_() noexcept
		{
			resourceRegistry.register_(
				ResourceRegistry::handleToVoidPtr(handle),
				static_cast<void*>(&handle),
				&deleterWrapper,
				&invalidateWrapper
			);
		}

		/// @brief Unregister the current handle from the RR.
		void unregister() const noexcept
		{
			resourceRegistry.unregister(static_cast<const void*>(&handle));
		}

		static void deleterWrapper(void* ptr) noexcept
		{
			Deleter(ResourceRegistry::handleFromVoidPtr<Handle_t>(ptr));
		}

		static void invalidateWrapper(void* handlePtr) noexcept
		{
			*static_cast<Handle_t*>(handlePtr) = Invalid;
		}

		Handle_t handle;
	};
}

#endif //GAL_UNIQUE_HANDLE_HPP
