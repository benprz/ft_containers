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

#include "../containers_test/srcs/map/common.hpp"
#define TESTED_NAMESPACE ft
#include <list>

#define T1 int
#define T2 foo<int>
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator ft_iterator;
typedef TESTED_NAMESPACE::map<T1, T2>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename MAP>
void	ft_bound(MAP &mp, const T1 &param)
{
	ft_iterator ite = mp.end(), it[2];
	_pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename MAP>
void	ft_const_bound(const MAP &mp, const T1 &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	_pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

/*
	ft_const_bound(mp, -10);
	ft_const_bound(mp, 1);
	ft_const_bound(mp, 5);
	ft_const_bound(mp, 10);
	ft_const_bound(mp, 50);

	printSize(mp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound(mp, 5);
	ft_bound(mp, 7);

	printSize(mp);
	*/
	return (0);
}


// #include <list>

// #define T1 int
// #define T2 int
// typedef _pair<const T1, T2> T3;

// int		main(void)
// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 7;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(lst_size - i, i));

// 	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
// 	TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();

// 	TESTED_NAMESPACE::map<T1, T2> mp_range(it, --(--ite));
// 	std::cout << "it=" << it->first << " ite=" << ite->first << std::endl;
	
// 	//printSize(mp);
// 	printSize(mp_range);
// 	for (int i = 0; it != ite; ++it)
// 		it->second = ++i * 5;

// 	//it = mp.begin(); ite = --(--mp.end());
// 	TESTED_NAMESPACE::map<T1, T2> mp_copy(mp);
// 	for (int i = 0; it != ite; ++it)
// 		it->second = ++i * 7;
// 	std::cout << "\t-- PART ONE --" << std::endl;
// 	//printSize(mp);
// 	//printSize(mp_range);
// 	// printSize(mp_copy);

// 	mp = mp_copy;
// 	mp_copy = mp_range;
// 	mp_range.clear();

// 	std::cout << "\t-- PART TWO --" << std::endl;
// 	printSize(mp);
// 	printSize(mp_range);
// 	printSize(mp_copy);
// 	return (0);
// }

// class B
// {
// 	public:
// 		B() { }
// };

// class A
// {
// 	public:
// 		B a()
// 		{
// 			std::cout << "B!\n";
// 		 	return B();
// 		}
// 		const B a() const
// 		{
// 			std::cout << "const B!\n";
// 		 	return B();
// 		}
// };

// int _ratio = 2;
// #define _map ft::map

// void a()
// {
// 	std::cout << "TEST->" << std::endl;
// 	std::vector<int> v;
// 	_map<int, int> mp;

//     for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
//         mp.insert(ft::make_pair(i, j));
//     }
//     _map<int, int> mp2(mp.begin(), mp.end());
//     _map<int, int>::iterator it = mp2.begin();
//     for (int i = 0; i < 30 * _ratio; ++i, it++) {
//         v.push_back(it->first);
//         v.push_back(it->second);
//     }
// }

// int main()
// {
	// const A tmp;
	// B b = tmp.a();
	// const B c = tmp.a();
	// ft::map<int, int> map;

	// map.insert(-1, 99);
	// map.insert(3, 99);
	// map.insert(2, 98);
	// map.insert(1, 97);
	// map.insert(7, 96);
	// map.insert(-42, 95);
	// map.insert(10, 94);

	// ft::map<int, int>::iterator it = map.end();
	// it--;
	// std::cout << (*it).second << std::endl;

	// std::map<int, int> std_map;
	// std_map.insert(ft::pair<int, int>(-1, 99));
	// std_map.insert(ft::pair<int, int>(3, 99));
	// std_map.insert(ft::pair<int, int>(2, 98));
	// std_map.insert(ft::pair<int, int>(1, 97));
	// std_map.insert(ft::pair<int, int>(7, 96));
	// std_map.insert(ft::pair<int, int>(-42, 95));
	// std_map.insert(ft::pair<int, int>(10, 94));
	// std::map<int, int>::iterator std_it = std_map.end();
	// std_it--;
	// std::cout << (*std_it).second << std::endl;
	// std::map<int, int> map;
	// printf("%p %p\n", &*map.begin(), &*map.end());
	// map.insert(ft::pair<int, int>(1, 42));
	// printf("%p %p\n", &*map.begin(), &*map.end());
	// map.insert(ft::pair<int, int>(2, 42));
	// printf("%p %p\n", &*++map.begin(), &*map.end());
	// std::map<int, int>::const_iterator it = map.begin();
	// printf("map2->%p\n", &*(map.insert(ft::pair<int, int>(1, 42)).first));

	// std::vector<int> v;
	// unsigned short y = 10000;
	// std::srand(std::time(NULL));
	// for (unsigned short i = 0; i < y; i++)
	// {
	// 	v.push_back(rand());
	// }
	// ft::map<int, int> ft_map;
	// std::map<int, int> std_map;
	// for (unsigned short i = 0; i < v.size(); i++)
	// {
	// 	ft_map.insert(ft::pair<int, int>(v[i], 42));
	// 	std_map.insert(std::pair<int, int>(v[i], 42));
	// }
	// ft::map<int, int> ft_map2(ft_map);
	// ft::map<int, int>::iterator ft_it = ft_map2.begin();
	// std::map<int, int>::iterator std_it = std_map.begin();
	// for (int i = 0; i < v.size(); i++)
	// {
	// 	if (ft_it->first != std_it->first)
	// 	{
	// 		std::cout << "ERORRRRRRNDSUIUCSDUHFUDHS\n";
	// 		exit(1);
	// 	}
	// 	else
	// 	{
	// 		std::cout << "TOUT JUSTE!!!!!!!!!!" << std::endl;
	// 	}
	// }
	// 1, 2, 3, 4, 5, 7, 13, 20,37,40,99,98,45,44,28,29,87,67,19,95,18,22,38,77,42 9
	// ft::map<int, int> map2;
	// map2.insert(ft::pair<int, int>(1, 42));
	// map2.insert(ft::pair<int, int>(2, 42));
	// map2.insert(ft::pair<int, int>(3, 42));
	// map2.insert(ft::pair<int, int>(4, 42));
	// map2.insert(ft::pair<int, int>(5, 42));
	// map2.insert(ft::pair<int, int>(7, 42));
	// map2.insert(ft::pair<int, int>(13, 42));
	// map2.insert(ft::pair<int, int>(20, 42));
	// map2.insert(ft::pair<int, int>(37, 42));
	// map2.insert(ft::pair<int, int>(40, 42));
	// map2.insert(ft::pair<int, int>(99, 42));
	// ft::map<int, int>::iterator begin = map2.begin();
	// begin++;
	// begin++;
	// begin++;
	// map2.insert(begin, ft::pair<int, int>(9, 42));
	// map2.erase(7);
	// map2.erase(4);
	// std::cout << std::distance(map2.begin(), map2.end());
	// ft::map<int, int> map3(map2);
	// ft::map<int, int> map4(map3.begin(), map3.end());
	// a();
	// printf("%p %p\n", &*map2.begin(), &*map2.end());
	// map2.insert(ft::pair<int, int>(1, 42));
	// printf("%p %p\n", &*map2.begin(), &*map2.end());
	// map2.insert(ft::pair<int, int>(2, 42));
	// printf("%p %p\n", &*++map2.begin(), &*map2.end());
	// map2.insert(ft::pair<int, int>(3, 42));
	// printf("%p %p\n", &*++map2.begin(), &*map2.end());
	// ft::map<int, int>::const_iterator it2 = map2.begin();
	// printf("map2->%p\n", &*(map2.insert(ft::pair<int, int>(3, 42)).first));
	return 0;
}
