#include <iostream>
#include <thread>
#include <atomic>
#include <deque>
#include <stack>
#include <queue>
#include <chrono>
#include <vector>
#include <condition_variable>


// LVM Chandler Carruth "High Performance Code 201: Hybrid Data Structures
// Small size optimization
//
template<typename T, size_t N>
class SmallVector
{
public:
    SmallVector()
    {

    }
private:
    T *begin = (T*) buffer;
    T *end = (T*) buffer;
    size_t capacity = N;
    char buffer[ sizeof(T) * N ];
};


template<typename T>
struct SetTraits
{

};

template<typename T, size_t N, typename Traits = SetTraits<T>>
class SmallSet
{
public:

private:
    T *buckets;
    size_t size=0, tombstones=0, bucketSize=N;
    char Buffer[sizeof(T) * N];

};


template<typename T, size_t size>
class SmallMap
{

};


#include <stdio.h>


//
// Variable Templates of C++14
//
template<typename T>
constexpr T PI = T(3.1415926535897932385);

template<typename T>
T area (T r)
{
    return PI<T> * r * r;
}


int main()
{
    std::cout << "starting main" << std::endl;

    SmallVector<int,100> sm;

    SmallSet<int,100> ss;


    printf("PI: %d, area: %d\n", PI<int>, area(2));
    printf("PI: %lf, area: %lf\n", PI<double>, area(2.0));

    std::cout << "ending main" << std::endl;
    return 0;
}
