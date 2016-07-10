#include <iostream>
#include <thread>
#include <atomic>
#include <deque>
#include <stack>
#include <queue>
#include <chrono>
#include <condition_variable>

///////////////////////////////////////////////////////////////////////////////
///
/// Splinlock using C++ primitives
///
///////////////////////////////////////////////////////////////////////////////
class SpinLock
{
public:
    SpinLock()
    {
    }
    void lock()
    {
        m_flag.test_and_set(std::memory_order_acquire);
    }

    void unlock()
    {
        m_flag.clear(std::memory_order_release);
    }
private:
    std::atomic_flag m_flag = ATOMIC_FLAG_INIT;
};
///////////////////////////////////////////////////////////////////////////////
///
/// Thread stack
///
///////////////////////////////////////////////////////////////////////////////
template<class TData>
class TSStack
{
public:
    TSStack()
    {
    }

    // deal with these later
    TData operator=(const TSStack &stack) = delete;
    TSStack(const TSStack &stack ) = delete;

    void push(TData data)
    {
        std::lock_guard<std::mutex> l(m_lock);
        m_stack.push(std::move(data));
    }

    bool pop(TData &data)
    {
        std::lock_guard<std::mutex> l(m_lock);

        if( m_stack.empty() ) return false;

        data = std::move(m_stack.top());

        m_stack.pop();

        return true;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> l(m_lock);
        return m_stack.empty();
    }
private:
    std::stack<TData> m_stack;
    std::mutex m_lock;
};
///////////////////////////////////////////////////////////////////////////////
///
/// Thread safe queue
///
///////////////////////////////////////////////////////////////////////////////
template<class TData>
class TSQueue
{
public:
    TSQueue()
    {
    }

    // deal with these later
    TData operator=(const TSQueue &queue) = delete;
    TSQueue(const TSQueue &queue ) = delete;

    void push(TData &data)
    {
        std::lock_guard<std::mutex> lock(m_lock);
        m_queue.push(std::move(data));
        m_cond.notify_one();
    }

    bool try_pop(TData &data)
    {
        std::lock_guard<std::mutex> lock(m_lock);

        if( m_queue.empty()) return false;

        data = std::move(m_queue.front());
        m_queue.pop();

        return true;
    }

    bool wait_and_pop(TData &data, size_t msec)
    {
        std::unique_lock<std::mutex> lock(m_lock);

        bool success = m_cond.wait_for(lock,std::chrono::milliseconds(msec), [this] {return !m_queue.empty();} );

        if( !success ) return false;

        data = std::move(m_queue.front());

        m_queue.pop();

        return true;
    }

    size_t size()
    {
        return m_queue.size();
    }
private:
    std::queue<TData> m_queue;
    std::mutex m_lock;
    std::condition_variable m_cond;
};
///////////////////////////////////////////////////////////////////////////////
///
/// ThreadPool
///
///////////////////////////////////////////////////////////////////////////////
class ThreadPool
{
public:


private:


};


using DataQueue = TSQueue<int>;

///////////////////////////////////////////////////////////////////////////////
///
/// producer
///
///////////////////////////////////////////////////////////////////////////////
class Producer
{
public:
    Producer(DataQueue &queue, size_t count)
    :m_queue(queue)
    ,m_counter(count)
    {
    }
    void operator()()
    {
        for( int i=0; i < m_counter; ++i)
        {
            int out = i;
            m_queue.push(out);
        }

    }
private:
    DataQueue &m_queue;
    int m_counter;
};

//////////////////////////////////////////////////////////////////////////////
///
/// Consumer
///
//////////////////////////////////////////////////////////////////////////////
class Consumer
{
public:
    Consumer(DataQueue &queue)
    :m_queue(queue)
    {
    }
    void operator()()
    {
        int item{};
        size_t msec = 100;

        while( !m_done )
        {
            if( m_queue.wait_and_pop(item,msec))
            {
                std::cout << item << std::endl;
            }
        }
    }

    void done()
    {
        m_done=true;
    }
private:
    DataQueue &m_queue;
    bool m_done;
};

//////////////////////////////////////////////////////////////////////////////
///
/// create thread from class
///
//////////////////////////////////////////////////////////////////////////////
class Active
{
public:
    Active()
    {
    }

    void init()
    {
        std::cout << "starting thread" << std::endl;
        std::thread tmp(&Active::run,this);
        std::cout << "ending thread" << std::endl;
        m_thread = std::move(tmp);
    }
    void done()
    {
        m_done=true;
        m_thread.join();
        std::cout << "done complete" << std::endl;
    }
private:
    bool m_done;
    std::thread m_thread;


    void run()
    {
        std::cout << "thread has started" << std::endl;
    }

};

/////////////////////////////////////////:q//////////////////////////////////////
///
/// ThreadPool
///
///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "Starting Application!" << std::endl;

    // create queue, producer/consumer

    int count=10;

    DataQueue queue;
    Producer p(queue,count);
    Consumer c(queue);

    // start threads with shared queue
    std::thread tp(p);
    std::thread tc(c);

    // wait until thread ends
 //   tp.join();
 //   tc.join();

    Active active;
    active.init();
    active.done();

    std::cout << "Application terminating" << std::endl;
    return 0;
}