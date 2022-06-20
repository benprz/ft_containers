#ifndef MAP_TREE_HPP
# define MAP_TREE_HPP

#include <memory>
#include <utility>
#include <iostream>

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
			class _node
			{
				public:
					value_type	pair_value;
					_node		*parent;
					_node		*left_child;
					_node		*right_child;

				_node(key_type key, mapped_type value) : pair_value(key, value), parent(NULL), left_child(NULL), right_child(NULL) {}

			};
		private:


			typedef typename Allocator::template rebind<_node>::other	allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;

			allocator_type	_alloc;
			pointer			_root;
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
				_size = 0;
			}
			void deallocate_node(pointer& node)
			{
				if (node)
				{
					deallocate_node(node->left_child);
					deallocate_node(node->right_child);
					_alloc.deallocate(node, 1);
					node = NULL;
				}
			}
			void insert_node(key_type key, mapped_type value)
			{
				pointer new_node = _alloc.allocate(1);
				_alloc.construct(new_node, key, value);
				if (!_root)
					_root = new_node;
				else
				{
					pointer node = _root;
					while (node->left_child || node->right_child)
					{
						if (node->left_child && key < node->pair_value.first)
							node = node->left_child;
						else if (node->right_child)
							node = node->right_child;
					}
					if (key < node->pair_value.first)
						node->left_child = new_node;
					else
						node->right_child = new_node;
				}
			}
			pointer search_node(key_type key)
			{
				pointer current_node = _root;
				while (current_node->left_child || current_node->right_child)
				{
					if (key == current_node->pair_value.first)
						return current_node;
					else if (key < current_node->pair_value.first)
						current_node = current_node->left_child;
					else
						current_node = current_node->right_child;
				}
				return NULL;
			}
			void delete_node(key_type key)
			{
				pointer n = search_node(key);
				if (n)
				{
					_alloc.deallocate(n, 1);
				}
			}
			void compute_node_height(pointer node, size_type& height)
			{
				if (node)
				{
					compute_node_height(node->left_child, height);
					compute_node_height(node->right_child, height);
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