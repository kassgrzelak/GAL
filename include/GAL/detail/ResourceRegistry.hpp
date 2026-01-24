//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_RESOURCE_REGISTRY_HPP
#define GAL_RESOURCE_REGISTRY_HPP

#include <algorithm>
#include <cstdint>
#include <vector>
#include <pstl/glue_execution_defs.h>

namespace gal::detail
{
	/// @brief Internal 'singleton' class that keeps track of all allocated objects (windows, buffers, etc.) and
	/// provides a single place to delete them all from upon calling terminate(),
	/// @copydetails UniqueHandle
	class ResourceRegistry
	{
	public:
		using DestroyFunc = void(*)(void*) noexcept;
		using InvalidateFunc = void(*)(void*) noexcept;

		/// @brief Register a handle with the RR.
		/// @param handle The handle to be registered, as converted using handleToVoidPtr().
		/// @param handlePtr A pointer to the handle to be registered, converted to void* with regular old static_cast.
		/// @param destroyFunc A pointer to a function that destroys the resource, given its handle in void* form (you
		/// can cast back with handleFromVoidPtr()).
		/// @param invalidateFunc A pointer to a function that invalidates a handle, given a pointer to that handle as
		/// a void*.
		void register_(void* handle, void* handlePtr,
		               DestroyFunc destroyFunc, InvalidateFunc invalidateFunc) noexcept
		{
			m_entries.emplace_back(handle, handlePtr, destroyFunc, invalidateFunc);
		}

		/// @brief Unregister a handle from the RR.
		/// @param handlePtr A pointer to the handle to be unregistered, converted to void* with regular old static_cast.
		void unregister(const void* handlePtr) noexcept
		{
			for (auto it = m_entries.cbegin(); it != m_entries.cend(); ++it)
				if (it->handlePtr == handlePtr)
				{
					m_entries.erase(it);
					break;
				}
		}

		/// @brief Destroy all resources registered with the RR.
		void destroyAll() noexcept
		{
			for (const auto& entry : m_entries)
			{
				entry.destroy(entry.handle);
				entry.invalidate(entry.handlePtr);
			}

			m_entries.clear();
		}

		/// @brief Convert a handle of any type to void* for use with RR functions.
		template<typename Handle_t>
		static void* handleToVoidPtr(Handle_t handle) noexcept
		{
			if constexpr (std::is_pointer_v<Handle_t>)
				return static_cast<void*>(handle);
			else
				return reinterpret_cast<void*>(static_cast<std::uintptr_t>(handle));
		}

		/// @brief Convert a handle in void* form back into a handle of any type.
		template<typename Handle_t>
		static Handle_t handleFromVoidPtr(void* ptr) noexcept
		{
			if constexpr (std::is_pointer_v<Handle_t>)
				return static_cast<Handle_t>(ptr);
			else
				return static_cast<Handle_t>(reinterpret_cast<std::uintptr_t>(ptr));
		}

#ifdef GAL_DEV_TESTING
		/// @brief Check if the RR contains the given handle.
		bool contains(void* handlePtr) const noexcept
		{
			return std::any_of(m_entries.cbegin(), m_entries.cend(),
			                   [handlePtr](const ResourceEntry& entry)
			                   {
				                   return entry.handlePtr == handlePtr;
			                   });
		}
#endif // GAL_DEV_TESTING

	private:
		struct ResourceEntry
		{
			ResourceEntry(void* handle, void* handlePtr,
			              const DestroyFunc destroy, const InvalidateFunc invalidate)
				: handle(handle), handlePtr(handlePtr), destroy(destroy), invalidate(invalidate) { }

			void* handle;
			void* handlePtr;
			DestroyFunc destroy;
			InvalidateFunc invalidate;
		};

		std::vector<ResourceEntry> m_entries{};
	};

	inline ResourceRegistry g_resourceRegistry;
}

#endif //GAL_RESOURCE_REGISTRY_HPP