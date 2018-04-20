#include "stdafx.h"
#include "foo.h"
#include <map>

template < typename Key, typename T >
using otus_map = map< Key, T, less<Key>, block_allocator< pair< const Key, T >, 10 >>;

template < typename F, typename S >
string to_string( pair<F, S> in){
    return to_string(in.first) + " : " + to_string(in.second);
}


int main()
{    

    map< uint32_t, uint32_t, less<uint32_t>, block_allocator< pair< const uint32_t, uint32_t >, 10 >> oom;
    oom[5] = 10;


    otus_map< uint8_t, uint64_t > om;

    om[0] = 1;
    uint64_t f = 1;
    for (int i = 1; i < 21; i++){
        cout << i << endl;
        om[i] = om[i-1]*i ;
    }  

    for (auto a: om){
        cout << to_string(a) << endl;
    }

    otus_list< int > ol;

    for (int i = 1; i < 10; i++) {
        ol.push_back( i );
    }

    for(auto a: ol) {
        cout << a << endl;
    }


    return 0;
}
