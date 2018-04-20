#include "stdafx.h"

#define BOOST_TEST_MODULE test_foo
#include <boost/test/unit_test.hpp>
#include "foo.h"
    
#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( test_suite_main )

BOOST_AUTO_TEST_CASE( test_block_allocator )
{
    map< uint32_t, uint32_t, less<uint32_t>, block_allocator< pair< const uint32_t, uint32_t >, 10 >> om;
    om[5] = 10;
    //for (uint32_t i = 0; i < 100; i++){
    //    om[i] = i ;
   // }
//
//    for ( const auto &pair : om ) {
//        BOOST_REQUIRE( pair.first  == pair.second);        
//    }
}


BOOST_AUTO_TEST_SUITE_END()
