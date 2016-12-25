#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>

#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

///
/// template template parameters only supports class templates
///

template <typename Type>
class Foo
{
    Type m_member;
};

// Template template class
template <template <typename> class TType>
class Bar
{
    TType<int> m_ints;
};

template<size_t TSize, typename TData>
class RingBuffer
{
public:
    RingBuffer()
    {
        SHOW_SIGNATURE;
    }
    ~RingBuffer()
    {
        SHOW_SIGNATURE;
    }
    bool push(TData &val)
    {
        return true;
    }
    bool pop(TData &val)
    {
        return true;
    }
private:
    TData m_data[TSize];
};

template<size_t TSize, typename TData>
class QueueBuffer
{
public:
    QueueBuffer()
    {
        m_data.reserve(TSize);
        SHOW_SIGNATURE;
    }
    ~QueueBuffer()
    {
        SHOW_SIGNATURE;
    }
    bool push(TData &val)
    {
        SHOW_SIGNATURE;
        return true;
    }
    bool pop(TData &val)
    {
        SHOW_SIGNATURE;
        return true;
    }
private:
    std::vector<TData> m_data;
};

template<size_t TSize, typename TData, template <size_t,typename> class TQueue>
class Queue
{
public:
    Queue()
    {
       SHOW_SIGNATURE;
    }
    ~Queue()
    {
        SHOW_SIGNATURE;
    }
    bool push(TData &val)
    {
        SHOW_SIGNATURE;
        return m_queue.push(val);
    }
    bool pop(TData &val)
    {
        SHOW_SIGNATURE;
        return m_queue.pop(val);
    }
private:
    TQueue<TSize,TData>  m_queue;
};



int main()
{
    std::cout << "starting main" << std::endl;

    Foo<int> foo;

    Bar<Foo> bar;

    int val=99;

    Queue<1024,int,QueueBuffer> queue;
    queue.push(val);
    queue.pop(val);

    Queue<1024,int,RingBuffer> rb;
    rb.push(val);
    rb.pop(val);

    std::cout << "ending main" << std::endl;

    return 0;
}
