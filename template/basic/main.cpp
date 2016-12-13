#include <iostream>
#include <type_traits>


#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

///
/// class template
///
template <typename T>
struct Less
{
    bool operator()(T a, T b) const
    {
        SHOW_SIGNATURE;
        return a < b;
    }
};
template <typename T>
struct Less<T*>
{
    bool operator()(T* a, T* b) const
    {
        SHOW_SIGNATURE;
        return *a < *b;
    }
};
template <>
struct Less<char *>
{
    bool operator()(const char *a, const char *b) const
    {
        SHOW_SIGNATURE;
        return strcmp(a,b);
    }
};

void test_specialization()
{
    Less<int> less1;

    Less<int*> less2;

    Less<char*> less3;

    int a=1;
    int b=2;

    const char *pa = "one";
    const char *pb = "two";

    std::cout << less1( a,b ) << std::endl;

    std::cout << less2( &a, &b) << std::endl;

    std::cout << less3( pa, pb) << std::endl;
}
///
/// function template
///
template <typename T>
const auto max( const T &a, const T &b )
{
    SHOW_SIGNATURE;
    return a < b ? b : a;
}
template <typename T>
const T max( T *a, T *b )
{
    SHOW_SIGNATURE;
    return *a < *b ? *b : *a;
}
template <typename T>
const auto max( const T &a, const T &b, const T &c )
{
    SHOW_SIGNATURE;
    return a < b ? (b < c ? c : b) : (a < c ? c : a);
}
template <typename T>
const auto max( const T *a, const T &b, const T *c )
{
    SHOW_SIGNATURE;
    return a < b ? (b < c ? c : b) : (a < c ? c : a);
}
const auto max( const char * a, const char *b )
{
    SHOW_SIGNATURE;
    return strcmp(a,b) < 0 ? a : b;
}
///
/// test driver
///
void test_max()
{
    const int a=1, b=2;
    std::cout << "max 1,2=" << max(1,2) << std::endl;
    std::cout << "max 1,2=" << max<double>(3,2.2) << std::endl;
    std::cout << "max 1,2,3=" << max(1,2,3) << std::endl;
    std::cout << "max 3,2,1=" << max<double>(3,2,1) << std::endl;
    std::cout << "max 2,3,1=" << max<unsigned int>(2,3,1) << std::endl;
    std::cout << "max<> 1,2=" << max<>(1,2) << std::endl;
    std::cout << "max 1,2=" << max(&a,&b) << std::endl;
}


int main()
{
    std::cout << "starting main" << std::endl;

    test_specialization();
    test_max();
    std::cout << "ending main" << std::endl;

    return 0;
}
