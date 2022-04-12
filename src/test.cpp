#include "vector.hpp"
#include <vector>

#include <iostream>
#include <iterator>

int main()
{
	//vector<int> array;
	std::vector<int> real_array;

	//array.push_back(42);
	//std::cout << array[0] << std::endl;
	//std::cout << array[1] << std::endl;

	real_array.reserve(5);
	real_array.push_back(42);
	std::cout << "real_array.capacity() = " << real_array.capacity() << std::endl;
	//while (1) ;
	return 0;
}
