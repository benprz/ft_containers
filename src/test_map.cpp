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

	tree.insert_node(5, 1);
	tree.insert_node(6, 1);
	tree.insert_node(4, 1);
	tree.insert_node(2, 1);
	tree.insert_node(7, 1);
	tree.insert_node(1, 1);
	std::cout << tree.compute_tree_height() << std::endl;
	return 0;
}