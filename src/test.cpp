#include "vector.hpp"
#include <vector>

#include <iterator>
#include <iostream>
#include <iterator>
#include <memory>

class Test
{
private:
	/* data */
public:
	Test(/* args */);
	Test(const Test& other);
	~Test();
};

Test::Test(/* args */)
{
	std::cout << "test constrcutor\n";
}

Test::Test(const Test& other)
{
	std::cout << "test constrcutor 2\n";
}

Test::~Test()
{
	std::cout << "test destrcutor\n";
}

#include <typeinfo>
#include <string>
#include <string_view>
#include <type_traits>
#include <algorithm>

int main()
{
	//std::allocator<int> *alloc = new std::allocator<int>;
	std::vector<int> array;

	array.push_back(2);
	array.push_back(4);
	array.push_back(6);
	array.push_back(1);
	array.push_back(3);
	array.push_back(5);
	std::vector<int> array2 = array;

	//std::cout << array.capacity() << std::endl;
	std::cout << "cap " << array2.capacity() << std::endl;

	array2.insert(++array2.begin(), 0);
	std::cout << "cap " << array2.capacity() << std::endl;
	for (std::vector<int>::iterator it = array2.begin(); it < array2.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}
