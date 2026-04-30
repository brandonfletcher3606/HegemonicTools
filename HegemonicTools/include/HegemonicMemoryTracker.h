#pragma once

#include <memory>
#include <string>
#include <utility>
#include <unordered_map>

#include "HegemonicToolsDefines.h"

namespace Hegemonic
{
	class HEXPORT_TOOLS MemoryTracker
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

		void addTag(std::string aTag);
		void incrimentUp(size_t aSize, std::string aTag);
		void incrimentDown(size_t aSize, std::string aTag);
		bool isTag(std::string aTag);
		int getCount(std::string aTag);
		int getTotal();

	private:
		static MemoryTracker* mMemoryTracker;
		std::unordered_map<std::string, int> mData;

		MemoryTracker() = default;
	};

	// static std::string convertCountToString(size_t aSize)
	// {
	// 	const int kb = 1000;
	// 	const int mb = 1000 * kb;
	// 	const int gb = 1000 * mb;
	// 	if (aSize > gb)
	// 	{
	// 		return std::to_string(aSize / gb) + "GB";
	// 	}
	// 	else if (aSize > mb)
	// 	{
	// 		return std::to_string(aSize / mb) + "MB";
	// 	}
	// 	else if (aSize > kb)
	// 	{
	// 		return std::to_string(aSize / kb) + "KB";
	// 	}
	// 	return std::to_string(aSize) + "B";
	// }
}