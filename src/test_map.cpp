#include <map>
#include "map.hpp"

#include <iterator>
#include <iostream>
#include <iterator>
#include <memory>

#include <typeinfo>
#include <string>
#include <string_view>
#include <type_traits>
#include <algorithm>

int main()
{
	ft::map<int, int> map;

	map.insert(3, 99);
	map.insert(2, 98);
	map.insert(1, 97);
	ft::map<int, int>::iterator it = map.begin();
	++it;

	std::map<int, int> std_map;
	std_map.insert(std::pair<int, int>(-1, 99));
	std_map.insert(std::pair<int, int>(3, 99));
	std_map.insert(std::pair<int, int>(2, 98));
	std_map.insert(std::pair<int, int>(1, 97));
	std_map.insert(std::pair<int, int>(7, 96));
	std_map.insert(std::pair<int, int>(-42, 95));
	std_map.insert(std::pair<int, int>(10, 94));
	std::map<int, int>::iterator std_it = std_map.begin();
	std::cout << (*std_it).second << std::endl;
	// tree.insert_node(1, 95);
	// tree.insert_node(10, 94);
	// tree.insert_node(-1, 93);
	// tree.insert_node(-10, 92);
	// tree.insert_node(3, 91);
	/*
	std::cout << tree.compute_tree_height() <<  " " << tree.compute_tree_factor() << std::endl;
	*/
	return 0;
}