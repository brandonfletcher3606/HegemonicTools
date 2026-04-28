#pragma once

#include "HegemonicMemory.h"
#include "HegemonicToolsDefines.h"

#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <new>

namespace Hegemonic
{
    template<size_t SIZE>
    class ArenaAllocator 
    {
    public:
        explicit ArenaAllocator() : mOffset(0) 
        {
            mBuffer = new char[SIZE];
        }
        ~ArenaAllocator() 
        {
            delete[] mBuffer;
        }

        ArenaAllocator(const ArenaAllocator&) = delete;
        ArenaAllocator& operator=(const ArenaAllocator&) = delete;
    
        template <typename T>
        T* allocate() 
        {
            // Calculate the required size and alignment.
            size_t required_size = sizeof(T);
            size_t alignment = alignof(T);

            // Adjust the offset to ensure correct alignment.
            size_t aligned_offset = (mOffset + alignment - 1) & ~(alignment - 1);

            // Check if there is enough space.
            if (aligned_offset + required_size > SIZE) {
                throw std::bad_alloc();
            }

            // Return a pointer to the newly allocated block.
            void* ptr = mBuffer + aligned_offset;
            mOffset = aligned_offset + required_size;

            // Use placement new to construct the object.
            return new (ptr) T();
        }
        void reset() 
        {
            mOffset = 0;
        }
        size_t isUsed()
        {
            return mOffset;
        }
        size_t isAvailable()
        {
            return SIZE - mOffset;
        }
        void* get()
        {
            return mBuffer;
        }

    private:
        char* mBuffer;
        size_t mOffset;
    };
    // template <size_t SIZE>
    // class ArenaAllocator 
    // {
    //     u64 mAllocated = 0;
    //     void* mMemory = nullptr;

    // public:
    //     ArenaAllocator() : offset(0) 
    //     {
            
    //     }
    //     void* allocate(size_t aBytes, size_t aAlignment) 
    //     {
    //         // // Round up offset to satisfy aAlignment
    //         // size_t padding = (aAlignment - (reinterpret_cast<uintptr_t>(mBuffer + offset) % aAlignment)) % aAlignment;
    //         // if (offset + padding + aBytes > SIZE) 
    //         // {
    //         //     return nullptr;
    //         // }
            
    //         // void* ptr = mBuffer + offset + padding;
    //         // offset += padding + aBytes;
    //         // return ptr;
    //     }
    //     void* allocate(size_t aBytes) 
    //     {
    //         // Round up offset to satisfy aAlignment
    //         size_t padding = 0;
    //         if (offset + padding + aBytes > SIZE) 
    //         {
    //             return nullptr;
    //         }
            
    //         void* ptr = mBuffer + offset + padding;
    //         offset += padding + aBytes;
    //         return ptr;
    //     }
    //     void get(void* &aValue)
    //     {
    //         if (aValue != nullptr)
    //         {
    //             aValue = nullptr;
    //         }
    //         aValue = mBuffer;;
    //     }
    //     void reset() 
    //     { 
    //         offset = 0; 
    //     }
    //     ~ArenaAllocator() 
    //     { 
    //         delete[] mBuffer; 
    //     }
    // };

    // template <size_t SIZE> 
    // class ArenaAllocator
    // {
    // private:
    //     static constexpr size_t mAlignment = alignof(std::max_align_t);
    //     void* mBuffer = nullptr;
    //     size_t mOffset = 0;
    //     size_t mCommited = 0;

    //     static constexpr size_t alignUp(size_t aSize) noexcept 
    //     {
    //         return (aSize + mAlignment-1) & ~(mAlignment-1);
    //     }

    // public:
    //     ArenaAllocator()
    //     {
    //         if (SIZE == 0) {throw std::logic_error("ArenaAllocator cannot have zero size"); };
    //         mBuffer = std::malloc(SIZE);
    //     }

    //     ~ArenaAllocator()
    //     {
    //         delete mBuffer;
    //         mBuffer = nullptr;
    //     }

    //     void get(void* &aValue)
    //     {
    //         if (aValue != nullptr)
    //         {
    //             aValue = nullptr;
    //         }
    //         aValue = mBuffer;;
    //     }

    //     size_t isUsed() const noexcept {
    //         return mOffset;
    //     }

    //     size_t isRemaining() const noexcept {
    //         return SIZE-mCommited;
    //     }

    //     void* allocate(std::size_t aSize)
    //     {
    //         void* currPtr = static_cast<char*>(mBuffer) + mOffset;
    //         void* offset = alignUp(aSize);
    //         offset -= static_cast<char*>(mBuffer);

    //         if (offset + aSize > SIZE)
    //         {
    //             return nullptr;
    //         }

    //         mCommited += aSize;
    //         void* ptr = static_cast<char*>(mBuffer) + offset;
    //         mOffset = offset + size;
            
    //         return ptr;


    //         // alignedMemory -= mBuffer;

    //         // if (alignedMemory + aSize > SIZE)
    //         // {
    //         //     // should return NULL or allocated memory, don't know yet
    //         //     return nullptr;
    //         // }

    //         // void* ptr = static_cast<char*>(mBuffer) + alignedMemory;
    //         // mOffset += alignedMemory + aSize;
    //         // return ptr;
    //     }
    // };
}