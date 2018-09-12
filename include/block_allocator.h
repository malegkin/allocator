#pragma once

#include <queue>
#include "stdafx.h"
#include "loggable_memory_management.h"

 template < typename T, size_t item_per_block = 10, size_t max_available_cells = 100 >
class block_allocator {
public:
    using value_type        = T;    
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;

    using available_cells_t = std::queue<T*>;

    class block {
        std::unique_ptr<T, function<void(T*)>> ptr;

        std::array<T*, item_per_block> available_cells;

    public:
        block()
        : ptr( reinterpret_cast<T*>( debug::malloc( sizeof(T) * item_per_block )), [](T* p){ debug::free(p); })
        {
            size_t n = 0;
            std::generate_n(begin(available_cells), item_per_block, [&n, this](){return ptr.get() + n++;});
            std::cout << "block: init unique_pointer: " << ptr.get() << std::endl;
        }

        block(block&& o) noexcept
        : ptr(std::move(o.ptr))
        {
            std::cout << "block: move unique_pointer: " << ptr.get() << std::endl;
        }

        std::array<T*, item_per_block>& get_available_cells(){


            return available_cells;
        }

        /*
        //subscript operator
        T* operator[] ( std::size_t id )
        {
            if (id >= item_per_block)
                throw new invalid_argument( "too large index" );

            return ptr.get() + id;
        }
        */
        ~block()
        {
            if (ptr.get())
                std::cout << "block: destroy unique_pointer: " << ptr.get() << std::endl;
        }
    };


    available_cells_t available_cells;
    std::list< block > blocks;

    uint32_t item_allocated_count = 0;
        

    template<typename U>
    struct rebind {
        using other = block_allocator<U>;
    };


    T* allocate( size_t n ){
        if (n != 1)
            throw new invalid_argument( "allocate only one block per call" );


        std::cout << available_cells.size() << std::endl;
        std::cout << available_cells.empty() << std::endl;

        if ( !available_cells.size() ){
            block new_block;
            auto new_cells = new_block.get_available_cells();
            available_cells.assign(begin(new_cells), end(new_cells));
            blocks.push_back(std::move(new_block));
        }
        
        //uint32_t block_id = item_allocated_count / item_per_block;
        //uint32_t item_id  = item_allocated_count % item_per_block;

/*
        if ( block_id >= blocks.size() ) {

            blocks.push_back( std::move(block()) );
            //blocks.insert(std::make_pair(block_id, block()));
        }
*/


//        item_allocated_count++;

        T* out = available_cells.back();
        available_cells.pop_back();
        return out;
    }


    void deallocate(T *p, size_t n){}

    void reserve( size_t n ) {
        blocks.reserve( n / item_per_block );
    }

    block_allocator()
    //: available_cells(max_available_cells)
    {

    }

    template <typename U, typename ... Args>
    void construct (U* p, Args&& ... args) {
        new(p) U( forward<Args> ( args ) ... ); 
    }

    void destroy(T *p){
        p->~T();
    }
};


/////////////////////////////////////////////////////////////////
// block_allocated_map
template < typename Key, typename T >
using block_allocated_map = map< Key, T, less<Key>, block_allocator< pair< const Key, T >, 10 >>;


/*
/////////////////////////////////////////////////////////////////
//template <typename T, typename _Alloc = block_allocator<T, 10 >>
template <typename T>
struct otus_list_node {

    using value_type = T;

    value_type      value_;
    otus_list_node* next_;

    otus_list_node(const T& value)
                : value_( value )
                , next_( nullptr )
                {}
};

template <typename T>
struct otus_list_iterator: public iterator< forward_iterator_tag, otus_list_node<T> >  
{
    using node_type         = otus_list_node<T>;
    using node_pointer      = otus_list_node<T>*;
    typedef typename otus_list_node<T>::value_type node_value_type;
 
    otus_list_iterator( node_pointer ptr ) : ptr_( ptr ) { }

    otus_list_iterator operator++() { 
        otus_list_iterator out = *this; 
        ptr_ = ptr_->next_; 
        return out; 
    }

    node_value_type operator*() { 
        return ptr_->value_ ; 
    }

    node_value_type* operator->() { 
        return &(ptr_->value_); 
    }

    bool operator==(const otus_list_iterator& rhs){
        return ptr_ == rhs.ptr_;
    }
    bool operator!=(const otus_list_iterator& rhs){
        return ptr_ != rhs.ptr_;
    }
    
    node_pointer ptr_;
};


template <typename T, typename _Alloc = allocator< T >>
class otus_list {
    using node_type     = otus_list_node<T>;
    using node_pointer  = otus_list_node<T>*;
    
    node_pointer head, tail;
    size_t elements;

    typedef typename _Alloc::template rebind< otus_list_node<T> >::other node_allocator_type;
    node_allocator_type alloc;

public:
    otus_list(): 
        head( nullptr ), 
        tail( nullptr )
    {}

    void push_back(const T& data){
        node_pointer pn = alloc.allocate( 1 );
        alloc.construct( pn, data );

        if ( head == nullptr)
            head = pn;

        if(tail != nullptr)
            tail->next_ = pn;

        tail = pn;
        elements++;
    }

    otus_list_iterator<T> begin(){
        return otus_list_iterator<T>( head );
    }

    otus_list_iterator<T> end(){
        return otus_list_iterator<T>( nullptr );
    }

};


/////////////////////////////////////////////////////////////////
// block_allocated_list
template < typename T >
using block_allocated_list = otus_list< T, block_allocator< T, 10 >>;
*/