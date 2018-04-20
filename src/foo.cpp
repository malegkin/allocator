#include "stdafx.h"
#include "foo.h"
/*
template < typename T, size_t item_per_block>
    T* block_allocator<T, item_per_block>::allocate( size_t n ){
        if (n > 1)
            throw new bad_alloc();

        item_allocated_count++;


        size_t block_id = item_allocated_count / item_per_block;
        size_t item_id  = item_allocated_count % item_per_block;

        if ( block_id >= blocks.size() )
            blocks.push_back( block() );


        return blocks[block_id][item_id];
    }
*/
