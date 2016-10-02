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
    int val = 0;
    node_t *lhs=nullptr;
    node_t *rhs= nullptr;

    static node_t *create(int val)
    {
        node_t *tmp = new node_t;
        tmp->val = val;
        return tmp;
    }

};

class Tree
{
public:
    Tree()
    {
    }

    node_t *&root()
    {
        return m_root;
    }

    void insert( int val )
    {
        if( m_root == nullptr )
        {
            m_root = node_t::create(val);
            return;
        }

        insert(m_root,val);
    }

    bool find(int val)
    {
        bool found = find( m_root, val);

        if( found )
        {
            std::cout << "found" << std::endl;
        }
        else
        {
            std::cout << "not found" << std::endl;
        }

        return found;
    }

    void print()
    {
        print(m_root);
    }

    int max_depth()
    {
        return max_depth(m_root);
    }

    int min_depth()
    {
        return min_depth(m_root);
    }

    int min_val()
    {
        if( m_root == nullptr ) return 0;

        node_t *c = m_root;
        while( c->lhs != nullptr )
        {
            c = c->lhs;
        }

        return c->val;
    }

    int max_val()
    {
        if( m_root == nullptr ) return 0;

        node_t *c = m_root;
        while( c->rhs != nullptr )
        {
            c = c->rhs;
        }

        return c->val;
    }

private:
    node_t *m_root = nullptr;

    bool find(node_t *node, int val)
    {
        if( node == nullptr) return false;
        if( node->val == val ) return true;
        else if( node->val <= val ) return find( node->lhs, val);
        else return find( node->rhs, val);
    }

    void insert( node_t *&node, int val )
    {
        if( node == nullptr )
        {
            node = node_t::create(val);
            return;
        }

        if( val <= node->val )
        {
            insert(node->lhs, val);
        }
        else
        {
            insert( node->rhs, val );
        }
    }

    void print( node_t *node )
    {
        if( node == nullptr ) return;

        print( node->lhs );

        std::cout << node->val << std::endl;

        print( node->rhs );
    }

    int max_depth(node_t *node)
    {
        if( node == nullptr ) return 0;

        int dlhs = max_depth(node->lhs);
        int drhs = max_depth(node->rhs);

        if( dlhs >= drhs ) return dlhs + 1;
        else return drhs + 1 ;
    }

    int min_depth(node_t *node)
    {
        if( node == nullptr ) return 0;

        int dlhs = min_depth(node->lhs);
        int drhs = min_depth(node->rhs);

        if( dlhs <= drhs ) return dlhs + 1;
        else return drhs + 1;
    }
};


int main()
{
    std::cout << "starting main" << std::endl;

    Tree tree;
    tree.insert(200);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.print();

    tree.find(200);
    tree.find(800);

    std::cout << "max-depth=" << tree.max_depth() << std::endl;

    std::cout << "min-depth=" << tree.min_depth() << std::endl;

    std::cout << "min-val=" << tree.min_val() << std::endl;

    std::cout << "max-val=" << tree.max_val() << std::endl;

    std::cout << "ending main" << std::endl;

    return 0;
}
