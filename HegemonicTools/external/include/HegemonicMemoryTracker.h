#pragma once

#include <memory>
#include <string>
#include <utility>

#include "defines.h"

namespace Hegemonic
{
	enum MemoryTag
	{
		UNKNOWN,
		ARENA,
		APPLICATION,
		USERAPPLICATION,
		RENDERER,
		WINDOW,
		EVENTINTERFACE,
		LOGINTERFACE,
		VECTOR,
		MEMORYTAGEND
	};

	struct MemoryStats
	{
		size_t totalAllocated = 0;
		size_t taggedAllocations[MemoryTag::MEMORYTAGEND];
	};

	// template this to take enum template<enum MEMORY_SET>
	// also move MemoryStats into MemoryTracker
	class MemoryTracker
	{
	public:
		// singleton shouldn't be copyable
		MemoryTracker(MemoryTracker& other) = delete;

		// singleton's shouldn't be assignable
		void operator=(const MemoryTracker&) = delete;
	
		static MemoryTracker& getInstance()
		{
			if (mMemoryTracker == nullptr)
			{
				// can't call new since it calls getInstance, have to manually insert the memory
				MemoryTracker* data = (MemoryTracker*)malloc(sizeof(MemoryTracker));
				new(data) MemoryTracker();
				mMemoryTracker = data;
			}
			return *mMemoryTracker;
		}

		void incrimentUp(size_t aSize, MemoryTag aTag);
		void incrimentDown(size_t aSize, MemoryTag aTag);
		size_t getCount(MemoryTag aTag);
		size_t getTotal();

	private:
		static MemoryTracker* mMemoryTracker;
		MemoryStats mMemoryStats = MemoryStats();

		MemoryTracker() = default;
	};

	static std::string convertCountToString(size_t aSize)
	{
		const int kb = 1000;
		const int mb = 1000 * kb;
		const int gb = 1000 * mb;
		if (aSize > gb)
		{
			return std::to_string(aSize / gb) + "GB";
		}
		else if (aSize > mb)
		{
			return std::to_string(aSize / mb) + "MB";
		}
		else if (aSize > kb)
		{
			return std::to_string(aSize / kb) + "KB";
		}
		return std::to_string(aSize) + "B";
	}
}