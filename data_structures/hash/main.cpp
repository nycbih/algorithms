#include <iostream>
#include "hash.h"


///
/// hashing with chaining
///
int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    hft::hash<5,std::string,std::string> hash1;

    std::string a("a");
    std::string b("b");
    std::string c("c");

    std::cout << hash1.insert(a, b) << std::endl;

    std::cout << hash1.find(a,b) << std::endl;

//    std::cout << hash1.find(a,c) << std::endl;

    std::cout << "done...\n";

    return 0;
}
