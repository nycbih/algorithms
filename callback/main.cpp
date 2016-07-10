#include <iostream>


// function pointers

void test_function(int val)
{
	std::cout << __FUNCTION__ << " called with value=" << val << std::endl;
}

// pointer to function
typedef void (*callback)(int val);


void test(callback cb, int val)
{
	callbac(val,val);
}

int main(int argc, char *argv[])
{
	std::cout << "starting application" << std::endl;

	test(test_func,10);



	return 1;
}
