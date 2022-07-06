#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include <utility>

#include "map_tree.hpp"
#include "iterator.hpp"

namespace ft
{
	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	> class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef std::pair<const Key, T>							value_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::bidirectional_iterator<value_type>			iterator;
			typedef ft::bidirectional_iterator<const value_type>	const_iterator;

		private:
			ft::map_tree<key_type, mapped_type>	_container;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {};
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
			map (const map& x);
			~map() {};
			reference operator= (const map& x);
			allocator_type get_allocator() const { return _container._node_alloc; };

			//----------
			// Iterators |
			//----------
			iterator begin() { return iterator(_container.getBegin()); }
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			// reverse_iterator rbegin();
			// const_reverse_iterator rbegin() const;
			// reverse_iterator rend();
			// const_reverse_iterator rend() const;

			//---------
			// Capacity |
			//---------
			bool empty() const;
			size_type size() const;
			size_type max_size() const;

			//---------------
			// Element access |
			//---------------
			mapped_type& operator[] (const key_type& k);

			//----------
			// Modifiers |
			//----------
			void insert(key_type key, mapped_type data)
			{
				_container.insert_node(key, data);
			}
			//std::pair<iterator,bool> insert (const value_type& val);
			//iterator insert (iterator position, const value_type& val);
			//template <class InputIterator>
			//void insert (InputIterator first, InputIterator last);
			//void erase (iterator position);
			size_type erase (const key_type& k);
			//void erase (iterator first, iterator last);
			void swap (map& x);
			void clear();

			//-------------
			// Observations |
			//-------------
			key_compare key_comp() const;

			//-----------
			// Operations |
			//-----------
			//iterator find (const key_type& k);
			//const_iterator find (const key_type& k) const;
			size_type count (const key_type& k) const;
			//iterator lower_bound (const key_type& k);
			//const_iterator lower_bound (const key_type& k) const;
			//iterator upper_bound (const key_type& k);
			//const_iterator upper_bound (const key_type& k) const;
			//pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			//pair<iterator,iterator> equal_range (const key_type& k);
	};
}

#endif