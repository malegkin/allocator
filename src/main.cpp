#include "stdafx.h"
#include "foo.h"
#include <map>


int main()
{
    map< uint8_t, uint64_t > m;
    for (uint8_t i = 0; i < 9; i++){
        m[i] = factorial(i);
    }



    block_allocated_map< uint32_t, uint64_t > om;
    for (uint32_t i = 0; i < 10; i++){
        om[i] = factorial(i);
    }
    for (auto a: om){
        cout << a.first << " " << a.second << endl;
    }


    otus_list< int > ol;
    for (int i = 0; i < 10; i++) {
        ol.push_back( i );
    }


    block_allocated_list< int > bl;
    for (int i = 0; i < 10; i++) {
        bl.push_back( i );
    }
    for(auto a: bl) {
        cout << a << endl;
    }


    return 0;
}
