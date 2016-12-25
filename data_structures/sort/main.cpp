#include <stdio.h>
#include <vector>
#include <iostream>


typedef std::vector<int> TVector;
void show(const TVector &vec)
{
    std::cout << "size=" << vec.size() << std::endl;
    for(const auto &i :  vec )
    {
        std::cout << i << std::endl;
    }
}


class SelectionSort
{
public:
    SelectionSort(TVector &vec)
        :m_vec(vec)
    {

    }
    bool sort(TVector &vec)
    {
        for( int i=0; i < m_vec.size(); i++)
        {
            int minPos = i;
            int j=i+1;
            for( ; j < m_vec.size(); j++ )
            {
                if( m_vec[j] < m_vec[i] )
                {
                    minPos = j;
                }
            }

            char c = m_vec[i];
            m_vec[i] = m_vec[minPos];
            m_vec[minPos] = c;
        }

        return true;
    }

private:
    TVector &m_vec;
};

class InsertionSort
{
public:
    InsertionSort(TVector &vec)
        :m_vec(vec)
    {

    }
    void sort(TVector &vec)
    {
        std::cout << "size=" << m_vec.size() << std::endl;
        for(auto i :  m_vec )
        {
            std::cout << i << std::endl;
        }
    }
private:
    TVector &m_vec;
};

int main(int argc, char *argv[])
{
    TVector array= {1,2,3,5,7,4};
    SelectionSort test(array);
    show(array);
    test.sort(array);
    show(array);

    InsertionSort test2(array);
    show(array);
    test.sort(array);
    show(array);

    return true;

}



