#include <iostream>

struct node_t
{
    int val=0;
    node_t *lhs = nullptr;
    node_t *rhs = nullptr;

    static node_t *create(int val_ )
    {
        node_t *tmp = new node_t;
        tmp->val = val_;
        return tmp;
    }
};

class Tree
{
public:
    node_t *&root()
    {
        return m_root;
    }

    void insert( int val, node_t *&node )
    {
        if( node == nullptr )
        {
            node = node_t::create(val);
            return;
        }

        else if( val < node->val )
        {
            insert(val, node->lhs);
        }
        else
        {
            insert(val, node->rhs);
        }
    }
    bool find( int val, node_t *&node )
    {
        if( node == nullptr )
        {
            return false;
        }
        else if( val == node->val )
        {
            return true;
        }
        else if( val <= node->val )
        {
            return find( val, node->lhs );
        }
        else
        {
            return find( val, node->rhs );
        }
    }
    bool remove( int val, node_t *&node )
    {
        // not found
        if( node == nullptr )
        {
            return false;
        }
        // left
        else if( val < node->val )
        {
            remove( val, node->lhs );
            return true;
        } // right
        else if( val > node->val )
        {
            remove( val, node->rhs );
            return true;
        } // match
        else
        {
            node = remove( node );
            return true;
        }

        return true;
    }
    size_t min_depth(const node_t *node)
    {
        if( nullptr == node ) return 0;

        if( !node->lhs && !node->rhs)
        {
            return 1;
        }
        else if( !node->lhs )
        {
            min_depth( node->rhs + 1);
        }
        else if( !node->rhs )
        {
            min_depth( node->lhs + 1);
        }

        size_t lhs = min_depth(node->lhs);
        size_t rhs = min_depth(node->rhs);

        return (lhs < rhs) ? lhs + 1 : rhs + 1;
    }
    size_t max_depth(const node_t *node)
    {
        if( nullptr == node ) return 0;

 //       std::cout << node->val << std::endl;

        size_t lhs = max_depth(node->lhs);
        size_t rhs = max_depth(node->rhs);

        return (lhs > rhs) ? lhs + 1 : rhs + 1;
    }
    size_t minValue(const node_t *node)
    {
        if( nullptr == node ) return 0;

        const node_t *current = node;

        while( current->lhs != nullptr )
        {
            current = current->lhs;
        }

        return current->val;
    }
    size_t maxValue(const node_t *node)
    {
        if( nullptr == node ) return 0;

        const node_t *current = node;

        while( current->rhs != nullptr )
        {
            current = current->rhs;
        }

        return current->val;
    }
    size_t size(const node_t *node)
    {
        if( node == nullptr ) return 0;

        return size(node->lhs) + 1 + size(node->rhs);
    }
    void inorder(const node_t *node)
    {
        if( node == nullptr ) return;
        inorder(node->lhs);
        std::cout << node->val << std::endl;
        inorder(node->rhs);
    }
    void preorder(const node_t *node)
    {
        if( node == nullptr ) return;
        std::cout << node->val << std::endl;
        preorder(node->lhs);
        preorder(node->rhs);
    }
    void postorder(const node_t *node)
    {
        if( node == nullptr ) return;
        postorder(node->lhs);
        postorder(node->rhs);
        std::cout << node->val << std::endl;

    }
private:
    node_t *m_root= nullptr;

    node_t *remove(node_t *&node)
    {
        // 1) no children
        if( !node->lhs && !node->rhs )
        {
            return nullptr;
        }
        // 2) rhs child
        else if( !node->lhs && node->rhs )
        {
            return node->rhs;
        }
        // 3) lhs child
        else if( node->lhs && !node->rhs )
        {
            return node->lhs;
        }
        // 4) both children present;
        else
        {
            if( node->rhs->lhs)
            {
                node->val = node->rhs->lhs->val;
                delete node->rhs->lhs;
                node->rhs->lhs = nullptr;
            }
            return node;
        }
    }
};


void status(Tree &tree, node_t *root)
{
    std::cout << "size=" << tree.size(root) << std::endl;
    std::cout << "min=" << tree.minValue(root) << std::endl;
    std::cout << "max=" << tree.maxValue(root) << std::endl;
    std::cout << "min_depth=" << tree.min_depth(root) << std::endl;
    std::cout << "max_depth=" << tree.max_depth(root) << std::endl;
}

int main()
{
    int vector[] = {4,2,5,1,3};

    Tree tree;

    node_t *&root = tree.root();

    for( auto val : vector )
    {
        tree.insert(val,root);
    }

    for( auto val : vector )
    {
        std::cout << "val=" << val << " find=" << tree.find(val,root) << std::endl;
    }

    //tree.inorder(root);
    //tree.preorder(root);
    //tree.postorder(root);

    //tree.remove(5,root);

    status(tree,root);

   // for( auto val : vector )
    //{
    //    tree.remove(val,root);
   // }

    //status(tree,root);
}
