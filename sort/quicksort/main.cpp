#include <iostream>
#include "quicksort.h"

///
/// heapsort, min/max heap
///
int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    int array[]={5,3,2,1,4};

    int sz = sizeof(array)/sizeof(int);

    for(int i=0; i < sz; i++ )
    {
        std::cout << "before i=" << i << " v=" << array[i] << std::endl;
    }

    qs::quicksort(array, 0, sz-1);

    for(int i=0; i < sz; i++ )
    {
        std::cout << "after i=" << i << " v=" << array[i] << std::endl;
    }

    std::cout << "done...\n";

    return 0;
}
