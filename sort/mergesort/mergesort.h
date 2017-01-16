#pragma once
#include <vector>


namespace hft
{
    void show( const char *msg, int array[], int sz)
    {
        std::cout << msg;

        for(int i=0; i < sz; i++)
        {
            std::cout << array[i] << ":";
        }

        std::cout << std::endl;
    }

    void merge(int array[], int l, int m, int r)
    {
        std::cout << "merge l=" << l << " m=" << m << " r=" << r << std::endl;

        int sz1 = m - l + 1;
        int sz2 = r - m;

        std::cout << "size sz1=" << sz1 << " sz2=" << sz2 << std::endl;

        // copy to local
        int a1[sz1];
        int a2[sz2];

        for( int i=0; i < sz1; i++ )
        {
            a1[i] = array[l+i];
        }

        for( int j=0; j < sz2; j++ )
        {
            a2[j] = array[m+1+j];
        }

        hft::show("a1=", a1, sz1);
        hft::show("a2=", a2, sz2);

        int i=0, j=0, k=l;

        while( i < sz1 && j < sz2 )
        {
            if( a1[i] <= a2[j] )
            {
                array[k] = a1[i++];
            }
            else
            {
                array[k] = a2[j++];
            }

            k++;
        }

        while( i < sz1 )
        {
            array[k++] = a1[i++];
        }

        while( j < sz2 )
        {
            array[k++] = a2[j++];
        }
    }

    void mergesort(int array[], int l, int r)
    {

        if( r > l )
        {
            int m = (r + l) / 2;

            std::cout << "mergesort l=" << l << " mid=" << m << " r=" << r << std::endl;

            mergesort(array, l, m );
            mergesort(array, m+1, r);
            merge(array, l, m, r);
        }
    }

}