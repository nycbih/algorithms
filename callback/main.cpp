#include <iostream>
#include <vector>

///
/// C styple pointer to function
///
void test_function(int val)
{
	std::cout << __PRETTY_FUNCTION__ << " called with value=" << val << std::endl;
}

// typedef pointer to function
typedef void (*callback)(int val);


///
/// C++ native pointer to member function
///
class TestClass
{
public:
	void operator()(int val)
	{
		std::cout << __PRETTY_FUNCTION__ << " called with value=" << val << std::endl;
	}
};
class Test2Class
{
public:
	void operator()(int val)
	{
		std::cout << __PRETTY_FUNCTION__ << " called with value=" << val << std::endl;
	}
};


///
/// pointer to specific callback function
///
using pCallback = void (TestClass::*)(int val);



///
/// pointers to hetrogenous types using std::function
///
class Async
{
public:
	using TCallback = std::function<void (int)>;
	Async()
	{
	}
	void add(TCallback cb)
	{
		m_array.push_back(cb);
	}
	void execute()
	{
		for( auto &worker : m_array)
		{
			int i=10;
			worker(i);
		}
	}
private:
	using TVector = std::vector<TCallback>;
	TVector m_array;
};


int main(int argc, char *argv[])
{
	std::cout << "starting application" << std::endl;

	int val = 10;
	callback test = test_function;
	test(val);


	TestClass myclass;

	pCallback cb = &TestClass::operator();

	(myclass.*cb)(val);

	TestClass tc1;
	Async::TCallback cb1(tc1);

	Test2Class tc2;
	Async::TCallback cb2(tc2);

	Async worker;
	worker.add(cb1);
	worker.add(cb2);
	worker.execute();

	return 1;
}
