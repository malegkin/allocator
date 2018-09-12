###
#global

    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -rdynamic -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    add_definitions(-DBOOST_TEST_DYN_LINK)
###
#foo library
    add_library(loggable_memory_managment loggable_memory_managment.cpp )

###
#Unit tests
    add_executable(test_foo test.cpp)
    add_test(test_foo test_foo )
    set_tests_properties(test_foo PROPERTIES TIMEOUT 30 )
        target_link_libraries(  test_foo
                            ${Boost_LIBRARIES}
                            loggable_memory_managment
                        )

###
#Main
    add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp )
    target_link_libraries(  ${PROJECT_NAME} 
                            ${Boost_LIBRARIES}
                            loggable_memory_managment
                        )

    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

