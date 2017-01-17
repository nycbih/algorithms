#pragma once
#include <vector>


namespace qs
{
    int partition(int array[], int l, int r )
    {
        int p = r;

        int pos = l;

        for( int i=l; i < r; i++ )
        {
            if( array[i] < array[p] )
            {
                std::swap(array[i], array[pos]);
                pos++;
            }
        }


        std::swap(array[p], array[pos]);

        return pos;
    }

    void quicksort(int array[], int l, int r )
    {
        if( l < r )
        {
            int p = partition(array, l, r);
            quicksort(array, l, p-1);
            quicksort(array, p+1, r);
        }
    }
}