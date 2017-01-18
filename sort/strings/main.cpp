#include <iostream>
#include "strings.h"

///
/// other, min/max heap
///
int main(int argc, char *argv[])
{
    std::cout << "starting...\n";

    char string[]={"ABCD"};

    char remove[]={"h e l l o"};

    char number[] = "1234";

    std::cout << remove << std::endl;
    printf("%s\n", string);

    my::reverse1( string );
    my::reverse2( string);
    my::remove(remove,' ');

    std::cout << my::atoi(number) << std::endl;

    std::cout << "pow=" << my::pow(10,2) << std::endl;

    std::cout << "fib=" << my::fib(10) << std::endl;

    printf("%s\n", string);

    std::cout << remove << std::endl;

    std::cout << "done...\n";

    return 0;
}
