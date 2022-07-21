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
#include <list>

#include "../containers_test/srcs/map/common.hpp"
//#define TESTED_NAMESPACE ft

#define T1 float
#define T2 foo<int>
typedef _pair<const T1, T2> T3;

#define N std

int		main(void)
{
	N::map<int, int> map;

	map.insert(N::make_pair(1, 42));
	map.insert(N::make_pair(2, 43));
	map.insert(N::make_pair(3, 44));
	N::map<int, int>::const_iterator it = map.begin();
	N::map<int, int>::iterator it2 = map.begin();
	//it->second = 2;
	//++it;
	++it2;
	if (it != it2)
		std::cout << it->second << std::endl;
	/*
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 + i, i + 1));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::iterator it(mp.begin());
	TESTED_NAMESPACE::map<T1, T2>::const_iterator ite(mp.begin());
	printSize(mp);

	printPair(++ite);
	printPair(ite++);
	printPair(ite++);
	printPair(++ite);

	it->second.m();
	ite->second.m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	(*it).second.m();
	(*ite).second.m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);
*/
	return (0);
}
