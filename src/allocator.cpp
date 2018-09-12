#include "../include/stdafx.h"
#include "../include/factorial.h"
#include "../include/block_allocator.h"

#include <map>



int main()
{
    printf("\n\nmap with default allocator:\n");
/*
    map< uint8_t, uint64_t > m;
    for (uint8_t i = 0; i < 19; i++){
        m[i] = factorial(i);
    }
*/

    printf("\n\nmap with block allocator:\n");
    block_allocator<pair< uint32_t, uint64_t >, 10 > ba;

    std::cout << ba.allocate(1) << std::endl;

    block_allocated_map< uint32_t, uint64_t > om;
    /*


    for (uint32_t i = 0; i < 22; i++){
        om[i] = factorial(i);
    }

    std::cout << "end" << std::endl;


    for (auto a: om){
        std::cout << a.first << " " << a.second << std::endl;
    }
*/
    /*

    std::cout << "otus list:\n";
    otus_list< int > ol;
    for (int i = 0; i < 10; i++) {
        ol.push_back( i );
    }

    std::cout << "list with block allocator:\n";
    block_allocated_list< int > bl;
    for (int i = 0; i < 10; i++) {
        bl.push_back( i );
    }
    for(auto a: bl) {
        cout << a << endl;
    }
    */

    return 0;
}
