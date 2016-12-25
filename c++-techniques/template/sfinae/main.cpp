#include <iostream>
#include <vector>
#include <string>

///
/// Example of Substitution failure is not an error SFINE
///


#define SHOW_SIGNATURE std::cout << __PRETTY_FUNCTION__ <<  ":" << __LINE__ << std::endl;


namespace my {

    template<bool, typename T = void>
    struct enable_if {
        // left blank for force SFINE failure
    };

    template<typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

///
/// template alias with using
///
    template<bool B, typename T = void>
    using enable_if_t = typename enable_if<B, T>::type;

    template<typename T>
    void do_stuff(enable_if_t<std::is_integral<T>::value, T> &t) {
        SHOW_SIGNATURE;
    }

    template<typename T>
    void do_stuff(enable_if_t<std::is_class<T>::value, T> &t) {
        SHOW_SIGNATURE;
    }

    int func(...) {
        SHOW_SIGNATURE;
        return 2;
    }

    template<typename T>
    std::enable_if_t<std::is_integral<T>::value, int>
    func(T val) {
        SHOW_SIGNATURE;
        return val;
    };

    int func(float f) {
        SHOW_SIGNATURE;
        return f;
    }
}

int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    std::cout << my::func(nullptr) << " ";
    std::cout << my::func(2) << " ";
    std::cout << my::func(2.f) << " ";
    std::cout << my::func(2.0) << " " << std::endl;

    int val=2l;

    struct foo
    {

    };

    my::do_stuff<int>(val);


    foo f;
    my::do_stuff<foo>(f);


    std::cout << "done...\n";

    return 1;
}
