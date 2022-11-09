#pragma once
#include "headers/System_Common.h"

namespace TurboHybrid {
    class StackAllocator
    {
    public:
        StackAllocator(const size_t& stackSize, char* buffer) :
            buffer(buffer),
            stackSize(stackSize)
        {
            clear();
        }

        ~StackAllocator() {
            delete buffer;
            
        }

        template <typename T>
        T* alloc() { alloc<T>(1); }

        template <typename T>
        T* alloc(size_t* arrayCount) {
            size_t sizeToAllocate = sizeof(T) * arrayCount;
            T* allocationPoint = (T*)base;
            // TODO: Make sure we're not writing past the
            //         end of the stack!
            if (base + sizeToAllocate > buffer + stackSize)
            {
                return nullptr;
            }
            base += sizeToAllocate;
            return allocationPoint;
        }

        void clear() {
            base = buffer;
        }

    private:
        char* buffer;
        char* base;
        size_t stackSize;
    };
}

