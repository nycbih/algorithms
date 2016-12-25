#include <iostream>
#include <vector>
#include <string>

#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

///
/// a technique to simulate artial specialization for function templates
///
struct Widget
{
    explicit Widget(int arg)
    {

    }
};

///
/// type without value
///
template<typename T>
struct Type2Type
{
    using OriginalType = T;
};

template<typename T, typename TArg>
T *create(TArg arg, Type2Type<T>)
{
    SHOW_SIGNATURE;
    return new T(arg);
};

template<typename TArg>
Widget *create(TArg arg, Type2Type<Widget>)
{
    SHOW_SIGNATURE;
    return new Widget(arg);
};


int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    create(100,Type2Type<Widget>());
    create(100,Type2Type<int>());

    std::cout << "done...\n";

    return 1;
}
