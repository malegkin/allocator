#include "stdafx.h"
#include "factorial.h"
#include "block_allocator.h"

#define BOOST_TEST_MODULE test_factorial
#include <boost/test/unit_test.hpp>

    
#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( ts_factorial )

    BOOST_AUTO_TEST_CASE( ts_factorial_check_correct_results ) {

        BOOST_REQUIRE( factorial(0)  == 1 );
        for (int i = 1; i < 23; i ++){
            BOOST_REQUIRE( factorial(i)  == i * factorial(i-1) );
        }
        BOOST_REQUIRE( factorial(23) == 0);

    }
BOOST_AUTO_TEST_SUITE_END()
