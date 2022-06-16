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
				value_type	pair;
				node		*parent;
				node		*left_child;
				node		*right_child;
		};

		allocator_type	_alloc;
		node*			_root;
		size_type		_size;

	public:
		map_tree() : _root(NULL), _size(0){}
		~map_tree(){}
		void insert_node(key_type key, mapped_type value)
		{
			node* new_node = _alloc(1);
			new_node->pair.first = key;
			new_node->pair.second = value;
			if (!root)
				root = new_node;
			else
			{
				node* current_node = root;
				while (current_node->left_child || current_node->right_child)
				{
					if (key < current_node->pair.first)
						current_node = current_node->left_child
				}
			}
		}
		void search_node();
		void delete_node();
};

#endif