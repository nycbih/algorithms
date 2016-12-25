///////////////////////////////////////////////////////////////////////////////
///
/// generic epoll handler for asynchronous tasks
///
///////////////////////////////////////////////////////////////////////////////

#include <sys/epoll.h>
#include <unistd.h>

#include <thread>
#include <iostream>

#define TMaxEvents 1024
#define TIMEOUT 1000

class Epoll
{
public:
    using TCallback = std::function<void (int)>;

    Epoll()
    {
    }
    ~Epoll()
    {
    }
    bool init()
    {
        int ret = epoll_create1(EPOLL_CLOEXEC);
        std::cout << "epoll_create=" << ret << std::endl;

        if( ret > 0 )
        {   
            std::thread tmp(&Epoll::run,this);
            m_thread = std::move(tmp);                
            return true;
        }

        return false;
    }
    void terminate()
    {
        if( m_epoll_fd > 0 )
        {   
            int ret = close(m_epoll_fd);
            std::cout << "epoll_close=" << ret << std::endl;
        }
    }
    bool add(int fd,TCallback *cb)
    {
        struct epoll_event event;

        event.events   = EPOLLIN | EPOLLOUT;  
        event.data.fd  = fd;
        event.data.ptr = cb;   

        int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD,fd,&event); 

        return ret > 0;
    }
    bool remove(int fd)
    {
        int ret = epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL,fd,NULL);
        return ret > 0;
    }
private:
    int m_epoll_fd = -1;
    bool m_alive = false;
    std::thread m_thread;

    void run()
    {
        std::cout << "starting epoll thread m_alive=" << 
            m_alive << std::endl;

        epoll_event events[TMaxEvents]={0};

        while( m_alive )
        {
            int n = epoll_wait(m_epoll_fd, events, TMaxEvents, TIMEOUT);

            // error
            if( n < 0 )
            {
                continue;
            }          
            // timeout  
            else if( 0 == n )
            {   
                continue;
            }
            // callback 
            for(int i=0; i < n; ++i)
            {
                epoll_event &event = events[i];
                int fd = event.data.fd;
                TCallback *cb = static_cast<TCallback *>(event.data.ptr);
                (*cb)(fd);
            }
        }

        std::cout << "endling epoll thread" << std::endl;
    }
};






int main(int argc, char *argv[])
{
    return 1;

}
