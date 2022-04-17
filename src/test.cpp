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


int main()
{
	const Test c;
	ft::vector<int> std_array;

	std_array.push_back(1);
	std_array.push_back(1);
	std_array.push_back(1);
	std_array.push_back(1);
	std_array.push_back(1);
	std::cout << std_array.capacity() << std::endl;
	std_array.resize(15, 2);
	std::cout << std_array.capacity() << std::endl;

	ft::vector<int> ft_array;

	ft_array.reserve(10);
	for (int i = 0; i < 20; i++)
	{
		ft_array.push_back(3);
		//std::cout << ft_array.capacity() << std::endl;
	}

	std_array.swap(ft_array);
	for (int i = 0; i < std_array.size(); i++)
		std::cout << std_array[i] << std::endl;
	for (int i = 0; i < ft_array.size(); i++)
	{
		std::cout << "ft_array[" << i << "] = " << ft_array[i] << std::endl;
	}
	std::cout << std_array.capacity() << std::endl;
	std::cout << ft_array.capacity() << std::endl;

	//std::iterator_traits<int> begin = std_array.begin();
	//ft_array.begin();
	
	// for (int i = 0; i < 100; i++)
	// {
	// 	std_array.push_back(i);
	// 	std::cout << std_array.capacity() << std::endl;
	// }
	return 0;
}
