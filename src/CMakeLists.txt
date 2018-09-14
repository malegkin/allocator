###
#global settings
    include_directories("${CMAKE_SOURCE_DIR}/include")
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    add_definitions(-DBOOST_TEST_DYN_LINK)

###
#library's
    add_library(loggable_memory_managment loggable_memory_managment.cpp )


###
#Tests
function(generate_tests test_name list_t)

    set(LIST_FOR_TEST "${list_t}")
    set(TEST_NAME "${test_name}")

    configure_file(
            ${CMAKE_SOURCE_DIR}/src/test/test_list.cpt
            ${CMAKE_SOURCE_DIR}/src/test/test_${test_name}.cpp
            @ONLY
    )
endfunction()

    function(add_new_test test_name)
    add_executable(${test_name} "${CMAKE_SOURCE_DIR}/src/test/${test_name}.cpp")
    add_test(${test_name} ${test_name} )
    set_tests_properties(${test_name} PROPERTIES TIMEOUT 30 )
    target_link_libraries(  ${test_name}
            ${Boost_LIBRARIES}
            loggable_memory_managment
            )
endfunction()


generate_tests(list "std::list<uint64_t>")
generate_tests(simple_list "simple_list<uint64_t>")
generate_tests(block_allocated_simple_list "block_allocated_simple_list<uint64_t>")
add_new_test(test_factorial)
add_new_test(test_allocator)
add_new_test(test_list)
add_new_test(test_simple_list)
add_new_test(test_block_allocated_simple_list)

###
#Main
    add_executable(${PROJECT_NAME} main.cpp )
    target_link_libraries(  ${PROJECT_NAME} 
                            ${Boost_LIBRARIES}
                            loggable_memory_managment
                        )

    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

