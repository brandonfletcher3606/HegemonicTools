#include "HegemonicArenaAllocator.h"
#include "HegemonicMemoryTracker.h"

namespace Hegemonic
{
    template <size_t SIZE>
    ArenaAllocator<SIZE>::ArenaAllocator(bool aShouldResize) : mHead(nullptr), mTotalSize(0), mShouldResize(aShouldResize)
    {
        mHead = new chunk(std::malloc(SIZE), SIZE, nullptr);
        mTotalSize = SIZE;
    }

    template <size_t SIZE>
    ArenaAllocator<SIZE>::~ArenaAllocator()
    {
        chunk* current = head;
        while (current != nullptr)
        {
            chunk*next = current->next;
            std::free(current->start);
            delete current;
            current = next;
        }
    }
    
    template <size_t SIZE>
    void* ArenaAllocator<SIZE>::allocate(size_t aSize)
    {
        if (mTotalSize - sizeof(chunk) < aSize)
        {
            if (!mShouldResize)
            {
                return std::malloc(aSize);
            }
            resize(aSize);
        }

        void* start = static_cast<char*>(head->start) + sizeof(chunk);
        head->size -= aSize + sizeof(chunk);
        head->next = new Chunk{start, aSize, head->next};
        mRunningTotal += head->size;
        return start;
    }

    template <size_t SIZE>
    void* ArenaAllocator<SIZE>::allocate(size_t aSize, size_t aAlignment)
    {
        if (alignment == 0 || alignment & (alignment - 1))
        {
            // Memory alignment bust be a power of 2
            throw std::invalid_argument("ArenaAlocator::allocate : Alignment must be a power of 2");
        }

        if (mTotalSize - sizeof(chunk) < aSize)
        {
            if (!mShouldResize)
            {
                return std::malloc(aSize);
            }
            resize(aSize);
        }

        void* start = head->start;
        size_t padding = reinterpret_cast<uintptr_t>(start) % aAlignment;
        if (padding != 0)
        {
            padding = aAlignment - padding;
            start = static_cast<char*>(start) + padding;
            aSize += padding;
        }

        if (mTotalSize - sizeof(chunk) < size)
        {
            return std::malloc(aSize);
        }

        mHead->size -= aSize + sizeof(chunk);
        head->next = new chunk(start, aSize, mHead->next);
        mRunningTotal += head->size;
        return start;
    }

    template <size_t SIZE>
    void ArenaAllocator<SIZE>::deallocate(void* aMemory, size_t aSize)
    {
        // Find the chunk that contains the block of memory to deallocate
        chunk* current = head;
        while (current->next != nullptr && current->next->start != aMemory)
        {
            current = current->next;
        }

        if (current->next == nullptr || static_cast<char*>(current->next->start) + current->next->size != static_cast<char*>(aMemory) + aSize)
        {
            // the block of memory to deallocate is not part of the arena, call free/delete it
            std::free(aMemory);
            return;
        }

        // Remove the chunk from the list
        chunk* toDelete = current->next;
        current->next = toDelete->next;
        toDelete->next = nullptr;

        // merge the deallocated chunk with the previous or next chunk if possible
        if (current->next != nullptr && current->next->start == static_cast<char*>(toDelete->start) + toDelete->size)
        {
            // merge with the next chunk
            current->size += toDelete->size + current->next->size;
            current->next = current->next->next;
        }
        else
        {
            current->size += toDelete->size;
        }

        mRunningTotal -= toDelete->size + sizeof(chunk);
        std::free(toDelete->start);
        delete toDelete;
    }

