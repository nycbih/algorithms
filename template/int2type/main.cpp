#include <iostream>
#include <vector>
#include <string>

#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

///
/// static switch
///
template<int v>
struct Int2Type
{
    enum { value = v };
};

template<typename T, int TState>
class StaticState
{
public:
    void execute(T* obj)
    {
        execute(obj,Int2Type<TState>());
    }
private:
    void execute( T* obj, Int2Type<0>)
    {
        SHOW_SIGNATURE;
    }

    void execute( T* obj, Int2Type<1>)
    {
        SHOW_SIGNATURE;
        obj->done();
    }

    void execute( T* obj, Int2Type<2>)
    {
        SHOW_SIGNATURE;
        obj->fun();
    }
};



int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    struct foo {};

    struct foo1
    {
        void done()
        {
        }
    };

    foo x;
    StaticState<foo,0> ss;
    ss.execute(&x);


    foo1 x1;
    StaticState<foo1,1> ss1;
    ss1.execute(&x1);


    std::cout << "done...\n";

    return 1;
}
