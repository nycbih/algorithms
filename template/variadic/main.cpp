
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
///////////////////////////////////////////////////////////////////////////////
///
/// generator variardic example
///
///////////////////////////////////////////////////////////////////////////////
class Generator
{
public:
    Generator(std::ostringstream &out, char delimiter='|')
            : m_out(out)
              , m_delimiter(delimiter)
    {
    }
    template<typename T>
    void generate(T &arg)
    {
        for( const auto &val : arg)
        {
            m_out << val << m_delimiter;
        }
    }

    template<typename T, typename...TArgs>
    void generate(T &arg, TArgs...args)
    {
        for( const auto &val : arg)
        {
            m_out << val << m_delimiter;
            generate(args...);
        }

        m_out << "\n";
    }
private:
    std::ostringstream &m_out;
    char m_delimiter;
};
///////////////////////////////////////////////////////////////////////////////
///
/// logger variardic example
///
///////////////////////////////////////////////////////////////////////////////
class Logger
{
public:
    Logger(std::ostringstream &out, char delimiter='|')
    : m_out(out)
    , m_delimiter(delimiter)
    {
    }
    template<typename T>
    void log(T &arg)
    {
        m_out << arg;
    }

    template<typename T, typename...TArgs>
    void log(T &arg, TArgs...args)
    {
        m_out << arg << m_delimiter;

        log(args...);
    }

private:
    std::ostringstream &m_out;
    char m_delimiter;
};

int main(int argc, char *argv[])
{
    std::ostringstream out;
    Logger log(out);
    log.log("this is an error", 4, 91.0);
    std::cout << out.str() << std::endl;


    using TVec = std::vector<std::string>;

    TVec a={"a", "b", "c"};
    TVec b={"A", "B", "C"};
    TVec c={"X", "Y", "Z"};
    TVec d={"x", "y", "z"};

    std::ostringstream out2;
    Generator gen(out2);
    gen.generate(a,b,c,d);
    std::cout << out2.str() << std::endl;

    return 1;
}
