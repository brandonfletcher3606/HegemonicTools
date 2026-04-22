#include <iostream>
#include <memory>

#include "HegemonicMemory.h"

namespace Hegemonic
{
	MemoryTracker* MemoryTracker::mMemoryTracker = nullptr;

	void MemoryTracker::incrimentUp(size_t aSize, MemoryTag aTag)
	{
		if (aTag == MemoryTag::MEMORYTAGEND)
		{
			aTag = MemoryTag::UNKNOWN;
		}

		mMemoryStats.taggedAllocations[aTag] += aSize;
		mMemoryStats.totalAllocated += aSize;
	}

	void MemoryTracker::incrimentDown(size_t aSize, MemoryTag aTag)
	{
		if (aTag == MemoryTag::MEMORYTAGEND)
		{
			aTag = MemoryTag::UNKNOWN;
		}

		mMemoryStats.taggedAllocations[aTag] -= aSize;
		mMemoryStats.totalAllocated -= aSize;
	}

	size_t MemoryTracker::getCount(MemoryTag aTag)
	{
		return mMemoryStats.taggedAllocations[aTag];
	}

	size_t MemoryTracker::getTotal()
	{
		size_t total = 0;
		total += getCount(MemoryTag::UNKNOWN);
		total += getCount(MemoryTag::APPLICATION);
		total += getCount(MemoryTag::USERAPPLICATION);
		total += getCount(MemoryTag::RENDERER);
		total += getCount(MemoryTag::WINDOW);
		total += getCount(MemoryTag::EVENTINTERFACE);
		total += getCount(MemoryTag::LOGINTERFACE);
		total += getCount(MemoryTag::VECTOR);
		total += getCount(MemoryTag::ARENA);
		return total;
	}
}