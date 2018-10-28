#pragma once

#include "stdafx.h"
#include "containers.h"
#include <type_traits>


template <typename T, typename _ = void >
struct is_map : std::false_type {};

template <typename T>
struct is_map< T, std::enable_if_t <
        std::is_same_v < typename  T::value_type, std::pair < const typename T::key_type, typename T::mapped_type >>>
        > : std::true_type {};

template <typename T>
constexpr bool is_map_v = is_map<T>::value;


static_assert(is_map_v<int>     == false);
static_assert(is_map_v<float>   == false);
static_assert(is_map_v<std::vector<int>>    == false);
static_assert(is_map_v<std::list<int>>      == false);
static_assert(is_map_v<simple_list<int>>    == false);
static_assert(is_map_v<block_allocated_simple_list<int>>    == false);
static_assert(is_map_v<std::map<int, int>>  == true);
static_assert(is_map_v<block_allocated_map<int, int>>  == true);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
        T,
        std::conditional_t<
                false,
                is_container_helper<
                        typename T::value_type,
                        typename T::size_type,
                        typename T::allocator_type,
                        typename T::iterator,
                        typename T::const_iterator,
                        decltype(std::declval<T>().size()),
                        decltype(std::declval<T>().begin()),
                        decltype(std::declval<T>().end()),
                        decltype(std::declval<T>().cbegin()),
                        decltype(std::declval<T>().cend())
                >,
                void
        >
> : public std::true_type {};

template <typename T>
constexpr bool is_container_v = is_container<T>::value;


static_assert(is_container_v<int>     == false);
static_assert(is_container_v<float>   == false);
static_assert(is_container_v<std::vector<int>>    == true);
static_assert(is_container_v<std::list<int>>      == true);
static_assert(is_container_v<simple_list<int>>    == true);
static_assert(is_container_v<block_allocated_simple_list<int>> == true);
static_assert(is_container_v<std::map<int, int>>  == true);
static_assert(is_container_v<block_allocated_map<int, int>>  == true);

