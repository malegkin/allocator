#include "stdafx.h"
#include "factorial.h"
#include "containers.h"


template <typename T>
struct is_map : std::false_type {} ;

//template <typename T>
//struct is_map<T, std::enable_if_t<
//                    std::is_same < typename  T::value_type, std::pair< const typename T::key_type, typename T::mapped_type
//template <typename Key, typename  Value>
//struct is_map<std::map<Key, Value>> : std::true_type {};

//template <typename T>
//struct is_pair : std::false_type {} ;

//template <typename T>
//struct is_map<T, std::enable_if_t<
//                    std::is_same < typename  T::value_type, std::pair< const typename T::key_type, typename T::mapped_type
//template <typename F, typename  L>
//struct is_pair<std::pair<F, L>> : std::true_type {};



template <  typename C
        , typename std::enable_if_t<std::is_base_of_v<std::pair, C::value_type>>
        >
std::ostream & print_container(const C & in, std::ostream & os = std::cout ){

    for(auto a: in){
        os << a.first << " = " << a.second << std::endl;
    }
};

/*
template < class input_it_t, class std::enable_if_t< is_pair<input_it_t::value_type>::value > >
std::ostream & print_container_content(input_it_t from, input_it_t to, std::ostream & os = std::cout){
    while (from != to){
        os << "[" << (*from).first << "] = " << (*from).second << std::endl;
        ++from;
    }
}

*/

template <class T>
       void test(T &t){
            std::cout << is_map(T)::value <<std::endl;
        }
int main() {

    try {
        dout << "\n\nmap with default allocator:\n";
        std::map<uint32_t, uint64_t> m;
        uint32_t mN = 10;
        std::generate_n(std::inserter(m, std::begin(m)), mN, [&](){
            mN--;
            return std::make_pair(mN, factorial(mN));
        });

        test(m);
  //      print_container(m);

        return -1;

        /*

        dout << "\n\nmap with block allocator:\n";
        block_allocated_map<uint32_t, uint64_t> bam;
        uint32_t bamN = 10;
        std::generate_n(std::inserter(bam, std::begin(bam)), bamN, [&](){
            bamN--;
            return std::make_pair(bamN, factorial(bamN));
        });

        for (uint32_t i = 0; i < 10; i++) {
            bam[i] = factorial(i);
        }
        */
        //print_container(bam);
        /*
        for (auto a: bam) {
            std::cout << a.first << " " << a.second << std::endl;
        }
        */

        dout << "\n\notus list:\n";
        simple_list<int> ol;
        for (int i = 0; i < 10; i++) {
            ol.push_back(i);
        }

        dout << "\n\nlist with block allocator:\n";
        block_allocated_simple_list<int> bl;
        for (int i = 0; i < 10; i++) {
            bl.push_back(i);
        }

        for (auto a: bl) {
            std::cout << a << std::endl;
        }

    }   catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;

    }   catch (...) {
        std::cerr << "Caught unknown exception." << std::endl;
        return -1;
    }

    return 0;
}
