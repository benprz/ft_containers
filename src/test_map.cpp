#include "map.hpp"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <typeinfo>
#include <type_traits>
#include <vector>

class B
{
	public:
		B() { }
};

class A
{
	public:
		B a()
		{
			std::cout << "B!\n";
		 	return B();
		}
		const B a() const
		{
			std::cout << "const B!\n";
		 	return B();
		}
};

int main()
{
	const A tmp;
	B b = tmp.a();
	const B c = tmp.a();
	ft::map<int, int> mp;

	mp.insert(-1, 99);
	mp.insert(3, 99);
	mp.insert(2, 98);
	mp.insert(1, 97);
	mp.insert(7, 96);
	mp.insert(-42, 95);
	mp.insert(10, 94);

	ft::map<int, int>::iterator it = mp.end();
	it--;
	std::cout << (*it).second << std::endl;

	std::map<int, int> std_map;
	std_map.insert(std::pair<int, int>(-1, 99));
	std_map.insert(std::pair<int, int>(3, 99));
	std_map.insert(std::pair<int, int>(2, 98));
	std_map.insert(std::pair<int, int>(1, 97));
	std_map.insert(std::pair<int, int>(7, 96));
	std_map.insert(std::pair<int, int>(-42, 95));
	std_map.insert(std::pair<int, int>(10, 94));
	std::map<int, int>::iterator std_it = std_map.end();
	std_it--;
	std::cout << (*std_it).second << std::endl;
	std::map<int, int> map;
	printf("%p %p\n", &*map.begin(), &*map.end());
	map.insert(std::pair<int, int>(1, 42));
	printf("%p %p\n", &*map.begin(), &*map.end());
	map.insert(std::pair<int, int>(2, 42));
	printf("%p %p\n", &*++map.begin(), &*map.end());
	std::map<int, int>::const_iterator it = map.begin();
	printf("map2->%p\n", &*(map.insert(std::pair<int, int>(1, 42)).first));

	std::vector<int> v;
	unsigned short y = 10000;
	std::srand(std::time(NULL));
	for (unsigned short i = 0; i < y; i++)
	{
		v.push_back(rand());
	}
	ft::map<int, int> ft_map;
	std::map<int, int> std_map;
	for (unsigned short i = 0; i < v.size(); i++)
	{
		ft_map.insert(ft::pair<int, int>(v[i], 42));
		std_map.insert(std::pair<int, int>(v[i], 42));
	}
	ft::map<int, int> ft_map2(ft_map);
	ft::map<int, int>::iterator ft_it = ft_map2.begin();
	std::map<int, int>::iterator std_it = std_map.begin();
	for (int i = 0; i < v.size(); i++)
	{
		if (ft_it->first != std_it->first)
		{
			std::cout << "ERORRRRRRNDSUIUCSDUHFUDHS\n";
			exit(1);
		}
		else
		{
			std::cout << "TOUT JUSTE!!!!!!!!!!" << std::endl;
		}
	}
	//1, 2, 3, 4, 5, 7, 13, 20,37,40,99,98,45,44,28,29,87,67,19,95,18,22,38,77,42 9
	ft::map<int, int> map2;
	map2.insert(ft::pair<int, int>(1, 42));
	map2.insert(ft::pair<int, int>(2, 42));
	map2.insert(ft::pair<int, int>(3, 42));
	map2.insert(ft::pair<int, int>(4, 42));
	map2.insert(ft::pair<int, int>(5, 42));
	map2.insert(ft::pair<int, int>(7, 42));
	map2.insert(ft::pair<int, int>(13, 42));
	map2.insert(ft::pair<int, int>(20, 42));
	map2.insert(ft::pair<int, int>(37, 42));
	map2.insert(ft::pair<int, int>(40, 42));
	map2.insert(ft::pair<int, int>(99, 42));
	ft::map<int, int>::iterator begin = map2.begin();
	begin++;
	begin++;
	begin++;
	map2.insert(begin, ft::pair<int, int>(9, 42));
	map2.erase(7);
	map2.erase(4);
	std::cout << std::distance(map2.begin(), map2.end());
	ft::map<int, int> map3(map2);
	ft::map<int, int> map4(map3.begin(), map3.end());
	a();
	printf("%p %p\n", &*map2.begin(), &*map2.end());
	map2.insert(ft::pair<int, int>(1, 42));
	printf("%p %p\n", &*map2.begin(), &*map2.end());
	map2.insert(ft::pair<int, int>(2, 42));
	printf("%p %p\n", &*++map2.begin(), &*map2.end());
	map2.insert(ft::pair<int, int>(3, 42));
	printf("%p %p\n", &*++map2.begin(), &*map2.end());
	ft::map<int, int>::const_iterator it2 = map2.begin();
	printf("map2->%p\n", &*(map2.insert(ft::pair<int, int>(3, 42)).first));
	return 0;
}
