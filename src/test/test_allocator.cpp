

#include "stdafx.h"
#include <random>
#include <algorithm>
#include "containers.h"


#define BOOST_TEST_MODULE test_allocator
#include <boost/test/unit_test.hpp>
#include <block_allocator.h>


BOOST_AUTO_TEST_SUITE( ts_allocator )



    BOOST_AUTO_TEST_CASE( simple_check_memory_leak ) {

        {
            block_allocator<uint64_t, 5> ba;
            std::array<uint64_t*, 100> bap;
            std::array<uint64_t, 100> is;

            std::generate_n(begin(bap), 100, [&]() { return ba.allocate(1); });
            uint64_t u = 0;
            std::generate_n(begin(is), 100, [&]() { return u++; });

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(begin(is), end(is), g);

            for(int i =0; i < 90; i++){
                ba.deallocate(bap[is[i]], 1);
            }

            BOOST_REQUIRE(ba._statistics.allocated_cells - ba._statistics.deallocated_cells == 10);
            BOOST_REQUIRE(ba._available_cells.size() == 90);
        }

        BOOST_REQUIRE(_block_statistics.total_allocated_blocks == _block_statistics.total_deallocated_blocks);

    }


BOOST_AUTO_TEST_SUITE_END()
