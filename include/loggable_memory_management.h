#pragma once

#include "stdafx.h"

#include <stdint.h>
#include <cstddef>
#include <new>

namespace debug {

    extern std::size_t alloc_counter;
    void* malloc(std::size_t size); //throw (std::bad_alloc);
    void free(void* p) noexcept;

} // namespace my



extern "C++" {

    void* operator new(std::size_t size);
    void* operator new(std::size_t size, const std::nothrow_t&) noexcept;

    void* operator new[](std::size_t size);
    void* operator new[](std::size_t size, const std::nothrow_t&) noexcept;
    

    
    void operator delete(void* p) noexcept;
    void operator delete(void* p, long unsigned int) noexcept;
    void operator delete(void* p, const std::nothrow_t&) noexcept;

    void operator delete[](void* p) noexcept; 
    void operator delete[](void* p, long unsigned int) noexcept;
    void operator delete[](void* p, const std::nothrow_t&) noexcept;

} // extern "C++"

