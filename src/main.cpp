#include "stdafx.h"
#include "foo.h"
#include <map>



template < typename F, typename S >
string to_string( pair<F, S> in){
    return to_string(in.first) + " : " + to_string(in.second);
}


int main()
{    
    otus_map< uint8_t, uint64_t > om;

    for (int i = 0; i < 21; i++){
        om[i] = factorial(i);
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
