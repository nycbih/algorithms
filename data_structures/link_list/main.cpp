#include <iostream>
#include <thread>
#include <atomic>
#include <deque>
#include <stack>
#include <queue>
#include <chrono>
#include <vector>
#include <condition_variable>

struct node_t
{
    int val = 0 ;
    node_t *next=nullptr;
};

class LinkList
{
public:
    LinkList()
    {
    }
    void add(int val)
    {
        std::cout << "start add" << std::endl;

        node_t *tmp = create(val);

        if( nullptr == m_head )
        {
            std::cout << "m_head is null" << std::endl;
            m_head = tmp;
            return;
        }

        tmp->next = m_head;
        m_head = tmp;

        std::cout << "end add" << std::endl;
    }
    bool remove(int val)
    {
        std::cout << "start add val=" << val << std::endl;

        if( nullptr == m_head )
        {
            return false;
        }
        else if( m_head->val == val )
        {
            node_t *tmp = m_head;
            m_head = m_head->next;
            delete tmp;
            return true;
        }

        node_t *c = m_head->next;
        node_t *p = m_head;

        while( c )
        {
            if( c->val == val )
            {
                p->next = c->next;
                std::cout << "val=" << val << "found" << std::endl;
                delete c;
                return true;
            }

            p = c;
            c = c->next;
        }

        std::cout << "val=" << val << " not found" << std::endl;
        return false;
    }
    void reverse()
    {
        if( m_head == nullptr ) return;

        node_t *p = nullptr;
        node_t *c = m_head;
        node_t *n = nullptr;

        std::cout << "reverse nodes" << std::endl;

        while( c )
        {
            n = c->next;
            c->next = p;
            p = c;
            c = n;
        }

        m_head = p;
    }
    void print()
    {
        std::cout << "start print" << std::endl;

        node_t *c = m_head;
        while( c )
        {
            std::cout << c->val << std::endl;

            c = c->next;
        }

        std::cout << "end print" << std::endl;
    }
private:
    node_t *m_head = nullptr;

    node_t *create(int val)
    {
        node_t *tmp = new node_t;
        tmp->val = val;
        return tmp;
    }
};


int main()
{
    std::cout << "starting main" << std::endl;

    LinkList list;
    list.add(1);
    list.add(3);
    list.add(5);
    list.add(10);
    list.add(888);
    list.print();
    list.reverse();
    list.print();

    std::cout << "ending main" << std::endl;

    return 0;
}
