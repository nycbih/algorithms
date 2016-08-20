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

using TArray = std::vector<int>;


void show(const TArray &array)
{
    for(const int &val : array)
    {
        std::cout << val << '|' ;
    }

    std::cout << std::endl;
}

int pivot(TArray &a, int l, int r)
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

    return pi;
}
size_t quicksort(TArray &a, int l, int r)
{
    int sz = (r-l) + 1;
    std::cout << "l=" << l << " r=" << r << " sz=" << sz << std::endl;

    if( sz > 1 )
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
    if( argc <= 1 )
    {
        std::cout << "please enter file to sort" << std::endl;
        return 0;
    }

    const std::string file(argv[1]);

    std::cout << "processing file=" << file << std::endl;
    std::string line;
    std::ifstream in(file.c_str());
    if( !in.is_open() )
    {
        std::cout << "failed to open file=" << file << std::endl;
        return 0;
    }

    TArray v;
    while( !in.eof() )
    {
        if( getline(in, line) )
        {
            size_t val = atoi(line.c_str());
            v.push_back(val);
        }
    }

    std::cout << "starting with count=" << v.size() << std::endl;
    show(v);

    int count = quicksort(v,0,v.size()-1);

    std::cout << "count=" << count << std::endl;

    show(v);

    return 0;
}
