#include "stdafx.h"
#include "factorial.h"
#include "containers.h"
#include "traits.h"


template < typename  T>
T & stuff_n(T & in, size_t n = 10){
    size_t N = n;

    std::generate_n( std::inserter(in, std::begin(in)), n, [&](){
        n--;
        if constexpr (is_map_v<T>) {
            return std::make_pair(n, factorial(n));
        } else if constexpr (is_container_v<T>){
            return N - n - 1;
        } else {
            throw new std::bad_function_call;
        }
    });

    return in;
};


template < typename  T>
void dump(const T & in, std::ostream & os = std::cout ){
    for(auto a: in){
        if constexpr (is_map_v<T>){
            os << a.first << " " << a.second << std::endl;
        } else if constexpr (is_container_v<T>){
            os << a << std::endl;
        } else {
            throw new std::bad_function_call;
        }
    }
};



int main() {

    try {
        dout << "\n\nmap with default allocator:\n";
        //* создание экземпляра std::map
        std::map< uint32_t, uint64_t > m;
        //* заполнение 10 элементами, где ключ это число от 0 до 9, а значение - факториал ключа
        stuff_n(m);

        dout << "\n\nmap with block allocator:\n";
        //* создание экземпляра std::map с новым аллокатором ограниченным 10 элементами
        block_allocated_map<uint32_t, uint64_t> bam;
        //* заполнение 10 элементами, где ключ это число от 0 до 9, а значение - факториал ключа
        stuff_n(bam);
        //* вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
        dump(bam);

        dout << "\n\notus list:\n";
        //* создание экземпляра своего контейнера для хранения int
        simple_list<int> sl;
        //* заполнение 10 элементами от 0 до 9
        stuff_n(sl);

        dout << "\n\nlist with block allocator:\n";
        //* создание экземпляра своего контейнера для хранения int с новым аллокатором ограниченным 10 элементами
        block_allocated_simple_list<int> basl;
        //* заполнение 10 элементами от 0 до 9
        stuff_n(basl);
        //* вывод на экран всех значений хранящихся в контейнере
        dump(basl);

    }   catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;

    }   catch (...) {
        std::cerr << "Caught unknown exception." << std::endl;
        return -1;
    }

    return 0;
}
