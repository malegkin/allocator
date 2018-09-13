#include "stdafx.h"
#include "containers.h"

#define BOOST_TEST_MODULE test_factorial
#include <boost/test/unit_test.hpp>


#define LOG_LEVEL all

BOOST_AUTO_TEST_SUITE( ts_simple_list )


    BOOST_AUTO_TEST_CASE( ts_simple_list_check_in_out_operation ) {
        simple_list<uint64_t> sl;
        sl.push_back(10);
        
    }
BOOST_AUTO_TEST_SUITE_END()

