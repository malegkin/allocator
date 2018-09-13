
#include "../include/loggable_memory_management.h"

#ifdef DEBUG

namespace debug {

  std::size_t alloc_counter      = 0;

  void* malloc(std::size_t size)  
  {
    void* p = std::malloc(size);
    dout << "\tmalloc: " << ++alloc_counter << " " <<  p << " " <<  size << std::endl;
    return p;
  }

  void free(void* p) noexcept
  {
    dout << "free: " << --alloc_counter << p << std::endl;
    std::free(p);
  }
}


extern "C++" {
    void* operator new(std::size_t size) 
    {
        return debug::malloc(size);
    }

    void* operator new(std::size_t size, const std::nothrow_t&) noexcept
    {
        return debug::malloc(size);
    }

    void* operator new[](std::size_t size) 
    {
        return debug::malloc(size);
    }

    void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
    {
        return debug::malloc(size);
    }



    void operator delete(void* p) noexcept
    {
        debug::free(p);
    }
    
    void operator delete(void* p, long unsigned int) noexcept
    {
        debug::free(p);
    }
    
    void operator delete(void* p, const std::nothrow_t&) noexcept
    {
        debug::free(p);
    }


    //
    void operator delete[](void* p)  noexcept
    {
        debug::free(p);
    }

    void operator delete [](void* p, long unsigned int) noexcept
    {
        debug::free(p);
    }

    void operator delete[](void* p, const std::nothrow_t&) noexcept
    {
        debug::free(p);
    }



}


#endif