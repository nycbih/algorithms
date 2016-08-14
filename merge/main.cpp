#include <iostream>
#include <thread>
#include <atomic>
#include <deque>
#include <stack>
#include <queue>
#include <chrono>
#include <vector>
#include <condition_variable>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

///
///
///
void show(const std::string &what, std::vector<int> &array)
{

    std::cout << what << ":";
    for( const auto x : array)
    {
        std::cout << x;
    }

    std::cout << std::endl;
}
///
///
///
void log(const char *msg, int a[], int low, int high)
{
    std::cout << msg <<  ": low=" << low << " high=" << high << " array=[";

   // for(int i=low; i <= high; i++)
   // {
   //     std::cout << a[i];
   // }

    std::cout << "]" << std::endl;
}
///
///
///
size_t merge(int a[], size_t low, size_t mid, size_t high)
{
    std::vector<int> ra;
    std::vector<int> la;

    for( size_t i=low; i <= mid; i++)
    {
        ra.push_back(a[i]);
    }

    for( size_t i=mid+1; i <= high; i++)
    {
        la.push_back(a[i]);
    }

 //   show("ra=", ra);
   // show("la=", la);

    int index=low;
    size_t inversions=0;

    size_t ls=0, rs=0;
    while( rs < ra.size() && ls < la.size() )
    {
        if( ra[rs] < la[ls])
        {
            a[index++] = ra[rs++];
        }
        else if( la[ls] < ra[rs])
        {
            inversions += ra.size() - rs;
            a[index++] = la[ls++];
        }
    }

    while( rs < ra.size())
    {
        a[index++] = ra[rs++];
    }

    while( ls < la.size())
    {
        a[index++] = la[ls++];
    }


    return inversions;
}
///
/// merge sort driver
///
int mergesort(int a[], size_t low, size_t high)
{
//    log("ms", a,low,high);

    if( low < high) {
        size_t mid = (low + high) / 2;
        size_t x = mergesort(a, low, mid);
        size_t y = mergesort(a, mid + 1, high);
        size_t z = merge(a, low, mid, high);
        return x + y + z;
    }

    return 0;
}
///
/// main
///
int main(int argc, char *argv[])
{
    std::cout << "starting main size of int=" << sizeof(int) << std::endl;

    int test[] = {1,2,5,6,4};
    int SIZE = sizeof(test)/sizeof(int);

    int MAX_SIZE=1000001;
    int *array = new int [MAX_SIZE];
    for(int i=0; i < SIZE; i++)
    {
        array[i] = test[i];
    }


    if( argc > 1)
    {
        std::string file = argv[1];
        std::string line;
        std::ifstream myfile (file.c_str());
        if (myfile.is_open())
        {
            size_t index=0;
            while (! myfile.eof()  )
            {
                if( getline(myfile, line) )
                {
                    size_t val = atoi(line.c_str());
                    array[index++] = val;
                   std::cout << "index=" << index << " value=" << val << std::endl;
                }
            }

            SIZE=index;

            std::cout << "index=" << index << std::endl;

            myfile.close();
        }
    }

    log("start", array,0,SIZE-1);

//    std::sort(array,array+SIZE);

    size_t inversions = mergesort(array,0,SIZE-1);

    std::cout << "inversions=" << inversions << std::endl;

    log("end", array,0,SIZE-1);

    std::cout << "done main" << std::endl;
    return 0;
}
