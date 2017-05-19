/*
Generator:

Every 0.1 second generate a timer event : current time + random number of millisecond (0 - 1000)
Wrap it in a timer struct {timer_id and scheduled_time} and hand over to Worker. (when a timer is generated, log the timer_id, scheduled_time and current_time)
30 events are enough

Worker:

Every second print out statistics: how many timers are going to fire in the future.
When a timer’s scheduled_time is reached: log timer_id, scheduled_time, current_time and throw away this timer

Generator and Worker should run in its own threads.

*/

#include <iostream>
#include <cstdlib>
#include <queue>
#include <thread>
#include <atomic>
#include <chrono>
#include <list>
#include <condition_variable>


namespace mystuff
{
///
/// data
///
    struct TimerInfo
    {
        size_t timer_id = 0;
        int64_t scheduled_time =0;

        void show(const char *msg)
        {
            int64_t nowTime = getTime();
            long timeleft = ( scheduled_time - nowTime );
            std::cout <<  msg << ": timer_id=" << timer_id << " nowTime=" << nowTime << " scheduled_time=" << scheduled_time << " timeleft=" << timeleft << std::endl;
        }

        bool show_and_remove()
        {
            int64_t nowTime = getTime();
            long timeleft = ( scheduled_time - nowTime );

            if( timeleft <= 0 )
            {
                std::cout << "Done Timer!!! timer_id=" << timer_id << " nowTime=" << nowTime << " scheduled_time=" << scheduled_time << " timeleft=" << timeleft << std::endl;
                return true;
            }

            return false;
        }

        static int64_t getTime()
        {
            // TODO needs cleaning up...
            std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
            auto epoch = now_ms.time_since_epoch();
            auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
            return value.count();
        }
    };
///
/// thread safe queue
/// please do'nt use this queue in an high performance system ;-)
/// since its a single producer/consumber its simple to create lockless queue
///
    class TSQueue
    {
    public:

        void push(TimerInfo &timer)
        {
            std::lock_guard<std::mutex> l(m_lock);
            m_queue.push(timer);
            m_cond.notify_one();
        }

        // wait for event, but timeout so we do'nt get stuck
        bool wait_and_pop(TimerInfo &timer, size_t msec)
        {
            std::unique_lock<std::mutex> lock(m_lock);

            bool success = m_cond.wait_for(lock,std::chrono::milliseconds(msec), [this] {return !m_queue.empty();} );

            if( !success ) return false;

            timer = m_queue.front();

            m_queue.pop();

            return true;
        }

        bool empty()
        {
            return m_queue.empty();
        }

    private:
        std::queue<TimerInfo> m_queue;
        std::mutex m_lock;
        std::condition_variable m_cond;
    };
///
/// generate timer events, generator run on its own thread
///
    class Generator
    {
    public:
        Generator(TSQueue &queue, size_t maxEvent)
                :m_queue(queue)
                ,m_maxEvent(maxEvent)
        {
            std::cout << "Generator CTOR" << std::endl;
        }
        bool init()
        {
            std::thread tmp(&Generator::run, this);
            m_thread = std::move(tmp);
            return true;
        }
        void done()
        {
            m_thread.join();
        }
    private:
        TSQueue &m_queue;
        std::thread m_thread;
        size_t m_maxEvent;

        void run()
        {
            std::cout << "generator thread has started" << std::endl;

            size_t timer_id = 0;

            for(size_t i=0; i < m_maxEvent; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                size_t offset = (rand() % 1000);

                // create event and queue
                TimerInfo info;
                info.timer_id = timer_id++;

                info.scheduled_time = TimerInfo::getTime() + offset;

                m_queue.push(info);
            }

            std::cout << "generator thread has ended" << std::endl;
        }

    };
///
/// print timer events, this worker has its own thread
///
    class Worker
    {
    public:
        Worker(TSQueue &queue)
                :m_queue(queue)
                ,m_done(false)
        {
            std::cout << "Worker CTOR" << std::endl;
        }

        // start thread here
        bool init()
        {
            std::thread tmp(&Worker::run, this);
            m_thread = std::move(tmp);
            return true;
        }

        // terminat thread
        void done()
        {
            m_done=true;
            m_thread.join();
        }

        bool empty()
        {
            return m_info.empty();
        }

        ///
        /// check timers and remove expired
        ///
        void checkTimer()
        {
            for( TList::iterator it=m_info.begin(); it != m_info.end(); ++it)
            {
                auto &rec = *it;
                if( rec.show_and_remove() )
                {
                    it = m_info.erase(it);
                    m_count++;
                }
            }
        }

        ///
        /// show active timers
        ///
        void showTimers()
        {
            std::cout << "active timers=" << m_info.size() << std::endl;
            for( TList::iterator it=m_info.begin(); it != m_info.end(); ++it)
            {
                auto &rec = *it;
                rec.show("Active Timers");
            }
        }

        //size_t remove_count() const
        //{
        //  return m_count;
        // }

    private:
        TSQueue &m_queue;
        std::atomic<bool> m_done;
        std::thread m_thread;
        size_t m_count;

        using TList = std::list<TimerInfo>;
        TList m_info;

        void run()
        {
            size_t timeout = 10;

            size_t lastTime = TimerInfo::getTime();
            size_t currentTime = TimerInfo::getTime();

            while( !m_done || !m_info.empty() )
            {
                TimerInfo info;

                if( m_queue.wait_and_pop(info,timeout) )
                {
                    m_info.push_back(info);
                    info.show("Recived Event");
                }

                checkTimer();

                currentTime = TimerInfo::getTime();

                // show stats every second
                long elapsed = currentTime - lastTime;

                // show timers every second
                const long SECOND = 1000;
                if( elapsed >= SECOND )
                {
                    lastTime = currentTime;
                    showTimers();
                }
            }
        }
    };

} // end namespace


int main()
{
    mystuff::TSQueue queue;

    // Generator and Worker share a queue
    size_t expected = 30;
    mystuff::Generator generator(queue, expected);
    mystuff::Worker worker(queue);
    worker.init();

    // give worker time to get settled.
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // generate events
    generator.init();
    generator.done();

    ///
    /// wait for a while before exiting
    /// since nothing may show up on sceen..
    /// all kind of timing issues
    ///
    size_t count=3;
    while( count-- )
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // exit thread grcefullly
    worker.done();

    std::cout << "Application is ending" << std::endl;

    return 0;
}