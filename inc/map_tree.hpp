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
	template <typename T>
	class _node_tree
	{
		public:
			typedef _node_tree<T>* node_pointer;
			typedef T value_type;
			typedef std::size_t	size_type;

			T data;
			node_pointer end;
			node_pointer parent;
			node_pointer left;
			node_pointer right;

			_node_tree() : data(0,0), parent(NULL), left(NULL), right(NULL) {}
			_node_tree(T data, node_pointer end, node_pointer parent = NULL) : data(data), end(end), parent(parent), left(NULL), right(NULL) {}
			node_pointer get_previous_node() const
			{
				node_pointer node = (node_pointer)this;
				if (left)
				{
					node = left;
					while (right)
						node = right;
				}
				else if (parent && parent->right == node)
					node = parent;
				return node;
			}
			node_pointer get_next_node() const
			{
				node_pointer node = (node_pointer)this;
				if (right)
				{
					node = right;
					////printf("%d/%d self=%p end=%p parent=%p left=%p right=%p\n", data.first, data.second, (node_pointer)this, end, parent, left, right);
					////printf("node->right: %d/%d self=%p end=%p parent=%p left=%p right=%p\n", node->data.first, node->data.second, node, node->end, node->parent, node->left, node->right);
					while (node->left)
						node = node->left;
				}
				else if (parent && parent->left == node)
				{
					node = parent;
					////printf("%d/%d self=%p end=%p parent=%p left=%p right=%p\n", data.first, data.second, (node_pointer)this, end, parent, left, right);
					////printf("node->parent: %d/%d self=%p end=%p parent=%p left=%p right=%p\n", node->data.first, node->data.second, node, node->end, node->parent, node->left, node->right);
				}
				else if (parent && parent->right == node && parent->parent && parent->parent->left == parent)
				{
					node = parent->parent;
					////printf("%d/%d self=%p end=%p parent=%p left=%p right=%p\n", data.first, data.second, (node_pointer)this, end, parent, left, right);
					////printf("node->parent->parent: %d/%d self=%p end=%p parent=%p left=%p right=%p\n", node->data.first, node->data.second, node, node->end, node->parent, node->left, node->right);
				}
				else
				{
					node = end;
					////printf("%d/%d->+END+\n", data.first, data.second);
				}
				return node;
			}
	};

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<pair<const Key, T> > >
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
			typedef typename Allocator::template rebind<_node_tree<value_type> >::other node_allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef _node_tree<value_type> node;
			typedef _node_tree<value_type>* node_pointer;
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
			map_tree() : _root(NULL), _size(0) {}
			map_tree(const key_compare& comp, const allocator_type& alloc) : _comp(comp), _alloc(alloc), _root(NULL), _size(0) {}
			~map_tree()
			{
				print_tree();
				deallocate_tree(_root);
			}

			size_type getSize() const { return _size; }
			node_pointer getRoot() const { return _root; }
			key_compare getComp() const { return _comp; }
			node_pointer begin() const
			{
				if (!_root)
					return (node_pointer)&_end_stack_node_object;

				node_pointer node = _root;
				if (node)
				{
					while (node->left)
						node = node->left;
				}
				return node;
			}
			node_pointer end() const { return (node_pointer)&_end_stack_node_object; }

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
			iterator insert_node(const value_type& data) { return insert_node(data.first, data.second); }
			iterator insert_node(key_type key, mapped_type value)
			{
				node_pointer node = search_node(key);
				if (node != &_end_stack_node_object)
					return iterator(node);

				//std::cout << key << "-----------------------------------\n";
				node_pointer new_node = _node_alloc.allocate(1);
				if (!_root)
				{
					_node_alloc.construct(new_node, value_type(key, value), &_end_stack_node_object);
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
					_node_alloc.construct(new_node, value_type(key, value), &_end_stack_node_object, node);
					if (key < node->data.first)
						node->left = new_node;
					else
						node->right = new_node;
					keep_node_balance(node);
				}
				_size++;
				return iterator(new_node);
			}
			iterator insert_node(iterator position, key_type key, mapped_type value)
			{
				node_pointer node = search_node(key);
				if (node != &_end_stack_node_object)
					return iterator(node);

				node_pointer new_node = _node_alloc.allocate(1);
				if (!_root)
				{
					_node_alloc.construct(new_node, value_type(key, value), &_end_stack_node_object);
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
					_node_alloc.construct(new_node, value_type(key, value), &_end_stack_node_object, node);
					if (key < node->data.first)
						node->left = new_node;
					else
						node->right = new_node;
					keep_node_balance(node);
				}
				_size++;
				return iterator(new_node);
			}
			node_pointer search_node(const key_type key)
			{
				node_pointer node = lower_bound(key);
				if (node->data.first == key)
					return node;
				return &_end_stack_node_object;
			}
			node_pointer lower_bound(const key_type& k)
			{
				node_pointer node = begin();
				while (node != &_end_stack_node_object && _comp(node->data.first, k))
					node = node->get_next_node();
				return node;
			}
			node_pointer upper_bound(const key_type& k)
			{
				node_pointer node = begin();
				while (node != &_end_stack_node_object && !_comp(node->data.first, k))
					node = node->get_next_node();
				return node;
			}
			mapped_type& get_node(const key_type key)
			{
				return search_node(key)->data.second;
			}
			void erase_node(value_type &value) { erase_node(value.first); }
			bool erase_node(key_type key)
			{
				node_pointer node = search_node(key);
				if (node != &_end_stack_node_object)
				{
					//std::cout << "ERASE(" << node->data.first << ") value=" << node->data.second << std::endl;
					//printf("#parent=%d left=%d right=%d\n", node->parent->data.first, node->left->data.first, node->right->data.first);
					node_pointer successor = node->get_next_node();
					if (successor != &_end_stack_node_object)
					{
						//std::cout << "successor != end()" << std::endl;
						if (node->parent)
						{
							if (node->parent->right == node)
								node->parent->right = successor;
							else
								node->parent->left = successor;
						}
						if (successor->parent != node && (successor->right || successor->left))
						{
							if (successor == successor->parent->left)
								successor->parent->left = successor->right;
							else
								successor->parent->right = successor->left;
						}
						else if (successor->parent != node)
							successor->parent->left = NULL;
						if (node->left)
						{
							successor->left = node->left;
							node->left->parent = successor;
						}
						if (node->right)
						{
							successor->right = node->right;
							node->right->parent = successor;
						}
						successor->parent = node->parent;
						// successor->right = node->right;
						// successor->left = node->left;
						////printf("remove: %d\n", node->data.first);
						_node_alloc.deallocate(node, 1);
					}
					if (_root == node)
						_root = successor == &_end_stack_node_object ? NULL : successor;
					//printf("# successor=%d parent=%p left=%p right=%p\n", successor->data.first, successor->parent, successor->left, successor->right);
					print_tree();
					return 1;
				}
				return 0;
			}
			void rotate_left(node_pointer node) // 1 2 3
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
			void rotate_right(node_pointer node) // 3 2 1
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
			void rotate_left_right(node_pointer node) // 3 1 2
			{
				node_pointer child = node->left;
				node_pointer parent = child->right;
				parent->parent = node->parent;
				node->parent = parent;
				child->parent = parent;
				child->right = NULL;
				node->left = NULL;
				parent->left = child;
				parent->right = node;
				if (_root == node)
					_root = parent;
			}
			/*
			1
					3
				2

	->						->
			1							2
				2					1		3
					3	
			*/
			void rotate_right_left(node_pointer node) // 1 3 2
			{
			}
			void keep_node_balance(node_pointer node)
			{
				//print_tree();
				while (node)
				{
					//std::cout << "keep_node_balance(" << node->data.first << ")" << std::endl;
					int bf = compute_balance_factor(node);
					//std::cout << "bf(" << node->data.first << ")=" << bf << std::endl;
					if (bf == -2 || bf == 2)
					{
						//std::cout << "checking childs\n";
						int lc_bf = compute_balance_factor(node->left);
						int rc_bf = compute_balance_factor(node->right);

						////std::cout << "bf=" << bf << " lc_bf=" << lc_bf << " rc_bf=" << rc_bf << std::endl;
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
			bool is_node_left_in_tree(node_pointer node) { return node->data.first < _root->data.first; }
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
						//std::cout << "kdsjhichuksduic\n";
				int tree_height = compute_tree_height();
						//std::cout << "#kdsjhichuksduic\n";
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