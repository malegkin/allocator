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
struct simple_list_node
{
    T                   _value;
    simple_list_node*   _next;

    simple_list_node(const T& value)
            : _value( value )
            , _next( nullptr )
    {}
};

template <typename T>
struct simple_list_iterator: public iterator< forward_iterator_tag, simple_list_node<T> >
{
    using node_t            = simple_list_node<T>;
    using node_pointer_t    = simple_list_node<T>*;
    using node_value_t      = T;

    simple_list_iterator( node_pointer_t p )
        : _ptr( p )
        { }

    simple_list_iterator operator++() {
        simple_list_iterator out = *this;
        _ptr = _ptr->_next;
        return out;
    }

    node_value_t operator*()    {
        return _ptr->_value ;
    }

    node_value_t* operator->()  {
        return &(_ptr->_value);
    }

    bool operator==(const simple_list_iterator& rhs){
        return _ptr == rhs._ptr;
    }
    bool operator!=(const simple_list_iterator& rhs){
        return !operator==(rhs);
    }

private:
    node_pointer_t _ptr;
};


template <typename T, typename _Alloc = allocator< T >>
struct simple_list {
    using node_t            = simple_list_node<T>;
    using node_pointer_t    = simple_list_node<T>*;
    using node_allocator_t  = typename _Alloc::template rebind< node_t >::other;

    using reference         = T&;
    using const_reference   = const T&;

    simple_list()
        : _head_p( nullptr )
        , _tail_p( nullptr )
    {}

    void push_back(const T& data)
    {
        node_pointer_t np = _node_allocator.allocate( 1 );
        _node_allocator.construct( np, data );

        if ( _tail_p )
            _tail_p->_next = np;

        _head_p = ( _head_p ) ? _head_p : np;
        _tail_p = np;
        _size++;
    }

    simple_list_iterator<T> begin(){
        return simple_list_iterator<T>( _head_p );
    }

    simple_list_iterator<T> end(){
        return simple_list_iterator<T>( nullptr );
    }


private:
    node_pointer_t  _head_p, _tail_p;
    size_t          _size;
    node_allocator_t _node_allocator;

};


/////////////////////////////////////////////////////////////////
// block_allocated_list
template < typename T >
using block_allocated_simple_list = simple_list< T, block_allocator< T, 10 >>;

