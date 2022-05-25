#ifndef MAP_TREE_HPP
# define MAP_TREE_HPP

#include <memory>
#include <utility>

template <typename value_type, typename allocator_type>
class map_tree
{
	private:
		class node
		{
			public:
				value_type	value;
				node		*parent;
				node		*left_child;
				node		*right_child;
		};

		node										*_node;
		//size_type									_size;
		//std::allocator<std::pair<const Key, T> >	_alloc;

	public:
		map_tree();
		~map_tree(){};
		void insert_node();
		void search_node();
		void delete_node();
};

#endif