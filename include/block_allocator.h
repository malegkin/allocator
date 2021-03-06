#pragma once
#include "stdafx.h"


#include <stack>
#include <memory>
#include <functional>

#include "loggable_memory_management.h"

#ifdef DEBUG
    #define dmalloc debug::malloc
    #define dfree   debug::free
#else
    #define dmalloc malloc
    #define dfree   free
#endif

static struct {
    size_t total_allocated_blocks   = 0;
    size_t total_deallocated_blocks = 0;
} _block_statistics;


template < typename T, size_t item_per_block = 10>
class block_allocator {
public:
    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;

    struct {
        size_t allocated_cells    = 0;
        size_t deallocated_cells  = 0;

        size_t constructed        = 0;
        size_t destructed         = 0;
    } _statistics;

    class block_t {
        std::unique_ptr<T, std::function<void(T*)>> _ptr;
        std::array<T*, item_per_block> _available_cells;

    public:

        block_t()
        : _ptr( reinterpret_cast<T*>( dmalloc( sizeof(T) * item_per_block )), [](T* p){ dfree(p); })
        {
            _block_statistics.total_allocated_blocks++;

            size_t n = 0;
            std::generate_n(begin(_available_cells), item_per_block, [&n, this](){return _ptr.get() + n++;});
            dout << "block: init unique_pointer: " << _ptr.get() << std::endl;
        }

        block_t(block_t&& o) noexcept
        : _ptr(std::move(o._ptr))
        {
            dout << "block: move unique_pointer: " << _ptr.get() << std::endl;
        }

        std::array<T*, item_per_block>& get_available_cells() {
            return _available_cells;
        }

        ~block_t()
        {
            if (_ptr.get()) {
                _block_statistics.total_deallocated_blocks++;
                dout << "block: destroy unique_pointer: " << _ptr.get() << std::endl;
            }
        }
    };



    std::list<block_t>  _blocks;
    std::stack<T*>      _available_cells;


    void _allocate_block(){

        dout << "block_allocator: _allocate_block()" << std::endl;

        block_t block;
        for(auto a: block.get_available_cells()){
            _available_cells.push(std::move(a));
        }
        _blocks.push_back(std::move(block));
    }



    template<typename U>
    struct rebind {
        using other = block_allocator<U>;
    };


    T* allocate( size_t n ){
        if (n != 1)
            throw new std::invalid_argument( "Sorry, cureent version cat to allocate only one block per call" );

        if ( _available_cells.empty() ){
            _allocate_block();
        }

        auto out = std::move(_available_cells.top());
        _available_cells.pop();

        dout << "block_allocator: _allocate: " << _available_cells.size() << " " << out << std::endl;

        _statistics.allocated_cells++;

        return std::move(out);

    }


    void deallocate(T *p, size_t n){
        dout << "deallocate: " << p << " n: " << n << std::endl;

        _statistics.deallocated_cells++;

        _available_cells.push(p);
    }

    void reserve( size_t n ) {
        _blocks.reserve( n / item_per_block );
    }

    block_allocator()
    {}

    template <typename U, typename ... Args>
    void construct (U* p, Args&& ... args) {
        _statistics.constructed++;

        new(p) U( std::forward<Args> ( args ) ... );
    }

    void destroy(T *p){
        _statistics.destructed++;
        p->~T();
    }
};


