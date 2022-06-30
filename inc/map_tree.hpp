#ifndef MAP_TREE_HPP
# define MAP_TREE_HPP

#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>

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

		private:
			class _node
			{
				public:
					value_type	pair_value;
					_node*		parent;
					_node*		left_child;
					_node*		right_child;
					int			level;

				_node(key_type key, mapped_type value, _node* parent = NULL) : pair_value(key, value), parent(parent), level(0), left_child(NULL), right_child(NULL) 
				{
					if (parent)
						level = parent->level + 1;
				}
			};
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
				deallocate_tree(_root);
			}
			void deallocate_tree(pointer& node)
			{
				if (node)
				{
					deallocate_tree(node->left_child);
					deallocate_tree(node->right_child);
					_alloc.deallocate(node, 1);
					node = NULL;
					_size--;
				}
			}
			void insert_node(key_type key, mapped_type value)
			{
				pointer new_node = _alloc.allocate(1);
				if (!_root)
				{
					_alloc.construct(new_node, key, value);
					_root = new_node;
				}
				else
				{
					pointer node = _root;
					while (node->left_child || node->right_child)
					{
						if (node->left_child && key < node->pair_value.first)
							node = node->left_child;
						else if (node->right_child && key > node->pair_value.first)
							node = node->right_child;
						else
							break ;
					}
					_alloc.construct(new_node, key, value, node);
					if (key < node->pair_value.first)
						node->left_child = new_node;
					else
						node->right_child = new_node;
					keep_node_balance(node);
				}
			}
			pointer search_node(key_type key)
			{
				pointer node = _root;
				while (node)
				{
					if (key == node->pair_value.first)
						return node;
					else if (node->left_child && key < node->pair_value.first)
						node = node->left_child;
					else if (node->right_child && key > node->pair_value.first)
						node = node->right_child;
					else
						break ;
				}
				return NULL;
			}
			void delete_node(key_type key)
			{
				pointer node = search_node(key);
				if (node)
				{
					std::cout << "key=" << node->pair_value.first << " value=" <<  node->pair_value.second << std::endl;
					//_alloc.deallocate(node, 1);
				}
			}
			void rotate_right(pointer node)
			{
				pointer lc = node->left_child;
				if (node->parent)
					node->parent->left_child = lc;
				lc->right_child = node;
				lc->parent = node->parent;
				node->parent = node->left_child;
				node->left_child = NULL;
				node->level++;
				lc->level--;
				lc->left_child->level--;
				if (_root == node)
					_root = lc;
			}
			void rotate_left(pointer node)
			{
				pointer lc = node->right_child;
				if (node->parent)
					node->parent->right_child = lc;
				lc->left_child = node;
				lc->parent = node->parent;
				node->parent = node->right_child;
				node->right_child = NULL;
				node->level++;
				lc->level--;
				lc->right_child->level--;
				if (_root == node)
					_root = lc;
			}
			pointer rotate_left_right(pointer node)
			{
				pointer n = node;
				pointer nlc = n->left_child;
				pointer nlcrc = nlc->right_child;

				n->left_child= nlcrc->right_child;
				nlc->right_child = nlcrc->left_child;
				nlcrc->right_child = n;
				nlcrc->left_child= nlc; 
				return nlcrc;
			}
			pointer rotate_right_left(pointer node)
			{
				pointer n = node;
				pointer nrc = n->right_child;
				pointer nrclc = nrc->left_child;

				n->right_child = nrclc->left_child;
				nrc->left_child = nrclc->right_child;
				nrclc->left_child = n;
				nrclc->right_child = nrc; 
				return nrclc;
			}
			void keep_node_balance(pointer node)
			{
				print_tree();
				while (node)
				{
					int bf = compute_balance_factor(node);
					std::cout << "bf(" << node->pair_value.first << ")=" << bf << std::endl;
					if (bf == -2 || bf == 2)
					{
						int lc_bf = compute_balance_factor(node->left_child);
						int rc_bf = compute_balance_factor(node->right_child);

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
					}
					node = node->parent;
				}
				print_tree();
			}
			void compute_node_height(pointer node, size_type& height)
			{
				if (node)
				{
					if (node->level > height)
						height = node->level;
					compute_node_height(node->left_child, height);
					compute_node_height(node->right_child, height);
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
			int compute_balance_factor(pointer node)
			{
				if (node)
				{
					size_type left_child_height = node->level;
					size_type right_child_height = node->level;
					compute_node_height(node->left_child, left_child_height);
					compute_node_height(node->right_child, right_child_height);
					return (left_child_height - right_child_height);
				}
				return 0;
			}
			bool is_node_left_in_tree(pointer node)
			{
				return node->pair_value.first < _root->pair_value.first;
			}
			void print_nodes_line(pointer node, size_type height, size_type left_width)
			{
				if (node)
				{
					if (node->level == height)
					{
						if (_root == node)
						{
							//std::cout << std::setw(left_width * 2);
							std::cout << "(" << node->pair_value.first << ")";
						}
						else
						{
							/*
							if (node->parent->left_child == node)
								std::cout << std::setw(left_width * 2);
							else if (node->parent->right_child == node)
								std::cout << std::setw(4);
							*/
							std::cout << "(" << node->parent->pair_value.first;
							if (node->parent->left_child == node)
								std::cout << "<";
							else
								std::cout << ">";
							std::cout << node->pair_value.first << ")";
						}
					}
					else
					{
						print_nodes_line(node->left_child, height, left_width);
						print_nodes_line(node->right_child, height, left_width);
					}
				}
			}
			void print_tree()
			{
				std::cout << "--------------TREE:\n";
				size_type left_width = 0;
				pointer node = _root;
				while (node)
				{
					node = node->left_child;
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