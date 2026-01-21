//
// Created by kassie on 21/01/2026.
//

#ifndef GAL_RESOURCE_REGISTRY_HPP
#define GAL_RESOURCE_REGISTRY_HPP

#include <algorithm>
#include <vector>

namespace gal::detail
{
	class ResourceRegistry
	{
	public:
		using DestroyFunc = void(*)(void*) noexcept;
		using InvalidateFunc = void(*)(void*) noexcept;

		void register_(void* resource, void* ownerHandlePtr,
		               DestroyFunc destroyFunc, InvalidateFunc invalidateFunc) noexcept
		{
			entries.emplace_back(resource, ownerHandlePtr, destroyFunc, invalidateFunc);
		}

		void unregister(void* resource) noexcept
		{
			const auto it = std::remove_if(entries.begin(), entries.end(),
			                               [resource](const auto& entry)
			                               {
				                               return entry.resource == resource;
			                               });

			entries.erase(it, entries.end());
		}

		void destroyAll() noexcept
		{
			for (const auto& entry : entries)
			{
				entry.destroy(entry.resource);
				entry.invalidate(entry.ownerHandlePtr);
			}

			entries.clear();
		}

	private:
		struct ResourceEntry
		{
			ResourceEntry(void* resource, void* ownerHandlePtr,
			              const DestroyFunc destroy, const InvalidateFunc invalidate)
				: resource(resource), ownerHandlePtr(ownerHandlePtr), destroy(destroy), invalidate(invalidate) { }

			void* resource;
			void* ownerHandlePtr;
			DestroyFunc destroy;
			InvalidateFunc invalidate;
		};

		std::vector<ResourceEntry> entries{};
	};

	inline ResourceRegistry resourceRegistry{};
}

#endif //GAL_RESOURCE_REGISTRY_HPP
