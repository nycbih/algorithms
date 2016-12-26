#include <iostream>
#include "hash.h"


///
/// hashing with chaining
///
int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    hft::hash<7,std::string,std::string> hash;

    const auto &status = hash.hash_perf_stats();

    std::string a("a");
    std::string b("b");
    std::string c("c");

    std::cout << hash.insert(a, b) << std::endl;

    std::cout << hash.find(a,b) << std::endl;

    std::cout << hash.find(a,c) << std::endl;

    std::cout << status.worst_search_len << std::endl;

    std::cout << "done...\n";

    return 0;
}
