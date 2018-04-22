#pragma once

#include "stdafx.h"
#include <vector>
#include <map>

constexpr uint64_t factorial(const size_t n)
{
    return (n < 2) ? 1 : factorial(n - 1) * n ;
}


//block_allocator

template < typename T, size_t item_per_block = 10 >
class block_allocator {
public:
    using value_type        = T;    
    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;

    struct block {
        unique_ptr< T, function< void(T*) >> ptr;
  
        block(): 
            ptr( reinterpret_cast<T*>( malloc( sizeof(T) * item_per_block )), [](T* p){ free(p); })
        {}

        T* operator[] ( size_t id ){
            if (id >= item_per_block)
                throw new invalid_argument( "too large index" );
            
            return ptr.get() + id;
        }
    };

    vector< block > blocks;
    size_t item_allocated_count = 0;
        

    template<typename U>
    struct rebind {
        using other = block_allocator<U>;
    };


    T* allocate( size_t n ){
        if (n > 1)
            throw new bad_alloc();
        
        item_allocated_count++;        
    
        
        size_t block_id = item_allocated_count / item_per_block;        
        size_t item_id  = item_allocated_count % item_per_block;

        if ( block_id >= blocks.size() )
            blocks.push_back( block() );


        return blocks[block_id][item_id];
    }

    void deallocate(T *p, size_t n){
    }

    void reserve( size_t n ) {
        blocks.reserve( n / item_per_block );
    }

    block_allocator() {
        reserve( item_per_block );
        blocks.reserve (10);
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
// otus_map
template < typename Key, typename T >
using otus_map = map< Key, T, less<Key>, block_allocator< pair< const Key, T >, 10 >>;



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


template <typename T, typename _Alloc = block_allocator< T , 10 >> 
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


