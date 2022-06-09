#include "vector.hpp"
#include <vector>

#include <map>
#include "map.hpp"

#include <iterator>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <typeinfo>
#include <string>
#include <string_view>
#include <type_traits>
#include <algorithm>

int main()
{
	/*
	std::vector<int> vec;
	
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);

	std::vector<int> vec2;

	vec2.push_back(1);
	vec2.push_back(2);
	vec2.push_back(3);
	vec2.push_back(4);
	vec2.push_back(5);
	vec2.push_back(6);
	vec2.push_back(7);
	vec2.push_back(8);
	vec2.push_back(9);

	vec2 = vec;
	printf("%p %lu %lu | %p %lu %lu\n", vec.data(), vec.size(), vec.capacity(), vec2.data(), vec2.size(), vec2.capacity());
	std::cout << *vec2.end() << std::endl;

	std::cout << *vec.begin() << std::endl;
	std::vector<int>::iterator it = vec.insert(vec.end(), 42);
	std::cout << *it << " " << *vec.begin() << " " << *++vec.begin() << std::endl;
	printf("%p %p\n\n", &*vec.begin(), &*it);

	ft::vector<int> a;

	std::cout << "cap=" << a.capacity() << std::endl;
	a.push_back(0);
	a.push_back(0);
	a.push_back(0);
	a.push_back(0);
	
	std::cout << "cap=" << a.capacity() << std::endl;
	ft::vector<int>::iterator ite = a.begin() + 2;
	a.insert(ite, 9);

	for (std::size_t i = 0; i < a.size(); i++)
		std::cout << a[i] << std::endl;

	std::cout << "cap=" << a.capacity() << std::endl;

	std::cout << "-------- b\n";
	std::vector<int> b;	

	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(5);
	b.push_back(6);
	b.push_back(7);
	b.push_back(8);

	std::cout << "cap=" << b.capacity() << std::endl;
	b.insert(b.begin() + 2, a.begin(), a.end() - 1);
	for (std::size_t i = 0; i < b.size(); i++)
		std::cout << b[i] << std::endl;
	std::cout << "cap=" << b.capacity() << std::endl;

	std::cout << "------------- b.remove\n";
	b.erase(b.begin(), b.end() - 1);
	for (std::size_t i = 0; i < b.size(); i++)
		std::cout << b[i] << std::endl;
	std::cout << "-------------------\n";
	ft::vector<int> strv;
	strv.push_back(1);
	ft::vector<int> strv2(strv);
	if (strv == strv2)
		std::cout << strv[0] << std::endl;
	*/

	ft::vector<int> v;
	ft::vector<int>::const_iterator it = v.begin();
	return 0;
}
