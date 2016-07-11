#include <iostream>
#include <thread>
#include <atomic>
#include <deque>
#include <stack>
#include <queue>
#include <chrono>
#include <vector>
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


////////////////////////////////////////////////////////////////////////////////
///
/// async logger
///
////////////////////////////////////////////////////////////////////////////////
class AsyncLogger
{
public:
    AsyncLogger()
    :m_done(false)
    {
        log("create AsyncLogger");
    }

    bool init()
    {
        log("starting logger init");
        std::thread tmp(&AsyncLogger::run,this);
        m_thread = std::move(tmp);
        log("done logger init");
        return true;
    }

    void log(const char *str)
    {
        std::lock_guard<std::mutex> l(m_lock);
        m_logger.push(str);
    }

    void done()
    {
        log("start logger done");
        m_done = true;
        m_thread.join();
        log("end logger done");
    }
private:
    bool m_done;
    std::mutex m_lock;
    std::thread m_thread;

    using TLogger=std::queue<std::string>;
    TLogger m_logger;

    void run()
    {
        log("start logger thread");

        while( !m_done && m_logger.size() )
        {
            while( !m_logger.empty() )
            {
                std:: string msg;
                {
                    std::lock_guard<std::mutex> l(m_lock);
                    msg = m_logger.front();
                    m_logger.pop();
                }

                std::cout << msg << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        log("done logger thread");
    }
};


///////////////////////////////////////////////////////////////////////////////
///
/// Thread stack
///
////////////////////////////////////////////////////////////////////////////////
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
    bool empty()
    {
        return m_queue.empty();
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
    Producer(AsyncLogger &logger,DataQueue &queue, size_t count)
    :m_logger(logger)
    ,m_queue(queue)
    ,m_counter(count)
    {
        m_logger.log("CTOR Producer");
    }

    void push(int val)
    {
        m_queue.push(val);
    }

private:
    AsyncLogger &m_logger;
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
    Consumer(AsyncLogger &logger, DataQueue &queue)
    :m_logger(logger)
    ,m_queue(queue)
    {
        m_logger.log("CTOR Consumer");
    }
    void operator()()
    {
        m_logger.log("start Consumer thread");

        int item{};
        size_t msec = 100;

        while( !m_done && !m_queue.empty() )
        {
            if( m_queue.wait_and_pop(item,msec))
            {
                std::string out = std::to_string(item);
                m_logger.log(out.c_str());
            }
        }

        m_logger.log("end Consumer thread");
    }

    void done()
    {
        m_done=true;
    }
private:
    AsyncLogger &m_logger;
    DataQueue &m_queue;
    bool m_done;
};

//////////////////////////////////////////////////////////////////////////////
///
/// create active class, single internal thead for class
///
//////////////////////////////////////////////////////////////////////////////
class Active
{
public:
    Active(AsyncLogger &logger)
    : m_logger(logger)
    ,m_done(false)
    {
        m_logger.log("Create Active");
    }

    void init()
    {
        m_logger.log("starting init Active");
        std::thread tmp(&Active::run,this);
        m_thread = std::move(tmp);
        m_logger.log("done init Active");
    }

    void done()
    {
        m_logger.log("start done Active");
        m_done=true;
        m_thread.join();
        m_logger.log("done done() active");
    }
private:
    AsyncLogger &m_logger;
    bool m_done;
    std::thread m_thread;
    std::mutex m_lock;

    void run()
    {
        m_logger.log("start run Active thread");

        while( !m_done )
        {
            m_logger.log("active thread running");
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        m_logger.log("end run Active thread");
    }
};

///////////////////////////////////////////////////////////////////////////////
///
/// ThreadPool
///
///////////////////////////////////////////////////////////////////////////////
int main()
{
    std::cout << "starting main" << std::endl;

    AsyncLogger logger;
    logger.init();

    std::cout << "gone logger init" << std::endl;

    logger.log("Starting Application!");


    // create queue, producer/consumer

    int count=10;

    DataQueue queue;
    Producer p(logger,queue,count);
    Consumer c(logger,queue);

    for(int i=0; i < 10; ++i)
    {
        p.push(i);
    }

    // start threads with shared queue
    std::thread tc(c);
    c.done();
    tc.join();

    Active active(logger);
    active.init();

    logger.log("Application sleeping 10 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(10));

    active.done();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    logger.done();


    return 0;
}
