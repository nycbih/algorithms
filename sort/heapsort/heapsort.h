#pragma once
#include <vector>


namespace pq
{
    enum Type{Min, Max};
    template <int TMax, Type TType >
    class PriorityQueue
    {
    public:
        PriorityQueue()
        {

        }
        bool make_heap(int array[], int sz)
        {
            if( sz >= TMax )
            {
                std::cout << "TMax=" << TMax << " sz=" << sz << std::endl;
                return false;
            }

            for(int i=0; i < sz; i++)
            {
                insert(array[i]);
            }

            return true;
        }

        int top() const
        {
            return m_array[1];
        }
        int remove_top()
        {
            if( m_count == 0 )
            {
                return -1;
            }

            int top = m_array[1];

            m_array[1] = m_array[m_count];
            m_count -= 1;

            if( m_type == Min )
            {
                min_heapify( 1 );
            }
            else
            {
                max_heapify( 1 );
            }

            return top;
        }
        void sort()
        {


        }

        int size() const
        {
            return m_count;
        }

        const int *array() const
        {
            return m_array;
        }

        void show(const char *msg)
        {
            std::cout << msg << std::endl;
            for (int i = 1; i <= m_count; i++)
            {
                std::cout << "i=" << i << " v=" << m_array[i] << std::endl;
            }
        }
    private:
        enum Type m_type = TType;
        int m_count = 0;
        int m_array[TMax] = {0};

        void insert( int val )
        {
            m_count += 1;
            m_array[m_count] = val;

            if( m_type == Min )
            {
                min_heap( m_count);
            }
            else
            {
                max_heap( m_count);
            }
        }

        void min_heap(int pos)
        {
            int parent = pos/2;
            if( parent )
            {
                if( m_array[parent] > m_array[pos] )
                {
                    std::swap(m_array[parent],m_array[pos]);
                    min_heap(parent);
                }
            }
        }

        void max_heap(int pos)
        {
            int parent = pos/2;
            if( parent )
            {
                if( m_array[parent] < m_array[pos] )
                {
                    std::swap(m_array[parent],m_array[pos]);
                    max_heap(parent);
                }
            }
        }

        void min_heapify(int root)
        {
            int lh = 2*root;
            int rh = 2*root + 1;

            int smallest = root;

            if( lh < m_count && m_array[lh] < m_array[smallest])
            {
                smallest = lh;
            }

            if( rh < m_count && m_array[rh] < m_array[smallest] )
            {
                smallest = rh;
            }

            if( smallest != root )
            {
                std::swap(m_array[root], m_array[smallest]);
                min_heapify(smallest);
            }
        }

        void max_heapify(int pos)
        {
            int root = pos;
            int lh = 2*pos;
            int rh = 2*pos + 1;

            int largest = pos;

            if( lh < m_count && m_array[lh] > m_array[largest])
            {
                largest = lh;
            }

            if( rh < m_count && m_array[rh] > m_array[largest] )
            {
                largest = rh;
            }

            if( largest != pos )
            {
                std::swap(m_array[pos], m_array[largest]);
                min_heapify(largest);
            }
        }
    };
}