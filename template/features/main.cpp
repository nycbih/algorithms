#include <iostream>
#include <vector>
#include <string>

void test_align()
{
    struct a
    {
        char x;
        int y;
        char z;
        double a;
    };

    struct b
    {
        double a;
        int y;
        char x;
        char z;
    };

    alignas(128) char cacheline[16];

    struct c
    {

    };


    std::cout << "alignof=" << alignof(a) << " sizeof=" << sizeof(a) << std::endl;

    std::cout << "alignof=" << alignof(b) << " sizeof=" << sizeof(b) << std::endl;

    std::cout << "max_align=" << alignof(std::max_align_t) << std::endl;

    std::cout << "alignas=" << alignof(cacheline) << " sizeof=" << sizeof(cacheline) << std::endl;

    std::cout << "c=" << alignof(c) << " sizeof=" << sizeof(c) << std::endl;
}



void test_static_assert()
{
    static_assert(sizeof(int) == 4, "incorrect!!!");
}



template<class T>
using Vec = std::vector<T>;


[[deprecated]]
void test_using()
{
    Vec<int> foo;
}


int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    test_align();


    std::cout << "ending...\n";

    return 1;
}
