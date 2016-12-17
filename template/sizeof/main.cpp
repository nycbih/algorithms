#include <iostream>
#include <vector>
#include <string>

#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;


class A {};

class B : public A {};

class C {};


template <class T, class U>
class Conversion
{
    using Small = char;
    class Big { char dummy[2]; };
    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum {exists = sizeof(Test(MakeT())) == sizeof(Small)};
    enum {SameType = false};
};

template <class T>
class Conversion<T,T>
{
public:
    enum { exists = 1, SameType = 1};
};



int main(int argc, char *argv[])
{
    std::cout << "starting...\n";
    //------
    std::cout << std::boolalpha;
    std::cout << "a2b: " << std::is_base_of<A, B>::value << '\n';
    std::cout << "b2a: " << std::is_base_of<B, A>::value << '\n';
    std::cout << "c2b: " << std::is_base_of<C, B>::value << '\n';
    std::cout << "same type: " << std::is_base_of<C, C>::value << '\n';
    //------
    std::cout << "is_conv?=" << Conversion<int,double>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<int,char*>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<char,float>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<float,char>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<A,B>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<B,A>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<A,B>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<A,A>::exists << std::endl;
    std::cout << "is_conv?=" << Conversion<C,A>::exists << std::endl;

    std::cout << "is_same=" << Conversion<B,B>::SameType << std::endl;

    std::cout << "is_derived=" << (!Conversion<B,A>::SameType && Conversion<B,A>::exists) << std::endl;

    std::cout << "is_derived=" << (!Conversion<A,B>::SameType && Conversion<A,B>::exists) << std::endl;

    std::cout << "done...\n";

    return 1;
}
