#pragma once

#include "stdafx.h"
#include <stack>

#include "loggable_memory_management.h"

template < typename T, size_t item_per_block = 10>
class block_allocator {
public:
    using value_type        = T;
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;

    class block_t {
        std::unique_ptr<T, function<void(T*)>> _ptr;
        std::array<T*, item_per_block> _available_cells;

    public:

        block_t()
#ifdef DEBUG
        : _ptr( reinterpret_cast<T*>( debug::malloc( sizeof(T) * item_per_block )), [](T* p){ debug::free(p); })
#else
        : _ptr( reinterpret_cast<T*>( malloc( sizeof(T) * item_per_block )), [](T* p){ free(p); })
#endif
        {
            size_t n = 0;
            std::generate_n(begin(_available_cells), item_per_block, [&n, this](){return _ptr.get() + n++;});
            dout << "block: init unique_pointer: " << _ptr.get() << std::endl;
        }

        block_t(block_t&& o) noexcept
        : _ptr(std::move(o._ptr))
        {
            dout << "block: move unique_pointer: " << _ptr.get() << std::endl;
        }

        const T* get_first_cell(){
            return _ptr.get();
        }

        std::array<T*, item_per_block>& get_available_cells() {
            return _available_cells;
        }


        ~block_t()
        {
            if (_ptr.get())
                dout << "block: destroy unique_pointer: " << _ptr.get() << std::endl;
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
            throw new invalid_argument( "allocate only one block per call" );

        if ( _available_cells.empty() ){
            _allocate_block();
        }


        auto out = std::move(_available_cells.top());
        _available_cells.pop();

        dout << "block_allocator: _allocate: " << _available_cells.size() << " " << out << std::endl;
        return std::move(out);

    }


    void deallocate(T *p, size_t n){
        dout << "deallocate: " << p << " n: " << n << std::endl;
        _available_cells.push(p);
    }

    void reserve( size_t n ) {
        _blocks.reserve( n / item_per_block );
    }

    block_allocator()
    {}

    template <typename U, typename ... Args>
    void construct (U* p, Args&& ... args) {
        new(p) U( forward<Args> ( args ) ... ); 
    }

    void destroy(T *p){
        p->~T();
    }
};


