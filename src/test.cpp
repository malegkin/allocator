#include "../include/stdafx.h"
#include "../include/foo.h"
#include "../include/block_allocator.h"

#define BOOST_TEST_MODULE test_allocator
#include <boost/test/unit_test.hpp>

    
#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( test_suite_foo )

    BOOST_AUTO_TEST_CASE( test_factorial_foo ) {
        BOOST_REQUIRE( factorial(0)  == 1 );
        BOOST_REQUIRE( factorial(1)  == 1 );
        BOOST_REQUIRE( factorial(2)  == 2 );
        BOOST_REQUIRE( factorial(3)  == 6 );
        BOOST_REQUIRE( factorial(4)  == 24 );
        BOOST_REQUIRE( factorial(5)  == 120 );
        BOOST_REQUIRE( factorial(20)  == 2432902008176640000 );
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( test_suite_main )

    BOOST_AUTO_TEST_CASE( test_otus_list )
    {
        otus_list< uint32_t > ol;

        for (uint32_t i = 1; i <= 1000; i++) {
            ol.push_back( i );
        }

        uint32_t acc = accumulate(ol.begin(), ol.end(), uint32_t(0), [](uint32_t sum, uint32_t a){ return sum + static_cast<uint32_t>(a);} );

        BOOST_REQUIRE(acc == (1 + 1000)*500 );
    }

    BOOST_AUTO_TEST_CASE( test_block_allocated_list )
    {
        block_allocated_list < uint32_t > ol;

        for (uint32_t i = 1; i <= 1000; i++) {
            ol.push_back( i );
        }

        uint32_t acc = accumulate(ol.begin(), ol.end(), uint32_t(0), [](uint32_t sum, uint32_t a){ return sum + static_cast<uint32_t>(a);} );

        BOOST_REQUIRE(acc == (1 + 1000)*500 );
    }


    BOOST_AUTO_TEST_CASE( test_block_allocated_map )
    {
        block_allocated_map< uint32_t, uint32_t > om;

        for (uint32_t i = 1; i <= 1000; i++) {
            om[i] = i;
        }

        for(auto a: om){
            BOOST_REQUIRE(a.first == a.second );
        }
    }

BOOST_AUTO_TEST_SUITE_END()
