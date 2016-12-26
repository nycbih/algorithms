#include <iostream>
#include <random>
#include <vector>
#include "hash.h"

#define CATCH_CONFIG_MAIN
#include <ut/catch.hpp>

///
/// hashing with chaining
///
TEST_CASE( "test with size_t", "[hash]" )
{
    const size_t SIZE=1024;

    hft::hash<SIZE,size_t,size_t> hash;
    const auto &status = hash.hash_perf_stats();

    using TVector = std::vector<std::pair<size_t, size_t>>;
    TVector list;

    const size_t MAX_ITEMS=1024;

    for(size_t i=0; i < MAX_ITEMS; ++i)
    {
        size_t key = rand() % MAX_ITEMS*10;
        list.push_back(std::make_pair(key,i));
    }

    for(size_t i=0; i < SIZE; i++)
    {
        REQUIRE(hash.insert(list[i].first, i) == true);
    }

    std::cout << "insert worst case=" << status.worst_search_len << std::endl;

    for(size_t i=0; i < SIZE; i++)
    {
        REQUIRE(hash.find(list[i].first, i) == true);
    }

    std::cout << "find worst case=" << status.worst_search_len << std::endl;

    for(size_t i=0; i < SIZE; i++)
    {
        REQUIRE(hash.remove(list[i].first, i) == true);
    }

    std::cout << "remove worse case=" << status.worst_search_len << std::endl;

    REQUIRE(hash.find(-1, -1) == false);

    std::cout << "cannot find worse case=" << status.worst_search_len << std::endl;
}









