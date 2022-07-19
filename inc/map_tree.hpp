#ifndef MAP_TREE_HPP
#define MAP_TREE_HPP

#include <memory>
#include <utility>
#include <iostream>
#include <iomanip>

#include "iterator.hpp"
#include "pair.hpp"

namespace ft
{
	template <typename Tree, typename T>
	class _node_tree
	{
		public:
			typedef _node_tree<Tree, T>* node_pointer;
			typedef T value_type;
			typedef std::size_t	size_type;

			Tree *tree;
			T data;
			node_pointer parent;
			node_pointer left;
			node_pointer right;

			_node_tree() : data(), parent(NULL), left(NULL), right(NULL) {}
			_node_tree(Tree *tree, T data, node_pointer parent = NULL) : tree(tree), data(data), parent(parent), left(NULL), right(NULL) {}

			node_pointer get_previous_node() const
			{
				node_pointer node = (node_pointer)this;
				if (node == tree->end())
					return tree->rightmost_node();
				if (left)
					return tree->rightmost_node(left);
				else if (parent && parent->right == node)
					return parent;
				else if (parent && parent->left == node)
				{
					while (node)
					{
						if (node->parent && node->parent->data.first < data.first)
							return node->parent;
						node = node->parent;
					}
				}
				return NULL;
			}
			node_pointer get_next_node() const
			{
				node_pointer node = (node_pointer)this;

				if (right)
					return tree->leftmost_node(right);
				else if (parent && parent->left == node)
					return parent;
				else if (parent && parent->right == node)
				{
					while (node)
					{
						if (node->parent && node->parent->data.first > data.first)
							return node->parent;
						node = node->parent;
					}
				}
				return tree->end();
			}
	};

	template <
		class Key,
		class T,
		class Compare,
		class Allocator>
	class map_tree
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<const Key, T> value_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::template rebind<_node_tree<map_tree, value_type> >::other node_allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef _node_tree<map_tree, value_type> node;
			typedef _node_tree<map_tree, value_type>* node_pointer;
			typedef typename ft::bidirectional_iterator<node> iterator;
			typedef typename ft::bidirectional_const_iterator<node> const_iterator;

		private:
			key_compare	_comp;
			allocator_type _alloc;
			node_allocator_type _node_alloc;
			node_pointer _root;
			node _end_stack_node_object;
			size_type _size;

		public:
			map_tree() : _root(NULL), _size(0) { _end_stack_node_object.tree = this; }
			map_tree(const key_compare& comp, const allocator_type& alloc) : _comp(comp), _alloc(alloc), _root(NULL), _size(0) { _end_stack_node_object.tree = this; }
			~map_tree() { clear(); }

			size_type getSize() const { return _size; }
			node_pointer getRoot() { return _root; }
			key_compare getComp() const { return _comp; }
			node_pointer begin() const
			{
				if (!_root)
					return (node_pointer)&_end_stack_node_object;

				return leftmost_node();
			}
			node_pointer end() const { return (node_pointer)&_end_stack_node_object; }
			size_type max_size() const { return _node_alloc.max_size(); }

