#include <iostream>

class A
{
	public:
		int i;
		class B
		{
			public:
				B() { std::cout << i << std::endl; }
		};
};

int main()
{
	return 0;
}