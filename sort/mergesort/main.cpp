#include <iostream>
#include "mergesort.h"


///
/// mergesort
///
int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    int array[]={38,27,43,3,9,82,10};

    int sz = sizeof(array)/sizeof(int);

    std::cout << "sz=" << sz << std::endl;

    hft::show("before ", array, sz);
    hft::mergesort(array, 0, sz-1);
    hft::show("after ", array, sz);

    std::cout << "done...\n";

    return 0;
}