			void clear() { deallocate_tree(_root); }
			void deallocate_tree(node_pointer &node)
			{
				if (node)
				{
					deallocate_tree(node->left);
					deallocate_tree(node->right);
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					node = NULL;
					_size--;
				}
			}
			iterator insert_node(const value_type& data) { return insert_node(data.first, data.second); }
			iterator insert_node(key_type key, mapped_type value)
			{
				node_pointer node = search_node(key);
				if (node != &_end_stack_node_object)
					return iterator(node);

				node_pointer new_node = _node_alloc.allocate(1);
				if (!_root)
				{
					_node_alloc.construct(new_node, this, value_type(key, value));
					_root = new_node;
				}
				else
				{
					node = _root;
					while (node->left || node->right)
					{
						if (node->left && key < node->data.first)
							node = node->left;
						else if (node->right && key > node->data.first)
							node = node->right;
						else
							break;
					}
					_node_alloc.construct(new_node, this, value_type(key, value), node);
					if (key < node->data.first)
						node->left = new_node;
					else
						node->right = new_node;
					keep_node_balance(node);
				}
				_size++;
				//print_tree();
				return iterator(new_node);
			}
			iterator insert_node(iterator position, key_type key, mapped_type value)
			{
				(void)position;
				return insert_node(key, value);
				/*
				node_pointer node = search_node(key);
				if (node != &_end_stack_node_object)
					return iterator(node);

				node_pointer new_node = _node_alloc.allocate(1);
				if (!_root)
				{
					_node_alloc.construct(new_node, this, value_type(key, value));
					_root = new_node;
				}
				else
				{
					node = position.ptr();
					while (node->left || node->right)
					{
						if (node->left && key < node->data.first)
							node = node->left;
						else if (node->right && key > node->data.first)
							node = node->right;
						else
							break;
					}
					_node_alloc.construct(new_node, this, value_type(key, value), node);
					if (key < node->data.first)
						node->left = new_node;
					else
						node->right = new_node;
					keep_node_balance(node);
				}
				_size++;
				return iterator(new_node);
				*/
			}
			node_pointer search_node(const key_type key)
			{
				node_pointer node = lower_bound(key);
				if (node->data.first == key)
					return node;
				return &_end_stack_node_object;
			}
			const_iterator search_node(const key_type key) const
			{
				node_pointer node = lower_bound(key);
				if (node->data.first == key)
					return const_iterator(node);
				return end();
			}
			node_pointer lower_bound(const key_type& k) const
			{
				node_pointer node = begin();
				while (node != &_end_stack_node_object && _comp(node->data.first, k))
					node = node->get_next_node();
				return node;
			}
			node_pointer upper_bound(const key_type& k) const
			{
				node_pointer node = lower_bound(k);
				node = node->get_next_node();
				return node;
			}
			node_pointer leftmost_node() const { return leftmost_node(_root); }
			node_pointer leftmost_node(node_pointer node) const
			{
				if (node)
				{
					while (node->left)
						node = node->left;
				}
				return node;
			}
			node_pointer rightmost_node() const { return rightmost_node(_root); }
			node_pointer rightmost_node(node_pointer node) const
			{
				if (node)
				{
					while (node->right)
						node = node->right;
				}
				return node;
			}
			size_type count(const key_type &k) const
			{
				if (search_node(k) != end())
					return 1;
				return 0;
			}
			void erase_node(value_type &value) { erase_node(value.first); }
			bool erase_node(key_type key)
			{
				node_pointer node = search_node(key);
				if (node != &_end_stack_node_object)
				{
					//std::cout << "> ERASE(" << key << ") !!!!!!!" << std::endl;
					//print_tree();

					node_pointer successor = node->get_next_node();
					if (!node->left && !node->right && node->parent)
					{
						if (node->parent->right == node)
							node->parent->right = NULL;
						else
							node->parent->left = NULL;
					}
					else if (((node->left && !node->right) || (node->right && !node->left)))
					{
						if (node->left)
						{
							if (node->parent && node->parent->left == node)
								node->parent->left = node->left;
							else if (node->parent && node->parent->right == node)
								node->parent->right = node->left;
							node->left->parent = node->parent;
						}
						else
						{
							if (node->parent && node->parent->left == node)
								node->parent->left = node->right;
							else if (node->parent && node->parent->right == node)
								node->parent->right = node->right;
							node->right->parent = node->parent;
						}
						successor = node->right ? node->right : node->left;
					}
					else if (node->left && node->right)
					{
						if (node->parent)
						{
							if (node->parent->right == node)
								node->parent->right = successor;
							else
								node->parent->left = successor;
						}
						if (successor->parent != node && successor->right)
							successor->parent->left = successor->right;
						else if (successor->parent != node)
							successor->parent->left = NULL;
						if (node->left)
						{
							successor->left = node->left;
							node->left->parent = successor;
						}
						if (node->right && node->right != successor)
						{
							successor->right = node->right;
							node->right->parent = successor;
						}
						successor->parent = node->parent;
					}
					if (_root == node)
					{
						if (!node->left && !node->right)
							_root = NULL;
						else if (node->left || node->right)
								_root = successor;
					}
					_size--;
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					//print_tree();
					//std::cout << "keep balance(" << successor->data.first << ")" << std::endl;
					keep_node_balance(successor);	
					//print_tree();
					return 1;
				}
				return 0;
			}
			void rotate_left(node_pointer node)
			{
				node_pointer child = node->right;

				if (node->parent)
				{
					if (node->parent->left == node)
						node->parent->left = child;
					else
						node->parent->right = child;
				}
				else
					_root = child;

				node->right = child->left;
				if (node->right)
					node->right->parent = node;

				child->parent = node->parent;
				child->left = node;
				node->parent = child;
			}
			void rotate_right(node_pointer node)
			{
				node_pointer child = node->left;

				if (node->parent)
				{
					if (node->parent->right == node)
						node->parent->right = child;
					else
						node->parent->left = child;
				}
				else
					_root = child;

				node->left = child->right;
				if (node->left)
					node->left->parent = node;

				child->parent = node->parent;
				child->right = node;
				node->parent = child;
			}
			void keep_node_balance(node_pointer node)
			{
				//print_tree();
				while (node)
				{
					//std::cout << "keep_node_balance(" << node->data.first << ")" << std::endl;
					int bf = compute_balance_factor(node);
					// std::cout << "bf(" << node->data.first << ")=" << bf << std::endl;
					if (bf == -2 || bf == 2)
					{
						//std::cout << "checking childs\n";
						int lc_bf = compute_balance_factor(node->left);
						int rc_bf = compute_balance_factor(node->right);

						//std::cout << "bf=" << bf << " lc_bf=" << lc_bf << " rc_bf=" << rc_bf << std::endl;
						if (lc_bf == 0 && rc_bf == 0)
						{
							if (node->left && !node->left->left && node->right->right)
								rc_bf = -1;
							else
								lc_bf = -1;
						}
						if (bf == 2 && lc_bf == 1) // 3 2 1
						{
							// std::cout << "right r" << std::endl;
							rotate_right(node);
						}
						else if (bf == -2 && rc_bf == -1) // 1 2 3
						{
							//std::cout << "left r" << std::endl;
							rotate_left(node);
						}
						else if (bf == 2 && lc_bf == -1)
						{
							//std::cout << "left right rotation" << std::endl;
							rotate_left(node->left);
							rotate_right(node);
						}
						else if (bf == -2 && rc_bf == 1)
						{
							//std::cout << "right left rotation" << std::endl;
							rotate_right(node->right);
							rotate_left(node);
						}
					}
					node = node->parent;
				}
				//print_tree();
			}
			int get_node_height(node_pointer node)
			{
				int height = 0;
				node_pointer node2 = _root;
				////std::cout << "get_node_height->" << node->data.first << " root=" << _root->data.first << std::endl;
				while (node2 != node && node2)
				{
					////std::cout << "node2=" << node2->data.first << std::endl;
					if (node->data.first < node2->data.first)
						node2 = node2->left;
					else
						node2 = node2->right;
					height++;
				}
				////std::cout << "height=" << height << std::endl;
				return height;

			}
			void compute_node_height(node_pointer node, int &height)
			{
				if (node)
				{
					////std::cout << "compute_node_height -> " << node->data.first << std::endl;
					int node_height = get_node_height(node);
					compute_node_height(node->left, height);
					compute_node_height(node->right, height);
					if (node_height > height)
						height = node_height;
				}
			}
			int compute_balance_factor(node_pointer node)
			{
				if (node)
				{
					int node_height = get_node_height(node);
					//std::cout << node->data.first << "->height = " << node_height << std::endl;
					int left_height = node_height;
					int right_height = node_height;
					compute_node_height(node->left, left_height);
					compute_node_height(node->right, right_height);
					left_height -= node_height;
					right_height -= node_height;
					//printf("node=%d bf=%d lc=%d rc=%d\n", node->data.first, left_height - right_height, left_height, right_height);
					return (left_height - right_height);
				}
				return 0;
			}
			int compute_tree_height()
			{
				int height = 0;
				compute_node_height(_root, height);
				return height;
			}
			void print_nodes_line(node_pointer node, int height, int left_width)
			{

				if (node)
				{
					if (get_node_height(node) == height)
					{
						if (_root == node)
						{
							std::cout << std::setw(left_width * 2);
							std::cout << "(" << node->data.first << ")";
						}
						else
						{
							std::cout << "(" << node->parent->data.first;
							if (node->parent->left == node)
							{
								std::cout << "<";
							}
							else
							{
								std::cout << ">";
							}
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
				int left_width = 0;
				node_pointer node = _root;
				while (node)
				{
					node = node->left;
					left_width++;
				}
				int tree_height = compute_tree_height();
				for (int i = 0; i <= tree_height; i++)
				{
					print_nodes_line(_root, i, left_width--);
					std::cout << std::endl;
				}
				std::cout << "-------------------\n";
			}
	};
}

#endif