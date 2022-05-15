#include "vector.hpp"
#include <vector>

#include <map>
#include "map.hpp"

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
	ft::map<char, int> map;

	return 0;
}
