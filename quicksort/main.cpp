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
#include <array>

void show(int array[], int r, int l)
{
    for(size_t i=r; i <= l; ++i)
    {
        std::cout << array[i];
    }

    std::cout << std::endl;
}
int pivot(int a[], int l, int r)
{
    int pi = l;
    int pv = a[l];

    std::cout << "pi=" << pi << " pv=" << pv << std::endl;

    for(int i = l+1 ; i <= r ; i++)
    {
        if(a[i] < pv)
        {
            pi++;
            std::swap(a[i], a[pi]);
        }
    }

    std::swap(a[pi], a[l]);

    show(a,0,7);

    return pi;
}
size_t quicksort(int a[], int l, int r)
{
    std::cout << "l=" << l << " r=" << r << std::endl;

    if( (r-l) > 0 )
    {
        int p = pivot(a, l, r);

        size_t c0 = r-l;
        size_t c1 = quicksort(a, l, p - 1);
        size_t c2 = quicksort(a, p + 1, r);

        return c0 + c1 + c2;
    }

   return 0;
}


///
/// main
///
int main(int argc, char *argv[])
{
    int a[] = {3,8,2,5,1,4,7,6};

    int SIZE = sizeof(a)/sizeof(int);

    show(a,0,SIZE-1);

    int count = quicksort(a,0,SIZE-1);


    //std::sort(array,array+SIZE, std::greater<int>());

    show(a,0,SIZE-1);

    std::cout << "done main" << "count=" << count <<  std::endl;
    return 0;
}
