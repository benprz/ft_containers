#ifndef MAP_TREE_HPP
# define MAP_TREE_HPP

#include <memory>
#include <utility>

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	> class map_tree
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef std::pair<const Key, T>						value_type;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

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
			~map_tree()
			{
				deallocate_tree();
			}
			void deallocate_tree()
			{
				deallocate_node(_root);
				_root = NULL;
				_size = 0;
			}
			void deallocate_node(node* n)
			{
				while (n)
				{
					if (n->left_child)
						deallocate_node(n->left_child);
					if (n->right_child)
						deallocate_node(n->right_child);
					_alloc.deallocate(n, 1);
				}
			}
			void insert_node(key_type key, mapped_type value)
			{
				node* new_node = _alloc(1);
				new_node->pair.first = key;
				new_node->pair.second = value;
				if (!_root)
					_root = new_node;
				else
				{
					node* n = _root;
					while (n->left_child || n->right_child)
					{
						if (key < n->pair.first)
							n = n->left_child;
						else
							n = n->right_child;

					}
					if (key < n->pair.first)
						n->left_child = n;
					else
						n->right_child = n;
				}
			}
			node* search_node(key_type key)
			{
				node* current_node = _root;
				while (current_node->left_child || current_node->right_child)
				{
					if (key == current_node->pair.first)
						return current_node;
					else if (key < current_node->pair.first)
						current_node = current_node->left_child;
					else
						current_node = current_node->right_child;
				}
				return NULL;
			}
			void delete_node(key_type key)
			{
				node* n = search_node(key);
				if (n)
				{
					_alloc.deallocate(n, 1);
				}
			}
			void compute_node_height(node* n, size_type& height)
			{
				while (n)
				{
					compute_node_height(n->left_child, height);
					compute_node_height(n->right_child, height);
					height++;
				}
			}
			size_type compute_tree_height()
			{
				size_type height = 0;
				compute_node_height(_root, height);
				return height;
			}
			int compute_balance_factor() {}
	};
}

#endif