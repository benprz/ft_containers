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
	ft::map_tree<int, int> tree;

	tree.insert_node(5, 100);
	tree.insert_node(4, 99);
	tree.insert_node(3, 98);
	// tree.insert_node(2, 97);
	// tree.insert_node(7, 96);
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