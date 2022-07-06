#ifndef MAP_TREE_HPP
#define MAP_TREE_HPP

#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>

namespace ft
{
	template <typename T>
	class _node_tree
	{
		public:
			T data;
			_node_tree<T> *parent;
			_node_tree<T> *left;
			_node_tree<T> *right;
			int level;

			_node_tree(T data, _node_tree *parent = NULL) : data(data), parent(parent), level(0), left(NULL), right(NULL)
			{
				if (parent)
					level = parent->level + 1;
			}
	};

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > >
	class map_tree
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::pair<const Key, T> value_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::template rebind<_node_tree<value_type> >::other node_allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef _node_tree<value_type>* node_pointer;

		private:
			allocator_type _alloc;
			node_allocator_type _node_alloc;
			node_pointer _root;
			size_type _size;

		public:
			map_tree() : _root(NULL), _size(0) {}
			~map_tree()
			{
				deallocate_tree(_root);
			}

			node_pointer getRoot() const { return _root; }


			void deallocate_tree(node_pointer &node)
			{
				if (node)
				{
					deallocate_tree(node->left);
					deallocate_tree(node->right);
					_node_alloc.deallocate(node, 1);
					node = NULL;
					_size--;
				}
			}
			void insert_node(key_type key, mapped_type value)
			{
				node_pointer new_node = _node_alloc.allocate(1);
				if (!_root)
				{
					_node_alloc.construct(new_node, value_type(key, value));
					_root = new_node;
				}
				else
				{
					node_pointer node = _root;
					while (node->left || node->right)
					{
						if (node->left && key < node->data.first)
							node = node->left;
						else if (node->right && key > node->data.first)
							node = node->right;
						else
							break;
					}
					_node_alloc.construct(new_node, value_type(key, value), node);
					if (key < node->data.first)
						node->left = new_node;
					else
						node->right = new_node;
					keep_node_balance(node);
				}
			}
			node_pointer search_node(key_type key)
			{
				node_pointer node = _root;
				while (node)
				{
					if (key == node->data.first)
						return node;
					else if (node->left && key < node->data.first)
						node = node->left;
					else if (node->right && key > node->data.first)
						node = node->right;
					else
						break;
				}
				return NULL;
			}
			void delete_node(key_type key)
			{
				node_pointer node = search_node(key);
				if (node)
				{
					std::cout << "key=" << node->data.first << " value=" << node->data.second << std::endl;
					//_node_alloc.deallocate(node, 1);
				}
			}
			void rotate_left(node_pointer node) // 1 2 3
			{
				node_pointer child = node->right;
				child->left = node;
				child->parent = node->parent;
				if (node->parent)
					node->parent->right = child;
				node->right = NULL;
				node->parent = child;
				child->level--;
				node->level++;
				child->right->level--;
				if (_root == node)
					_root = child;
			}
			void rotate_right(node_pointer node) // 3 2 1
			{
				node_pointer child = node->left;
				child->right = node;
				child->parent = node->parent;
				if (node->parent)
					node->parent->left = child;
				node->left = NULL;
				node->parent = child;
				child->level--;
				node->level++;
				child->left->level--;
				if (_root == node)
					_root = child;
			}
			void rotate_left_right(node_pointer node) // 3 1 2
			{
				node_pointer child = node->left;
				node_pointer parent = child->right;
				parent->level = node->level;
				parent->parent = node->parent;
				node->parent = parent;
				child->parent = parent;
				child->right = NULL;
				node->left = NULL;
				node->level++;
				parent->left = child;
				parent->right = node;
				if (_root == node)
					_root = parent;
			}
			void rotate_right_left(node_pointer node) // 1 3 2
			{
				node_pointer child = node->right;
				node_pointer parent = child->left;
				parent->level = node->level;
				parent->parent = node->parent;
				node->parent = parent;
				child->parent = parent;
				child->left = NULL;
				node->right = NULL;
				node->level++;
				parent->right = child;
				parent->left = node;
				if (_root == node)
					_root = parent;
			}
			void keep_node_balance(node_pointer node)
			{
				print_tree();
				while (node)
				{
					int bf = compute_balance_factor(node);
					std::cout << "bf(" << node->data.first << ")=" << bf << std::endl;
					if (bf == -2 || bf == 2)
					{
						int lc_bf = compute_balance_factor(node->left);
						int rc_bf = compute_balance_factor(node->right);

						std::cout << "bf=" << bf << " lc_bf=" << lc_bf << " rc_bf=" << rc_bf << std::endl;
						if (bf == 2 && lc_bf == 1)
						{
							std::cout << "right r" << std::endl;
							rotate_right(node);
						}
						else if (bf == -2 && rc_bf == -1)
						{
							std::cout << "left r" << std::endl;
							rotate_left(node);
						}
						else if (bf == 2 && lc_bf == -1)
						{
							std::cout << "left right rotation" << std::endl;
							rotate_left_right(node);
						}
						else if (bf == -2 && rc_bf == 1)
						{
							std::cout << "right left rotation" << std::endl;
							rotate_right_left(node);
						}
					}
					node = node->parent;
				}
				print_tree();
			}
			void compute_node_height(node_pointer node, size_type &height)
			{
				if (node)
				{
					if (node->level > height)
						height = node->level;
					compute_node_height(node->left, height);
					compute_node_height(node->right, height);
				}
			}
			size_type compute_tree_height()
			{
				size_type height = 0;
				compute_node_height(_root, height);
				return height;
			}
			int compute_tree_factor()
			{
				return compute_balance_factor(_root);
			}
			int compute_balance_factor(node_pointer node)
			{
				if (node)
				{
					size_type left_child_height = node->level;
					size_type right_child_height = node->level;
					compute_node_height(node->left, left_child_height);
					compute_node_height(node->right, right_child_height);
					return (left_child_height - right_child_height);
				}
				return 0;
			}
			bool is_node_left_in_tree(node_pointer node)
			{
				return node->data.first < _root->data.first;
			}
			void print_nodes_line(node_pointer node, size_type height, size_type left_width)
			{
				if (node)
				{
					if (node->level == height)
					{
						if (_root == node)
						{
							// std::cout << std::setw(left_width * 2);
							std::cout << "(" << node->data.first << ")";
						}
						else
						{
							/*
							if (node->parent->left == node)
								std::cout << std::setw(left_width * 2);
							else if (node->parent->right == node)
								std::cout << std::setw(4);
							*/
							std::cout << "(" << node->parent->data.first;
							if (node->parent->left == node)
								std::cout << "<";
							else
								std::cout << ">";
							std::cout << node->data.first << ")";
						}
					}
					else
					{
						print_nodes_line(node->left, height, left_width);
						print_nodes_line(node->right, height, left_width);
					}
				}
			}
			void print_tree()
			{
				std::cout << "--------------TREE:\n";
				size_type left_width = 0;
				node_pointer node = _root;
				while (node)
				{
					node = node->left;
					left_width++;
				}
				size_type tree_height = compute_tree_height();
				for (size_type i = 0; i <= tree_height; i++)
				{
					print_nodes_line(_root, i, left_width--);
					std::cout << std::endl;
				}
				std::cout << "-------------------\n";
			}
	};
}

#endif