#include <iostream>
#include <vector>
#include <string>

///
/// Various tmp sample programs
///


#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;


namespace my
{

template<unsigned long N>
struct Binary
{
    static unsigned const value = Binary<N/10>::value << 1 | N%10;
};

template<>
struct Binary<0>
{
    static unsigned const value = 0;
};

constexpr unsigned Binary2(unsigned long N)
{
    unsigned result = 0;
    for( unsigned bit = 0x1; N; N /= 10,  bit <<=1 )
    {
        if( N%10)
        {
            result += bit;
        }
    }

    return result;
}

}

int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    std::cout << my::Binary<1>::value << std::endl;
    std::cout << my::Binary<11>::value << std::endl;
    std::cout << my::Binary<111>::value << std::endl;
    std::cout << my::Binary<1111>::value << std::endl;

    std::cout << my::Binary2(1)    << std::endl;
    std::cout << my::Binary2(11)   << std::endl;
    std::cout << my::Binary2(111)  << std::endl;
    std::cout << my::Binary2(1111) << std::endl;

    std::cout << "done...\n";

    return 1;
}
