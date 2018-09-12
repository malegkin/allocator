#pragma once

#include "stdafx.h"
#include "block_allocator.h"

/////////////////////////////////////////////////////////////////
// block_allocated_map
template < typename Key, typename T >
using block_allocated_map = map< Key, T, less<Key>, block_allocator< pair< const Key, T >, 10 >>;



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

