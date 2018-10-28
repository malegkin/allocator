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
    using _iterator_t = simple_list_iterator;

    simple_list_iterator() = default;
    simple_list_iterator( simple_list_node<T>* p )          : _ptr( p )         { }
    simple_list_iterator( const simple_list_iterator& sli)  : _ptr( sli._ptr )  { }

    //prefix
    _iterator_t& operator++() { _ptr = _ptr->_next; return *this; }
    _iterator_t& operator--() { _ptr = _ptr->_prev; return *this; }

    //postfix
    _iterator_t operator++(int) { _iterator_t out = *this; _ptr = _ptr->_next; return out; }
    _iterator_t operator--(int) { _iterator_t out = *this; _ptr = _ptr->_prev; return out; }

    T&   operator*()   { return _ptr->_value ;   }
    T*   operator->()  { return &(_ptr->_value); }

    bool operator==(const _iterator_t& rhs){ return _ptr == rhs._ptr; }
    bool operator!=(const _iterator_t& rhs){ return !operator==(rhs); }


    simple_list_node<T>* _ptr;

};

template <typename T>
struct simple_list_const_iterator: public std::iterator< std::bidirectional_iterator_tag, simple_list_node<T> >
{
    using _iterator_t = simple_list_const_iterator;

    simple_list_const_iterator() = default;
    simple_list_const_iterator( simple_list_node<T>* p )                : _ptr( p )         { }
    simple_list_const_iterator( const simple_list_iterator<T>& sli)     : _ptr( sli._ptr )  { }
    simple_list_const_iterator( const simple_list_const_iterator& sli)  : _ptr( sli._ptr )  { }

    //prefix
    _iterator_t& operator++() { _ptr = _ptr->_next; return *this; }
    _iterator_t& operator--() { _ptr = _ptr->_prev; return *this; }

    //postfix
    _iterator_t operator++(int) { _iterator_t out = *this; _ptr = _ptr->_next; return out; }
    _iterator_t operator--(int) { _iterator_t out = *this; _ptr = _ptr->_prev; return out; }


    const T&   operator*()  const { return _ptr->_value ;   }
    const T*   operator->() const { return &(_ptr->_value); }

    bool operator==(const _iterator_t& rhs){ return _ptr == rhs._ptr; }
    bool operator!=(const _iterator_t& rhs){ return !(operator==(rhs)); }


    simple_list_node<T>* _ptr;

};


template <typename T, typename _Alloc = std::allocator< T >>
struct simple_list   {

    using value_type        = T;

    using reference         = T&;
    using rv_reference      = T&&;
    using const_reference   = const T&;

    using iterator          = simple_list_iterator<T>;
    using const_iterator    = simple_list_const_iterator<T>;

    using difference_type   = std::ptrdiff_t;
    using size_type         = std::size_t;

    using allocator_type    = _Alloc;

    using node_t            = simple_list_node<T>;
    using node_pointer_t    = simple_list_node<T>*;
    using node_allocator_t  = typename _Alloc::template rebind< node_t >::other;


    simple_list()
    :_size( 0 )
    {
        _head_p = _node_allocator.allocate( 1 );
        _node_allocator.construct( _head_p );
        _tail_p = _head_p;
    }

    iterator begin(){
        return iterator( _head_p );
    }

    const_iterator begin() const {
        return const_iterator( _head_p );
    }

    const_iterator cbegin() const {
        return const_iterator( _head_p );
    }

    iterator end(){
        return iterator( _tail_p );
    }

    const_iterator end() const {
        return const_iterator( _tail_p );
    }

    const_iterator cend() const {
        return const_iterator( _tail_p );
    }


    //inserts value before position
    iterator insert ( const_iterator position, const value_type& value ){
        node_pointer_t np = _node_allocator.allocate( 1 );
        _node_allocator.construct( np, value );
        _size++;

        if ( cbegin() == position ){
                _head_p = np;
                //_tail_p = _tail_p;

                np->_next = position._ptr;
                //np->_prev = np;

                //position->_next = position->_next;
                position._ptr->_prev = np;

        }   else {

                //_head_p = _head_p;
                //_tail_p = _tail_p;

                np->_next = position._ptr;
                np->_prev = position._ptr->_prev;

                //position->_next = position->_next;
                position._ptr->_prev = np;

                np->_prev->_next = np;

        }

        return simple_list_iterator<T>(np);
    }

    void push_back(const_reference value)
    {
        insert(cend(), value);
    }

    void push_front(const_reference value)
    {
        insert(cbegin(), value);
    }

    void pop_back(){
        if ( !_size )
            return;

        node_pointer_t op = _tail_p;
        _tail_p = _tail_p->_prev;
        _tail_p->_next = _tail_p;

        _node_allocator.destroy(op);
        _node_allocator.deallocate(op, 1);

        _size--;
    }

    void pop_front(){
        if ( !_size )
            return;

        node_pointer_t op = _head_p;
        _head_p = _head_p->_next;
        _head_p->_prev = _head_p;

        _node_allocator.destroy(op);
        _node_allocator.deallocate(op, 1);

        _size--;
    }


    reference       front()         {   return *(begin());  }
    reference       back()          {   return *(--end());  }

    const_reference front() const   {   return *(begin());  }
    const_reference back()  const   {   return *(--end());  }

    size_type       size()      const   {   return _size;   }
    size_type       max_size()  const   {   return _size;   }
    bool            empty()     const   {   return !_size; }


private:
    node_pointer_t      _head_p, _tail_p;
    size_t              _size;
    node_allocator_t    _node_allocator;

};


/////////////////////////////////////////////////////////////////
// block_allocated_list
template < typename T >
using block_allocated_simple_list = simple_list< T, block_allocator< T, 10 >>;

