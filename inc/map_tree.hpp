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
			node* n = _alloc(1);
			n->pair.first = key;
			n->pair.second = value;
			if (!root)
				root = n;
			else
			{
				node* current_node = root;
				while (current_node->left_child || current_node->right_child)
				{
					if (key < current_node->pair.first)
						current_node = current_node->left_child;
					else
						current_node = current_node->right_child;

				}
				if (key < current_node->pair.first)
					current_node->left_child = n;
				else
					current_node->right_child = n;
			}
		}
		node* search_node(key_type key)
		{
			node* current_node = root;
			while (current_node->left_child || current_node->right_child)
			{
				if (key == current_node->pair.first)
					return current_node;
				else if (key < current_node->pair.first)
					current_node = current_node->left_child;
				else
					current_node = current_node->right_child;
			}
		};
		void delete_node();
};

#endif