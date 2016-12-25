#include <iostream>
#include <thread>
#include <atomic>
#include <deque>
#include <stack>
#include <queue>
#include <chrono>
#include <vector>
#include <condition_variable>

template<typename TType, size_t TSize>
class Queue
{
public:
    Queue()
    :m_head(0)
    ,m_tail(0)
    {

    }

    bool push( TType &val )
   {
       if( is_full() ) return false;

       size_t index = next(m_tail);

       m_array[index] = val;

       m_tail = index;

       return true;
   }

   bool pop( TType &val )
   {
       if( is_empty() )
       {
           return false;
       }

       val = m_array[m_head];

       m_head = next(m_head);

       return true;
   }

  bool is_full() const
  {
      int next_tail = next(m_tail);

      if( next_tail == m_head )
      {
          return true;
      }

      return false;
  }

  bool is_empty() const
  {
      if( m_head == m_tail )
      {
          return true;
      }

      return false;
  }

  int size() const
  {
    return TSize;
  }

private:
  std::atomic<size_t> m_head;
  std::atomic<size_t> m_tail;

  int m_array[TSize];

  int next(int idx) const
  {
    return (idx + 1) % TSize;
  }

};



int main()
{
    std::cout << "starting main" << std::endl;

    Queue<int,1024> queue;

    int val=1;
    queue.push(val);

    if( queue.pop(val))
    {
        std::cout << "val=" << val << std::endl;
    }

    std::cout << "ending main" << std::endl;

    return 0;
}
