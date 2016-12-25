#include <iostream>
#include <vector>
#include <string>

#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

///
/// Curiously Recursive Template Pattern
/// Example of static polymorphism
/// Static bound without virtual functions, but not selectable at runtime
///

///
/// derived is template
///
template <typename Derived>
class Base2
{
public:
    Base2()
    {
        SHOW_SIGNATURE;
    }

    ~Base2()
    {
        SHOW_SIGNATURE;
    }

    void execute()
    {
        SHOW_SIGNATURE;
        static_cast<Derived*>(this)->executeImp();
    }
};
template<typename T>
class Derived2 : public Base2<Derived2<T>>
{
public:
    Derived2()
    {
        SHOW_SIGNATURE;
    }

    ~Derived2()
    {
        SHOW_SIGNATURE;
    }
    void executeImp()
    {
        SHOW_SIGNATURE;
    }
};
///
/// Simple case
///
template<typename Derived>
class Base
{
public:
    Base()
    {
        SHOW_SIGNATURE;
    }
    void execute()
    {
        SHOW_SIGNATURE;
        static_cast<Derived*>(this)->executeImp();
    }
    static void init()
    {
        SHOW_SIGNATURE;
        Derived::init();
    }
private:

};
class Derived : public Base<Derived>
{
public:
    Derived()
    {
        SHOW_SIGNATURE;
    }

    void executeImp()
    {
        SHOW_SIGNATURE;
    }
    static void init()
    {
        SHOW_SIGNATURE;
    }
};



int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    Derived d;
    d.execute();

    Base<Derived> *b = &d;
    d.execute();

    b->init();

    Derived2<int> d2;
    d2.execute();

    std::cout << "done...\n";

    return 1;
}
