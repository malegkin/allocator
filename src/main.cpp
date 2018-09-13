#include "stdafx.h"
#include "factorial.h"
#include "containers.h"

int main() {

    dout << "\n\nmap with default allocator:\n";
    std::map<uint8_t, uint64_t> m;
    for (uint8_t i = 0; i < 10; i++) {
        m[i] = factorial(i);
    }

    dout << "\n\nmap with block allocator:\n";
    block_allocated_map< uint32_t, uint64_t > bam;

    for (uint32_t i = 0; i < 10; i++) {
        bam[i] = factorial(i);
    }

    for (auto a: bam){
        std::cout << a.first << " " << a.second << std::endl;
    }



    dout << "\n\notus list:\n";
    simple_list< int > ol;
    for (int i = 0; i < 10; i++) {
        ol.push_back( i );
    }


    dout << "\n\nlist with block allocator:\n";
    block_allocated_simple_list< int > bl;
    for (int i = 0; i < 10; i++) {
        bl.push_back( i );
    }

    for(auto a: bl) {
        std::cout << a << std::endl;
    }


    return 0;
}
