#include <iostream>
#include "heapsort.h"

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
        std::cout << "i=" << i << " v=" << array[i] << std::endl;

    }

    pq::PriorityQueue<16,pq::Max> pq;
    pq.make_heap(array,sz);

    pq.show("before");

    std::cout << "sorted" << std::endl;
    int size = pq.size();
    for( int i=1; i <= size; i++ )
    {
        std::cout << "remove top: i=" << i << " val=" << pq.remove_top() << std::endl;
    }


    std::cout << "done...\n";

    return 0;
}
