///
/// Rvalues used for (1) move semantics and (2) perfect forwarding
///
/// An lvalue is an expression that refers to a memory location and allows us to take the address of that memory location via the & operator.
/// An rvalue is an expression that is not an lvalue
///
///
///
///


#include <iostream>

class Logger {
public:
    static Logger &instance() {
        static Logger log;
        return log;
    }

    void log(const char *msg) {
        std::cout << msg << std::endl;
    }
};


class RValueLValue {
public:
    RValueLValue()
            : m_log(Logger::instance())
    {

    }

    void push(int &val)
    {
        m_log.log(__PRETTY_FUNCTION__);
    }

    void push(int &&val)
    {
        m_log.log(__PRETTY_FUNCTION__);
    }

    //
    // universal reference
    // can be either rvalue or lvalue
    //
    template<typename T>
    void enplace(T &&val)
    {
        m_log.log(__PRETTY_FUNCTION__);

        auto &&temp = val;

        show(std::forward<int>(val));
    }

private:
    Logger &m_log;


    void show(int &&val)
    {
        std::cout << val << std::endl;
    }
};


int bar() {
    return 11;
}

int main(int argc, char *argv[])
{
    RValueLValue rlval;

    Logger::instance().log("starting");


    int val = 10;
    rlval.push(10);
    rlval.push(val);
    rlval.push(bar());

    int val2 = 10;
    rlval.enplace(10);
    rlval.enplace(val2);
    rlval.enplace(std::move(val2));
    rlval.enplace(bar());

    int a=10;
    int b=20;
    rlval.enplace(a+b);
    Logger::instance().log("starting");

    return 1;
}