    template <size_t SIZE>
    void ArenaAllocator<SIZE>::deallocate(void* aMemory, size_t aSize, size_t aAlignment)
    {
        if (alignment == 0 || alignment & (alignment - 1))
        {
            // Memory alignment bust be a power of 2
            throw std::invalid_argument("ArenaAlocator::allocate : Alignment must be a power of 2");
        }

        // Find the chunk that contains the block of memory to deallocate
        chunk* current = head;
        while (current->next != nullptr && current->next->start != aMemory)
        {
            current = current->next;
        }

        if (current->next == nullptr || static_cast<char*>(current->next->start) + current->next->size != static_cast<char*>(aMemory) + aSize)
        {
            // the block of memory to deallocate is not part of the arena, call free/delete it
            std::free(aMemory);
            return;
        }

        // Remove the chunk from the list
        chunk* toDelete = current->next;
        current->next = toDelete->next;
        toDelete->next = nullptr;

        // Merge the deallocated chunk with the previous or next chunk if possible
        if (current->next != nullptr && current->next->start == static_cast<char*>(toDelete->start) + aAlignment - 1)
        {
            // merge with next chunk
            current->size += toDelete->size + aAlignment - 1;
            current->next = current->next->next;
        }
        else
        {
            current->size += toDelete->size;
        }

        mRunningTotal -= toDelete->size + sizeof(chunk);
        std::free(toDelete->start);
        delete toDelete;
    }

    template <size_t SIZE>
    void ArenaAllocator<SIZE>::resize(size_t aToAccomodateSize)
    {
        size_t newSize = std::max(aToAccomodateSize, 2 * mTotalSize);
        chunk* newChunk = new chunk{std::malloc(newSize), newSize, mHead};
        mHead = newChunk;
        totalSize = newSize;
    }
}

// // example 1
// int main() {
//     // Create an arena allocator with an initial size of 1024 bytes and alignment turned off
//     ArenaAllocator arena1(1024, false);

//     // Allocate a 100-byte block of memory
//     char* p1 = static_cast<char*>(arena1.allocate(100));

//     // Create an arena allocator with an initial size of 1024 bytes and alignment turned on
//     ArenaAllocator arena2(1024, true);

//     // Allocate a 100-byte block of memory aligned to a 16-byte boundary
//     char* p2 = static_cast<char*>(arena2.allocateAligned(100, 16));

//     // The total size of the allocated blocks should be 200 bytes
//     std::cout << "Total size of allocated blocks: " << (arena1.totalSize + arena2.totalSize - 2048) << " bytes\n";

//     // Deallocate the memory manually when it is no longer needed
//     arena1.deallocate(p1, 100);
//     arena2.deallocateAligned(p2, 100, 16);

//     return 0;
// }

// // example 2
// int main() {
//     // Create an arena allocator with an initial size of 1024 bytes and alignment turned off
//     ArenaAllocator arena(1024, false);

//     // Create a vector of integers using the arena allocator
//     std::vector<int, ArenaAllocator<int, 1024>> vec(arena);

//     // Add some elements to the vector
//     vec.push_back(1);
//     vec.push_back(2);
//     vec.push_back(3);

//     // The vector should have 3 elements and a total size of 12 bytes
//     std::cout << "Vector size: " << vec.size() << " bytes\n";
//     std::cout << "Vector capacity: " << vec.capacity() << " bytes\n";

//     // Deallocate the memory manually when it is no longer needed
//     vec.clear();
//     arena.deallocate(vec.data(), vec.capacity() * sizeof(int));

//     return 0;
// }

// // example 3
// int main() {
//     // Create an arena allocator with an initial size of 1024 bytes and alignment turned on
//     ArenaAllocator<int, 1024, 16> arena(1024, true);

//     // Create a vector of integers using the arena allocator
//     std::vector<int, ArenaAllocator<int, 1024, 16>> vec(arena);

//     // Add some elements to the vector
//     vec.push_back(1);
//     vec.push_back(2);
//     vec.push_back(3);

//     // The vector should have 3 elements and a total size of 12 bytes
//     std::cout << "Vector size: " << vec.size() << " bytes\n";
//     std::cout << "Vector capacity: " << vec.capacity() << " bytes\n";

//     // Deallocate the memory manually when it is no longer needed
//     vec.clear();
//     arena.deallocateAligned(vec.data(), vec.capacity() * sizeof(int), 16);

//     return 0;
// }
