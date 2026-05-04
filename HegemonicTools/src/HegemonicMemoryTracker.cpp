#include <iostream>
#include <memory>

#include "HegemonicMemory.h"
#include "HegemonicLogger.h"

namespace Hegemonic
{
	MemoryTracker* MemoryTracker::mMemoryTracker = nullptr;

	void MemoryTracker::incrimentUp(size_t aSize, std::string aTag)
	{
		if (!isTag(aTag))
		{
			Hegemonic::logWarning("MemoryTracker::incrimentUp string ", aTag, " is not a tag");
			return;
		}
		mData[aTag] += aSize;
	}
	void MemoryTracker::incrimentDown(size_t aSize, std::string aTag)
	{
		if (!isTag(aTag))
		{
			Hegemonic::logWarning("MemoryTracker::incrimentDown string ", aTag, " is not a tag");
			return;
		}
		mData[aTag] -= aSize;
	}
	bool MemoryTracker::isTag(std::string aTag)
	{
		return mData.count(aTag) > 0;
	}
	void MemoryTracker::addTag(std::string aTag)
	{
		if (isTag(aTag))
		{
			Hegemonic::logWarning("MemoryTracker::addTag string ", aTag, " is already a tag");
			return;
		}
		mData[aTag] = 0;
	}
	int MemoryTracker::getCount(std::string aTag)
	{
		if (!isTag(aTag))
		{
			Hegemonic::logWarning("MemoryTracker::getCount string ", aTag, " is not a tag");
			return 0;
		}
		return mData[aTag];
	}
	int MemoryTracker::getTotal()
	{
		int total = 0;
		for (const auto& pair : mData) 
		{
			total += pair.second;
		}
		return total;
	}

	std::vector<std::string> MemoryTracker::getTags()
	{
		std::vector<std::string> keys;
		if (mData.size() == 0)
		{
			return keys;
		}

		keys.reserve(mData.size());
		for (const auto& pair : mData)
		{
			keys.push_back(pair.first);
		}
		return keys;
	}
}