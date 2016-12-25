#include <iostream>
#include <vector>
#include <string>

///
/// Various tmp sample programs
///


#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;


namespace my
{
///////////////////////////////////////////////////////////////////////////////
///
/// Binary
///
///////////////////////////////////////////////////////////////////////////////

    template<unsigned long N>
    struct Binary
    {
        static unsigned const value = Binary<N / 10>::value << 1 | N % 10;
    };

    template<>
    struct Binary<0>
    {
        static unsigned const value = 0;
    };

    constexpr unsigned Binary2(unsigned long N)
    {
        unsigned result = 0;
        for (unsigned bit = 0x1; N; N /= 10, bit <<= 1)
        {
            if (N % 10)
            {
                result += bit;
            }
        }

        return result;
    }

///////////////////////////////////////////////////////////////////////////////
///
/// greatest common denominator
///
///////////////////////////////////////////////////////////////////////////////
    template<typename T>
    constexpr T abs1(T val)
    {
        return val >= 0 ? val : -val;
    }

    template<int N>
    struct abs2
    {
        static constexpr int value = N >= 0 ? N : -N;
    };

    constexpr unsigned int gcd1(unsigned int M, unsigned int N)
    {
        if (M % N == 0) return N;

        return gcd1(N, M % N);
    }


    template<unsigned M, unsigned N>
    struct gcd2
    {
        static unsigned constexpr value = gcd2<N, M % N>::value;
    };

    template<unsigned M>
    struct gcd2<M, 0>
    {
        static unsigned constexpr value = M;
    };
///////////////////////////////////////////////////////////////////////////////
///
/// factorial
///
///////////////////////////////////////////////////////////////////////////////
    template<int N>
    constexpr int fac()
    {
        return N * fac<N - 1>();
    }

    template<>
    constexpr int fac<1>()
    {
        return 1;
    }

    constexpr int fac(int n)
    {
        if( n <= 1 ) return 1;

        return n * fac(n - 1);
    }

//////////////////////////////////////////////////////////////////////////////
///
/// power
///
///////////////////////////////////////////////////////////////////////////////

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

    static_assert(my::abs1(45) == 45, "error");

    static_assert(my::abs2<45>::value == 45, "error");

    std::cout << my::gcd1(105,10) << std::endl;

    std::cout << my::gcd2<105,10>::value << std::endl;

    constexpr int N=10;
    int v1 = my::fac(N);

    int v2 = my::fac<N>();

    std::cout << "v1=" << v1 << std::endl;

    std::cout << "v2=" << v2 << std::endl;

    std::cout << "done...\n";

    return 1;
}
