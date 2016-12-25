#include <iostream>
#include <vector>
#include <string>

///
/// enable_if uses
/// 1) Function return type
/// 2) Function argument type
/// 3) Function template parameter
/// 4) Class template parameter
///




#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;


template<typename T, class enable=void>
class Sample;

template<typename T>
class Sample<T,std::enable_if_t<std::is_integral<T>::value> >
{
public:
    void execute()
    {
        SHOW_SIGNATURE;
    }
};

template<typename T>
class Sample<T,std::enable_if_t<std::is_class<T>::value> >
{
public:
    void execute()
    {
        SHOW_SIGNATURE;
    }
};





class Base
{

};


class Derived : public Base
{

};


template<typename B, typename D, class enable=void>
class Sample2;

template<typename B, typename D>
class Sample2<B,D,std::enable_if_t<std::is_base_of<B,D>::value>  >
{
public:
    void execute()
    {
        SHOW_SIGNATURE;
    }
};

template<typename B, typename D>
class Sample2<B,D,std::enable_if_t<!std::is_base_of<B,D>::value>  >
{
public:
    void execute()
    {
        SHOW_SIGNATURE;
    }
};

int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    Sample<int> a;
    a.execute();

    class foo{};

    Sample<foo> b;
    b.execute();

    Sample2<Base,Derived> c;
    c.execute();

    Sample2<Derived,Base> d;
    d.execute();

    Sample2<Derived,Derived> e;
    e.execute();

    std::cout << "done...\n";

    return 0;
}
