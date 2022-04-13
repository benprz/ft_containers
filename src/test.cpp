#include "vector.hpp"
#include <vector>

#include <iterator>
#include <iostream>
#include <iterator>
#include <memory>

int main()
{
	std::vector<int> std_array;

	std_array.push_back(42);
	std_array.push_back(43);

	std_array.pop_back();
	std::cout << std_array.size() << std::endl;
/*
	ft::vector<int> ft_array;

	std::cout << "empty=" << ft_array.empty() << std::endl;
	ft_array.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		ft_array.push_back(i * 2);
		std::cout << ft_array.capacity() << std::endl;
	}
	for (int i = 0; i < ft_array.size(); i++)
	{
		std::cout << "ft_array[" << i << "] = " << ft_array[i] << std::endl;
	}
	std::cout << "empty=" << ft_array.empty() << std::endl;

	ft_array.begin();
	//std::iterator_traits<int> begin = std_array.begin();
	//ft_array.begin();
	for (int i = 0; i < 100; i++)
	{
		std_array.push_back(i);
		std::cout << std_array.capacity() << std::endl;
	}
	*/
	return 0;
}
