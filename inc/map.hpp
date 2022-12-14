#ifndef MAP_HPP
# define MAP_HPP

#include <iterator>
#include <memory>
#include <utility>

#include "map_tree.hpp"
#include "iterator.hpp"
#include "utils.hpp"

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
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef pair<const Key, T>									value_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef Compare												key_compare;
			typedef Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename ft::map_tree<key_type, mapped_type, key_compare, allocator_type>	tree;
			typedef typename tree::iterator								iterator;
			typedef typename tree::const_iterator						const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					key_compare comp;
					value_compare(key_compare c) : comp(c) {}
				public:
					bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
			};

		private:
			tree _container;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _container(comp, alloc) {}
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _container(comp, alloc) { insert(first, last); }
			map (const map& x) { insert(x.begin(), x.end()); }
			~map() {};
			map& operator= (const map& x)
			{
				if (&x == this)
					return *this;
				clear();
				insert(x.begin(), x.end());
				return *this;
			}
			allocator_type get_allocator() const { return _container._node_alloc; };

			//----------
			// Iterators |
			//----------
			iterator begin() { return iterator(_container.begin()); }
			const_iterator begin() const { return const_iterator(_container.begin()); }
			iterator end() { return iterator(_container.end()); }
			const_iterator end() const { return const_iterator(_container.end()); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

			//---------
			// Capacity |
			//---------
			bool empty() const { return begin() == end(); }
			size_type size() const { return _container.getSize(); }
			size_type max_size() const { return _container.max_size(); }

			//---------------
			// Element access |
			//---------------
			mapped_type& operator[] (const key_type& k)
			{
				iterator it = _container.search_node(k);
				if (it == end())
					it = _container.insert_node(k, mapped_type());
				return it->second;
			};

			//----------
			// Modifiers |
			//----------
			pair<iterator,bool> insert (const value_type& val)
			{
				size_type siz = size();
				iterator it = _container.insert_node(val.first, val.second);
				if (siz == size())
					return pair<iterator, bool>(it, false);
				return pair<iterator, bool>(it, true);
			}
			iterator insert (iterator position, const value_type& val) { return _container.insert_node(position, val.first, val.second); }
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
					_container.insert_node(*(first++));
			}
			void erase (iterator position) { _container.erase_node(*position); };
			size_type erase (const key_type& k) { return _container.erase_node(k); }
			void erase (iterator first, iterator last)
			{
				while (first != last)
					_container.erase_node(*(first++));
			};
			void swap (map& x) { _container.swap(x._container); }
			void clear() { _container.clear(); }

			//-------------
			// Observations |
			//-------------
			key_compare key_comp() const { return _container.getComp(); }
			value_compare value_comp() const { return key_comp(); }

			//-----------
			// Operations |
			//-----------
			iterator find (const key_type& k) { return iterator(_container.search_node(k)); }
			const_iterator find (const key_type& k) const { return const_iterator(_container.search_node(k)); }
			size_type count (const key_type& k) const { return _container.count(k); }
			iterator lower_bound (const key_type& k) { return iterator(_container.lower_bound(k)); }
			const_iterator lower_bound (const key_type& k) const { return const_iterator(_container.lower_bound(k)); }
			iterator upper_bound (const key_type& k) { return iterator(_container.upper_bound(k)); }
			const_iterator upper_bound (const key_type& k) const { return const_iterator(_container.upper_bound(k)); }
			pair<iterator,iterator> equal_range (const key_type& k) { return pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }
	};
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		if (lhs.size() == rhs.size())
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		return false;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::map<Key,Compare,Alloc>& lhs, ft::map<Key,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}
}

#endif