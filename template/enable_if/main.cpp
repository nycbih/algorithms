#include <iostream>
#include <type_traits>

#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;

namespace my
{
    // when false, sfinae failure
    template<bool, typename T>
    struct enable_if {

    };

    // when true enable	
    template<typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    ///
    /// template variable using alias
    ///
    template <typename T>
    using enable_if_ic = typename enable_if<std::is_integral<T>::value, T>::type;

    template <typename T>
    using enable_if_class = typename enable_if<std::is_class<T>::value, T>::type;

    ///
    /// pick function at compile time, base on type
    ///
    template<typename T>
    void execute(enable_if_ic<T> t)
    {
        SHOW_SIGNATURE;
    }

    template<typename T>
    void execute(enable_if_class<T> t) 
    {
        SHOW_SIGNATURE;
    }
}


int main(int argc, char *argv[])
{
    struct test
    {

    };

    std::cout << "starting...\n";

    my::execute<int>(44);

    test foo;
    my::execute<test>(foo);

    std::cout << "done...\n";

    return 1;
}
