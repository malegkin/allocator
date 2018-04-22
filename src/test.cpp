#include "stdafx.h"

#define BOOST_TEST_MODULE test_foo
#include <boost/test/unit_test.hpp>
#include "foo.h"
    
#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( test_suite_main )

    BOOST_AUTO_TEST_CASE( test_factorial_foo ) {
        BOOST_REQUIRE( factorial(0)  == 1 );
        BOOST_REQUIRE( factorial(1)  == 1 );
        BOOST_REQUIRE( factorial(2)  == 2 );
        BOOST_REQUIRE( factorial(3)  == 6 );
        BOOST_REQUIRE( factorial(4)  == 24 );
        BOOST_REQUIRE( factorial(5)  == 120 );
        BOOST_REQUIRE( factorial(20)  == 2432902008176640000 );

    }

    BOOST_AUTO_TEST_CASE( test_otus_map )
    {
        otus_map< uint8_t, uint64_t > om;
        om[0] = 10;
        BOOST_REQUIRE(om[0] = 10);
    }


BOOST_AUTO_TEST_SUITE_END()
