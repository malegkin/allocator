#include <cstdlib>
#include <stdio.h>
#include <new>

#include <execinfo.h>

namespace debug {

  std::size_t alloc_counter = 0;

  void* malloc(std::size_t size)  
  {
      /*
      void *bt_array[2];
      backtrace(bt_array, 2);

      // print out all the frames to stderr
      printf("Error: signal %s:\n", bt_array[1]);
        */


    void* p = std::malloc(size);
    printf("\tmalloc: %zu %p %zu\n", ++alloc_counter, p, size);
    return p;
  }

  void free(void* p) noexcept
  {
    printf("\tfree: %zu %p\n", --alloc_counter, p);
    std::free(p);
    return;
  }
}


extern "C++" {
    /*
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
     */

/*

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
*/


}
