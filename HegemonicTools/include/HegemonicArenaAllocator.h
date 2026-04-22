#pragma once

#include "HegemonicMemory.h"
#include "HegemonicLogger.h"

namespace Hegemonic
{
    template <size_t SIZE> 
    class ArenaAllocator
    {
    private:
        struct chunk
        {
            void* start;
            size_t size;
            chunk* next;
        };

        chunk* mHead;
        size_t mTotalSize;
        size_t mRunningTotal = 0;
        bool mShouldResize = false; // tell the arena to resize/gain more memory if it runs out, otherwise it will resort to malloc

        void resize(size_t aToAccomodateSize);

    public:
        ArenaAllocator(bool aShouldResize);
        ~ArenaAllocator();
        
        void* allocate(size_t aSize);
        void* allocate(size_t aSize, size_t aAlignment);
        void deallocate(void* aMemory, size_t aSize);
        void deallocate(void* aMemory, size_t aSize, size_t aAlignment);

        size_t getTotalSize() { return mTotalSize; };
        size_t getAvailable() { return SIZE - mRunningTotal; };
        size_t getUsed() { return mRunningTotal; };

        bool isAligned() { return mAlignMemory; };
    };
}