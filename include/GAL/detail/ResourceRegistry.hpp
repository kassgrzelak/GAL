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

		void register_(void* resourcePtr, DestroyFunc destroyFunc)
		{
			entries.emplace_back(resourcePtr, destroyFunc);
		}

		void unregister(void* resourcePtr)
		{
			const auto it = std::remove_if(entries.begin(), entries.end(),
			                               [resourcePtr](const auto& entry)
			                               {
				                               return entry.ptr == resourcePtr;
			                               });

			entries.erase(it, entries.end());
		}

		void destroyAll() noexcept
		{
			for (auto& entry : entries)
				entry.destroy(entry.ptr);

			entries.clear();
		}

	private:
		struct ResourceEntry
		{
			ResourceEntry(void* ptr, const DestroyFunc destroy) : ptr(ptr), destroy(destroy) { }

			void* ptr;
			DestroyFunc destroy;
		};

		std::vector<ResourceEntry> entries = {};
	};

	inline ResourceRegistry resourceRegistry{};
}

#endif //GAL_RESOURCE_REGISTRY_HPP
