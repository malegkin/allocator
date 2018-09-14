

#include "stdafx.h"
#include "containers.h"

#define BOOST_TEST_MODULE test_list
#include <boost/test/unit_test.hpp>

struct global_fixture {
    global_fixture()
    {
        for(int i = 0; i < 22; i++){
            sl64.push_back(i);
        }
    }

    std::list<uint64_t> sl64;

};

BOOST_FIXTURE_TEST_SUITE(test_simple_list, global_fixture );

    BOOST_AUTO_TEST_CASE( is_empty_list_begin_and_end_iterators_equal ) {
        std::list<uint64_t>  empty_list;
        BOOST_REQUIRE( empty_list.begin() == empty_list.end() );
    }

    BOOST_AUTO_TEST_CASE( check_push_back ) {
        std::list<uint64_t>  empty_list;
        uint64_t in = 555;
        empty_list.push_back( in );
        empty_list.push_back( std::move(in) );

        BOOST_REQUIRE( empty_list.back() == 555 );
    }

    BOOST_AUTO_TEST_CASE( is_begin_iterator_point_to_first_element )    {
        BOOST_REQUIRE( *(sl64.begin()) == 0  );
    }

    BOOST_AUTO_TEST_CASE( is_end_iterator_point_to_next_after_last_element )    {
        BOOST_REQUIRE( *(--sl64.end()) == 21  );
    }

    BOOST_AUTO_TEST_CASE( is_list_size_correct )    {
        BOOST_REQUIRE( (sl64.size()) == 22  );
    }

    BOOST_AUTO_TEST_CASE( is_iterator_return_reference )    {
        *(sl64.begin()) = 123;
        *(--sl64.end()) = 321;

        BOOST_REQUIRE( *(sl64.begin()) == 123  );
        BOOST_REQUIRE( *(--sl64.end()) == 321  );
    }

    BOOST_AUTO_TEST_CASE( check_front_back )    {
        const uint64_t cf = sl64.front();
        const uint64_t cb = sl64.back();

        sl64.front() = 123;
        sl64.back()  = 321;

        BOOST_REQUIRE( cf == 0 );
        BOOST_REQUIRE( cb == 21 );
        BOOST_REQUIRE( sl64.front() == 123 );
        BOOST_REQUIRE( sl64.back()  == 321 );
    }


BOOST_AUTO_TEST_SUITE_END()
