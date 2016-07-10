#include <sys/epoll.h>
#include <unistd.h>

#include <thread>
#include <iostream>




template <size_t TMaxEvents=1024>
class Async
{
public:
    Async()
    {
    }
    ~Async()
    {
    }
    bool init()
    {
        int ret = epoll_create1(EPOLL_CLOEXEC);
        std::cout << "epoll_create=" << ret << std::endl;
        return ret > 0;
    }
    void terminate()
    {
        if( m_epoll_fd > 0 )
        {   
            int ret = close(m_epoll_fd);
            std::cout << "epoll_close=" << ret << std::endl;
        }
    }
    bool add(int fd)
    {
        struct epoll_event event;
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
    epoll_event m_events[TMaxEvents]={0};

    void wait()
    {
        std::cout << "starting epoll thread m_alive=" << 
            m_alive << std::endl;

        int ret=-1;
        while( m_alive )
        {
            ret = epoll_wait(m_epoll_fd, m_events, TMaxEvents);
        }

        std::cout << "endling epoll thread" << std::endl;
    }
};






int main(int argc, char *argv[])
{
    return 1;

}
