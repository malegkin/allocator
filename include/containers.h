#pragma once

#include "stdafx.h"
#include "block_allocator.h"

/////////////////////////////////////////////////////////////////
// block_allocated_map
template < typename Key, typename T >
using block_allocated_map = std::map< Key, T, std::less<Key>, block_allocator< std::pair< const Key, T >, 10 >>;


/////////////////////////////////////////////////////////////////
template <typename T>
struct simple_list_node
{
    T                   _value;
    simple_list_node*   _next;
    simple_list_node*   _prev;

    simple_list_node()
        : _next( this )
        , _prev( this )
    {}

    simple_list_node(const T& value)
            : _value( value )
            , _next( this )
            , _prev( this )
    {}
};

template <typename T>
struct simple_list_iterator: public std::iterator< std::bidirectional_iterator_tag, simple_list_node<T> >
{
    simple_list_iterator() = default;
    simple_list_iterator( simple_list_node<T>* p )          : _ptr( p )         { }
    simple_list_iterator( const simple_list_iterator& sli)  : _ptr( sli._ptr )  { }

    //prefix
    simple_list_iterator& operator++() { _ptr = _ptr->_next; return *this; }
    simple_list_iterator& operator--() { _ptr = _ptr->_prev; return *this; }

    //postfix
    simple_list_iterator operator++(int) { simple_list_iterator out = *this; _ptr = _ptr->_next; return out; }
    simple_list_iterator operator--(int) { simple_list_iterator out = *this; _ptr = _ptr->_prev; return out; }


    T&   operator*()   { return _ptr->_value ;   }
    T*   operator->()  { return &(_ptr->_value); }

    bool operator==(const simple_list_iterator& rhs){ return _ptr == rhs._ptr; }
    bool operator!=(const simple_list_iterator& rhs){ return !operator==(rhs); }

private:

    simple_list_node<T>* _ptr;

};


template <typename T, typename _Alloc = std::allocator< T >>
struct simple_list   {

    using value_type        = T;

    using reference         = T&;
    using const_reference   = const T&;

    using iterator          = simple_list_iterator<T>;

    using difference_type   = std::ptrdiff_t;
    using size_type         = std::size_t;



    using node_t            = simple_list_node<T>;
    using node_pointer_t    = simple_list_node<T>*;
    using node_allocator_t  = typename _Alloc::template rebind< node_t >::other;


    simple_list() noexcept
        : _head_p( &_last_node )
        , _tail_p( &_last_node )
        , _size( 0 )
    {}

    void push_back(const_reference data)
    {
        node_pointer_t np = _node_allocator.allocate( 1 );

        _node_allocator.construct( _tail_p, data );
        np->_prev = _tail_p;
        _tail_p = np;

        _size++;
    }

    simple_list_iterator<T> begin(){
        return simple_list_iterator<T>( _head_p );
    }

    simple_list_iterator<T> end(){
        return simple_list_iterator<T>( _tail_p );
    }


    reference       front()         {   return *(begin()); }
    reference       back()          {   return *(--end()); }

    const_reference front() const   {   return *(begin()); }
    const_reference back()  const   {   return *(--end()); }

    size_t  size(){
        return _size;
    }

private:
    node_pointer_t  _head_p, _tail_p;
    size_t          _size;
    node_allocator_t _node_allocator;
    node_t          _last_node;
};


/////////////////////////////////////////////////////////////////
// block_allocated_list
template < typename T >
using block_allocated_simple_list = simple_list< T, block_allocator< T, 10 >>;

